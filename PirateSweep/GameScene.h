#pragma once
#include "Scene.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Emitter.h"
#include "Ground.h"
#include "Obstacle.h"
#include "Effect.h"
#include "Text.h"
#include "Item.h"
#include "SavePoint.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	Player *player;
	list<Sprite*> background;
	Timer shakeTimer;
	Ground *ground;
	Sprite *hpBar;
	Sprite *expBar;
	Sprite *bossHpBar;
	Sprite *bossHpBarBack;
	Sprite *weaponBaseUI;
	Sprite *weaponMgunUI;
	Sprite *weaponBzuUI;
	Sprite *stage1ClearText;
	Sprite *stage2ClearText;
	Sprite *infinite;
	Sprite *backSky;

	Sprite *continueScreen;
	Sprite *yesBtn;
	Sprite *noBtn;
	Sprite *temp;

	Text *boomCountText;
	Text *bulletCountText;
	Text *levelText;
	Text *scoreText;

	Animation *shopBox;

	list<Bullet*> bulletList;
	list<Item*> itemList;
	list<Enemy*> enemyList;
	list<Emitter*> effectList;
	list<BoomEffect*> boomEffectList;
	list<Obstacle*> obstacleList;
	list<Sprite*> UIList;
	list<Text*> UITextList;
	list<SavePoint*> savePointList;

	float finishTimer;
	bool isEnd;

	void update(float dt) override;
	void render() override;
	void shake(int n, float amount, float time = 0.05);
	void SetStage1();
	void SetStage2();
	void SetUI(Vec2 setPos, string imgPath, Sprite **img);
	/*{
		*img = new Sprite(imgPath);
		(*img)->pos = setPos;
		UIList.push_back(*img);
	}*/
	void SetUI(Vec2 setPos, string imgPath);
	/*{
		Sprite *img = new Sprite(imgPath);
		img->pos = setPos;
		UIList.push_back(img);
	}*/
};

