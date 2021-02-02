#pragma once
#include "Object.h"
class Block : public Object {
private:
	int vector;
public:
	Block(int x, int y, int r, int put, int vector);
	~Block();

	void update();
	void draw();

	int getX();
	int getY();
	int getPut();
	int getVector();

	void setX(int x);
	void setY(int y);
	void setPut(int put);
	void setVector(int vector);
};

