#include "SceneGameBegin.h"
#include "glc2d.h"
#include "TexturePath.h"
#include "CApplication.h"

#include "stdio.h"

int SceneGameBegin::Init()
{
	texture.mainTexture = g2_TextureLoad(TX_MAIN);
	return 0;
}

int SceneGameBegin::Update(CApplication& cApp)
{
	// 마우스 입력 확인
	if (InputStart() ==TRUE)
	{
		// 씬 전환
		printf("%d\n", cApp.GetScene());
		cApp.ChangeScene(GAMEPLAY);
		printf("씬변경, %d\n", cApp.GetScene());
		return 0;
	}

	return 0;
}

int SceneGameBegin::Render()
{
	RECT startPos{ startLeft,startTop,startRight,startBottom };
	g2_Draw2D(texture.mainTexture, nullptr);

	int startButton = g2_FontCreate("굴림", 60, 0);
	g2_FontDrawText(startButton, startPos, 0xFFFFFFFF, "Start");

	return 0;
}

int SceneGameBegin::Destroy()
{
	g2_TextureRelease(texture.mainTexture);

	return 0;
}

bool SceneGameBegin::InputStart()
{
	//마우스위치 받고 그 위치가 스타트 버튼 안이라면 true
	if(g2_GetMouseEvent(0) == EINPUT_DOWN)
	{
		int mouseX = g2_GetMouseX();
		int mouseY = g2_GetMouseY();

		if (mouseX >= startLeft && mouseX <= startRight && mouseY >= startTop && mouseY <= startBottom)
		{
			return TRUE;
		}
	}
	return FALSE;
}