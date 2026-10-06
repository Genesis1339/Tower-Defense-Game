#pragma once

#include "iostream"
#include "vector"
#include "string"

#include "raylib.h"

#include "enemy.h"

//#include "tower.h"
#include "gunnerTower.h"
#include "rangerTower.h"


class gameState
{

public:

	std::vector<enemy> enemies;

	std::vector<std::unique_ptr<tower>> towersPlaced;
	bool canPlaceTower;

	std::vector<Vector2> pathWaypoints;

	enum towerType
	{
	
		NONE = 0,
		GUNNER = 1,
		RANGER = 2

	};

	towerType currentTowerType;

	int currentEnemyCount;
	int waveSpawnNo;
	int waveBossSpawnNo;
	int enemiesSpawnedThisWave;
	int bossesSpawnedThisWave;

	int waveCount;
	int finalWaveNo;
	int money;
	int baseHealth;

	bool isGameOver;
	bool isWaveOver;
	bool isFinalWave;

	bool hasMouseClicked;

	gameState();

	void startWave();
	void nextWave();
	void finalWave();

	void drawWaveCount();
	void drawMoney();
	void drawHealth();

	void buyMenu();
	void drawBuyMenu();

	void drawGunnerBuy();
	void drawRangerBuy();

	void spawnEnemy();
	void moveEnemy();
	void enemyDeath();

	void placeTower();

	void drawPath();
	void canPlaceTowerCheck();

	void towerLogic();
	void sellTower();
	void towerAttack();
	void towerSelect();

	void takeDamage();

	void gameOver();


};
