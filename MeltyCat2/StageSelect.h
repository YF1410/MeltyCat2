#pragma once
#include "DxLib.h"

class StageSelect
{
private:
	int key_graphic[2];
	int buck_graphic[5];
	int number;
	int pos_x[2];//0->A/1->D
	int pos_y[2];
	int buckground_x[5];
	int buckground_y[5];
	
public:
	StageSelect();
	~StageSelect() {};

	void update(char A, char D);
	void draw();

	int getnumber()
	{
		return number;
	}
};

