#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <raylib.h>
#include"game.h"
#include "colors.h"
#include<iostream>

double lastupdatetime = 0;

bool EventTriggred(double interval)
{
    double currenTime = GetTime();
    if (currenTime - lastupdatetime >= interval)
    {
        lastupdatetime = currenTime;
        return true;
    }
    return false;
}

int main() {

    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

   // Font font = LoadFont("monogram.ttf", 60, 0, 0);
    Font font = LoadFont("monogram.ttf");

    Game game = Game();


    while (!WindowShouldClose()) {
        UpdateMusicStream(game.music);
        game.HandelInput();
        if (EventTriggred(0.2))
        {
            game.MovesBlockDown();

        }
        BeginDrawing();
        ClearBackground(darBlue);
        DrawTextEx(font, "Score", { 365, 15 }, 38, 1, WHITE);
        DrawTextEx(font, "Next", { 370, 175 }, 38, 1, WHITE);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", { 320, 450 }, 38, 2, WHITE);
        }
        DrawRectangleRounded({ 320, 55,170, 60 }, 0.3, 6, lightBlue);

        char scoreText[10];
        
        //sprintf(scoreText, "%d", game.score);
        sprintf_s(scoreText, sizeof(scoreText), "%d", game.score);

        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);


        DrawTextEx(font, scoreText, { 365+(170- textSize.x)/2, 65 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320, 215,170, 180 }, 0.3, 6, lightBlue);
        game.Draw();


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
