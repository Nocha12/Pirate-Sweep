#pragma once
#include "Scene.h"
#include "Text.h"
#include "Sprite.h"
#include <fstream>

using namespace std;

struct Rank
{
	string name;
	int score;
};

class ViewRankingScene : public Scene
{
public:
	ViewRankingScene(string name, int score);
	~ViewRankingScene();
	
	void update(float dt) override;

	Text* nameText[3];
	Text* scoreText[3];

	ifstream input;
	ofstream output;

	Sprite *backBtn;

	list<Rank> ranks;
	                                                                                                                                                                                                                                                                                                                                                                                      
	string name;
	int score;
};

