#pragma once
#include "Entity.h"
#include "Enum.h"

class Item : public Entity
{
public:
	Item(ItemType itemType);
	~Item();

	ItemType itemType;
};

