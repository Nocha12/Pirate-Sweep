#include "DXUT.h"
#include "BoomEnemy.h"
#include "Bullet.h"
#include "World.h"
#include "GameScene.h"
#include "GameManager.h"

BoomEnemy::BoomEnemy() : isChangeAttackAni(false)
{
	if (gameManager.stage == 1)
	{
		addChild(animation = new Animation("image/mob/mob1/walk", 19, 19, true));
		addChild(attackAni = new Animation("image/mob/mob1/attack", 17, 17, true));
	}
	if (gameManager.stage == 2)
	{
		addChild(animation = new Animation("image/mob/mob3/walk", 19, 19, true));
		addChild(attackAni = new Animation("image/mob/mob3/attack", 17, 17, true));
	}
	rect = animation->rect;
	SetPivot();
	animation->scaleCenter = animation->center();
	attackAni->scaleCenter = animation->center();
	attackAni->visible = false;
	hp = 200;
	shootDelay = 1.05f;
	shootTimer = 0;
	speed = 300;
}

BoomEnemy::~BoomEnemy()
{
}

void BoomEnemy::update(float dt)
{
	Enemy::update(dt);

	if (!gameManager.isBoss)
	{
		if ((playerDistance > 450 && (playerDistance < 1000 || isFollowing)) && !isBlink)
		{
			isFollowing = true;
			shootTimer = 0;
			if (isRight && canMoveRight)
				pos.x += speed * dt;
			else if (canMoveLeft)
				pos.x -= speed * dt;

			isChangeAttackAni = false;
			animation->visible = true;
			attackAni->visible = false;
		}
		else if (playerDistance <= 450)
		{
			shootTimer += dt;

			if (!isChangeAttackAni) // АјАн
			{
				isChangeAttackAni = true;
				animation->visible = false;
				attackAni->visible = true;
				attackAni->currentFrame = 0;
			}

			if (shootTimer >= shootDelay && !isBlink)
			{
				shootTimer = 0;
				GameScene *scene = (GameScene*)world.currentScene;

				Bullet *b;

				if (gameManager.stage == 1)
					b = new Bullet(MOB1, 1200, 15, 200, D3DXToRadian(250));
				else if (gameManager.stage == 2)
					b = new Bullet(MOB3, 1200, 50, 200, D3DXToRadian(250));

				if (!isRight)
				{
					b->angle = D3DXToRadian(250);
					b->pos = pos;
				}
				else
				{
					b->angle = D3DXToRadian(-70);
					b->pos = pos + Vec2(230, -10);
				}
				scene->bulletList.push_back(b);
				scene->addChild(b);
			}
		}
	}
}