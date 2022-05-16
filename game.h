#pragma once
#include "Header.h"

//Toạ độ
struct coordinate
{
    int X, Y;
};

//Trạng thái rắn
enum snakeState
{
    outside,
    goingIn,
    inside,
    goingOut
};

//Rắn
struct snake
{
    int score, totalScore;
    unsigned long long deadTime;
    char direction;
    bool dead, levelFinished;
    float speed;
    snakeState state;
    std::list<coordinate> body;
};

//Trạng thái game
enum gameState { inMenu, inGame, inLoad, inPaused ,gameOver,inSetting,inHighscore};

//thông tin ma trận màn hình
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

//Định dạng lưu hình ảnh kí tự
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

//Nút
struct button
{
    int index;
    coordinate coordi;
    int sizeX, sizeY;
    LPCWSTR str;
};

//Đặt thông số mặc định cho rắn
void init(snake& snake1);

//Chuyển toạ độ 2 chiều sang 1 chiều
int index(const int& x, const int& y, screen& s);

//Vẽ menu load
void drawLoadMenu();

//vẽ thông tin game
void drawInfo();

// vẽ thanh điểm
void drawScoreBar();

//Vẽ nút
void draw(button b, bool selected);

//Vẽ thanh phải màn hình
void drawSideBar();

//Vẽ menu
void drawMenu();

//Vẽ màn hình đếm ngược
void countDown();

//Vẽ màn hình dead
void showGameOver();

//Vẽ rắn
void draw(snake x);

//Vẽ điểm
void drawScore(snake a);

//Vẽ hình theo định dạng frame
void draw(screen& s, frame a, coordinate w, int orientation = 0, bool drawColor = true, bool drawSpace = false);

//Vẽ cổng
void drawPortal();

//Xoá màn hình
void clear(screen& s);

//Vẽ thức ăn
void drawFood(int food);

//Vẽ cài đặt
void drawSetting();

//Lưu game
void saveGame();

//Ghi file save
void writeSaveFile();

static const long width = 50, height = 30; // Chieu rong , chieu cao

//Tìm vị trí trống trên màn hình
coordinate findSpace(int sizeX = 1, int sizeY = 1);

//Kiểm tra vị trí có trống không
bool valid(int x, int y, int sizeX, int sizeY);

//Reset data rắn
void resetData(snake& snake1);

//reset game
void resetGame();

//Di chuyển rắn
void move(char c, snake& snake1);

//Xử lí input
void input();

//Tạo cổng
void spawnPortal();

//Qua màn
void nextLevel();

//Xử lí logic
void update();
//Vẽ hộp trống
void drawBox(screen& s, int sizeX, int sizeY, coordinate W, int color, bool selected);
//Vẽ màn hình highscore
void drawHighScore();