#include "DxLib.h"
#include "SceneManager.h"
#include "StarDust.h"

StarDust::StarDust(SceneManager* manager, Vector2 basePos)
{

	mSceneManager = manager;
	mBasePos = basePos;

}

void StarDust::Init(void)
{
}

void StarDust::Update(void)
{

	if (!mIsVisible)
	{
		return;
	}

	mStep += mSceneManager->GetDeltaTime();

	if (mStep > mTime)
	{
		mIsVisible = false;
	}
	else
	{
		mMovePow.y--;
		mPos.x += mMovePow.x;
		mPos.y -= mMovePow.y;
	}

}

void StarDust::Draw(void)
{

	if (!mIsVisible)
	{
		return;
	}

	Vector2 pos = { mBasePos.x + mPos.x, mBasePos.y + mPos.y };

	float x1 = 0.0f;
	float x2 = 0.0f;
	float y1 = 0.0f;
	float y2 = 0.0f;

	// άδ―‚Μ•`‰ζ
	float angle = 0.0f;
	float mvAngle = 360.0f / 5.0f * 2.0f;
	while (!(angle > 360.0f * 2.0f))
	{

		x2 = DEFAULT_RADIS * sin(angle / 180.0f * DX_PI_F);
		y2 = DEFAULT_RADIS * cos(angle / 180.0f * DX_PI_F);

		if (angle > 0.0f)
		{
			DrawLine(
				pos.x + x1, pos.y - y1,
				pos.x + x2, pos.y - y2,
				mColor, 1
			);
		}

		x1 = x2;
		y1 = y2;
		angle += mvAngle;

	}

}

void StarDust::Release(void)
{
}

void StarDust::Random(void)
{

	int r = GetRand(255);
	int g = GetRand(255);
	int b = GetRand(255);
	mColor = GetColor(r, g, b);

	mPos = { 0, 0 };

	mMovePow.x = 5 - (1 + GetRand(9));
	mMovePow.y = 10 + GetRand(12);

	mTime = 2.0f + (float)GetRand(3);
	mStep = 0.0f;

	mRadis = DEFAULT_RADIS;

	mIsVisible = true;

}

Vector2 StarDust::GetPos(void)
{
	Vector2 ret = mBasePos;
	ret.x += mPos.x;
	ret.y += mPos.y;
	return ret;
}
