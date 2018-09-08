#include "DXUT.h"
#include "Ground.h"
#include "GameManager.h"

Ground::Ground()
{
	for (int i = 0; i < 5; i++)
	{
		if (gameManager.stage == 1)
			hitMap[i] = new Sprite("image/map/stage1/asdf/" + to_string(i) + ".png");
		else 
			hitMap[i] = new Sprite("image/map/stage2/adsf2/" + to_string(i) + ".png");
		addChild(hitMap[i]);
	}

	InitMap(hitMap);
}

Ground::~Ground()
{
	SAFE_DELETE(map);
}

void Ground::InitMap(Sprite* img[])
{
	DWORD* data;
	D3DLOCKED_RECT lockRect;
	LPDIRECT3DSURFACE9 surface;

	const int x = 14400;
	const int y = 3500;
	int totalBit = x * y;
	map = new int[(totalBit / 32) + ((totalBit % 32 > 0) ? 1 : 0)];
	mapWidth = x;

	memset(map, 0, sizeof(int)* (totalBit / 32 + ((totalBit % 32 > 0) ? 1 : 0)));

	for (int divided = 0; divided < 5; divided++)
	{
		img[divided]->texture->d3dTexture->GetSurfaceLevel(0, &surface);
		surface->LockRect(&lockRect, 0, 0);
		data = (DWORD*)lockRect.pBits;

		for (int i = 0; i < y; i++){
			for (int j = 0; j < 2880; j++){
				int index = i * lockRect.Pitch / 4 + j;
				if (data[index] <= D3DCOLOR_XRGB(10, 10, 10))
					SetBit(j + (2880 * divided), i, 1);
			}
		}

		surface->UnlockRect();
		SAFE_RELEASE(surface);
	} 
}

bool Ground::GetBit(int x, int y) {
	int pitch = y * mapWidth + x;
	return map[pitch / 32] & (1 << (pitch % 32));
}

void Ground::SetBit(int x, int y, bool b) { 
	if (GetBit(x, y) == b) return;
	int pitch = y * mapWidth + x;
	map[pitch / 32] ^= (1 << (pitch % 32));
}