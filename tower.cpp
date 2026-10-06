#include "tower.h"

tower::tower()
{

	pos.x = 0;
	pos.y = 0;

	width = 50.0f;
	height = 50.0f;

	color = DARKGREEN;

	towerName = "tower";

	damage = 5;
	range = 125.0f;
	
	price = 50;
	sellPrice = price / 2;

	upgradePrice = 150;
	
	maxLevel = 5;
	currentLevel = 1;

	isTowerSeleceted = false;

}

void tower::drawTower()
{

	//DrawRectangle(pos.x - (range / 2), pos.y - (range / 2), width + range, height + range, WHITE);
	DrawRectangle(pos.x, pos.y, width, height, color);

}

void tower::drawRange()
{

	DrawRectangle(pos.x - (range / 2), pos.y - (range / 2), width + range, height + range, WHITE);

}
