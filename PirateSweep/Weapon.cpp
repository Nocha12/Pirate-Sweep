 #include "DXUT.h"
#include "Weapon.h"

Weapon::Weapon() : weaponType(GUN), gunPos(60, 60), gunCenter(4, 12), bazookaPos(-10, 15), bazookaCenter(80, 61), machineGunPos(20, 45), machineGunCenter(46, 24), currentPos(gunPos)
{
	rotationCenter = gunCenter;
	scaleCenter = gunCenter;

	gun = new Sprite("image/player/weapon/basegun.tga");
	rect = gun->rect;
	addChild(gun);

	bazooka = new Sprite("image/player/weapon/bzu.tga");
	addChild(bazooka);
	bazooka->visible = false;

	machineGun = new Sprite("image/player/weapon/mgun.tga");
	addChild(machineGun);
	machineGun->visible = false;
}

Weapon::~Weapon()
{
}

void Weapon::ChangeWeapon(WeaponType weaponType)
{
	this->weaponType = weaponType;

	if (weaponType == GUN)
	{
		bazooka->visible = false;
		machineGun->visible = false;

		gun->visible = true;
		rect = gun->rect;

		rotationCenter = gunCenter;
		scaleCenter = gunCenter - Vec2(20, 0);

		currentPos = gunPos;
	}
	else if (weaponType == BAZOOKA)
	{
		gun->visible = false;
		machineGun->visible = false;

		bazooka->visible = true;
		rect = bazooka->rect;

		rotationCenter = bazookaCenter;
		scaleCenter = bazookaCenter;
		
		currentPos = bazookaPos;
	}
	else if (weaponType == MACHINEGUN)
	{
		gun->visible = false;
		bazooka->visible = false;

		machineGun->visible = true;
		rect = machineGun->rect;
		rotationCenter = machineGunCenter;
		scaleCenter = machineGunCenter;

		currentPos = machineGunPos;
	}
}
