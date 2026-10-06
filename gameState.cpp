#include "gameState.h"

gameState::gameState()
{

	canPlaceTower = true;

	pathWaypoints = { {500, 540}, {500, 300}, {800, 300}, {800, 700}, {1100, 700}, {1100, 500}, {1720, 500}};

	currentTowerType = towerType::NONE;

	currentEnemyCount = 0;
	waveSpawnNo = 20;
	waveBossSpawnNo = 1;
	enemiesSpawnedThisWave = 0;
	bossesSpawnedThisWave = 0;

	waveCount = 1;
	finalWaveNo = 5;
	money = 100;
	baseHealth = 500;

	isGameOver = false;
	isWaveOver = false;
	isFinalWave = false;

	hasMouseClicked = false;

}

void gameState::startWave()
{

	drawWaveCount();
	drawMoney();
	drawHealth();

	drawPath();
	placeTower();

	spawnEnemy();

}

void gameState::nextWave()
{

	if (isWaveOver == true && baseHealth > 0)
	{

		waveSpawnNo += 1;
		waveCount += 1;

		enemiesSpawnedThisWave = 0;
		currentEnemyCount = 0;

		isWaveOver = false;
		spawnEnemy();

	}

}

void gameState::finalWave()
{

	if (isFinalWave == true)
	{

	
		if (bossesSpawnedThisWave < waveBossSpawnNo && currentEnemyCount <= 0)
		{

			currentEnemyCount += 1;

			enemy bossEnemy;

			bossEnemy.pos.x = 50;
			bossEnemy.pos.y = 540;

			bossEnemy.height = 75.0f;
			bossEnemy.width = 75.0f;

			bossEnemy.color = RED;

			bossEnemy.baseHealth = 200;

			enemies.push_back(bossEnemy);
			

			bossesSpawnedThisWave += 1;

		}

		if (currentEnemyCount <= 0)
		{
			isGameOver = true;
		}

	}

}

void gameState::drawWaveCount()
{

	std::string waveString = std::to_string(waveCount);

	DrawText(waveString.c_str(), 1000, 25, 50, RAYWHITE);

}

void gameState::drawMoney()
{

	std::string moneyString = std::to_string(money);

	DrawText(moneyString.c_str(), 25, 25, 50, GOLD);

}

void gameState::drawHealth()
{

	std::string healthString = std::to_string(baseHealth);

	DrawText(healthString.c_str(), 125, 25, 50, RED);

}

void gameState::buyMenu()
{

	drawBuyMenu();
	
	drawGunnerBuy();
	drawRangerBuy();

}

void gameState::drawBuyMenu()
{

	DrawRectangle(1720, 0, 200, 1080, DARKGRAY);

}

void gameState::drawGunnerBuy()
{

	Vector2 gunnerBuyPosition;
	gunnerBuyPosition.x = 1770;
	gunnerBuyPosition.y = 25;
	int gunnerBuyWidth = 100;
	int gunnerBuyHeight = 100;

	DrawRectangle(gunnerBuyPosition.x, gunnerBuyPosition.y, gunnerBuyWidth, gunnerBuyHeight, GRAY);
	DrawText("GUNNER", gunnerBuyPosition.x + (gunnerBuyWidth / 4) - 20, gunnerBuyPosition.y + (gunnerBuyHeight / 2), 20, BLACK);

	DrawText("25", gunnerBuyPosition.x + (gunnerBuyWidth / 4) - 20 + 40, gunnerBuyPosition.y + (gunnerBuyHeight / 2) + 50, 20, GOLD);


	if (CheckCollisionPointRec(GetMousePosition(), { gunnerBuyPosition.x, gunnerBuyPosition.y, (float)gunnerBuyWidth, (float)gunnerBuyHeight }))
	{

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{

			currentTowerType = towerType::GUNNER;

		}
	}	

}

void gameState::drawRangerBuy()
{

	Vector2 rangerBuyPosition;
	rangerBuyPosition.x = 1770;
	rangerBuyPosition.y = 150;
	int rangerBuyWidth = 100;
	int rangerBuyHeight = 100;

	DrawRectangle(rangerBuyPosition.x, rangerBuyPosition.y, rangerBuyWidth, rangerBuyHeight, GRAY);
	DrawText("RANGER", rangerBuyPosition.x + (rangerBuyWidth / 4) - 20, rangerBuyPosition.y + (rangerBuyHeight / 2), 20, BLACK);

	DrawText("75", rangerBuyPosition.x + (rangerBuyWidth / 4) - 20 + 40, rangerBuyPosition.y + (rangerBuyHeight / 2) + 50, 20, GOLD);

	if (CheckCollisionPointRec(GetMousePosition(), { rangerBuyPosition.x, rangerBuyPosition.y, (float)rangerBuyWidth, (float)rangerBuyHeight }))
	{

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{

			currentTowerType = towerType::RANGER;

		}
	}

}

void gameState::spawnEnemy()
{

	while (enemiesSpawnedThisWave < waveSpawnNo)
	{
		enemy newEnemy;

		bool isEnemyPosValid = true;

		newEnemy.pos.x = 0;
		newEnemy.pos.y = 540;

		newEnemy.baseHealth += 5 * waveCount;

		for (auto& enemy : enemies)
		{

			float distance = abs(newEnemy.pos.x - enemy.pos.x);

			if (distance < 100)
			{

				isEnemyPosValid = false;
				break;

			}

		}

		if (isEnemyPosValid)
		{
			enemies.push_back(newEnemy);

			currentEnemyCount += 1;
			enemiesSpawnedThisWave += 1;

		}
		else
		{
			break;
		}

	}

	for (auto& enemy : enemies)
	{
		enemy.drawEnemy();
	}

	if (waveCount == finalWaveNo && enemiesSpawnedThisWave == waveSpawnNo)
	{

		isFinalWave = true;

	}

}

void gameState::moveEnemy()
{
	for (auto& enemy : enemies)
	{

        Vector2 target = pathWaypoints[enemy.currentWaypoint];

        Vector2 direction = {
            target.x - enemy.pos.x,
            target.y - enemy.pos.y
        };

        float distance = sqrtf(
            direction.x * direction.x +
            direction.y * direction.y
        );

        if (distance < 1.0f)
        {
            enemy.pos.x = target.x;
			enemy.pos.y = target.y;


            if (enemy.currentWaypoint < pathWaypoints.size() -1)
            {
                enemy.currentWaypoint++;
            }

			continue;
        }

		direction.x /= distance;
		direction.y /= distance;

        enemy.pos.x += direction.x * enemy.speed * GetFrameTime();
        enemy.pos.y += direction.y * enemy.speed * GetFrameTime();


	}

}

void gameState::enemyDeath()
{

	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](const enemy& enemy)
		{

			if (enemy.baseHealth <= 0)
			{
				currentEnemyCount--;
				money += 5;
				return true;
			}
				
			else
				return false;

		}),
		enemies.end());


	if (currentEnemyCount <= 0 && enemiesSpawnedThisWave >= waveSpawnNo && isFinalWave == false)
	{

		isWaveOver = true;
		nextWave();

	}

}


void gameState::placeTower()
{

	canPlaceTowerCheck();

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && canPlaceTower == true && hasMouseClicked == false)
	{
		
		// creates a unique pointer of type tower* 
		// Later it'll allow you to point directly to the child class and use the overridden variables and methods instead 
		// for example std::unique_ptr<tower> newTower = std::make_unique<rangerTower>(); -- Which'll later allow you to acces the variables and methods of this child class instead of others which'll mean different children class can be in the same vector
		//std::unique_ptr<tower> newTower = std::make_unique<tower>();

		if (currentTowerType == towerType::NONE)
		{

			

		}

		if (currentTowerType == towerType::GUNNER)
		{
			std::unique_ptr<tower> newTower = std::make_unique<gunnerTower>();

			if (money >= newTower->price)
			{
				Vector2 mousePos;
				mousePos.x = GetMouseX();
				mousePos.y = GetMouseY();

				newTower->pos.x = mousePos.x - (newTower->width / 2);
				newTower->pos.y = mousePos.y - (newTower->height / 2);

				money -= newTower->price;

				// Transfers ownership of the pointer to the vector. Allows you to make a tower temp and then transfer its ownership to the vector.

				towersPlaced.push_back(std::move(newTower));

			}
		}
		if (currentTowerType == towerType::RANGER)
		{
			std::unique_ptr<tower> newTower = std::make_unique<rangerTower>();

			if (money >= newTower->price)
			{
				Vector2 mousePos;
				mousePos.x = GetMouseX();
				mousePos.y = GetMouseY();

				newTower->pos.x = mousePos.x - (newTower->width / 2);
				newTower->pos.y = mousePos.y - (newTower->height / 2);

				money -= newTower->price;

				towersPlaced.push_back(std::move(newTower));

			}
		}


	}

	for (auto& tower : towersPlaced)
	{

		tower->drawTower();

	}

}


void gameState::drawPath()
{

	DrawRectangle(0, 515, 525, 100, BROWN);
	DrawRectangle(475, 300, 100, 315, BROWN);
	DrawRectangle(475, 285, 350, 115, BROWN);
	DrawRectangle(785, 285, 100, 450, BROWN);
	DrawRectangle(785, 675, 375, 100, BROWN);
	DrawRectangle(1075, 475, 100, 300, BROWN);
	DrawRectangle(1075, 475, 645, 100, BROWN);


}

void gameState::canPlaceTowerCheck()
{

	canPlaceTower = true;

	if (CheckCollisionPointRec(GetMousePosition(), { 0, 515, 525, 100 }))
		canPlaceTower = false;
	else if (CheckCollisionPointRec(GetMousePosition(), { 475, 300, 100, 315 }))
		canPlaceTower = false;
	else if (CheckCollisionPointRec(GetMousePosition(), { 475, 285, 350, 115 }))
		canPlaceTower = false;
	else if (CheckCollisionPointRec(GetMousePosition(), { 785, 285, 100, 450 }))
		canPlaceTower = false;
	else if (CheckCollisionPointRec(GetMousePosition(), { 785, 675, 375, 100 }))
		canPlaceTower = false;
	else if (CheckCollisionPointRec(GetMousePosition(), { 1075, 475, 100, 300 }))
		canPlaceTower = false;
	else if (CheckCollisionPointRec(GetMousePosition(), { 1075, 475, 645, 100 }))
		canPlaceTower = false;
	else if (CheckCollisionPointRec(GetMousePosition(), { 1720, 0, 200, 1080 }))
		canPlaceTower = false;

	for (auto& tower : towersPlaced)
	{

		if (tower->isTowerSeleceted == true)
		{
			canPlaceTower = false;
			break;
		}

	}

}

void gameState::towerLogic()
{

	bool hasSellClicked = false;

	hasMouseClicked = false;

	towerSelect();

	tower* selectedTower = nullptr;

	for (auto& towers : towersPlaced)
	{

		if (towers->isTowerSeleceted == true)
		{

			towers->drawRange();

			selectedTower = towers.get();

			// Upgrade Menu

			Vector2 upgradePos = { 1520, 50 };
			int upgradeWidth = 200;
			int upgradeHeight = 250;

			DrawRectangle(upgradePos.x, upgradePos.y, upgradeWidth, upgradeHeight, YELLOW);

			DrawRectangle(upgradePos.x + (upgradeWidth - 50), upgradePos.y, 50, 50, RED);

			if (CheckCollisionPointRec(GetMousePosition(), { upgradePos.x + (upgradeWidth - 50), upgradePos.y, 50, 50 }))
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					towers->isTowerSeleceted = false;
					hasMouseClicked = true;
				}

			DrawText(towers->towerName.c_str(), upgradePos.x + 7, upgradePos.y + 10, 40, BLACK);

			// Sell Button

			Vector2 sellPos = { upgradePos.x + (upgradeWidth / 4), upgradePos.y + (upgradeHeight - 50)};
			int sellWidth = 100;
			int sellHeight = 50;

			DrawRectangle(sellPos.x, sellPos.y, sellWidth, sellHeight, RED);
			DrawText("SELL", sellPos.x + (sellWidth / 4), sellPos.y + (sellHeight / 4), 25, BLACK);

			if (CheckCollisionPointRec(GetMousePosition(), { sellPos.x, sellPos.y, (float)sellWidth, (float)sellHeight }))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{

					money += towers->sellPrice;
					hasMouseClicked = true;
					hasSellClicked = true;

					break;

				}
			}

			// Upgrade Button

			Vector2 upgradeButtonPos = { sellPos.x - (75 / 2) + 20, sellPos.y - sellHeight - 35 };
			int upgradeButtonWidth = 150;
			int upgradeButtonHeight = 75;

			DrawRectangle(upgradeButtonPos.x, upgradeButtonPos.y, upgradeButtonWidth, upgradeButtonHeight, RED);
			DrawText("UPGRADE", upgradeButtonPos.x + (upgradeButtonWidth / 4) - 15, upgradeButtonPos.y + (upgradeButtonHeight / 4), 25, BLACK);

			std::string upgradeString = std::to_string(towers->upgradePrice);
			DrawText(upgradeString.c_str(), upgradeButtonPos.x + (upgradeButtonWidth / 4) + 20, upgradeButtonPos.y + (upgradeButtonHeight / 4) + 30, 25, GOLD);

			if (CheckCollisionPointRec(GetMousePosition(), { upgradeButtonPos.x, upgradeButtonPos.y, (float)upgradeButtonWidth, (float)upgradeButtonHeight }))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{

					if (towers->currentLevel < towers->maxLevel && money >= towers->upgradePrice)
					{

						money -= towers->upgradePrice;
						towers->currentLevel += 1;

						towers->sellPrice += towers->upgradePrice / 2;

						towers->upgradePrice = towers->upgradePrice * towers->currentLevel;

						towers->range += 15 * towers->currentLevel;
						towers->damage += 20 * towers->currentLevel;

					}

					hasMouseClicked = true;

				}
			}

		}
	}

	if (hasMouseClicked && selectedTower != nullptr && hasSellClicked == true)
	{

		towersPlaced.erase(std::remove_if(towersPlaced.begin(), towersPlaced.end(), [&](const std::unique_ptr<tower>& tower)
			{

				return tower.get() == selectedTower;

			}),
			towersPlaced.end());

	}

}

void gameState::towerAttack()
{

	for (auto& enemy : enemies)
	{

		for (auto& tower : towersPlaced)
		{

			if (CheckCollisionRecs({ enemy.pos.x, enemy.pos.y, enemy.width, enemy.height }, { tower->pos.x - (tower->range / 2), tower->pos.y - (tower->range / 2), tower->width + tower->range, tower->height + tower->range }))
			{

				enemy.baseHealth -= tower->damage * GetFrameTime();
				

			}

		}


	}

	enemyDeath();

}

void gameState::towerSelect()
{

	for (auto& tower : towersPlaced)
	{

		if (CheckCollisionPointRec({ GetMousePosition() }, { tower->pos.x, tower->pos.y, tower->width, tower->height }))
		{

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				tower->isTowerSeleceted = true;

		}

	}

}

void gameState::takeDamage()
{

	for (auto& enemy : enemies)
	{

		if (CheckCollisionRecs({ enemy.pos.x, enemy.pos.y, enemy.width, enemy.height }, { 1720, 0, 200, 1080 }))
		{


			baseHealth -= enemy.baseHealth;
			enemy.baseHealth = 0;


			enemyDeath();

			if (baseHealth <= 0)
			{

				isGameOver = true;

			}

		}

	}

}

void gameState::gameOver()
{

	if (isGameOver == true)
	{

		for (auto& enemy : enemies)
		{

			enemy.baseHealth = 0;
			enemyDeath();

		}

		Vector2 playagainButtonPos;
		playagainButtonPos.x = GetScreenWidth() / 2;
		playagainButtonPos.y = GetScreenHeight() / 2;

		int playagainButtonWidth = 250;
		int playagainButtonHeight = 50;

		DrawRectangle(playagainButtonPos.x - (playagainButtonWidth / 2), playagainButtonPos.y - (playagainButtonHeight / 2), playagainButtonWidth, playagainButtonHeight, GREEN);
		DrawText("Play Again", playagainButtonPos.x - (playagainButtonWidth / 4), playagainButtonPos.y - (playagainButtonHeight / 4), 25, BLACK);

		if (CheckCollisionPointRec(GetMousePosition(), { playagainButtonPos.x - (playagainButtonWidth / 2), playagainButtonPos.y - (playagainButtonHeight / 2), 250, 50 }))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentTowerType = towerType::NONE;

				currentEnemyCount = 0;
				waveSpawnNo = 5;
				waveBossSpawnNo = 1;
				enemiesSpawnedThisWave = 0;
				bossesSpawnedThisWave = 0;

				waveCount = 1;
				money = 100;
				baseHealth = 500;

				isGameOver = false;
				isWaveOver = false;
				isFinalWave = false;

				startWave();
	
			}
		}

		Vector2 quitButtonPos;
		quitButtonPos.x = GetScreenWidth() / 2;
		quitButtonPos.y = ((GetScreenHeight() / 2) + 200);

		int quitButtonWidth = 250;
		int quitButtonHeight = 50;

		DrawRectangle(quitButtonPos.x - (quitButtonWidth / 2), quitButtonPos.y - (quitButtonWidth / 2), quitButtonWidth, quitButtonHeight, RED);
		DrawText("Quit", quitButtonPos.x - (quitButtonWidth / 4) + 35, quitButtonPos.y - (quitButtonHeight / 4) - 100, 25, BLACK);

		if (CheckCollisionPointRec(GetMousePosition(), { quitButtonPos.x - (quitButtonWidth / 2), quitButtonPos.y - (quitButtonWidth / 2), (float)quitButtonWidth, (float)quitButtonHeight }))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{

				exit(-1);

			}
		}

	}

}
