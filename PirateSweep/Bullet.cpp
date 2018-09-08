#include "DXUT.h"
#include "Bullet.h"
#include "Define.h"

Bullet::Bullet(WeaponType weaponType, float speed, float damage, float range, float angle) : weaponType(weaponType), speed(speed), damage(damage), range(range), isPlayerBullet(false), angle(angle)
{
	if (weaponType == GUN)
	{
		sprite = new Sprite("image/bullet/player/base_bullet.png");
		isFallable = false;
	} else if (weaponType == BAZOOKA)
	{
		sprite = new Sprite("image/bullet/player/bzu_bullet.tga");
		isFallable = true;
	} else if (weaponType == MACHINEGUN)
	{
		sprite = new Sprite("image/bullet/player/mgun_bullet.tga");
		isFallable = false;
	} else if (weaponType == GRENADE)
	{
		sprite = new Sprite("image/bullet/player/bomb.tga");
		isFallable = true;
	} else if (weaponType == MOB1)
	{
		sprite = new Sprite("image/bullet/mob/mob/mob1.tga");
		isFallable = true;
	} else if (weaponType == MOB2)
	{
		sprite = new Sprite("image/bullet/mob/mob/mob2.tga");
		isFallable = false;
	} else if (weaponType == MOB3)
	{
		sprite = new Sprite("image/bullet/mob/mob/mob3.tga");
		isFallable = true;
	} else if (weaponType == MOB4)
	{
		sprite = new Sprite("image/bullet/mob/mob/mob4.tga");
		isFallable = false;
	}
	else if (weaponType == BOSS1_BOOM1)
	{
		sprite = new Sprite("image/bullet/mob/boss/boss1_2.tga");
		isFallable = true;
	}
	else if (weaponType == BOSS1_BOOM2)
	{
		sprite = new Sprite("image/bullet/mob/boss/boss1_1.tga");
		isFallable = true;
	}
	else if (weaponType == BOSS1_GUN)
	{
		sprite = new Sprite("image/bullet/mob/boss/boss1_3.tga");
		isFallable = false;
	}
	else if (weaponType == BOSS2_BOOM1)
	{
		sprite = new Sprite("image/bullet/mob/boss/boss2_2.tga");
		isFallable = true;
	}
	else if (weaponType == BOSS2_BOOM2)
	{
		sprite = new Sprite("image/bullet/mob/boss/boss2_1.tga");
		isFallable = true;
	}
	else if (weaponType == BOSS2_GUN)
	{
		sprite = new Sprite("image/bullet/mob/boss/boss2_3.tga");
		isFallable = false;
	}


	rect = sprite->rect;
	addChild(sprite);

	rotationCenter = center();
	scaleCenter = center();
	gravity = 0;
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt)
{	
	Entity::update(dt);

	velocity = Vec2(cosf(angle), sinf(angle)) * speed * dt;

	if (isFallable)
	{
		pos.x += velocity.x;
		pos.y += velocity.y + gravity;
		
		gravity += 9.8 * dt + 50 * dt;

		rotation = atan2(velocity.y + gravity, velocity.x);
	}
	else 
		pos += velocity;
}
