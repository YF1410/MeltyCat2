#include "DxLib.h"
#include "Cursor.h"

Cursor::Cursor(int x, int y, int r, int putX, int putY, int vector) {
	this->graphic = LoadGraph("graphic/SetBlock.png");
	this->x = x;
	this->y = y;
	this->r = r;
	this->putX = putX;
	this->putY = putY;
	this->vector = vector;
}
Cursor::~Cursor() {}

void Cursor::update(int edgeL,
	char* keys, char* oldkeys,
	int click, int oldclick, Block* block,
	int WIN_WIDTH, int WIN_HEIGHT) {
	drag(edgeL);
	spin(keys, oldkeys);
	put(click, oldclick, block);
}

void Cursor::drag(int edgeL) {
	GetMousePoint(&x, &y);
	putX = (x - edgeL) / 64 * 64 + edgeL + 32;
	putY = y / 64 * 64 + 32;
}

void Cursor::spin(char* keys, char* oldkeys) {
	if (keys[KEY_INPUT_LSHIFT] == 1 && oldkeys[KEY_INPUT_LSHIFT] == 0) {
		vector++;
		if (vector > 3) {/*LU=0,LD=1,RD=2,RU=3*/
			vector = 0;
		}
	}
}

void Cursor::put(int click, int oldclick, Block* block) {
	if ((oldclick & MOUSE_INPUT_LEFT) == 0 && (click & MOUSE_INPUT_LEFT) == 1) {
		block->setX(putX);
		block->setY(putY);
		block->setVector(vector);
		block->setPut(1);
	}
}

void Cursor::draw(int edgeL, int WIN_WIDTH, int WIN_HEIGHT) {
	if (x >= edgeL && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT) {
		DrawBox(putX - 32, putY - 32, putX + 32, putY + 32, GetColor(255, 255, 0), false);
	}/*LU=0,LD=1,RD=2,RU=3*/
	DrawRectRotaGraph(x, y, 64, 0, 64, 64, 1.0, -3.1415 / 2 * vector, graphic, true);
}

int Cursor::getX() { return x; }
int Cursor::getY() { return y; }
int Cursor::getPutX() { return putX; }
int Cursor::getPutY() { return putY; }
int Cursor::getVector() { return vector; }

void Cursor::setX(int x) { this->x = x; }
void Cursor::setY(int y) { this->y = y; }
void Cursor::setPutX(int putX) { this->putX = putX; }
void Cursor::setPutY(int putY) { this->putY = putY; }
void Cursor::setVector(int Vector) { this->vector = vector; }
