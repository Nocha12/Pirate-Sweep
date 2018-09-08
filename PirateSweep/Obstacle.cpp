#include "DXUT.h"
#include "Obstacle.h"
#include "GameScene.h"
#include "World.h"
#include "Effect.h"
#include "Item.h"

Obstacle::Obstacle(ObstacleType obstacleType) : obstacleType(obstacleType), hp(100)
{
	if (obstacleType == SPINE)
		sprite = new Sprite("image/map/trip/asdf1.png");
	else if (obstacleType == BOX)
		sprite = new Sprite("image/map/trip/asdf2.png");

	addChild(sprite);
	rect = sprite->rect;
}

Obstacle::~Obstacle()
{
}

void Obstacle::update(float dt)
{
	Entity::update(dt);

	if (hp <= 0 && obstacleType == BOX)
	{
		GameScene *scene = (GameScene*)world.currentScene;
		ExpEffect *eff = new ExpEffect(scene->player);
		eff->pos = center();
		scene->addChild(eff);
		scene->effectList.push_back(eff);

		int randNum = random(0, 20);

		if (randNum <= 3)
		{
			Item *itm = new Item((ItemType)randNum);
			itm->pos = pos;
			scene->itemList.push_back(itm);
			scene->addChild(itm);
		}

		removeChild(this);
		scene->obstacleList.remove(this);
		return;
	}
}