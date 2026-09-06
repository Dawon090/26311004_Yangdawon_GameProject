#include "SceneGameBegin.h"
#include "glc2d.h"
#include "TexturePath.h"
#include "CApplication.h"

int SceneGameBegin::Init()
{
	texture.mainTexture = g2_TextureLoad(TX_MAIN);

	return 0;
}

int SceneGameBegin::Update()
{
	return 0;
}

int SceneGameBegin::Render()
{
	g2_Draw2D(texture.mainTexture, nullptr);

	return 0;
}

int SceneGameBegin::Destroy()
{
	g2_TextureRelease(texture.mainTexture);

	return 0;
}