#pragma once

class CApplication;

class SceneGameBegin
{
public:
	int Init();
	int Update(CApplication& cApp);
	int Render();
	int Destroy();

	bool InputStart();

private:
	static constexpr int startLeft = 580;
	static constexpr int startTop = 400;
	static constexpr int startRight = 730;
	static constexpr int startBottom = 500;

};

