#pragma once
#define GameWidth 100
#define GameHeight 30
#define InteractOrigin_x 0
#define InteractOrigin_y 0

void gotoXY(int x, int y);
void ShowConsoleCursor(bool showFlag);
void FixConsoleColor(int k);
void FixConsoleWindow();
void DrawMessBoard(int x, int y, int h, int w);
void Mes_Exit(int x, int y);
void Mes_exit();
void loading();
void ExitGame();
void setTextColor(int color);
void drawBoard(int height, int width, int posX, int posY);
void drawIntroduction();

