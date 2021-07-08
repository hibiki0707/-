#pragma once
#include <string>
#include "Vector2.h"

class Unit
{
public:

	Unit(int hp, std::string name, Vector2 pos);
	int GetHp(void);
	std::string GetName(void);
	Vector2 GetPos(void);

private:

	int mHp;
	std::string mName;

	Vector2 mPos;

};

