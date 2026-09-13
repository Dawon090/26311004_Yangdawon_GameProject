#pragma once

class CApplication;
class SceneGamePlay;

class SceneGameResult
{
public:
	int Init();
	int Update(CApplication& cApp);
	int Render();
	int Destroy();
};

