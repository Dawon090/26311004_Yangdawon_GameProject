#include "CApplication.h"
#include "glc2d.h"
#include "Player.h"

TextureList texture;
extern CApplication g_app;

int AppUpdate()
{
	return g_app.Update();
}

int AppRender()
{
	return g_app.Render();
}

int CApplication::Init()
{
	g2_InitSdk();

	g2_SetFrameMove(AppUpdate);
	g2_SetRender(AppRender);

	g2_CreateWin(100, 25, screenWidth, screenHeight, "ENDURE");

	g2_SetStateShow(true);
	g2_SetCursorShow(true);

	sceneBegin.Init();

	return 0;
}

int CApplication::Update()
{
	sceneBegin.Update();

	return 0;
}

int CApplication::Render()
{
	sceneBegin.Render();

	return 0;
}

int CApplication::Destroy()
{
	sceneBegin.Destroy();

	g2_DestroyWin();
	return 0;
}
