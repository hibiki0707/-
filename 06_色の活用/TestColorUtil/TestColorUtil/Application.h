#pragma once
#include "SceneManager.h"

class Application
{
private:		//メンバ変数
	//インスタンスの生成
	SceneManager mSceneManager;

public:			//メンバ関数
	bool Init(void);
	void Run(void);
	bool Release(void);
};