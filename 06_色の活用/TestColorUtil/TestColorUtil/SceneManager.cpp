#include "DxLib.h"
#include "Fader.h"
#include "TestScene.h"
#include "Support.h"
#include "SceneManager.h"

void SceneManager::Init()
{

	mSceneID = SCENE_ID::TITLE;
	mWaitSceneID = SCENE_ID::NONE;

	mFader = new Fader();
	mFader->Init();

	mScene = new TestScene(this);
	mScene->Init();

	auto ts = dynamic_cast<TestScene*>(mScene);
	mSupport = new Support(this, ts);

	mIsSceneChanging = false;

	// デルタタイム
	mTickCount = GetTickCount64();

}

void SceneManager::Update(void)
{

	if (mScene == nullptr)
	{
		return;
	}

	float tickCount = GetTickCount64();
	// ミリ秒 →　秒
	mDeltaTime = (tickCount - mTickCount) / 1000.0f;
	mTickCount = tickCount;

	mFader->Update();
	if (mIsSceneChanging)
	{
		Fader::FADE_STATE fState = mFader->GetState();
		switch (fState)
		{
		case Fader::FADE_STATE::FADE_IN:
			if (mFader->IsEnd())
			{
				mFader->SetFade(Fader::FADE_STATE::NONE);
				mIsSceneChanging = false;
			}
			break;
		case Fader::FADE_STATE::FADE_OUT:
			if (mFader->IsEnd())
			{
				DoChangeScene();
				mFader->SetFade(Fader::FADE_STATE::FADE_IN);
			}
			break;
		default:
			break;
		}
	}
	else 
	{
		mScene->Update();
	}

	SetFontSize(16);
	mScene->Draw();

	SetFontSize(16);
	mSupport->Draw();

}

void SceneManager::Release(void)
{
	mScene->Release();
}

void SceneManager::ChangeScene(SCENE_ID nextId, bool isFading)
{
	mWaitSceneID = nextId;

	if (isFading)
	{
		mFader->SetFade(Fader::FADE_STATE::FADE_OUT);
		mIsSceneChanging = true;
	}
	else 
	{
		DoChangeScene();
	}

}

float SceneManager::GetDeltaTime(void)
{
	return mDeltaTime;
}

void SceneManager::DoChangeScene(void)
{
	mScene->Release();

	mSceneID = mWaitSceneID;

	switch (mSceneID)
	{
	case SCENE_ID::TITLE:
		mScene = new TestScene(this);
		break;
	default:
		break;
	}

	mScene->Init();

	mWaitSceneID = SCENE_ID::NONE;

}



