#pragma once
#include "Block.h"
#include "Object.h"
class Cursor : public Object {
private:
	int putX, putY, vector;
public:
	Cursor(int x, int y, int r, int putX, int putY, int vector);
	~Cursor();

	void update(int edgeL,
		char* keys, char* oldkeys,
		int click, int oldclick, Block* block,
		int WIN_WIDTH, int WIN_HEIGHT);
	void drag(int edgeL);
	void spin(char* keys, char* oldkeys);
	void put(int click, int oldclick, Block* block);
	void draw(int edgeL, int WIN_WIDTH, int WIN_HEIGHT);

	int getX();
	int getY();
	int getPutX();
	int getPutY();
	int getVector();

	void setX(int x);
	void setY(int y);
	void setPutX(int putX);
	void setPutY(int putY);
	void setVector(int Vector);
};

