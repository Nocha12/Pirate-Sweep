#include "DXUT.h"
#include "GameScene.h"
#include "ShooterEnemy.h"
#include "BoomEnemy.h"
#include "Effect.h"
#include "Obstacle.h"
#include "Boss1.h"
#include "GameManager.h"
#include "World.h"
#include "ShopScene.h"
#include "Boss2.h"
#include "RankScene.h"
#include "MainScene.h"

GameScene::GameScene() : isEnd(false), finishTimer(0)
{
	ground = new Ground();
	addChild(ground);

	player = new Player();
	addChild(player);
	player->pos = Vec2(300, 1000);

	follow(player, Vec2(1280 / 2, 720 / 2));

	pos.x = -250;

	if (gameManager.stage == 1)
		SetStage1();
	else 
		SetStage2();
	SetUI(Vec2(13, 20), "image/outgame/hpbar/hpbar1.png");
	SetUI(Vec2(15, 22), "image/outgame/hpbar/hpbar2.png", &hpBar);
	SetUI(Vec2(15, 92), "image/outgame/hpbar/expbar1.png");
	SetUI(Vec2(16, 94), "image/outgame/hpbar/expbar2.png", &expBar);
	SetUI(Vec2(8, 9), "image/outgame/hpbar/level.png");
	SetUI(Vec2(34, 118), "image/outgame/weapon/base.png", &weaponBaseUI);
	SetUI(Vec2(34, 118), "image/outgame/weapon/mgun.png", &weaponMgunUI);
	weaponMgunUI->visible = false;
	SetUI(Vec2(34, 118), "image/outgame/weapon/bzu.png", &weaponBzuUI);
	weaponBzuUI->visible = false;
	SetUI(Vec2(94, 145), "image/outgame/weapon/x.png");
	SetUI(Vec2(235, 145), "image/outgame/weapon/x.png");
	SetUI(Vec2(121, 145), "image/outgame/weapon/inf.png", &infinite);
	SetUI(Vec2(180, 118), "image/outgame/weapon/bomb.png");
	SetUI(Vec2(0, 0), "image/outgame/text/continue.png", &continueScreen);
	continueScreen->visible = false;
	SetUI(Vec2(237, 462), "image/outgame/text/yes.png", &yesBtn);
	yesBtn->visible = false;
	SetUI(Vec2(875, 462), "image/outgame/text/no.png", &noBtn);
	noBtn->visible = false;
	SetUI(Vec2(956, 51), "image/outgame/text/score.png");
	SetUI(Vec2(0, 0), "image/outgame/text/stageclear1.png", &stage1ClearText);
	SetUI(Vec2(0, 0), "image/outgame/text/stageclear2.png", &stage2ClearText);
	stage1ClearText->visible = false;
	stage2ClearText->visible = false;

	bossHpBarBack = new Sprite("image/outgame/hpbar/boss1.png");
	bossHpBar = new Sprite("image/outgame/hpbar/boss2.png");
	bossHpBarBack->pos = Vec2(13700, 1930);
	bossHpBar->pos = Vec2(13703, 1933);
	addChild(bossHpBarBack);
	addChild(bossHpBar);

	boomCountText = new Text(to_string(player->grenadeCount), 35, D3DXCOLOR(0, 0, 0, 1));
	boomCountText->pos = Vec2(253, 134);
	UITextList.push_back(boomCountText);

	bulletCountText = new Text(to_string(player->bulletCount), 35, D3DXCOLOR(0, 0, 0, 1));
	bulletCountText->pos = Vec2(121, 134);
	bulletCountText->visible = false;
	UITextList.push_back(bulletCountText);

	levelText = new Text(to_string(player->level), 25, D3DXCOLOR(0, 0, 0, 1));
	levelText->pos = Vec2(461, 85);
	UITextList.push_back(levelText);

	scoreText = new Text(to_string(gameManager.score), 40, D3DXCOLOR(1, 1, 1, 1));
	scoreText->pos = Vec2(1106, 51);
	UITextList.push_back(scoreText);
}

GameScene::~GameScene()
{
	SAFE_DELETE(backSky);
	for_iter(iter, UIList)
	{
		SAFE_DELETE(*iter);
		iter = UIList.erase(iter);
		if (iter == UIList.end())
			break;
	}
	for_iter(iter, UITextList)
	{
		SAFE_DELETE(*iter);
		iter = UITextList.erase(iter);
		if (iter == UITextList.end())
			break;
	}
	if (scoreText)
		SAFE_DELETE(scoreText);
	if (bulletCountText)
		SAFE_DELETE(bulletCountText);
	if (temp)
		SAFE_DELETE(temp);
}

void GameScene::update(float dt)
{
	Scene::update(dt);

	if (continueScreen->visible && yesBtn->rectWithPos().contains(world.getMousePos()))
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			player->pos = Vec2(gameManager.startX, 1000);
			player->visible = true;
			player->isDeath = false;
			player->hp = player->currentHp;
			player->exp = 0;
			continueScreen->visible = false;
			yesBtn->visible = false;
			noBtn->visible = false;
		}
	}

	if (continueScreen->visible && noBtn->rectWithPos().contains(world.getMousePos()))
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			world.changeScene(new MainScene());
			return;
		}
	}

	backSky->pos.x -= 2;
	
	if (backSky->pos.x <= -1280)
		backSky->pos.x = 0;

	boomCountText->text = to_string(player->grenadeCount);
	bulletCountText->text = to_string(player->bulletCount);
	scoreText->text = to_string(gameManager.score);
	levelText->text = to_string(player->level);

	hpBar->visibleRect.right = hpBar->rect.width() * (player->hp / player->currentHp);
	expBar->visibleRect.right = expBar->rect.width() * (player->exp / player->currentExp);

	if (player->isShoot) // MakeBullet
	{
		Bullet *b;
		player->isShoot = false;
		
		if (player->isGrenade)
		{     
			player->isGrenade = false;
			b = new Bullet(GRENADE, 1200, 100 + player->power, 300, player->weapon->rotation);
			b->pos = player->pos + player->weapon->pos + Vec2(cos(player->weapon->rotation), sin(player->weapon->rotation)) * player->weapon->rect.width();
			b->rotation = player->weapon->rotation;
			bulletList.push_back(b);
			addChild(b);
			shake(3, 6);
		} else if (player->weapon->weaponType == GUN)
		{
			b = new Bullet(player->weapon->weaponType, 2000, 10 + player->power, 1, player->weapon->rotation);
			b->pos = player->pos + player->weapon->pos + Vec2(cos(player->weapon->rotation), sin(player->weapon->rotation)) * player->weapon->rect.width();
			b->rotation = player->weapon->rotation;
			bulletList.push_back(b);
			addChild(b);
			shake(3, 5);
		} else if (player->weapon->weaponType == BAZOOKA)
		{
			b = new Bullet(player->weapon->weaponType, 3000, 100 + player->power, 300, player->weapon->rotation);
			b->pos = player->pos + player->weapon->pos + Vec2(cos(player->weapon->rotation), sin(player->weapon->rotation)) * player->weapon->rect.width();
			bulletList.push_back(b);
			addChild(b);
			shake(3, 10);
		} else if (player->weapon->weaponType == MACHINEGUN)
		{
			b = new Bullet(player->weapon->weaponType, 2000, 13 + player->power, 1, player->weapon->rotation);
			b->pos = player->pos + player->weapon->pos + Vec2(cos(player->weapon->rotation), sin(player->weapon->rotation)) * player->weapon->rect.width();
			b->rotation = player->weapon->rotation;
			bulletList.push_back(b);
			addChild(b);
			shake(1, 3);
		}
		b->isPlayerBullet = true;
	}

	Rect t;

	for_iter(bullet, bulletList)
	{
		for_iter(obj, obstacleList)
		{
			if ((*obj)->obstacleType == BOX)
			{
				if ((*bullet)->rectWithPos().intersects((*obj)->rectWithPos(), &t))
				{
					if ((*bullet)->weaponType == BAZOOKA || (*bullet)->weaponType == GRENADE || (*bullet)->weaponType == BOSS1_BOOM1 || (*bullet)->weaponType == BOSS1_BOOM2 || (*bullet)->weaponType == BOSS2_BOOM1 || (*bullet)->weaponType == BOSS2_BOOM2 || (*bullet)->weaponType == MOB1 || (*bullet)->weaponType == MOB3)
					{
						
						BoomEffect *eff;
						if ((*bullet)->weaponType == MOB1 || (*bullet)->weaponType == MOB3)
							eff = new BoomEffect(MOB_BOOM);
						else if ((*bullet)->weaponType == BOSS1_BOOM1 || (*bullet)->weaponType == BOSS2_BOOM1)
							eff = new BoomEffect(BOSS);
						else if ((*bullet)->weaponType == BOSS1_BOOM2 || (*bullet)->weaponType == BOSS2_BOOM2)
							eff = new BoomEffect(BOSS_BOOM);
						else if ((*bullet)->isPlayerBullet)
							eff = new BoomEffect(PLAYER_BOOM);
						eff->pos = (*bullet)->pos;
						addChild(eff);
						boomEffectList.push_back(eff);

						for_iter(obj, obstacleList) // 裹困面倒贸府
						{
							if (collision(eff->center(), (*obj)->center(), (*bullet)->range))
								(*obj)->hp -= (*bullet)->damage;
						}

						shake(5, 50);
					}
					else
					{
						(*obj)->hp -= (*bullet)->damage;
						BulletEffect *eff;
						if ((*bullet)->isPlayerBullet)
							eff = new BulletEffect(PLAYER_BULLET);
						else 
							eff = new BulletEffect(MOB_BULLET);
	
						eff->pos = (*bullet)->pos;
						addChild(eff);
						effectList.push_back(eff);
						eff->rotationOffset = (*bullet)->rotation;
					}
					removeChild(*bullet);
					bulletList.remove(*bullet);

					return;
				}
			}
		}

		if ((*bullet)->isPlayerBullet)
		{
			for_iter(enemy, enemyList) // 面倒贸府
			{
				if ((*bullet)->rectWithPos().intersects((*enemy)->rectWithPos(), &t))
				{
					if ((*bullet)->weaponType == BAZOOKA || (*bullet)->weaponType == GRENADE)
					{
						BoomEffect *eff;
						eff = new BoomEffect(PLAYER_BOOM);
						eff->pos = (*bullet)->pos;
						addChild(eff);
						boomEffectList.push_back(eff);

						for_iter(e, enemyList) // 裹困面倒贸府
						{
							if (collision(eff->center(), (*e)->center(), (*bullet)->range))
							{
								(*e)->hp -= (*bullet)->damage;
								if ((*e)->hp > 0)
									(*e)->OnHit();
								gameManager.score += (*bullet)->damage;
							}
						}
			
						shake(5, 50);
					}
					else
					{
						(*enemy)->hp -= (*bullet)->damage;
						gameManager.score += (*bullet)->damage;
						BulletEffect *eff = new BulletEffect(PLAYER_BULLET);
						eff->pos = (*bullet)->pos;
						addChild(eff);
						effectList.push_back(eff);
						if ((*enemy)->hp > 0)
							(*enemy)->OnHit();
						eff->rotationOffset = (*bullet)->rotation;
					}
					removeChild(*bullet);
					bulletList.remove(*bullet);

					return;
				}
			}
		}
		else if ((*bullet)->rectWithPos().intersects((player)->rectWithPos(), &t)) {
			if ((*bullet)->weaponType == MOB1 || (*bullet)->weaponType == MOB3 || (*bullet)->weaponType == BOSS1_BOOM1 || (*bullet)->weaponType == BOSS1_BOOM2 || (*bullet)->weaponType == BOSS2_BOOM1 || (*bullet)->weaponType == BOSS2_BOOM2)
			{
				BoomEffect *eff;
				player->hp -= (*bullet)->damage;
				player->OnHit();
				if ((*bullet)->weaponType == MOB1 || (*bullet)->weaponType == MOB3)
					eff = new BoomEffect(MOB_BOOM);
				else if ((*bullet)->weaponType == BOSS1_BOOM1 || (*bullet)->weaponType == BOSS2_BOOM1)
					eff = new BoomEffect(BOSS);
				else if ((*bullet)->weaponType == BOSS1_BOOM2 || (*bullet)->weaponType == BOSS2_BOOM2)
					eff = new BoomEffect(BOSS_BOOM);
				eff->pos = (*bullet)->pos;
				addChild(eff);
				boomEffectList.push_back(eff);
				removeChild(*bullet);
				bulletList.remove(*bullet);
			}
			else
			{
				player->hp -= (*bullet)->damage;
				player->OnHit();
				BulletEffect *eff = new BulletEffect(MOB_BULLET);
				eff->pos = (*bullet)->pos;
				addChild(eff);
				effectList.push_back(eff);
				eff->rotationOffset = (*bullet)->rotation;
				removeChild(*bullet);
				bulletList.remove(*bullet);
			}

			return;
		}

		if ((*bullet)->pos.y < 0 || (*bullet)->pos.x < 0 || (*bullet)->pos.x > 14500 ||
			ground->GetBit((*bullet)->center().x, (*bullet)->center().y))
		{
			if ((*bullet)->weaponType == BAZOOKA || (*bullet)->weaponType == GRENADE)
			{
				BoomEffect *eff;
				eff = new BoomEffect(PLAYER_BOOM);
				eff->pos = (*bullet)->pos;
				addChild(eff);
				boomEffectList.push_back(eff);

				for_iter(e, enemyList) // 裹困面倒贸府
				{
					if (collision(eff->center(), (*e)->center(), (*bullet)->range))
						(*e)->hp -= (*bullet)->damage;
				}

				shake(5, 50);
			}
			else if ((*bullet)->weaponType == MOB1 || (*bullet)->weaponType == MOB3 || (*bullet)->weaponType == BOSS1_BOOM1 || (*bullet)->weaponType == BOSS1_BOOM2 || (*bullet)->weaponType == BOSS2_BOOM1 || (*bullet)->weaponType == BOSS2_BOOM2)
			{
				BoomEffect *eff;
				if ((*bullet)->weaponType == MOB1 || (*bullet)->weaponType == MOB3)
					eff = new BoomEffect(MOB_BOOM);
				else if ((*bullet)->weaponType == BOSS1_BOOM1 || (*bullet)->weaponType == BOSS2_BOOM1)
					eff = new BoomEffect(BOSS);
				else if ((*bullet)->weaponType == BOSS1_BOOM2 || (*bullet)->weaponType == BOSS2_BOOM2)
					eff = new BoomEffect(BOSS_BOOM);
				eff->pos = (*bullet)->pos;
				addChild(eff);
				boomEffectList.push_back(eff);
				if (collision(eff->center(), player->center(), (*bullet)->range))
				{
					player->hp -= (*bullet)->damage;
					player->OnHit();
				}
			}
			else
			{
				BulletEffect *eff;
				if ((*bullet)->isPlayerBullet)
					eff = new BulletEffect(PLAYER_BULLET);
				else 
					eff = new BulletEffect(MOB_BULLET);
				eff->pos = (*bullet)->pos;
				addChild(eff);
				effectList.push_back(eff);
				eff->rotationOffset = (*bullet)->rotation;
			}

			removeChild(*bullet);
			bulletList.remove(*bullet);

			return;
		}
	}

	for_iter(effect, effectList)
	{
		if ((*effect)->isEnd())
		{
			removeChild(*effect);
			effectList.remove(*effect);
			return;
		}
	}

	for_iter(effect, boomEffectList)
	{
		if ((*effect)->animation->currentFrame == (*effect)->animation->textures.size() - 1)
		{
			removeChild(*effect);
			boomEffectList.remove(*effect);
			return;
		}
	}

	for_iter(point, savePointList)
	{
		if ((*point)->rectWithPos().intersects((player)->rectWithPos(), &t))
		{
			(*point)->Save();
		}
	}

	if (gameManager.stage == 1)
	{
		if (shopBox->visible)
		{
			stage1ClearText->visible = true;
			finishTimer += dt;
			if (finishTimer > 3)
			{
				stage1ClearText->visible = false;
				shopBox->stop = false;
			}
		}
		if (shopBox->currentFrame == shopBox->textures.size() - 1)
		{
			finishTimer = 0;
			gameManager.playerLevel = player->level;
			world.changeScene(new ShopScene());
		}
	}
	
	if (isEnd && gameManager.stage == 2)
	{
		stage2ClearText->visible = true;
		finishTimer += dt;
		if (finishTimer > 3)
		{
			gameManager.isBoss = false;
			world.changeScene(new RankScene());
			return;
		}
	}
}

void GameScene::render()
{
	Scene::render();

	backSky->render();
	for_iter(iter, background)
		(*iter)->render();
	for_iter(iter, savePointList)
		(*iter)->render();
	for_iter(iter, obstacleList)
		(*iter)->render();
	if (gameManager.stage == 1)
		shopBox->render();
	player->render();
	for_iter(iter, itemList)
		(*iter)->render();
	for_iter(iter, enemyList)
		(*iter)->render();
	for_iter(iter, bulletList)
		(*iter)->render();
	for_iter(iter, effectList)
		(*iter)->render();
	for_iter(iter, boomEffectList)
		(*iter)->render();
	for_iter(iter, UIList)
		(*iter)->render();
	for_iter(iter, UITextList)
		(*iter)->render();
	bossHpBarBack->render();
	bossHpBar->render();
}

void GameScene::shake(int n, float amount, float time)
{
	shakeTimer.reset(time, n, true);
	
	shakeTimer.onTick = [=]()
	{
		pos += Vec2(random(-amount, amount), random(-amount, amount));
	};
}

void GameScene::SetStage1()
{
	Boss1 *e = new Boss1();
	e->pos = Vec2(13490, 620);
	addChild(e);
	enemyList.push_back(e);

	for (int i = 0; i < 4; i++)
	{
		BoomEnemy *e = new BoomEnemy();
		e->pos = Vec2(random(1500, 12000), 500);
		addChild(e);
		enemyList.push_back(e);
	}

	for (int i = 0; i < 5; i++)
	{
		ShooterEnemy *e = new ShooterEnemy();
		e->pos = Vec2(random(1500, 12000), 500);
		addChild(e);
		enemyList.push_back(e);
	}

	backSky = new Sprite("image/map/background/stage1.png");

	for (int i = 0; i < 5; i++)
	{
		Sprite *b = new Sprite("image/map/stage1/map/" + to_string(i) + ".png");
		background.push_back(b);
		b->pos = Vec2(i * 2880, 0);
		addChild(b);
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Obstacle *box = new Obstacle(BOX);
			box->pos = Vec2(5016 + (2 * box->rect.width()) - (i * box->rect.width()), 1540 + (2 * (box->rect.height() - 40)) - (j * (box->rect.height() - 40)));
			obstacleList.push_back(box);
			addChild(box);
		}
	}

	SavePoint *save = new SavePoint();
	save->pos = Vec2(3903, 1662);
	addChild(save);
	savePointList.push_back(save);

	SavePoint *save2 = new SavePoint();
	save2->pos = Vec2(8777, 1662);
	addChild(save2);
	savePointList.push_back(save2);

	shopBox = new Animation("image/map/box", 10, 10, false, true);
	addChild(shopBox);
	shopBox->pos = Vec2(13690, 1620);
	shopBox->visible = false;
	shopBox->stop = true;

	Obstacle *spine1 = new Obstacle(SPINE);
	spine1->pos = Vec2(5848, 1904);
	addChild(spine1);
	obstacleList.push_back(spine1);
	Obstacle *spine2 = new Obstacle(SPINE);
	spine2->pos = Vec2(6435, 1904);
	addChild(spine2);
	obstacleList.push_back(spine2);
	Obstacle *spine3 = new Obstacle(SPINE);
	spine3->pos = Vec2(7035, 1904);
	addChild(spine3);
	obstacleList.push_back(spine3);
}

void GameScene::SetStage2()
{
	Boss2 *e = new Boss2();
	e->pos = Vec2(13490, 620);
	addChild(e);
	enemyList.push_back(e);

	for (int i = 0; i < 8; i++)
	{
		BoomEnemy *e = new BoomEnemy();
		e->pos = Vec2(random(1500, 12000), 500);
		addChild(e);
		enemyList.push_back(e);
	}

	for (int i = 0; i < 10; i++)
	{
		ShooterEnemy *e = new ShooterEnemy();
		e->pos = Vec2(random(1500, 12000), 500);
		addChild(e);
		enemyList.push_back(e);
	}

	backSky = new Sprite("image/map/background/stage2.png");

	for (int i = 0; i < 5; i++)
	{
		Sprite *b = new Sprite("image/map/stage2/map/" + to_string(i) + ".png");
		background.push_back(b);
		b->pos = Vec2(i * 2880, 0);
		addChild(b);
	}

	SavePoint *save = new SavePoint();
	save->pos = Vec2(3903, 1662);
	addChild(save);
	savePointList.push_back(save);

	SavePoint *save2 = new SavePoint();
	save2->pos = Vec2(8777, 1662);
	addChild(save2);
	savePointList.push_back(save2);

	Vec2 spinePos[] = { Vec2(5848, 1860), Vec2(6435, 1860), Vec2(7035, 1860), Vec2(8000, 1860), Vec2(4675, 2244) };

	for (int i = 0; i < 5; i++)
	{
		Obstacle *spine = new Obstacle(SPINE);
		spine->pos = spinePos[i];
		addChild(spine);
		obstacleList.push_back(spine);
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Obstacle *box = new Obstacle(BOX);
			box->pos = Vec2(7516 + (2 * box->rect.width()) - (i * box->rect.width()), 1540 + (2 * (box->rect.height() - 40)) - (j * (box->rect.height() - 40)));
			obstacleList.push_back(box);
			addChild(box);
		}
	}
}

void GameScene::SetUI(Vec2 setPos, string imgPath, Sprite **img)
{
	*img = new Sprite(imgPath);
	(*img)->pos = setPos;
	UIList.push_back(*img);
}

void GameScene::SetUI(Vec2 setPos, string imgPath)
{
	temp = new Sprite(imgPath);
	temp->pos = setPos;
	UIList.push_back(temp);
}