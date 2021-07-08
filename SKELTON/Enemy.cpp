#include "Enemy.h"
#include"Player.h"

using namespace Battle;

void Enemy::OnDamage(int damage){
	life_ -= damage;	// ダメージを食らう
}

void Enemy::Attack(){
	player_->OnDamage(10);	// プレイヤーにダメージを与える
}
