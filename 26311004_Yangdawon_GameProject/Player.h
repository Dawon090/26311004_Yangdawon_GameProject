#pragma once
#include "glc2d.h"

class Player
{
public:
	void TakeDamage(int damage);
	void Attack();
	void Move();

	VEC2 GetPosition() const;
	int GetHP() const;
	int GetAttack() const;
	int GetScore() const;
	float GetDefence() const;
	bool IsDead() const;

private:
	VEC2 playerPosition{ 640.0f, 360.0f };
	int hp = 100;
	int attack = 20;
	int score = 0;
	float attackSpeed = 0.5f;
	float moveSpeed = 2.0f;
	float defence = 0.0f;
};

