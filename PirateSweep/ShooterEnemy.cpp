#include "DXUT.h"
#include "ShooterEnemy.h"
#include "GameManager.h"
#include "GameScene.h"
#include "World.h"
#include "Bullet.h"

ShooterEnemy::ShooterEnemy()
{
	if (gameManager.stage == 1)
	{
		addChild(animation = new Animation("image/mob/mob2/walk", 13, 13, true));
		addChild(attackAni = new Animation("image/mob/mob2/attack", 13, 13, true));
	}
	if (gameManager.stage == 2)
	{
		addChild(animation = new Animation("image/mob/mob4/walk", 13, 13, true));
		addChild(attackAni = new Animation("image/mob/mob4/attack", 13, 13, true));
	}
	
	rect = animation->rect;
	SetPivot();
	animation->scaleCenter = animation->center();
	attackAni->scaleCenter = animation->center();
	attackAni->visible = false;
	hp = 100;
	shootDelay = 1; 
	shootTimer = 0;
	speed = 200;
}

ShooterEnemy::~ShooterEnemy()
{
}

void ShooterEnemy::update(float dt)
{
	Enemy::update(dt);

	shootTimer += dt;

	if (!gameManager.isBoss)
	{
		if ((playerDistance > 550 && (playerDistance < 1000 || isFollowing)) && !isBlink)
		{
			isFollowing = true;

			if (isRight && canMoveRight)
				pos.x += speed * dt;
			else if (canMoveLeft)
				pos.x -= speed * dt;

			animation->visible = true;
			attackAni->visible = false;
		}
		else if (playerDistance <= 550)
		{
			animation->visible = false;
			attackAni->visible = true;

			GameScene *scene = (GameScene*)world.currentScene;

			if (shootTimer >= shootDelay && !isBlink)
			{
				shootTimer = 0;

				Bullet *b;

				if (gameManager.stage == 1)
					b = new Bullet(MOB2, 500, 10, 200, D3DXToRadian(250));
				else if (gameManager.stage == 2)
					b = new Bullet(MOB4, 500, 30, 200, D3DXToRadian(250));

				b->isPlayerBullet = false;
				b->pos = center();

				if (!isRight)
				{
					b->angle = b->rotation = D3DXToRadian(180);
				}
				else
				{
					b->sprite->scale.x *= -1;
					b->angle = b->rotation = D3DXToRadian(0);
				}
				b->isFallable = false;
				scene->bulletList.push_back(b);
				scene->addChild(b);
			}
		}
	}
}