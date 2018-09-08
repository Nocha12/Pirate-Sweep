#pragma once
#include "Enemy.h"
#include "GameManager.h"
#include "GameScene.h"
#include "World.h"

class Boss2 : public Enemy
{
public:
	Boss2();
	~Boss2();

	bool isCannonBroken;
	int count;

	void update(float dt);
};

