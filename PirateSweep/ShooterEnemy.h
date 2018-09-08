#pragma once
#include "Enemy.h"

class ShooterEnemy : public Enemy
{
public:
	ShooterEnemy();
	~ShooterEnemy();

	void update(float dt) override;
};


