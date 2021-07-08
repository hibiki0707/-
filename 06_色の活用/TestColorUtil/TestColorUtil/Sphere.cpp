#include "DxLib.h"
#include "GameCommon.h"
#include "Sphere.h"

void Sphere::Init(void)
{
	mColor = GetColor(0, 0, 0);
}

void Sphere::Update(void)
{
}

void Sphere::Draw(void)
{

	DrawCircle(
		mPos.x, mPos.y,
		mSize,
		mColor, true
	);

}

void Sphere::Release(void)
{
}

void Sphere::SetSize(int size)
{
	mSize = size;
}

Vector2 Sphere::GetPos(void)
{
	return mPos;
}

void Sphere::SetPos(Vector2 pos)
{
	mPos = pos;
}

void Sphere::SetColor(int color)
{
	mColor = color;
}

int Sphere::Lerp(int start, int end, float t)
{

	// ê¸å`ï‚ä‘
	int ret = start;
	ret += t * (end - start);
	return ret;

}

bool Sphere::InRange(Vector2 pos)
{

	int diffX = pos.x - mPos.x;
	int diffY = pos.y - mPos.y;

	int diff = abs(diffX) + abs(diffY);

	if (diff <= mSize)
	{
		return true;
	}

	return false;

}
