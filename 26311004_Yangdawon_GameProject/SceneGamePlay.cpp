#include "SceneGamePlay.h"
#include "glc2d.h"
#include "TexturePath.h"
#include "CApplication.h"
#include "Enemy.h"
#include "Player.h"

#include "stdio.h"


int SceneGamePlay::Init()
{
	player = new Player();
	enemy = new Slime();
	pKeyboard = g2_GetKeyboard();
	printf("생성됨");
	TextureLoad();

	return 0;
}
int SceneGamePlay::Update(CApplication& cApp)
{
	// ESC
	if (pKeyboard[VK_ESCAPE] == EINPUT_DOWN)
	{
		_isInputEsc = !_isInputEsc;
	}

	if (_isInputEsc)
	{
		if(g2_GetMouseEvent(0) == EINPUT_DOWN)
			printf("Mouse: %d, %d \n", g2_GetMouseX(), g2_GetMouseY());
		if (cApp.InputMouse(gameReplayPos) == TRUE)
		{
			printf("재시작 선택\n");
			g2_SoundPlay(texture.startSound);
			if (!g2_SoundIsPlaying(texture.startSound))
			{
				printf("효과음 종료, 씬 전환 시도\n");
				// 효과음 종료 후 씬 전환
				Destroy();
				Init();
				_isInputEsc = false;
			}
		}
		else if (cApp.InputMouse(gameExitPos) == TRUE)
		{
			printf("게임종료 선택");
			cApp.Destroy();
			return 0;
		}

		return 0;
	}



	if (!g2_SoundIsPlaying(texture.battleSound))
		g2_SoundPlay(texture.battleSound);
	//커서이동
	player->CursorMOve();
	
	// 스페이스 입력 받았을 시 공격 로직 시작
	if (InputSpace()&& !g2_SoundIsPlaying(texture.attackSound))
	{
		Battle();
		if (player->Die() || enemy->Die())
		{
			cApp.Outcome(_isWin);
			// 씬 전환
			printf("%d\n", cApp.GetScene());
			cApp.ChangeScene(GAMEOVER);
			printf("씬변경, %d\n", cApp.GetScene());
			return 0;
		}
	}

	//전투
	//

	

	return 0;
}
int SceneGamePlay::Render()
{
	g2_Draw2D(texture.backgroundTexture, NULL);
	g2_Draw2D(texture.gaugeTexture, NULL, &player->gaugePosition); //이름, 이미지사용, 생성위치

	g2_Draw2D(texture.cursorTexture, NULL, &player->cursorPosition);

	//조건따른 몬스터 그리기
	// . . .
	enemyPos = enemy->GetPos();
	g2_Draw2D(texture.slimeTexture, NULL, &enemyPos);

	//hp바 표시
	g2_FontDrawText(hpBar, playerHp, 0xFFFFFFFF, "HP : %d", player->GetHP());
	g2_FontDrawText(hpBar, enemyHp, 0xFFFFFFFF, "%d / %d", enemy->GetHp(), enemy->GetMaxHp());
	
	// 나가기
	if (_isInputEsc)
	{		
		//검은 창
		g2_Draw2D(texture.escwindowTexture, NULL, &escScreen);
		//다시시작
		g2_FontDrawText(escButton, gameReplayPos, 0xFFFFFFFF, "다시 하기");
		//게임 종료
		g2_FontDrawText(escButton, gameExitPos, 0xFFFFFFFF, "게임 종료");
	}

	return 0;
}
int SceneGamePlay::Destroy()
{
	g2_SoundStop(texture.battleSound);
	TextureRelease();

	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	if (enemy != nullptr)
	{
		delete enemy;
		enemy = nullptr;
	}

	return 0;
}

bool SceneGamePlay::InputSpace()
{
	if (pKeyboard[VK_SPACE] == EINPUT_DOWN)
	{
		printf("키보드 입력");
		// 커서 위치 저장
		s_cursorX = player->cursorPosition.x;
		return TRUE;
	}
	return FALSE;
}
void SceneGamePlay::Battle()
{
	//공격사운드 재생 및 판정결과출력
	g2_SoundPlay(texture.attackSound);
	player->Attack(s_cursorX, *enemy);
	printf("적의 남은 체력 : %d\n", enemy->GetHp());
	
	//적이 죽었을 경우
	if (enemy->Die())
	{
		//적제거
		
		//다음 라운드 적 생성
		//플레이어 수치 초기화
		printf("적을 처치했다");

		//보스를 죽일시
		_isWin = true;
		return;
	}

	//피격 사운드 재생 및 HP바 색깔 빨간색으로	
	enemy->Attack(*player);
	printf("플레이어의 남은 체력 : %d\n", player->GetHP());

	//플레이어가 죽었을 경우
	if (player->Die())
	{
		printf("플레이어가 사망했습니다");
		_isWin = false;
		return;
	}


}
void SceneGamePlay::TextureLoad()
{
	//그림
	texture.backgroundTexture = g2_TextureLoad(TX_BACKGROUND);
	texture.gaugeTexture = g2_TextureLoad(TX_GAUGE);
	texture.cursorTexture = g2_TextureLoad(TX_CURSOR);
	texture.escwindowTexture = g2_TextureLoad(TX_ESC);

	texture.slimeTexture = g2_TextureLoad(TX_SLIME);
	texture.goblinTexture = g2_TextureLoad(TX_GOBLIN);
	texture.orcTexture = g2_TextureLoad(TX_ORC);
	texture.dragonTexture = g2_TextureLoad(TX_DRAGON);

	//문자열
	hpBar = g2_FontCreate("굴림", 50, 0);
	attackFont = g2_FontCreate("굴림", 70, 1);
	escButton = g2_FontCreate("굴림", 50, 0);

	//사운드
	texture.startSound = g2_SoundLoad(VFX_START);
	texture.battleSound = g2_SoundLoad(VFX_BGM);
	texture.attackSound = g2_SoundLoad(VFX_ATTACK);
	texture.damageSound = g2_SoundLoad(VFX_TAKEDAMAGE);
}
void SceneGamePlay::TextureRelease()
{
	g2_TextureRelease(texture.backgroundTexture);
	g2_TextureRelease(texture.gaugeTexture);
	g2_TextureRelease(texture.cursorTexture);
	g2_TextureRelease(texture.escwindowTexture);

	g2_TextureRelease(texture.slimeTexture);
	g2_TextureRelease(texture.goblinTexture);
	g2_TextureRelease(texture.orcTexture);
	g2_TextureRelease(texture.dragonTexture);

	g2_SoundRelease(texture.startSound);
	g2_SoundRelease(texture.battleSound);
	g2_SoundRelease(texture.attackSound);
	g2_SoundRelease(texture.damageSound);
}