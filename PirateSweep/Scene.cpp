#include "DXUT.h"
#include "Scene.h"
#include "GameManager.h"

Scene::Scene(void)
	:followTarget(nullptr)
{
}


Scene::~Scene(void)
{
}

void Scene::follow(Entity* target, Vec2 offset)
{
	this->followTarget = target;
	this->offset = offset;
}

void Scene::unfollow()
{
	this->followTarget = nullptr;
	this->offset = Vec2(0, 0);
}

void Scene::shake(int n, float range, float duration)
{
	shakeTimer.reset(duration, n, true);
	shakeTimer.onTick = [=]()
	{
		pos = pos + Vec2(random(-range, range), random(-range, range));
	};
}

void Scene::update(float dt)
{
	Entity::update(dt);
	
	if(followTarget)
	{
		if (followTarget->pos.x >= 800 && followTarget->pos.x < 12600)
			pos.x += (-followTarget->center().x + offset.x - pos.x) * 0.15f;

		if (followTarget->pos.x >= 12600)
		{
			gameManager.isBoss = true;
			pos += (Vec2(-12800, -1350) - pos) * 0.15f;
		} else if (followTarget->pos.y <= 2100)
			pos.y += (-followTarget->center().y + offset.y - pos.y) * 0.15f;
	}
}