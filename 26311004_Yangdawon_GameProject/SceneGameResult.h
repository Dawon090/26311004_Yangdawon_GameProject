#pragma once
#include "glc2d.h"

class CApplication;

enum RESULT
{
	NONE,
	LOSE,
	WIN
};

class SceneGameResult
{
public:
	int Init();
	int Update(CApplication& cApp);
	int Render();
	int Destroy();

	void SetOutcome(bool outcome);

	
private:
	RESULT result = NONE;
	bool _isWin = false;

	int resultText = -1;
	RECT resultPos{ 570,230,750,300 };
	bool _isPlayed = false;

	int exitText = -1;
	int replayText = -1;
	RECT exitPos{ 590,405,720,455 };
	RECT replayPos{ 550,350,730,400 };
};

