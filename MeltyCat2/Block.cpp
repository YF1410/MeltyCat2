#include "DxLib.h"
#include "Block.h"

Block::Block(int x, int y, int r, int put, int vector) {
	this->graphic = LoadGraph("graphic/SetBlock.png");
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
		DrawRectRotaGraph(x, y, 64, 0, 64, 64, 1.0, -3.1415 / 2 * vector, graphic, true);
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
