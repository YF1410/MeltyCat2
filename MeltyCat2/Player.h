#pragma once
#include "Block.h"
#include "Goal.h"
#include "Item.h"
#include "Object.h"
class Player : public Object {
private:
	int moveX, moveY, state;
public:
	Player(int x, int y, int r, int moveX, int moveY, int state);
	~Player();

	void update(int edgeL, int WIN_WIDTH, int WIN_HEIGHT, Block* block, Item* item);
	void move(int edgeL, int WIN_WIDTH, int WIN_HEIGHT);
	void arrive(Goal* goal, int edgeL, Player* player);
	void turn(Block* block);
	void change(Item* item, int edgeL);
	void draw();

	int getX();
	int getY();
	int getR();
	int getMoveX();
	int getMoveY();
	int getState();

	void setX(int x);
	void setY(int y);
	void setR(int r);
	void setMoveX(int moveX);
	void setMoveY(int moveY);
	void setState(int state);
};
