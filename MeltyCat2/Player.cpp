#include "DxLib.h"
#include "Player.h"

Player::Player(int x, int y, int r, int moveX, int moveY, int state) {
	this->graphic = LoadGraph("graphic/cat.png");
	this->graphic2 = LoadGraph("graphic/cat2.png");
	this->x = x;
	this->y = y;
	this->r = r;
	this->moveX = moveX;
	this->moveY = moveY;
	this->state = state;
}
Player::~Player() {}

void Player::update(int edgeL, int WIN_WIDTH, int WIN_HEIGHT, Block* block, Item* item) {
	move(edgeL, WIN_WIDTH, WIN_HEIGHT);
	turn(block);
	change(item, edgeL);
}

void Player::move(int edgeL, int WIN_WIDTH, int WIN_HEIGHT) {
	x += moveX;
	y += moveY;
	if (x < edgeL + r || x > WIN_WIDTH - r) {
		moveX = -moveX;
	}
	if (y < 0 + r || y > WIN_HEIGHT - r) {
		moveY = -moveY;
	}
}

//void Player::arrive(Goal* goal, int edgeL, Player* player) {
//	if ((x - edgeL) / 64 == (goal->getX() - edgeL) / 64 && y / 64 == goal->getY() / 64) {
//		delete player;
////		Player()
//	}
//}

void Player::turn(Block* block) {/*LU=0,LD=1,RD=2,RU=3*/
	if (x == block->getX() && y == block->getY() && moveX > 0) {
		if (block->getVector() == 0) {
			moveX = 0;
			moveY = -2;
		} else if (block->getVector() == 1) {
			moveX = 0;
			moveY = 2;
		}
	} else if (x == block->getX() && y == block->getY() && moveX < 0) {
		if (block->getVector() == 3) {
			moveX = 0;
			moveY = -2;
		} else if (block->getVector() == 2) {
			moveX = 0;
			moveY = 2;
		}
	} else if (x == block->getX() && y == block->getY() && moveY > 0) {
		if (block->getVector() == 0) {
			moveX = -2;
			moveY = 0;
		} else if (block->getVector() == 3) {
			moveX = 2;
			moveY = 0;
		}
	} else if (x == block->getX() && y == block->getY() && moveY < 0) {
		if (block->getVector() == 1) {
			moveX = -2;
			moveY = 0;
		} else if (block->getVector() == 2) {
			moveX = 2;
			moveY = 0;
		}
	}
}

void Player::change(Item* item, int edgeL) {
	if (item->getPut() == 1 && (x - edgeL) / 64 == (item->getX() - edgeL) / 64 && y / 64 == item->getY() / 64) {
		item->setPut(0);
		state++;
		if (state > 1/*LIQUID*/) {
			state = 0/*SOLID*/;
		}
	}
}

void Player::draw() {
	//if (state == 0/*SOLID*/) {
	//	DrawCircle(x, y, r, GetColor(255, 255, 128), true);
	//} else if (state == 1/*LIQUID*/) {
	//	DrawCircle(x, y, r, GetColor(128, 128, 255), true);
	//}
	if (moveY != 0) {
		DrawGraph(x - r, y - r, graphic, true);
	}
	else if (moveX > 0) {
		DrawGraph(x - r, y - r, graphic2, true);
	}
	else if (moveX < 0) {
		DrawRotaGraph(x, y, 1, 0, graphic2, true, true);
	}
}

int Player::getX() { return x; }
int Player::getY() { return y; }
int Player::getR() { return r; }
int Player::getMoveX() { return moveX; }
int Player::getMoveY() { return moveY; }
int Player::getState() { return state; }

void Player::setX(int x) { this->x = x; }
void Player::setY(int y) { this->y = y; }
void Player::setR(int r) { this->r = r; }
void Player::setMoveX(int moveX) { this->moveX = moveX; }
void Player::setMoveY(int moveY) { this->moveY = moveY; }
void Player::setState(int state) { this->state = state; }
