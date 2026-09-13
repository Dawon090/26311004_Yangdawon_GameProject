#pragma once
#include "glc2d.h"

class Player;

class Enemy
{
protected:
	int attack{};
	int hp{};
	int maxHp{};
	VEC2 spawnPos = { 512.0f,232.0f };
	bool isDead = false;

public:
	virtual ~Enemy();
	int GetAttack() const;
	int GetHp() const;
	int GetMaxHp() const;
	VEC2 GetPos() const;

	void Attack(Player& target);
	void Damage(int damage);
	bool Die();

};

class Slime : public Enemy
{
public:
	Slime();
};


