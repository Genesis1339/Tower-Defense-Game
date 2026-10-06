#include "iostream"

#include "raylib.h"

#include "gameState.h"

int main(void)
{

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "game");

    SetTargetFPS(60);

    gameState mainState;

    while (!WindowShouldClose())
    {
        // Update

        if (mainState.isGameOver == false)
        {

            mainState.moveEnemy();
            mainState.towerAttack();
            mainState.takeDamage();
            mainState.towerLogic();

            mainState.buyMenu();
            mainState.finalWave();

        }

        // Draw


        BeginDrawing();

        if (mainState.isGameOver == false)
        {

            mainState.startWave();

        }
        else
        {
            mainState.gameOver();
        }



        ClearBackground(BLACK);


        EndDrawing();
    }

    CloseWindow();

    return 0;
}