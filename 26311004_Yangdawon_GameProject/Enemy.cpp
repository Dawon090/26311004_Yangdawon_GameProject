#include "Enemy.h"
#include "glc2d.h"
#include "Player.h"

#include "stdio.h";

Enemy::~Enemy()
{
}

int Enemy::GetAttack() const
{
	return attack;
}

int Enemy::GetHp() const
{
	return hp;
}

int Enemy::GetMaxHp() const
{
	return maxHp;
}

VEC2 Enemy::GetPos() const
{
	return spawnPos;
}

void Enemy::Attack(Player& target)
{
	target.TakeDamage(attack);
	printf("플레이어에게 %d만큼 피해가함 \n", attack);
}

void Enemy::Damage(int damage)
{
	hp -= damage;
	if (hp <= 0)
		hp = 0;
}

bool Enemy::Die()
{
	if (hp <= 0)
		return isDead = true;
	return isDead = false;
}

Slime::Slime()
{
	hp = 10;
	maxHp = 10;
	attack = 1;
}
