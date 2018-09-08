#pragma once
#include "Entity.h"
#include "Enum.h"
#include "Sprite.h"

class Bullet : public Entity
{
public:
	Bullet(WeaponType weaponType, float speed, float damage, float range, float angle);
	~Bullet();

	Sprite *sprite;

	WeaponType weaponType;
	float speed;
	float damage;
	float range;
	float angle;
	Vec2 velocity;
	bool isPlayerBullet;

	void update(float dt) override;
};

