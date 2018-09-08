#include "DXUT.h"
#include "Enemy.h"
#include "GameScene.h"
#include "World.h"
#include "Define.h"
#include "Effect.h"
#include "GameManager.h"

Enemy::Enemy() : isRight(false), isBlink(false), canMoveLeft(true), canMoveRight(true), speed(0), isFollowing(false)
{
	isFallable = true;
}

Enemy::~Enemy()
{
}

void Enemy::update(float dt)
{
	Entity::update(dt);

	if (pos.y <= 100)
		pos.y = 100;
	else if (pos.y >= 3500)
		pos.y = 500;
	if (isFallable)
	{
		gravity += 9.8 * dt + 50 * dt;
		pos.y += gravity;
	}

	GameScene *scene = (GameScene*)world.currentScene;
	
	float playerAngle = angle(pos, scene->player->pos);
	playerDistance = calDistance(center(), scene->player->center());

	if (playerAngle > D3DXToRadian(-90) && playerAngle < D3DXToRadian(90) && !gameManager.isBoss)
	{
		animation->scale.x = -1;
		attackAni->scale.x = -1;
		isRight = true;
	}	
	else
	{
		animation->scale.x = 1;
		attackAni->scale.x = 1;
		isRight = false;  
	}	

	if (scene->ground->GetBit(pos.x + bottom.x, pos.y + bottom.y))
	{
		int cnt = 0;
		while (scene->ground->GetBit(pos.x + bottom.x, pos.y + bottom.y - cnt))
			++cnt;
		pos.y -= cnt;
		gravity = 0;
	}

	for_iter(obj, scene->obstacleList)
	{
		if ((*obj)->obstacleType == BOX)
		{
			if ((*obj)->rectWithPos().contains(Vec2(pos.x + left.x - speed * dt, pos.y + left.y)))
			{
				canMoveLeft = false;
				pos.x += speed * dt;
			}if ((*obj)->rectWithPos().contains(Vec2(pos.x + right.x + speed * dt, pos.y + right.y)))
			{
				canMoveLeft = false;
				pos.x -= speed * dt;
			}
		}
	}

	if (scene->ground->GetBit(pos.x + left.x - speed * dt, pos.y + left.y))
	{
		canMoveLeft = false;
		pos.x += speed * dt;
	}
	else
	{
		canMoveLeft = true;
	}
	if (scene->ground->GetBit(pos.x + right.x + speed * dt, pos.y + right.y))
	{
		canMoveRight = false;
		pos.x -= speed * dt;
	}
	else
	{
		canMoveRight = true;
	}

	if (hp <= 0 && !isBlink) // Àû Á×À½
	{
		Blink();
		animation->stop = true;
		attackAni->stop = true;
		hp = 0;
	}
}

void Enemy::Blink()
{
	blinkTimer.reset(0.1f, 6, true);

	isBlink = true;

	blinkTimer.onTick = [=]()
	{
		animation->color = D3DXCOLOR(1, 1, 1, 0.7*float(blinkTimer.count.first % 2) + 0.3);
		attackAni->color = D3DXCOLOR(1, 1, 1, 0.7*float(blinkTimer.count.first % 2) + 0.3);
	};

	blinkTimer.onFinished = [=]()
	{	
		GameScene *scene = (GameScene*)world.currentScene;
		ExpEffect *eff = new ExpEffect(scene->player);
		eff->pos = center();
		scene->addChild(eff);
		scene->effectList.push_back(eff);

		removeChild(this);
		scene->enemyList.remove(this);
		gameManager.score += 200;

		if (gameManager.isBoss && gameManager.stage == 1)
		{
			scene->shopBox->visible = true;
			//scene->shopBox->stop = false;
		}

		return;
	};
}

void Enemy::OnHit()
{
	if (isBlink)
		return;

	hitTimer.reset(0.05f, 50, true);

	animation->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);
	attackAni->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);

	hitTimer.onTick = [=]()
	{
		animation->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
		attackAni->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
	};
}

void Enemy::SetPivot()
{
	int bodyWidth = rect.width(), bodyHeight = rect.height();

	right = Vec2(bodyWidth, bodyHeight / 2);
	left = Vec2(0, bodyHeight / 2);
	bottom = Vec2(bodyWidth / 2, bodyHeight);
}