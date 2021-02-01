#include "StageSelect.h"

StageSelect::StageSelect() {
	LoadDivGraph("graphic/key.png", 2, 2, 1,
		64, 64, key_graphic);
	number = 0;
	pos_x[0] = 40;
	pos_y[0] = 350;
	pos_x[1] = 1166;
	pos_y[1] = 350;
	buckground_x[5];
	buckground_y[5];
}

void StageSelect::update(char A, char D,char space) {
	if (A == true)
	{
		if (number > 0)
		{
			number--;
		}
	}

	if (D == true)
	{
		if (number < 6)
		{
			number++;
		}
	}
}

void StageSelect::draw(){
	for (int i = 0; i < 5; i++)
	{
		DrawGraph(buckground_x[i], buckground_y[i],
			buck_graphic[i], TRUE);
	}
	
	DrawGraph(pos_x[0], pos_y[0],
		key_graphic[0], TRUE);

	DrawGraph(pos_x[1], pos_y[1],
		key_graphic[1], TRUE);
}
