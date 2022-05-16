#pragma once
#include "Header.h"
struct coordinate
{
    int X, Y;
};
enum snakeState
{
    outside,
    goingIn,
    inside,
    goingOut
};
struct snake
{
    int score;
    unsigned long long deadTime;
    char direction;
    bool dead, levelFinished;
    float speed;
    snakeState state;
    std::list<coordinate> body;
};
enum gameState { inMenu, inGame, inLoad, inPaused ,gameOver};
struct screen {
    int width, height;
    wchar_t* characters; // Ma tran man hinh
    WORD* color;     // Ma tran mau
    screen(const int width1, const int height1) {
        width = width1, height = height1;
        characters = (wchar_t*)malloc((width1 * height1) * sizeof(wchar_t)); // Ma tran man hinh
        color = (WORD*)malloc((width1 * height1) * sizeof(WORD));     // Ma tran mau
    }
    ~screen() {
        free(characters);
        free(color);
    }
};
extern std::wifstream fin;
struct frame
{
    int sizeX, sizeY;
    std::vector<wchar_t> character;
    std::vector<int> color;
    frame() : sizeX(0), sizeY(0), character(), color() {};
    frame(int x, int y)
    {
        sizeX = x;
        sizeY = y;
        character.resize(x * y);
        color.resize(x * y);
    }
    void inputFrame()
    {
        for (int i = 0; i < sizeX * sizeY; i++)
        {
            fin >> character[i];
            if (character[i] == L'~')
                character[i] = L' ';
        }
        for (int i = 0; i < sizeX * sizeY; i++)
            fin >> color[i];
    }
};
struct button
{
    int index;
    coordinate coordi;
    int sizeX, sizeY;
    LPCWSTR str;
};
void init(snake& snake1);
int index(const int& x, const int& y, screen& s);
void drawLoadMenu();
void drawInfo();
void drawScoreBar();
void draw(button b, bool selected);
void drawSideBar();
void drawMenu();
void countDown();
void showGameOver();
void draw(snake x);
void drawScore(snake a);
void draw(screen& s, frame a, coordinate w, int orientation = 0, bool drawColor = true, bool drawSpace = false);
void drawPortal();
void clear(screen& s);
void drawFood(std::unordered_set<int> food);

void saveGame();
void writeSaveFile();
static const long width = 50, height = 30; // Chieu rong , chieu cao
void countDown();
coordinate findSpace(int sizeX = 1, int sizeY = 1);
bool valid(int x, int y, int sizeX, int sizeY);
int index(const int& x, const int& y, screen& s);
void resetData(snake& snake1);
void resetGame();
void move(char c, snake& snake1);
void input();
void spawnPortal();
void nextLevel();
void update();
