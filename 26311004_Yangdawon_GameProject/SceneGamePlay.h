#pragma once
#include "Player.h"
#include "Enemy.h"

class CApplication;

class SceneGamePlay
{
public:
	int Init();
	int Update(CApplication& cApp);
	int Render();
	int Destroy();

	bool InputSpace();

private:
	void Battle();
	void TextureLoad();
	void TextureRelease();

	Player* player = nullptr;
	Enemy* enemy = nullptr;
	float s_cursorX{}; //플레이어가 공격 시 커서 위치 저장
	VEC2 enemyPos{};

	bool _isWin = false;
	int hpBar = -1;
	RECT playerHp{10,10,230,60};
	RECT enemyHp{ 550,230,750,330 };

	int attackFont = -1;
	RECT attackPos{ 440,540,840,590 };
	RECT damagePos{ 720,320,820,365 };

	int escButton = -1;
	const KEYCODE* pKeyboard = g2_GetKeyboard();
	//게임종료, 다시시작, 마저하기
	RECT gameExitPos{ 570,350,750,400 };
	RECT gameReplayPos{ 570,290,750,340 };
	bool _isInputEsc = false;
};
