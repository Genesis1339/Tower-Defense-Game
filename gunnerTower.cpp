#include "gunnerTower.h"

gunnerTower::gunnerTower()
{

	pos.x = 0;
	pos.y = 0;

	width = 50.0f;
	height = 50.0f;

	color = BLUE;

	towerName = "gunner";

	damage = 5;
	range = 125.0f;

	price = 25;
	sellPrice = price / 2;

	upgradePrice = 100;

	isTowerSeleceted = false;

}
