#include "enemy.h"

enemy::enemy()
{

	pos.x = 0;
	pos.y = 540;
	height = 50.0f;
	width = 50.0f;
	color = WHITE;
	
	speed = 200.0f;
	currentWaypoint = 0;

	baseHealth = 50;

}

void enemy::drawEnemy()
{

	DrawRectangle(pos.x, pos.y, width, height, color);

}

