#include "DXUT.h"
#include "ViewRankingScene.h"
#include "World.h"
#include "MainScene.h"

ViewRankingScene::ViewRankingScene(string name, int score) : input("data.txt"), output("data.txt", ios::out | ios::app)
{
	addChild(new Sprite("image/ed/26.tga"));
	addChild(backBtn = new Sprite("image/outgame/ranking/rank.png"));
	backBtn->pos = Vec2(1126, 529);
	this->name = name;
	this->score = score;

	addChild(new Sprite("image/outgame/ranking/rank_2.png"));

	if (name != "")
		output << name << ' ' << score << endl;
	
	output.close();

	for (int i = 0; i < 3; i++)
	{
		addChild(nameText[i] = new Text("", 60, D3DXCOLOR(1, 1, 1, 1)));
		nameText[i]->pos = Vec2(260, 253 + (i * 132));

		addChild(scoreText[i] = new Text("", 60, D3DXCOLOR(1, 1, 1, 1)));
		scoreText[i]->pos = nameText[i]->pos + Vec2(350, 0);
	}

	Rank r;

	while (input >> r.name >> r.score)
	{
		ranks.push_back(r);
	}

	ranks.sort([](Rank r1, Rank r2)
	{
		return r1.score > r2.score;
	});

	int i = 0;
	for_iter(iter, ranks)
	{
		nameText[i]->text = iter->name;
		scoreText[i]->text = to_string(iter->score);
		if (i++ == 2) break;
	}
}

ViewRankingScene::~ViewRankingScene()
{
}

void ViewRankingScene::update(float dt)
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
}