#include "rangerTower.h"

rangerTower::rangerTower()
{

	pos.x = 0;
	pos.y = 0;

	width = 50.0f;
	height = 50.0f;

	color = PURPLE;

	towerName = "ranger";

	damage = 2;
	range = 250.0f;

	price = 75;
	sellPrice = price / 2;

	isTowerSeleceted = false;

}
