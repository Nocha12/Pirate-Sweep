#include "DXUT.h"
#include "Boss1.h"
#include "GameManager.h"
#include "GameScene.h"
#include "World.h"

Boss1::Boss1() : isCannonBroken(false), count(0)
{
	addChild(animation = new Animation("image/mob/boss1/attack1", 10, 10, true));  // attackani1
	addChild(attackAni = new Animation("image/mob/boss1/attack2", 8, 8, true));
	attackAni->visible = false;
	rect = animation->rect;
	rect.bottom -= 56;
	SetPivot();
	shootDelay = 1;
	shootTimer = 0;
	hp = 1000;
	isFallable = true;
}

Boss1::~Boss1()
{
}

void Boss1::update(float dt)
{
	Enemy::update(dt);

	if (hp < 0)
		hp = 0;
	if (gameManager.isBoss)
	{
		shootTimer += dt;

		GameScene *scene = (GameScene*)world.currentScene;

		scene->bossHpBar->visibleRect.right = scene->bossHpBar->rect.width() * (hp / 1000);
		
		if (hp > 500) // 자잘한 대포
		{
			if (shootTimer >= shootDelay && !isBlink && count == 0)
			{
				shootTimer = 0;
				for (int i = 0; i < 3; i++)
				{
					Bullet *b = new Bullet(BOSS1_BOOM1, 1600, 20, 10, D3DXToRadian(-150 - i * 30));
					b->isPlayerBullet = false;
					b->scale.x *= -1;
					b->pos = center() + Vec2(-150, -50);
					scene->bulletList.push_back(b);
					scene->addChild(b);

				}
				++count;
			} else if (shootTimer >= shootDelay && !isBlink && count == 1)
			{
				shootTimer = 0;
				for (int i = 0; i < 4; i++)
				{
					Bullet *b = new Bullet(BOSS1_BOOM1, 1600, 20, 10, D3DXToRadian(-130 - i * 30));
					b->isPlayerBullet = false;
					b->scale.x *= -1;
					b->pos = center() + Vec2(-150, -50);
					b->rotation = D3DXToRadian(-130 - i * 30);
					scene->bulletList.push_back(b);
					scene->addChild(b);
				}
				++count;
			} else if (shootTimer >= shootDelay && !isBlink && count == 2)
			{
				shootTimer = 0;
			
				Bullet *b = new Bullet(BOSS1_BOOM1, 600, 20, 150, 0);
				b->isPlayerBullet = false;
				b->scale.x *= -1;
				b->pos = center() + Vec2(-150, -50);
				b->rotation = b->angle = angle(b->center(), scene->player->center());
				b->isFallable = false;
				scene->bulletList.push_back(b);
				scene->addChild(b);

				count = 0;
			}
		}
		else if (hp > 300) // 큰 대포
		{
			if (shootTimer >= shootDelay && !isBlink && count == 0)
			{
				shootTimer = 0;
				for (int i = 0; i < 4; i++)
				{
					Bullet *b = new Bullet(BOSS1_BOOM1, 1600, 20, 10, D3DXToRadian(-130 - i * 30));
					b->isPlayerBullet = false;
					b->scale.x *= -1;
					b->pos = center() + Vec2(-150, -50);
					scene->bulletList.push_back(b);
					scene->addChild(b);
				}
				++count;
			}if (shootTimer >= shootDelay && !isBlink && count == 1)
			{
				shootTimer = 0;
		
				Bullet *b = new Bullet(BOSS1_BOOM2, 1650, 50, 200, D3DXToRadian(random(-110, -100)));
				b->isPlayerBullet = false;
				b->scale.x *= -1;
				b->pos = center() + Vec2(-350, -150);
				scene->bulletList.push_back(b);
				scene->addChild(b);
				++count;
			}
			else if (shootTimer >= shootDelay && !isBlink && count == 2)
			{
				shootTimer = 0;

				Bullet *b = new Bullet(BOSS1_BOOM2, 500, 50, 200, 0);
				b->scale.x *= -1;
				b->isPlayerBullet = false;
				b->pos = center() + Vec2(-320, -70);
				b->rotation = b->angle = angle(b->center(), scene->player->center());
				b->isFallable = false;
				scene->bulletList.push_back(b);
				scene->addChild(b);

				count = 0;
			}
		}
		else
		{
			if (!isCannonBroken)
			{
				count = 0;
				isCannonBroken = true;
				animation->visible = false;
				attackAni->visible = true;
				rect = attackAni->rect;
				SetPivot();
				pos.x += 200;
				shootDelay = 0.5f;
			}

			if (shootTimer >= shootDelay && !isBlink && count == 0)
			{ 
				shootTimer = 0;

				Bullet *b = new Bullet(BOSS1_GUN, 500, 10, 10, 0);
				b->isPlayerBullet = false;
				b->pos = center() + Vec2(-80, -70);
				b->rotation = b->angle = D3DXToRadian(random(-200, -100));
				b->isFallable = false;
				scene->bulletList.push_back(b);
				scene->addChild(b);

				++count;
			}
			else if (shootTimer >= shootDelay && !isBlink && count == 1)
			{
				shootTimer = 0;

				Bullet *b = new Bullet(BOSS1_GUN, 500, 10, 10, 0);
				b->isPlayerBullet = false;
				b->pos = center() + Vec2(-80, -70);
				b->rotation = b->angle = angle(b->center(), scene->player->center());
				b->isFallable = false;
				scene->bulletList.push_back(b);
				scene->addChild(b);

				count = 0;
			}
		}
	}
}
