#pragma once
#include "Vector2.h"
class SceneManager;

class StarDust
{

public:

	static constexpr int DEFAULT_RADIS = 14;

	StarDust(SceneManager* manager, Vector2 basePos);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void Random(void);

	Vector2 GetPos(void);

private:

	SceneManager* mSceneManager;

	bool mIsVisible;

	Vector2 mBasePos;
	Vector2 mPos;
	Vector2 mMovePow;
	
	float mTime;
	float mStep;

	float mRot;
	int mColor;
	int mRadis;

};

