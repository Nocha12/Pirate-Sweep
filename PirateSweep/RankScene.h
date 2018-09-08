#pragma once
#include "Scene.h"
#include "Animation.h"
#include "Sprite.h"
#include "Text.h"

class RankScene : public Scene
{
public:
	RankScene();
	~RankScene();

	Animation *ed;

	Sprite *inputName;
	Sprite *rank;
	Sprite *backBtn;

	Text *inputNameText;

	float timer;

	void update(float dt);
};

