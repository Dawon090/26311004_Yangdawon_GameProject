#include "Player.h"
#include "glc2d.h"

void Player::TakeDamage(int damage)
{

}

void Player::Attack()
{

}

void Player::Move()
{

}

VEC2 Player::GetPosition() const
{
	return playerPosition;
}

int Player::GetHP() const
{
	return hp;
}

int Player::GetAttack() const
{
	return attack;
}

int Player::GetScore() const
{
	return score;
}

float Player::GetDefence() const
{
	return defence;
}

bool Player::IsDead() const
{
	return hp <= 0;
}