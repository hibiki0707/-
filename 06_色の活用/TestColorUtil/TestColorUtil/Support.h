#pragma once
#include "TestScene.h"
class SceneManager;
class TestScene;

class Support
{
public:
	Support(SceneManager* _manager, TestScene* _scene);
	void Draw(void);
private:
	SceneManager* mSceneManager;
	TestScene* mTestScene;

	void DrawCenterLine(void);
};

