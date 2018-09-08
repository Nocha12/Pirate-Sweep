#include "DXUT.h"
#include "Player.h"
#include "World.h"
#include "GameScene.h"
#include "World.h"
#include "GameManager.h"

Player::Player() : jumpNum(0), shootDelay(0.3f), shootTimer(0), isShoot(false), isGrenade(false), isMove(false), flyTimer(0), isFlying(false), hp(300), exp(0), grenadeCount(5), getGround(false), isRight(false), bulletCount(0), level(1), currentHp(300), currentExp(50), isDeath(false), power(0), isLevelUp(false)
{
	if (gameManager.buyPower)
		power = 10;

	level = gameManager.playerLevel;
	currentHp = 300 + (level - 1) * 50;
	currentExp = 50 + (level - 1) * 20;

	if (gameManager.buyHp)
		currentHp += 200;
	hp = currentHp;
	exp = 0;
	
	body = new Animation("image/player/walk body", 10, 10, true);
	rect = body->rect;
	addChild(body);
	body->rotationCenter = body->center();
	body->scaleCenter = body->center();

	jumpBody = new Animation("image/player/jump", 7, 15, false);
	addChild(jumpBody);
	jumpBody->rotationCenter = jumpBody->center();
	jumpBody->scaleCenter = jumpBody->center();
	jumpBody->visible = false;

	flyBody = new Animation("image/player/fly", 6, 6, true);
	addChild(flyBody);
	flyBody->rotationCenter = flyBody->center();
	flyBody->scaleCenter = flyBody->center();
	flyBody->visible = false;

	foot = new Animation("image/player/walk foot", 12, 12, true);
	addChild(foot);
	foot->scaleCenter = foot->center();
	foot->visible = false;

	jumpFoot = new Animation("image/player/jump foot", 7, 12, false);
	addChild(jumpFoot);
	jumpFoot->scaleCenter = jumpFoot->center();
	jumpFoot->visible = false;

	stopFoot = new Sprite("image/player/stop foot.tga");
	stopFoot->scaleCenter = stopFoot->center();
	addChild(stopFoot);

	flyFoot = new Sprite("image/player/fly_foot.tga");
	flyFoot->scaleCenter = flyFoot->center();
	flyFoot->visible = false;
	addChild(flyFoot);

	LevelUpText = new Sprite("image/outgame/text/levelup.png");
	LevelUpText->pos.x += 10;
	LevelUpText->visible = false;
	addChild(LevelUpText);
	

	weapon = new Weapon();
	addChild(weapon);

	int bodyWidth = rect.width(), bodyHeight = rect.height();

	right = Vec2(bodyWidth, bodyHeight / 2);
	left = Vec2(0, bodyHeight / 2);
	bottom = Vec2(bodyWidth / 2, bodyHeight);
	top = Vec2(bodyWidth / 2, 0);

	ResizeRect(&rect, 15);
	
	isFallable = true;
}

Player::~Player()
{
}

void Player::update(float dt)
{
	Entity::update(dt);

	if (pos.y <= 100)
		pos.y = 100;

	if (isDeath)
	{
		visible = false;
		return;
	}

	if (isLevelUp && LevelUpText->color.a > 0)
	{
		LevelUpText->visible = true;
		LevelUpText->color.a -= 0.01f;
		LevelUpText->pos.y -= 0.05f;
	}
	else if (LevelUpText->color.a < 0)
	{
		LevelUpText->color.a = 1;
		LevelUpText->visible = false;
		LevelUpText->pos.y = 0; 
		isLevelUp = false;
	}

	if (exp >= currentExp) //Level Up
	{
		currentExp += 20;
		exp = 0;
		
		currentHp += 50;
		hp = currentHp;

		isLevelUp = true;

		++level;
	}

	if (pos.x <= 250)
		pos.x = 250;
	if (pos.x >= 13930)
		pos.x = 13930;

	if (gameManager.isBoss && pos.x <= 12800)
		pos.x = 12800;
		

	if (pos.y > 3000)
		pos = Vec2(300, 1000);

	int moveSpeed = 500;

	if (world.getKeyState('X') == 2)
	{
		pos.x = 12600;
	}

	GameScene *scene = (GameScene*)world.currentScene;

	if (hp <= 0)
	{
		scene->continueScreen->visible = true;
		scene->yesBtn->visible = true;
		scene->noBtn->visible = true;
		isDeath = true;

		weapon->ChangeWeapon(GUN);
		shootDelay = 0.3f;
		scene->weaponBaseUI->visible = true;
		scene->weaponMgunUI->visible = false;
		scene->weaponBzuUI->visible = false;
		bulletCount = 0;
		scene->infinite->visible = true;
		scene->bulletCountText->visible = false;
	}

	if (!getGround)
	{
		getGround = true;
		ground = scene->ground;
	}

	body->rotation = angle(pos + weapon->pos + world.currentScene->pos, world.getMousePos());
	jumpBody->rotation = body->rotation;
	flyBody->rotation = body->rotation;
	weapon->rotation = body->rotation;

	if (world.getKeyState('W') == 1) //Jump
	{
		if (jumpNum < 2 && !isFlying)
		{
			stopFoot->visible = false;
			jumpBody->visible = true;
			body->visible = false;
			jumpBody->currentFrame = 0;
			jumpFoot->visible = true;
			foot->visible = false;
			jumpFoot->currentFrame = 0;
			jumpNum++;
			gravity = -1200 * dt;
			pos.y -= 2;
		}
	}
	if (isFlying && world.getKeyState('W') == 2) // Fly
	{
		gravity = 0;
		pos.y -= 10;
	}

	bool canGoLeft = true, canGoRight = true;

	for_iter(obj, scene->obstacleList)
	{
		if ((*obj)->obstacleType == BOX)
		{
			if ((*obj)->rectWithPos().contains(Vec2(pos.x + left.x - moveSpeed * dt, pos.y + left.y)))
				canGoLeft = false;
			if ((*obj)->rectWithPos().contains(Vec2(pos.x + right.x + moveSpeed * dt, pos.y + right.y)))
				canGoRight = false;
			if ((*obj)->rectWithPos().contains(Vec2(pos.x + bottom.x, pos.y + bottom.y - 30)))
			{
				jumpFoot->visible = false;
				jumpBody->visible = false;
				if (!isFlying)
					body->visible = true;

				int cnt = 0;

				while ((*obj)->rectWithPos().contains(Vec2(pos.x + bottom.x, pos.y + bottom.y - 30 - cnt)))
					++cnt;

				pos.y -= cnt;

				gravity = 0;
				jumpNum = 0;
			}
			if ((*obj)->rectWithPos().contains(Vec2(pos.x + top.x, pos.y + top.y)))
			{
				int cnt = 0;

				while ((*obj)->rectWithPos().contains(Vec2(pos.x + top.x, pos.y + top.y + cnt)))
					++cnt;

				pos.y += cnt;
			}
		}
		if ((*obj)->obstacleType == SPINE)
		{
			Rect t;
			if ((*obj)->rectWithPos().intersects((this)->rectWithPos(), &t))
			{
				hp -= 10;
				gravity = -1000 * dt;
				OnHit();
			}
		}
	}

	for_iter(item, scene->itemList)
	{
		Rect t;
		if ((*item)->rectWithPos().intersects(rectWithPos(), &t))
		{
			if ((*item)->itemType == HP)
				hp = currentHp;
			else if ((*item)->itemType == ITEM_GRENADE)
				grenadeCount += 5;
			else if ((*item)->itemType == ITEM_MACHINEGUN)
			{
				weapon->ChangeWeapon(MACHINEGUN);
				shootDelay = 0.1f;
				scene->weaponBaseUI->visible = false;
				scene->weaponMgunUI->visible = true;
				scene->weaponBzuUI->visible = false;
				bulletCount = 100;
				scene->infinite->visible = false;
				scene->bulletCountText->visible = true;
			}
			else if ((*item)->itemType == ITEM_BAZOOKA)
			{
				weapon->ChangeWeapon(BAZOOKA);
				shootDelay = 1;
				scene->weaponBaseUI->visible = false;
				scene->weaponMgunUI->visible = false;
				scene->weaponBzuUI->visible = true;
				bulletCount = 10;
				scene->infinite->visible = false;
				scene->bulletCountText->visible = true;
			}

			scene->removeChild(*item);
			scene->itemList.remove(*item);
			return;
		}
	}

	if (world.getKeyState('A') == 2 && !ground->GetBit(pos.x + left.x - moveSpeed * dt, pos.y + left.y) && canGoLeft) 
	{
		if (!isFlying)
		{
			stopFoot->visible = false;
			if (jumpNum == 0)
				foot->visible = true;
			isMove = true;
		}

		pos.x -= moveSpeed * dt;
	}

	if (ground->GetBit(pos.x + top.x, pos.y + top.y))
	{
		int cnt = 0;

		while (ground->GetBit(pos.x + top.x, pos.y + top.y + cnt))
			++cnt;

		pos.y += cnt;
	}

	else if (world.getKeyState('A') == -1)
	{
		if (!isFlying)
		{
			stopFoot->visible = true;
			foot->visible = false;
			isMove = false;
		}
	}
	if (world.getKeyState('D') == 2 && !ground->GetBit(pos.x + right.x + moveSpeed * dt, pos.y + right.y) && canGoRight) 
	{
		if (!isFlying)
		{
			stopFoot->visible = false;
			if (jumpNum == 0)
				foot->visible = true;
			isMove = true;
		}
		pos.x += moveSpeed * dt;
	}
	else if (world.getKeyState('D') == -1)
	{
		if (!isFlying)
		{
			stopFoot->visible = true;
			foot->visible = false;
			isMove = false;
		}
	}

	weapon->pos += (weapon->currentPos - weapon->pos) * 0.2;
	if (world.getKeyState(VK_LBUTTON) == 2) //Fire
	{
		if (shootTimer >= shootDelay || (gameManager.buyBullet && shootTimer >= shootDelay / 2))
		{
			if (--bulletCount == 0 && !weapon->weaponType == GUN)
			{
				weapon->ChangeWeapon(GUN);
				shootDelay = 0.3f;
				scene->weaponBaseUI->visible = true;
				scene->weaponMgunUI->visible = false;
				scene->weaponBzuUI->visible = false;
				bulletCount = 0;
				scene->infinite->visible = true;
				scene->bulletCountText->visible = false;
			}
			shootTimer = 0;
			isShoot = true;
			weapon->pos.x -= cos(weapon->rotation) * 10;
			weapon->pos.y -= sin(weapon->rotation) * 10;
		}
	} if (world.getKeyState(VK_RBUTTON) == 1) //Fire 
	{
		if (grenadeCount > 0)
		{
			--grenadeCount;
			isShoot = true;
			isGrenade = true;
			weapon->pos.x -= cos(weapon->rotation) * 15;
			weapon->pos.y -= sin(weapon->rotation) * 15;
		}
	}

	if (world.getKeyState('Q') == 1) // changeWeapon
	{
		weapon->ChangeWeapon(BAZOOKA);
		shootDelay = 1;
		scene->weaponBaseUI->visible = false;
		scene->weaponMgunUI->visible = false;
		scene->weaponBzuUI->visible = true;
		bulletCount = 10;
		scene->infinite->visible = false;
		scene->bulletCountText->visible = true;
	}
	if (world.getKeyState('E') == 1) // changeWeapon
	{
		weapon->ChangeWeapon(MACHINEGUN);
		shootDelay = 0.1f;
		scene->weaponBaseUI->visible = false;
		scene->weaponMgunUI->visible = true;
		scene->weaponBzuUI->visible = false;
		bulletCount = 100;
		scene->infinite->visible = false;
		scene->bulletCountText->visible = true;
	}
	if (world.getKeyState('2') == 1) // changeWeapon
	{
		weapon->ChangeWeapon(GUN);
		shootDelay = 0.3f;
		scene->weaponBaseUI->visible = true;
		scene->weaponMgunUI->visible = false;
		scene->weaponBzuUI->visible = false;
		bulletCount = 0;
		scene->infinite->visible = true;
		scene->bulletCountText->visible = false;
		scene->isEnd = true;
	}

	if (world.getKeyState('F') == 1) // StartFlying
	{
		isFlying = true;
		stopFoot->visible = false;
		flyBody->visible = true;
		body->visible = false;
		jumpBody->visible = false;
		flyBody->currentFrame = 0;
		jumpFoot->visible = false;
		flyFoot->visible = true;
		foot->visible = false;
	}

	if (!isMove && jumpNum == 0 && !isFlying)
		stopFoot->visible = true;
	
	if (ground->GetBit(pos.x + bottom.x, pos.y + bottom.y))
	{
		jumpFoot->visible = false;
		jumpBody->visible = false;
		if (!isFlying)
			body->visible = true;

		int cnt = 0;
		
		while (ground->GetBit(pos.x + bottom.x, pos.y + bottom.y - cnt))
			++cnt;

		pos.y -= cnt;

		gravity = 0;
		jumpNum = 0;
	}

	if (ground->GetBit(pos.x + top.x, pos.y + top.y))
	{
		int cnt = 0;

		while (ground->GetBit(pos.x + top.x, pos.y + top.y + cnt))
			++cnt;

		pos.y += cnt;
	}

	if (weapon->rotation > D3DXToRadian(-90) && weapon->rotation < D3DXToRadian(90))
	{
		body->scale.y = 1;
		flyBody->scale.y = 1;
		jumpBody->scale.y = 1;
		weapon->scale.y = 1;
		foot->scale.x = 1;
		stopFoot->scale.x = 1;
		jumpFoot->scale.x = 1;
		flyFoot->scale.x = 1;
		isRight = true;
	}
	else
	{
		body->scale.y = -1;
		flyBody->scale.y = -1;
		jumpBody->scale.y = -1;
		weapon->scale.y = -1;
		foot->scale.x = -1;
		stopFoot->scale.x = -1;
		jumpFoot->scale.x = -1;
		flyFoot->scale.x = -1;
		isRight = false;
	}

	shootTimer += dt;

	if (isFallable) // Gravity
	{
		gravity += 9.8 * dt + 50 * dt;
		pos.y += gravity;
	}
}

void Player::OnHit()
{
	hitTimer.reset(0.05f, 50, true);

	body->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);;
	flyBody->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);
	jumpBody->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);
	weapon->gun->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);
	weapon->machineGun->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);
	weapon->bazooka->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);
	foot->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);
	stopFoot->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);
	jumpFoot->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);
	flyFoot->color = D3DXCOLOR(1, 0.5f, 0.5f, 1);

	hitTimer.onTick = [=]()
	{
		body->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
		flyBody->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
		jumpBody->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
		weapon->gun->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
		weapon->machineGun->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
		weapon->bazooka->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
		foot->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
		stopFoot->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
		jumpFoot->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
		flyFoot->color = D3DXCOLOR(1, 0.5f + float(hitTimer.count.first) / 10, 0.5f + float(hitTimer.count.first) / 10, 1);
	};
}