#include "DXUT.h"
#include "GameManager.h"

GameManager::GameManager() : stage(1), isBoss(false), score(0), startX(300), playerLevel(1), buyBullet(false), buyHp(false), buyPower(false)
{
}

GameManager::~GameManager()
{
}

GameManager gameManager;