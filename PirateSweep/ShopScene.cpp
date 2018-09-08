#include "DXUT.h"
#include "ShopScene.h"
#include "GameManager.h"
#include "World.h"
#include "GameScene.h"

ShopScene::ShopScene()
{
	Sprite *back = new Sprite("image/outgame/shop/shopframe.png");
	addChild(back);
	
	nextBtn = new Sprite("image/outgame/shop/next.png");
	nextBtn->pos = Vec2(936, 615);
	addChild(nextBtn);

	buyBtn = new Sprite("image/outgame/shop/buy_button.png");
	buyBtn->pos = Vec2(887, 460);
	addChild(buyBtn);

	select = new Sprite("image/outgame/shop/select_frame.png");
	select->pos = Vec2(185, 141);
	addChild(select);

	bullet = new Sprite("image/outgame/shop/bullet.png");
	bullet->pos = Vec2(202, 159);
	addChild(bullet);
	bulletEx = new Sprite("image/outgame/shop/bullet_ex.png");
	bulletEx->pos = Vec2(217, 496);
	addChild(bulletEx);

	power = new Sprite("image/outgame/shop/power.png");
	power->pos = Vec2(530, 159);
	addChild(power);
	powerEx = new Sprite("image/outgame/shop/power_ex.png");
	powerEx->pos = Vec2(217, 496);
	addChild(powerEx);
	powerEx->visible = false;

	hp = new Sprite("image/outgame/shop/hp.png");
	hp->pos = Vec2(857, 159);
	addChild(hp);
	hpEx = new Sprite("image/outgame/shop/hp_ex.png");
	hpEx->pos = Vec2(217, 496);
	addChild(hpEx);
	hpEx->visible = false;

	scoreText = new Text(to_string(gameManager.score), 30, D3DXCOLOR(1, 1, 1, 1));
	scoreText->pos = Vec2(1038, 60);
	addChild(scoreText);
	for (int i = 0; i < 3; ++i)
		buy[i] = false;
}

ShopScene::~ShopScene()
{
}

void ShopScene::update(float dt)
{
	Scene::update(dt);

	if (buyBtn->rectWithPos().contains(world.getMousePos()))
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			if (select->pos == Vec2(185, 141) && gameManager.score >= 1000)
			{
				buy[0] = true;
				gameManager.buyBullet = true;
				scoreText->text = to_string(gameManager.score -= 1000);

				if (!buy[1])
				{
					select->pos = Vec2(513, 141);
					powerEx->visible = false;
					hpEx->visible = false;
					bulletEx->visible = true;
				}
				else if (!buy[2])
				{
					select->pos = Vec2(840, 141);
					powerEx->visible = false;
					hpEx->visible = true;
					bulletEx->visible = false;
				}
				else
				{
					select->visible = false;
					Vec2(0, 0);
				}
			}
			else if (select->pos == Vec2(513, 141) && gameManager.score >= 1000)
			{
				buy[1] = true;
				gameManager.buyPower = true;
				scoreText->text = to_string(gameManager.score -= 1000);

				if (!buy[0])
				{
					select->pos = Vec2(185, 141);
					powerEx->visible = false;
					hpEx->visible = false;
					bulletEx->visible = true;
				}
				else if (!buy[2])
				{
					select->pos = Vec2(840, 141);
					powerEx->visible = false;
					hpEx->visible = true;
					bulletEx->visible = false;
				}
				else
				{
					select->visible = false;
					Vec2(0, 0);
				}
			}
			else if (select->pos == Vec2(840, 141) && gameManager.score >= 1000)
			{
				buy[2] = true;
				gameManager.buyHp = true;
				scoreText->text = to_string(gameManager.score -= 1000);

				if (!buy[0])
				{
					select->pos = Vec2(185, 141);
					powerEx->visible = false;
					hpEx->visible = false;
					bulletEx->visible = true;
				}
				else if (!buy[1])
				{
					select->pos = Vec2(513, 141);
					powerEx->visible = false;
					hpEx->visible = true;
					bulletEx->visible = false;
				}
				else
				{
					select->visible = false;
					Vec2(0, 0);
				}
			}
		}
	}

	if (bullet->rectWithPos().contains(world.getMousePos()) && !buy[0])
	{
		select->pos = Vec2(185, 141);

		powerEx->visible = false;
		hpEx->visible = false;
		bulletEx->visible = true;
	}

	if (power->rectWithPos().contains(world.getMousePos()) && !buy[1])
	{
		select->pos = Vec2(513, 141);

		powerEx->visible = true;
		hpEx->visible = false;
		bulletEx->visible = false;
	}
	if (hp->rectWithPos().contains(world.getMousePos()) && !buy[2])
	{
		select->pos = Vec2(840, 141);

		powerEx->visible = false;
		hpEx->visible = true;
		bulletEx->visible = false;
	}

	if (nextBtn->rectWithPos().contains(world.getMousePos()))
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			gameManager.isBoss = false;
			gameManager.stage = 2;
			world.changeScene(new GameScene());
		}
	}
}