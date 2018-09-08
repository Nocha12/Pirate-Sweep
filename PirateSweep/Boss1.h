#pragma once
#include "Enemy.h"

class Boss1 : public Enemy
{
public:
	Boss1();
	~Boss1();
	
	bool isCannonBroken;
	int count;

	void update(float dt);
};

