#include "DxLib.h"
#include "Smoke.h"

Smoke::Smoke(int img, Vector2 pos)
{
	mImage = img;
	mPos = pos;
}

void Smoke::Init(void)
{
}

void Smoke::Update(void)
{
}

void Smoke::Draw(void)
{
	DrawRotaGraph(
		mPos.x, mPos.y,
		0.5f, 0.0f,
		mImage, true);
}

void Smoke::Release(void)
{
	DeleteGraph(mImage);
}
