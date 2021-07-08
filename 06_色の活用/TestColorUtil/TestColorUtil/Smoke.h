#pragma once
#include "Vector2.h"

class Smoke
{

public:

	Smoke(int img, Vector2 pos);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	int mImage;

	Vector2 mPos;

};

