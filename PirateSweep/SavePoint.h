#pragma once
#include "Entity.h"
#include "Animation.h"

class SavePoint : public Entity
{
public:
	SavePoint();
	~SavePoint();

	Animation *a, *b;
	Sprite *saveText;

	int alpha;

	void update(float dt);
	void Save();
};

