#include "DxLib.h"
#include "Item.h"

Item::Item(int x, int y, int r, int put) {
	this->graphic = LoadGraph("graphic/SetBlock.png");
	this->x = x;
	this->y = y;
	this->r = r;
	this->put = put;
}
Item::~Item() {}

void Item::update() {}

void Item::draw() {
	if (put == 1) {
		DrawRectGraph(x - 32, y - 32, 0, 0, 64, 64, graphic, true);
	}
}

int Item::getX() { return x; }
int Item::getY() { return y; }
int Item::getPut() { return put; }

void Item::setX(int x) { this->x = x; }
void Item::setY(int y) { this->y = y; }
void Item::setPut(int put) { this->put = put; }
