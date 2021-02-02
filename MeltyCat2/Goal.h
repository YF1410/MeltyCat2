#pragma once
#include "Object.h"
class Goal : public Object {
private:

public:
	Goal(int x, int y, int r);
	~Goal();

	void update();
	void draw();

	int getX();
	int getY();
	int getR();

	void setX(int x);
	void setY(int y);
	void setR(int r);
};
