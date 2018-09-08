#pragma once
#include "Entity.h"
#include "Sprite.h"
class Ground :
	public Entity
{
public:
	Ground();
	~Ground();

	int* map;
	int mapWidth;
	Sprite *hitMap[5];

	bool GetBit(int x, int y);
	void SetBit(int x, int y, bool b);
	void InitMap(Sprite* img[]);
};

