#pragma once
#include "Enemy.h"

class BoomEnemy : public Enemy
{
public:
	BoomEnemy();
	~BoomEnemy();

	bool isChangeAttackAni;

	void update(float dt);
};

