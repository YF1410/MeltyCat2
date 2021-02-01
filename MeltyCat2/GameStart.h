#pragma once
#include "DxLib.h"
#include <ctime>
#include <cstdlib>

extern const int WIN_WIDTH;
extern const int WIN_HEIGHT;

class GameStart
{
private:
	int graphic;
	char alive;
	char flag;
	float size;
	float pos_x;
	float pos_y;

public:
	GameStart();
	~GameStart() {};

	void start(int i);
	void update();
	void draw(int i);
};

