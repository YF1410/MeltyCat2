#include "DxLib.h"
#include "Block.h"

Block::Block(int x, int y, int r, int put, int vector) {
	this->x = x;
	this->y = y;
	this->r = r;
	this->put = put;
	this->vector = vector;
}
Block::~Block() {}

void Block::update() {}

void Block::draw() {
	if (put == 1) {/*LU=0,LD=1,RD=2,RU=3*/
		switch (vector) {
		case 0:
			DrawTriangle(x - r, y + r, x + r, y - r, x + r, y + r, GetColor(192, 255, 192), true);
			break;

		case 1:
			DrawTriangle(x - r, y - r, x + r, y + r, x + r, y - r, GetColor(192, 255, 192), true);
			break;

		case 2:
			DrawTriangle(x + r, y - r, x - r, y + r, x - r, y - r, GetColor(192, 255, 192), true);
			break;

		case 3:
			DrawTriangle(x + r, y + r, x - r, y - r, x - r, y + r, GetColor(192, 255, 192), true);
			break;
		}
	}
}

int Block::getX() { return x; }
int Block::getY() { return y; }
int Block::getPut() { return put; }
int Block::getVector() { return vector; }

void Block::setX(int x) { this->x = x; }
void Block::setY(int y) { this->y = y; }
void Block::setPut(int put) { this->put = put; }
void Block::setVector(int vector) { this->vector = vector; }
