#include "DXUT.h"
#include "MainScene.h"
#include "World.h"
#include "GameScene.h"
#include "ViewRankingScene.h"
#include "GameManager.h"

MainScene::MainScene() : ani(0), isHowTo(false)
{
	Sprite *back = new Sprite("image/outgame/title/title.png");
	addChild(back);

	player = new Sprite("image/outgame/title/char.png");
	player->pos = Vec2(46, 62);
	addChild(player);

	howToPlayBtn = new Sprite("image/outgame/title/buttonselect_howto.png");
	addChild(howToPlayBtn);
	howToPlayBtn->pos = Vec2(756, 463);
	
	playBtn = new Sprite("image/outgame/title/buttonselect_playgame.png");
	addChild(playBtn);
	playBtn->pos = Vec2(811, 392);

	rankingBtn = new Sprite("image/outgame/title/buttonselect_rank.png");
	addChild(rankingBtn);
	rankingBtn->pos = Vec2(891, 550);

	exitBtn = new Sprite("image/outgame/title/buttonselect_exit.png");
	addChild(exitBtn);
	exitBtn->pos = Vec2(977, 628);

	op = new Animation("image/op", 20, 20, false, true);
	op->visible = false;
	addChild(op);
	op->stop = true;

	howTo1 = new Sprite("image/outgame/howto/1.png");
	howTo1->visible = false;
	addChild(howTo1);
	howTo2 = new Sprite("image/outgame/howto/2.png");
	howTo2->visible = false;
	addChild(howTo2);

	addChild(backBtn = new Sprite("image/outgame/howto/undo_button.png"));
	backBtn->visible = false;
	backBtn->pos = Vec2(1126, 529);
}

MainScene::~MainScene()
{
}

void MainScene::update(float dt)
{
	Scene::update(dt);

	gameManager.stage = 1;
	gameManager.score = 0;

	if (!isHowTo)
	{
		player->pos.y = 62 + sinf(ani) * 10;
		ani += dt * 5;

		if (howToPlayBtn->rectWithPos().contains(world.getMousePos()))
		{
			howToPlayBtn->visible = true;
			if (world.getKeyState(VK_LBUTTON) == 1 && op->stop)
			{
				backBtn->visible = true;
				howTo1->visible = true;
				isHowTo = true;
			}
		}
		else
			howToPlayBtn->visible = false;

		if (playBtn->rectWithPos().contains(world.getMousePos()))
		{
			playBtn->visible = true;
			if (world.getKeyState(VK_LBUTTON) == 1 && op->stop)
			{
				op->stop = false;
				op->visible = true;
				op->currentFrame = 0;
			}
		}
		else
			playBtn->visible = false;

		if (rankingBtn->rectWithPos().contains(world.getMousePos()))
		{
			rankingBtn->visible = true;
			if (world.getKeyState(VK_LBUTTON) == 1 && op->stop)
			{
				world.changeScene(new ViewRankingScene("", 0));
				return;
			}
		}
		else
			rankingBtn->visible = false;

		if (exitBtn->rectWithPos().contains(world.getMousePos()))
		{
			exitBtn->visible = true;
			if (world.getKeyState(VK_LBUTTON) == 1 && op->stop)
			{
				exit(0);
				return;
			}
		}
		else
			exitBtn->visible = false;

		if (op->currentFrame == op->textures.size() - 1)
		{
			world.changeScene(new GameScene());
			return;
		}
	}
	else
	{
		if (backBtn->visible && backBtn->rectWithPos().contains(world.getMousePos()))
		{
			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				backBtn->visible = false;
				howTo1->visible = false;
				howTo2->visible = false;
				isHowTo = false;
			}
		}

		if (backBtn->visible && backBtn->rectWithPos().contains(world.getMousePos()))
		{
			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				backBtn->visible = false;
				howTo1->visible = false;
				howTo2->visible = false;
				isHowTo = false;
			}
		}
		if (backBtn->visible && world.getKeyState(VK_LBUTTON) == 1)
		{
			if (howTo2->visible)
			{
				howTo1->visible = true;
				howTo2->visible = false;
			}
			else
			{
				howTo1->visible = false;
				howTo2->visible = true;
			}
		}
	}
}