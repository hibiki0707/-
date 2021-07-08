#include "DxLib.h"
#include "GameCommon.h"
#include "Enemy.h"

void Enemy::Init(void)
{
	mImage = LoadGraph("Image/Enemy.png");
	mPos = {SCREEN_SIZE_X / 2, (SCREEN_SIZE_Y / 2) - 50};
}

void Enemy::Update(void)
{
}

void Enemy::Draw(void)
{
	DrawRotaGraph(
		mPos.x, mPos.y, 
		2.0f, 0.0f, 
		mImage, true);
}

void Enemy::Release(void)
{
	DeleteGraph(mImage);
}
