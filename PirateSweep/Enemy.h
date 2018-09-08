#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Timer.h"
#include "Ground.h"

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	Vec2 left;
	Vec2 right;
	Vec2 bottom;

	Animation *animation;
	Animation *attackAni;
	Timer blinkTimer;
	Timer hitTimer;

	float hp;
	float shootTimer;
	float shootDelay;
	float playerDistance;
	float speed;
	bool isShoot;
	bool isRight;
	bool isBlink;
	bool canMoveLeft;
	bool canMoveRight;
	bool isFollowing;

	void update(float dt);
	void Blink();
	void OnHit();
	void SetPivot();
};

