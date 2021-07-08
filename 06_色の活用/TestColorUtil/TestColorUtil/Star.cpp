#include "DxLib.h"
#include "Star.h"

void Star::Init(void)
{
	mImage = LoadGraph("Image/Star.png");
	mPos = { 50, 100 };
	mRot = 0;
	mSizeRate = 0.5f;
}

void Star::Update(void)
{
}

void Star::Draw(void)
{
	mRot += 1;
	int tmpRot = mRot / SPEED_SLOW_ROT;
	if (tmpRot > 360)
	{
		mRot = 0;
	}
	DrawRotaGraph(
		mPos.x, mPos.y, 
		mSizeRate,
		tmpRot,
		mImage, 
		true);
}

void Star::Release(void)
{
	DeleteGraph(mImage);
}

Vector2 Star::GetPos(void)
{
	return mPos;
}

void Star::SetPos(Vector2 pos)
{
	mPos = pos;
}

void Star::SetSizeRate(float rate)
{
	mSizeRate = rate;
}
