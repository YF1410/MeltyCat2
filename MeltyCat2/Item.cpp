#include "DxLib.h"
#include "Item.h"

Item::Item(int x, int y, int r, int put) {
	this->x = x;
	this->y = y;
	this->r = r;
	this->put = put;
}
Item::~Item() {}

void Item::update() {}

void Item::draw() {
	if (put == 1) {
		DrawCircle(x, y, r, GetColor(112, 112, 255), true);
	}
}

int Item::getX() { return x; }
int Item::getY() { return y; }
int Item::getPut() { return put; }

void Item::setX(int x) { this->x = x; }
void Item::setY(int y) { this->y = y; }
void Item::setPut(int put) { this->put = put; }
