#include "DXUT.h"
#include "Item.h"
#include "Sprite.h"

Item::Item(ItemType itemType) : itemType(itemType)
{
	Sprite *sprite;

	if (itemType == ITEM_GRENADE)
		sprite = new Sprite("image/item/bomb.png");
	else if (itemType == ITEM_BAZOOKA)
		sprite = new Sprite("image/item/bzu.png");
	else if (itemType == ITEM_MACHINEGUN)
		sprite = new Sprite("image/item/mgun.png");	
	else if (itemType == HP)
		sprite = new Sprite("image/item/hp.png");
	
	rect = sprite->rect;
	addChild(sprite);
}

Item::~Item()
{
}


