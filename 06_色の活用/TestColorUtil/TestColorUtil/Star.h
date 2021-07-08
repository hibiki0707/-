#pragma once
#include "Vector2.h"
class Star
{
public:

	static constexpr int SPEED_SLOW_ROT = 4;

	// 初期処理
	void Init(void);

	// 更新ステップ
	void Update(void);

	// 描画処理
	void Draw(void);

	// 解放処理
	void Release(void);

	Vector2 GetPos(void);
	void SetPos(Vector2 pos);
	void SetSizeRate(float rate);

private:

	int mImage;

	Vector2 mPos;

	int mRot;

	float mSizeRate;

};

