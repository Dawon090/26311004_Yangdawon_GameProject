#pragma once
#include "Player.h"
#include "Enemy.h"

class CApplication;

class SceneGamePlay
{
public:
	SceneGamePlay();
	~SceneGamePlay();

	int Init();
	int Update(CApplication& cApp);
	int Render();
	int Destroy();

	bool InputSpace();

private:
	void Battle();

	Player* player = nullptr;
	Enemy* enemy = nullptr;
	float s_cursorX{}; //플레이어가 공격 시 커서 위치 저장
	VEC2 enemyPos{};

};
