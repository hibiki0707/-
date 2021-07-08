#include "Unit.h"

Unit::Unit(int hp, std::string name, Vector2 pos)
{
	mHp = hp;
	mName = name;
	mPos = pos;
}

int Unit::GetHp(void)
{
	return mHp;
}

std::string Unit::GetName(void)
{
	return mName;
}

Vector2 Unit::GetPos(void)
{
	return mPos;
}
