#pragma once

#include "iostream"
#include "raylib.h"

class enemy
{

public:

	Vector2 pos;

	float height;
	float width;

	Color color;

	float speed;

	int currentWaypoint;

	int baseHealth;

	enemy();
	void drawEnemy();

};
