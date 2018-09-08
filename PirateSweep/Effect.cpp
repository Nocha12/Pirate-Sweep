#include "DXUT.h"
#include "Effect.h"
#include "Define.h"

ExpEffect::ExpEffect(Player *player) : Emitter("image/effect/exp/0.png", false, true), player(player)
{
	color(D3DXCOLOR(1, 1, 1, 1), D3DXCOLOR(1, 1, 1, 0));
	scale(0.8f, 1);
	rotationOffset = D3DXToRadian(-105);
	rotation(D3DXToRadian(00), D3DXToRadian(30));
	speed(800, 1600);
	lifeTime(10000, 100000);
	start(0, 15, 2);
	spritePath.push_back("image/effect/exp/1.png");
	spritePath.push_back("image/effect/exp/2.png");
}

ExpEffect::~ExpEffect()
{
}

void ExpEffect::update(float dt)
{
	Emitter::update(dt);

	for_iter(iter, particles)
	{
		float distance = calDistance(pos + iter->sprite->center(), player->center());
		
		if (distance < 2000 && iter->isFollowPlayer)
		{
			float dir = angle(player->center(), pos + iter->sprite->center());
			iter->sprite->pos -= Vec2(cos(dir), sin(dir)) * 2000 * dt;
			iter->isFollowing = true;
			if (distance < 50) // Exp Áõ°¡
			{
				++player->exp;
				removeChild(iter->sprite);
				iter = particles.erase(iter);
				if (iter == particles.end())
					break;
			}
		}
	}
}

BulletEffect::BulletEffect(EffectType effectType) : Emitter("", true, false)
{
	spritePath.clear();

	if(effectType == PLAYER_BULLET)
		spritePath.push_back("image/effect/player/bullet/0.png");
	else if (effectType == MOB_BULLET)
		spritePath.push_back("image/effect/mob/mob 2, 4/0.png");

	color(D3DXCOLOR(1, 1, 1, 1), D3DXCOLOR(1, 1, 1, 0));
	scale(0.8f, 1);
	rotation(D3DXToRadian(00), D3DXToRadian(30));
	speed(100, 200);
	lifeTime(0.5f, 1);
	start(0, 15, 2);
}

BulletEffect::~BulletEffect()
{

}

BoomEffect::BoomEffect(EffectType effectType)
{
	if (effectType == PLAYER_BOOM)
	{
		animation = new Animation("image/effect/player/bzu", 20, 20, false);
	}
	else if (effectType == MOB_BOOM)
	{
		animation = new Animation("image/effect/mob/mob 1, 3", 20, 20, false);
	}
	else if (effectType == BOSS)
	{
		animation = new Animation("image/effect/boss/bullet", 20, 20, false);
	}
	else if (effectType == BOSS_BOOM)
	{
		animation = new Animation("image/effect/boss/bomb", 20, 20, false);
	}

	addChild(animation);
}

BoomEffect::~BoomEffect()
{

}