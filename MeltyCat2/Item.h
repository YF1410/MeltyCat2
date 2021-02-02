#pragma once
#include "Object.h"
class Item : public Object {
private:

public:
	Item(int x, int y, int r, int put);
	~Item();

	void update();
	void draw();

	int getX();
	int getY();
	int getPut();

	void setX(int x);
	void setY(int y);
	void setPut(int put);
};

