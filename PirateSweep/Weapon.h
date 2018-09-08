#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Enum.h"

class Weapon : public Entity
{
public:
	Weapon();
	~Weapon();

	Sprite *gun;
	Sprite *bazooka;
	Sprite *machineGun;

	Vec2 gunPos;
	Vec2 bazookaPos;
	Vec2 machineGunPos;

	Vec2 gunCenter;
	Vec2 bazookaCenter;
	Vec2 machineGunCenter;

	Vec2 currentPos;

	WeaponType weaponType;

	void ChangeWeapon(WeaponType weaponType);
};