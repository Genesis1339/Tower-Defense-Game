#pragma once

#include "iostream"
#include "raylib.h"

class tower
{

public:

	Vector2 pos;

	float width;
	float height;

	Color color;

	std::string towerName;

	int damage;
	float range;

	int price;
	int sellPrice;

	int upgradePrice;

	int maxLevel;
	int currentLevel;

	bool isTowerSeleceted;

	tower();

	void drawTower();
	void drawRange();

};
