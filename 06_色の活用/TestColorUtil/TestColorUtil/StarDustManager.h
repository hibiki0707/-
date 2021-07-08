#pragma once
#include <vector>
#include "Vector2.h"
class SceneManager;
class StarDust;
class Sphere;

class StarDustManager
{

public:

	StarDustManager(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(Sphere* sphere);
	void Release(void);

	void Create(Vector2 pos, float loopTime, int num);

private:

	SceneManager* mSceneManager;

	std::vector<StarDust*> mStarDusts;

	Vector2 mPos;

	float mLoopTime;
	float mStep;

};
