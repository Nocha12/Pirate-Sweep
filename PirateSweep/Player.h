#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Weapon.h"
#include "Ground.h"
#include "Timer.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	Vec2 left;
	Vec2 right;
	Vec2 bottom;
	Vec2 top;
	
	Ground *ground;

	Animation *body;
	Animation *jumpBody;
	Animation *flyBody;
	Animation *foot;
	Animation *jumpFoot;
	Sprite *stopFoot;
	Sprite *flyFoot;
	Sprite *LevelUpText;
	Weapon *weapon;
	Timer hitTimer;

	int jumpNum;
	int grenadeCount;
	int bulletCount;
	int level;
	float exp;
	float currentExp;
	float shootTimer;
	float shootDelay;
	float flyTimer;
	float hp;
	float currentHp;
	bool isShoot;
	bool isGrenade;
	bool isMove;
	bool isFlying;
	bool getGround;
	bool isRight;
	bool isDeath;
	bool isLevelUp;
	float power;

	void update(float dt) override;
	void OnHit();
};

