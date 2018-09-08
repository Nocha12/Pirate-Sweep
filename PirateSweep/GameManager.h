#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();

	int stage;
	int score;
	bool isBoss;
	float startX;
	int playerLevel;
	bool buyBullet;
	bool buyHp;
	bool buyPower;
};

extern GameManager gameManager;