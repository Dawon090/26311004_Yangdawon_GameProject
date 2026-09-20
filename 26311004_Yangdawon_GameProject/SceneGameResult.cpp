#include "SceneGameResult.h"
#include "glc2d.h"
#include "CApplication.h"
#include "TexturePath.h"
#include <stdio.h>

int SceneGameResult::Init()
{
	resultText = g2_FontCreate("±¼¸²", 70, 0);
	exitText = g2_FontCreate("±¼¸²", 50, 0);
	replayText = g2_FontCreate("±¼¸²", 50, 0);

	texture.loseSound = g2_SoundLoad(VFX_LOSE);
	texture.winSound = g2_SoundLoad(VFX_WIN);
	_isPlayed = false;
	return 0;
}

int SceneGameResult::Update(CApplication& cApp)
{
	if (!_isPlayed)
	{
		if (_isWin)
			g2_SoundPlay(texture.winSound);
		else
			g2_SoundPlay(texture.loseSound);
		_isPlayed = true;
	}

	if (cApp.InputMouse(exitPos) == TRUE)
	{
		cApp.Destroy();
	}
	else if (cApp.InputMouse(replayPos) == TRUE)
	{
		g2_SoundPlay(texture.startSound);
		if (!g2_SoundIsPlaying(texture.startSound))
		{
			// È¿°úÀ½ Á¾·á ÈÄ ¾À ÀüÈ¯
			printf("%d\n", cApp.GetScene());
			cApp.ChangeScene(GAMEPLAY);
			printf("¾Àº¯°æ, %d\n", cApp.GetScene());
		}
	}

	return 0;
}

int SceneGameResult::Render()
{
	
	g2_FontDrawText(resultText, resultPos, 0xFFFFFFFF, _isWin ? "WIN" : "LOSE");
	g2_FontDrawText(exitText, exitPos, 0xFFFFFFFF, "EXIT");
	g2_FontDrawText(replayText, replayPos, 0xFFFFFFFF, "REPLAY");

	return 0;
}

int SceneGameResult::Destroy()
{
	return 0;
}

void SceneGameResult::SetOutcome(bool outcome)
{
	_isWin = outcome;
	return;
}

