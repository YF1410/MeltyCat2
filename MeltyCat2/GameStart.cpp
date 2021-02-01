#include "GameStart.h"

GameStart::GameStart() {
	graphic = LoadGraph("graphic/particle.jpg");
	alive = true;
	flag = true;
	size = 0;
	pos_x = 0;
	pos_y = 0;
}

void GameStart::start(int i) {
	pos_x = rand() % WIN_WIDTH;
	pos_y = rand() % WIN_HEIGHT;
	size = 0.1 + 0.01 * i;
}

void GameStart::update() {
	if (alive == true)
	{
		if (flag == true)
		{
			size += 0.01;
		} else if (flag == false)
		{
			size -= 0.01;
		}

		if (size > 1.5)
		{
			flag = false;
		} else if (size < 0.1)
		{
			flag = true;
		}
	}
}

void GameStart::draw(int i) {
	
	SetDrawBlendMode(DX_BLENDMODE_ADD, 140);
	if (i % 2 == 0)
	{
		SetDrawBright(0, 100, 100);
		DrawRotaGraph(pos_x, pos_y, size, 0, graphic, true);
	} else if (i % 2 == 1)
	{
		//SetDrawBright(200, 0, 200);
		DrawRotaGraph(pos_x, pos_y, size, 0, graphic, true);
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
}

