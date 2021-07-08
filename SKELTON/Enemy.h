#pragma once
#include"Player.h"

namespace Battle {
	class Player;

	class Enemy
	{
		Player* player_;
		int life_ = 100;
	public:
		void OnDamage(int damage);	// ダメージを食らう
		void Attack();	// 敵にダメージを与える
	};
}