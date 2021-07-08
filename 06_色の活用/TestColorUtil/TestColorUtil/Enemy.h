#pragma once
#include "Vector2.h"

class Enemy
{

public:

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	int mImage;

	Vector2 mPos;

};

