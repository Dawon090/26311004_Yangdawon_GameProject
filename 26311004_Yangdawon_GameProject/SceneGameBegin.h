#pragma once
#include "glc2d.h"
class CApplication;

class SceneGameBegin
{
public:
	int Init();
	int Update(CApplication& cApp);
	int Render();
	int Destroy();

private:
	static constexpr int startLeft = 580;
	static constexpr int startTop = 400;
	static constexpr int startRight = 730;
	static constexpr int startBottom = 500;

	int startButton = -1;
	RECT startPos{ 580,400,730,460 };

};

