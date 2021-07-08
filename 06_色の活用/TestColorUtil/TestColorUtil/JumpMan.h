#pragma once
#include <vector>
#include "GameCommon.h"
#include "Vector2.h"
class JumpMan
{

public:

	static constexpr int DEFAULT_POS_X = 100;
	static constexpr int DEFAULT_POS_Y = 350;

	static constexpr int SPEED_ANM = 10;
	static constexpr int SPEED_RUN = 3;
	static constexpr int SPEED_JUMP = 5;

	static constexpr int POW_JUMP = 16;

	static constexpr int CNT_AFTER_IMAGE = 5;

	enum STATE {
		RUN01,
		JUMP,
		RUN02
	};

	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawJump(void);
	void Release(void);

private:

	int mImage[4][3];

	STATE mState;

	Vector2 mPos;
	DIR mDir;

	int mAnmCnt;
	int mJumpPow;
	int mRot;

	std::vector<Vector2> mAfterImagePos;
	int mCntAfterImage;

	void ChangeState(STATE state);

};

