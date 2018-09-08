#include "DXUT.h"
#include "RankScene.h"
#include "MainScene.h"
#include "World.h"
#include "GameManager.h"
#include "ViewRankingScene.h"

RankScene::RankScene() : timer(0)
{
	addChild(ed = new Animation("image/ed", 26, 12, false));
	addChild(inputName = new Sprite("image/outgame/ranking/rank_1.png"));
	inputName->visible = false;
	addChild(inputNameText = new Text("", 80, D3DXCOLOR(1, 1, 1, 1)));
	inputNameText->visible = false;
	inputNameText->pos = Vec2(372, 412);
	addChild(backBtn = new Sprite("image/outgame/ranking/rank.png"));
	backBtn->visible = false; 
	backBtn->pos = Vec2(1126, 529);
}

RankScene::~RankScene()
{
}

void RankScene::update(float dt)
{
	Scene::update(dt);

	if (backBtn->visible && backBtn->rectWithPos().contains(world.getMousePos()))
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			world.changeScene(new MainScene());
			return;
		}
	}

	if (ed->currentFrame == ed->textures.size() - 1)
	{
		if(timer > 0.5f)
		{
			inputName->visible = true;
			inputNameText->visible = true;
			backBtn->visible = true;
		}
		timer += dt;
	}

	for (int i = 0; i < 256; ++i)
	{
		if (world.getKeyState(i) == 1)
		{
			if (i == VK_BACK)
			{
				if (inputNameText->text.size() > 0)
					inputNameText->text.pop_back();
			}
			else if (inputNameText->text.length() < 5)
			{
				inputNameText->text += MapVirtualKey(i, 2);
			}
		}
	}

	if (world.getKeyState(VK_RETURN) == 1)
	{
		if (inputNameText->text != "")
		{
			world.changeScene(new ViewRankingScene(inputNameText->text, gameManager.score));
			return;
		}
	}
}
