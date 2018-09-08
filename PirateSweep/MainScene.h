#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	void update(float dt);

	Sprite *playBtn;
	Sprite *howToPlayBtn;
	Sprite *rankingBtn;
	Sprite *exitBtn;
	Sprite *player;

	Sprite *howTo1;
	Sprite *howTo2;
	Sprite *backBtn;

	float ani;
	bool isHowTo;

	Animation *op;
};

