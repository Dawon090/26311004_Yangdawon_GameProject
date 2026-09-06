#pragma once
#include "Player.h"
#include "SceneGameBegin.h"


enum ScreenState
{
	MAINMENU,
	GAMEPLAY,
	GAMEOVER
};

struct TextureList
{
	int mainTexture = -1;
	int backgroundTexture = -1;
	int playerTexture = -1;
};
extern TextureList texture;

class CApplication
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

protected:
	static constexpr int screenWidth = 1280;
	static constexpr int screenHeight = 720;

	SceneGameBegin sceneBegin;

private:
	Player player;
};

