#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Text.h"

class ShopScene : public Scene
{
public:
	ShopScene();
	~ShopScene();

	Sprite *bullet;
	Sprite *hp; 
	Sprite *power;

	Sprite *bulletEx;
	Sprite *hpEx;
	Sprite *powerEx;

	Sprite *select;
	Sprite *nextBtn;
	Sprite *buyBtn;

	Text *scoreText;

	bool buy[3];

	void update(float dt);
};

