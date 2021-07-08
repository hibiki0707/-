#include "DxLib.h"
#include "JumpMan.h"

void JumpMan::Init(void)
{

	LoadDivGraph(
		"Image/JumpMan.png", 
		12, 3, 4, 
		32, 32, &mImage[0][0]);

	mDir = DIR::RIGHT;
	mAnmCnt = 0;
	mPos = { DEFAULT_POS_X, DEFAULT_POS_Y };
	mJumpPow = 0;
	mRot = 0;
	mState = STATE::RUN01;

}

void JumpMan::Update(void)
{

	switch (mState)
	{
	case JumpMan::RUN01:
		mPos.x += SPEED_RUN;
		if (mPos.x > 450)
		{
			ChangeState(STATE::JUMP);
			return;
		}
		break;
	case JumpMan::JUMP:

		mPos.x += SPEED_JUMP;
		mJumpPow--;
		mPos.y -= mJumpPow;
		mRot += 1;
		mCntAfterImage++;

		if (mCntAfterImage > CNT_AFTER_IMAGE)
		{
			mCntAfterImage = 0;

			if (mAfterImagePos.size() < 10)
			{
				mAfterImagePos.push_back(mPos);
			}
			else
			{
				mAfterImagePos.erase(mAfterImagePos.begin());
			}

		}

		if (mPos.y > DEFAULT_POS_Y)
		{
			mJumpPow = 0;
			mPos.y = DEFAULT_POS_Y;
			ChangeState(STATE::RUN02);
			return;
		}
		break;
	case JumpMan::RUN02:
		mPos.x += SPEED_RUN;
		if (mPos.x > 1000)
		{
			ChangeState(STATE::RUN01);
			return;
		}
		break;
	}

}

void JumpMan::Draw(void)
{

	mAnmCnt += 1;
	int anm = (mAnmCnt / SPEED_ANM) % 4;
	if (anm == 3)
	{
		anm = 1;
	}

	switch (mState)
	{
	case JumpMan::RUN01:
	case JumpMan::RUN02:
		DrawRotaGraph(
			mPos.x, mPos.y,
			2.0f, 0.0f,
			mImage[(int)mDir][anm], true
		);
		break;
	case JumpMan::JUMP:

		DrawJump();
		break;

	}

}

void JumpMan::DrawJump(void)
{

	// 残像の表示
	Vector2 pos;
	int size = mAfterImagePos.size();
	for (int i = 0; i < size; i++)
	{

		pos = mAfterImagePos[i];

		DrawRotaGraph(
			pos.x, pos.y,
			2.0f, mRot / 2,
			mImage[(int)mDir][1], true
		);

	}

	// ブレンドモードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 実体の表示
	DrawRotaGraph(
		mPos.x, mPos.y,
		2.0f, mRot / 2,
		mImage[(int)mDir][1], true
	);

}

void JumpMan::Release(void)
{

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			DeleteGraph(mImage[y][x]);
		}
	}

}

void JumpMan::ChangeState(STATE state)
{

	mState = state;
	switch (state)
	{
	case JumpMan::RUN01:
		mPos.x = DEFAULT_POS_X;
		mPos.y = DEFAULT_POS_Y;
		break;
	case JumpMan::JUMP:
		mJumpPow = POW_JUMP;
		mCntAfterImage = 0;
		mAfterImagePos.clear();
		break;
	case JumpMan::RUN02:
		break;
	}

}
