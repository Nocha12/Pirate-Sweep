#include "DXUT.h"
#include "Boss2.h"
#include "GameManager.h"
#include "GameScene.h"
#include "World.h"
#include "RankScene.h"

Boss2::Boss2() : isCannonBroken(false), count(0)
{
	addChild(animation = new Animation("image/mob/boss2/attack1", 10, 10, true));  // attackani1
	addChild(attackAni = new Animation("image/mob/boss2/attack2", 8, 8, true));
	attackAni->visible = false;
	rect = animation->rect;
	rect.bottom -= 56;
	SetPivot();
	shootDelay = 1;
	shootTimer = 0;
	hp = 3000;
	isFallable = true;
}

Boss2::~Boss2()
{
}

void Boss2::update(float dt)
{
	Enemy::update(dt);

	if (gameManager.isBoss)
	{
		shootTimer += dt;

		GameScene *scene = (GameScene*)world.currentScene;

		if (hp < 0)
		{
			hp = 0;
			scene->isEnd = true;
		}

		scene->bossHpBar->visibleRect.right = scene->bossHpBar->rect.width() * (hp / 3000);

		if (hp > 2000) // 자잘한 대포
		{
			if (shootTimer >= shootDelay && !isBlink && count == 0)
			{
				shootTimer = 0;
				for (int i = 0; i < 5; i++)
				{
					Bullet *b = new Bullet(BOSS2_BOOM1, 1700, 50, 10, D3DXToRadian(-100 - i * 30));
					b->isPlayerBullet = false;
					b->scale.x *= -1;
					b->pos = center() + Vec2(-150, -50);
					scene->bulletList.push_back(b);
					scene->addChild(b);
				}
				++count;
			}
			else if (shootTimer >= shootDelay && !isBlink && count == 1)
			{
				shootTimer = 0;
				for (int i = 0; i < 6; i++)
				{
					Bullet *b = new Bullet(BOSS2_BOOM1, 1700, 50, 10, D3DXToRadian(-80 - i * 30));
					b->isPlayerBullet = false;
					b->scale.x *= -1;
					b->pos = center() + Vec2(-150, -50);
					b->rotation = D3DXToRadian(-130 - i * 30);
					scene->bulletList.push_back(b);
					scene->addChild(b);
				}
				++count;
			}
			else if (shootTimer >= shootDelay && !isBlink && count == 2)
			{
				shootTimer = 0;

				Bullet *b = new Bullet(BOSS2_BOOM1, 600, 20, 150, 0);
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
		else if (hp > 1000) // 큰 대포
		{
			if (shootTimer >= shootDelay && !isBlink && count == 0)
			{
				shootTimer = 0;
				for (int i = 0; i < 7; i++)
				{
					Bullet *b = new Bullet(BOSS2_BOOM1, 1700, 50, 10, D3DXToRadian(-80 - i * 30));
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

				for (int i = 0; i < 2; i++)
				{
					Bullet *b = new Bullet(BOSS2_BOOM2, 1700, 100, 200, D3DXToRadian(random(-110, -100)));
					b->isPlayerBullet = false;
					b->scale.x *= -1;
					b->pos = center() + Vec2(-350, -150);
					scene->bulletList.push_back(b);
					scene->addChild(b);
				}
				++count;
			}
			else if (shootTimer >= shootDelay && !isBlink && count == 2)
			{
				shootTimer = 0;

				Bullet *b = new Bullet(BOSS2_BOOM2, 500, 80, 200, 0);
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
				shootDelay = 0.25f;
			}

			if (shootTimer >= shootDelay && !isBlink && count == 0)
			{
				shootTimer = 0;

				Bullet *b = new Bullet(BOSS2_GUN, 600, 80, 10, 0);
				b->isPlayerBullet = false;
				b->pos = center() + Vec2(-80, -70);
				b->rotation = b->angle = D3DXToRadian(random(-200, -100));
				b->isFallable = false;
				scene->bulletList.push_back(b);
				scene->addChild(b);
				Bullet *b2 = new Bullet(BOSS2_GUN, 600, 80, 10, 0);
				b2->isPlayerBullet = false;
				b2->pos = center() + Vec2(-80, -70);
				b2->rotation = b2->angle = D3DXToRadian(random(-200, -100));
				b2->isFallable = false;
				scene->bulletList.push_back(b2);
				scene->addChild(b2);

				++count;
			}
			else if (shootTimer >= shootDelay && !isBlink && count == 1)
			{
				shootTimer = 0;

				Bullet *b = new Bullet(BOSS2_GUN, 700, 80, 10, 0);
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