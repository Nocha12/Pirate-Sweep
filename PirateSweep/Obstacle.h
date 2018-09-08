#pragma once
#include "Entity.h"
#include "Enum.h"
#include "Sprite.h"

class Obstacle : public Entity
{
public:
	Obstacle(ObstacleType obstacleType);
	~Obstacle();

	Sprite *sprite;
	float hp;

	ObstacleType obstacleType;

	void update(float dt);
};

