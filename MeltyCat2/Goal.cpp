#include "DxLib.h"
#include "Goal.h"

Goal::Goal(int x, int y, int r) {
	this->x = x;
	this->y = y;
	this->r = r;
}
Goal::~Goal() {}

void Goal::update() {}

void Goal::draw() {
	DrawCircle(x, y, r, GetColor(192, 192, 192), true);
}

int Goal::getX() { return x; }
int Goal::getY() { return y; }
int Goal::getR() { return r; }

void Goal::setX(int x) { this->x = x; }
void Goal::setY(int y) { this->y = y; }
void Goal::setR(int r) { this->r = r; }
