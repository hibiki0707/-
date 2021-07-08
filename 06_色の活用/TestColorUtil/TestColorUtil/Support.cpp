#include "GameCommon.h"
#include "SceneManager.h"
#include "TestScene.h"
#include "DxLib.h"
#include "Support.h"

Support::Support(SceneManager* _manager, TestScene* _scene)
{
	mSceneManager = _manager;
	mTestScene = _scene;
}

void Support::Draw(void)
{
	
	int page = mTestScene->GetPage();
	switch (page)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 7:
		break;
	default:
		break;
	}

	DrawFormatString(
		SCREEN_SIZE_X - 300, SCREEN_SIZE_Y - 50,
		0x000000, "Spaceキーで次の問題に進みます。");

}

void Support::DrawCenterLine(void)
{

	int x1 = 0;
	int x2 = SCREEN_SIZE_X / 2;
	int x3 = SCREEN_SIZE_X;

	int y1 = 0;
	int y2 = SCREEN_SIZE_Y / 2;
	int y3 = SCREEN_SIZE_Y;

	DrawLine(x1, y2, x3, y2, 0x000000);
	DrawLine(x2, y1, x2, y3, 0x000000);

}
