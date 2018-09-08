#include "DXUT.h"
#include "SavePoint.h"
#include "GameManager.h"

SavePoint::SavePoint() : alpha(100)
{
	b = new Animation("image/savepoint/f2", 6, 6, false);
	b->stop = true;
	addChild(b);

	a = new Animation("image/savepoint/f1", 6, 6, false);
	a->stop = true;
	addChild(a);

	saveText = new Sprite("image/outgame/text/saved.png");
	addChild(saveText);
	saveText->visible = false;

	rect = a->rect;
}

SavePoint::~SavePoint()
{
}

void SavePoint::update(float dt)
{
	Entity::update(dt);

	if (!a->stop)
	{
		if (saveText->color.a > 0)
		{
			saveText->visible = true;
			saveText->color.a -= 0.01;
			saveText->pos.y -= 0.05;
		}
		a->color = D3DXCOLOR(1, 1, 1, --alpha / 100.0f);
	}
}

void SavePoint::Save()
{
	a->stop = false;
	b->stop = false;
	gameManager.startX = pos.x;
}
