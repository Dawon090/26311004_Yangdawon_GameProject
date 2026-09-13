#include "SceneGamePlay.h"
#include "glc2d.h"
#include "TexturePath.h"
#include "CApplication.h"
#include "Enemy.h"
#include "Player.h"

#include "stdio.h"

SceneGamePlay::SceneGamePlay()
{
	player = new Player();
	enemy = new Slime();
}
SceneGamePlay::~SceneGamePlay()
{
	if (player != nullptr)
		delete player;
	if (enemy != nullptr)
		delete enemy;
}

int SceneGamePlay::Init()
{
	texture.backgroundTexture = g2_TextureLoad(TX_BACKGROUND);
	texture.gaugeTexture = g2_TextureLoad(TX_GAUGE);
	texture.cursorTexture = g2_TextureLoad(TX_CURSOR);

	texture.slimeTexture = g2_TextureLoad(TX_SLIME);
	texture.goblinTexture = g2_TextureLoad(TX_GOBLIN);
	texture.orcTexture = g2_TextureLoad(TX_ORC);
	texture.dragonTexture = g2_TextureLoad(TX_DRAGON);

	return 0;
}
int SceneGamePlay::Update(CApplication& cApp)
{
	//커서이동
	player->CursorMOve();
	
	// 스페이스 입력 받았을 시 공격 로직 시작
	if (InputSpace())
	{
		Battle();
		if (player->Die() || enemy->Die())
		{
			// 씬 전환
			printf("%d\n", cApp.GetScene());
			cApp.ChangeScene(GAMEOVER);
			printf("씬변경, %d\n", cApp.GetScene());
			return 0;
		}
	}

	//전투
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
	
	//printf("%d |", texture.backgroundTexture);

	return 0;
}
int SceneGamePlay::Destroy()
{
	g2_TextureRelease(texture.backgroundTexture);
	g2_TextureRelease(texture.gaugeTexture);
	g2_TextureRelease(texture.cursorTexture);
	g2_TextureRelease(texture.slimeTexture);

	return 0;
}

bool SceneGamePlay::InputSpace()
{
	const KEYCODE* pKeyboard = g2_GetKeyboard();
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
	player->Attack(s_cursorX, *enemy);
	printf("적의 남은 체력 : %d\n", enemy->GetHp());

	//적이 죽었을 경우
	if (enemy->Die())
	{
		//적제거
		//다음 라운드 적 생성
		//플레이어 수치 초기화
		printf("적을 처치했다");
		
		return;
	}

	enemy->Attack(*player);
	printf("플레이어의 남은 체력 : %d\n", player->GetHP());

	//플레이어가 죽었을 경우
	if (player->Die())
	{
		printf("플레이어가 사망했습니다");
		return;
	}


}
