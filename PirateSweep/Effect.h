#pragma once
#include "Emitter.h"
#include "Player.h"
#include "Entity.h"
#include "Enum.h"
#include "Animation.h"

class ExpEffect : public Emitter
{
public:
	ExpEffect(Player *player);
	~ExpEffect();

	Player *player;

	void update(float dt) override;
};

class BulletEffect : public Emitter
{
public:
	BulletEffect(EffectType effectType);
	~BulletEffect();
};

class BoomEffect : public Entity
{
public:
	BoomEffect(EffectType effectType);
	~BoomEffect();

	Animation *animation;
};


