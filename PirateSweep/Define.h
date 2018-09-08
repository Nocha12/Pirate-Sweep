#pragma once
#pragma warning(disable:4244 4800)
#include "DXUT.h"

#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace std::tr2::sys;

#define Vec2(x,y) D3DXVECTOR2((x),(y))
typedef D3DXVECTOR2 Vec2;

#define for_iter(iter, collection) for(auto iter = collection.begin(); iter != collection.end(); iter++)

class Rect:public RECT
{
public:
	Rect()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	Rect(int left, int top, int right, int bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	bool intersects(Rect r, Rect* intersection = nullptr)
	{
		return IntersectRect(intersection, this, &r);
	}

	bool contains(Vec2 pos)
	{
		return pos.y >= top && pos.y <= bottom && pos.x >=  left && pos.x <= right;
	}

	int width()
	{
		return right - left;
	}

	int height()
	{
		return bottom - top;
	}

	Vec2 center()
	{
		return Vec2(width(), height())/2;
	}

	Rect offset(Vec2 pos)
	{
		Rect r = *this;
		r.left += pos.x;
		r.right += pos.x;
		r.top += pos.y;
		r.bottom += pos.y;
		return r;
	}
};

inline float angle(Vec2 p1, Vec2 p2)
{
	return atan2(p2.y-p1.y, p2.x-p1.x);
}

inline int random(int from, int to)
{
	static default_random_engine random(timeGetTime());
	uniform_int_distribution<int> d(from, to);
	return d(random);
}

inline float random(float from, float to)
{
	static default_random_engine random(timeGetTime());
	uniform_real_distribution<float> d(from, to);
	return d(random);
}

inline float clamp(float value, float max)
{
	return (value > max)?max:value;
}

inline float calDistance(Vec2 a, Vec2 b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

inline float getLength(Vec2 p1, Vec2 p2)
{
	return sqrtf((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

inline bool collision(Vec2 p1, Vec2 p2, float radius)
{
	return getLength(p1, p2) <= radius;
}

inline void ResizeRect(Rect *r, int number)
{
	r->left += number;
	r->top += number;
	r->right -= number;
	r->bottom -= number;
}

enum class Direction : int
{
	TOP,
	LEFT,
	RIGHT,
	BOTTOM
};