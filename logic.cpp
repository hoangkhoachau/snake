#include "Header.h"
#include "game.h"
#include "fileProcessing.h"
#include "sound.h"
#include "externalGraphics.h"

using namespace std;
extern snake snake1;
extern bool paused, start;
extern screen screen1, screen2;
extern int level, levelScore, cursor2, cursor3,cursor4, startLoadIndex, portalOrientation, speedSetting,maxLength;
extern unsigned long long frameN, portalSpawnTime, countDownStartTime;
extern list<button>::iterator cursor;
extern list<button> buttons;
extern unordered_map<wstring, frame> object;
extern vector<Save> save;
extern gameState state;
extern wstring MSSV;
extern coordinate portalPos;
extern int food;
extern unordered_map<char, bool> key;
extern frame map[10];


void init(snake& snake1) {
    snake1.score = 0;
    snake1.levelFinished = false;
    snake1.deadTime = 0;
    snake1.totalScore=0;
    snake1.state = inside;
    snake1.direction = 'D'; // Ban đầu hướng di chuyển là sang phải
    snake1.speed = 0.9;       // Tốc độ ban đầu của rắn
    snake1.dead = false;
    snake1.body.clear();
    snake1.body = {
        {-50, -50},
        {-50 - 1, -50},
        {-50 - 2, -50},
        {-50 - 3, -50},
        {-50 - 4, -50},
    };
}

void resetData(snake& snake1)
{
    init(snake1);
}

void resetGame()
{
    level = 0;
    resetData(snake1);
    food=-1;
}

void move(char c, snake& snake1)
{
    switch (c)
    {
    case 'D':
        snake1.body.push_front({ snake1.body.front().X + 1, snake1.body.front().Y });
        break;
    case 'A':
        snake1.body.push_front({ snake1.body.front().X - 1, snake1.body.front().Y });
        break;
    case 'S':
        snake1.body.push_front({ snake1.body.front().X, snake1.body.front().Y + 1 });
        break;
    case 'W':
        snake1.body.push_front({ snake1.body.front().X, snake1.body.front().Y - 1 });
    } // Thêm vào đầu mới với vị trí theo hướng di chuyển

    // Kiem tra ran chet chua
    if (screen1.characters[index(snake1.body.front().X, snake1.body.front().Y, screen1)] == L'&')
    {
        // speed+=0.5;
        snake1.score++;
        snake1.totalScore++;
        sound.playEat1();
        food=-1;
        if (!snake1.levelFinished)
        {
            coordinate t = findSpace();
            food=index(t.X, t.Y, screen1);
        }
        return;
    }

    snake1.body.pop_back(); // Xoá phần đuôi
    if (snake1.state == goingIn && snake1.body.back().X < 0 && snake1.body.back().Y < 0)
    {
        snake1.state = inside;
    }
    if (snake1.state == goingOut && snake1.body.back().X >= 0 && snake1.body.back().Y >= 0)
    {
        snake1.state = outside;
        coordinate t = findSpace();
        food=index(t.X, t.Y, screen1);
        snake1.levelFinished = false;
        portalPos = { -1, -1 };
    }
    if (screen1.characters[index(snake1.body.front().X, snake1.body.front().Y, screen1)] == L'I')
    {
        snake1.state = goingIn;
        snake1.body.front() = { -50, -50 };
        snake1.direction = 'W';
    }
    if (screen1.characters[index(snake1.body.front().X, snake1.body.front().Y, screen1)] != ' ' && (snake1.body.front().X >= 0 && snake1.body.front().Y >= 0)) // Nếu đầu rắn đi tới chỗ không phải là khoảng trống
    {
        // sound.playHitting();
        sound.playLose1();
        snake1.deadTime = frameN;
        snake1.dead = true;
    }
}

void input()
{
    if ((GetAsyncKeyState('W') & 0x8000) && !key['W'] && (paused || snake1.direction != 'S'))
    {
        key['W'] = true;
        switch (state) {
        case inMenu:
            if (cursor2 > 0)
            {
                cursor2--;
                sound.playMenu();
            }
            break;
        case inSetting:
            if (speedSetting < 10) speedSetting++;
            break;
        case inGame:
            if (snake1.direction != 'S')
                snake1.direction = 'W';
            break;
        case inPaused:
            if (cursor != buttons.begin()) {
                cursor--;
                sound.playMenu();
            }
            break;
        case inLoad:
            if (save.size() > 1)
            {
                sound.playMenu();
            }
            if (cursor3 == 0 && startLoadIndex > 0)
                startLoadIndex--;
            else if (cursor3 > 0)
                cursor3--;
            break;
        }
    }
    if (GetAsyncKeyState('W') == 0)
        key['W'] = false;

    if ((GetAsyncKeyState('D') & 0x8000) && !key['D'] && (paused || snake1.direction != 'A'))
    {
        key['D'] = true;
        switch (state) {
        case inSetting:
            if (cursor4 <4) cursor4++;
            break;
        case inGame:
            if (snake1.direction != 'A')
                snake1.direction = 'D';
            break;
        }
    }
    if (GetAsyncKeyState('D') == 0)
        key['D'] = false;

    if ((GetAsyncKeyState('S') & 0x8000) && !key['S'] && (paused || snake1.direction != 'W'))
    {
        key['S'] = true;
        switch (state) {
        case inMenu:
            if (cursor2 < 6)
            {
                sound.playMenu();
                cursor2++;
            }
            break;
        case inSetting:
            if (speedSetting > 1) speedSetting--;
            break;
        case inGame:
            if (snake1.direction != 'W')
                snake1.direction = 'S';
            break;
        case inPaused:
            if (cursor != prev(buttons.end())) {
                sound.playMenu();
                cursor++;
            }
            break;
        case inLoad:
            if (save.size() > 1)
            {
                sound.playMenu();
            }
            if (cursor3 == 18 && cursor3 + startLoadIndex + 1 < save.size())
                startLoadIndex++;
            else if (cursor3 < min(save.size() - startLoadIndex - 1, 18))
                cursor3++;
            break;
        }

    }
    if (GetAsyncKeyState('S') == 0)
        key['S'] = false;

    if ((GetAsyncKeyState('A') & 0x8000) && !key['A'] && (paused || snake1.direction != 'D'))
    {
        key['A'] = true;
        switch (state) {
        case inSetting:
            if (cursor4 > 0) cursor4--;
            break;
        case inGame:
            if (snake1.direction != 'D')
                snake1.direction = 'A';
            break;
        }
    }
    if (GetAsyncKeyState('A') == 0)
        key['A'] = false;

    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && !key[' '])
    {
        key[' '] = true;
        if (state == inPaused || state == inGame || state==gameOver) {
            if (state == inPaused || state==gameOver) state = inGame;
            else if (state == inGame) state = inPaused;
            paused = !paused;
            cursor = buttons.begin();
            if (snake1.dead)
            {
                state = inGame;
                resetGame();
            }
        }
    }
    if (GetAsyncKeyState(VK_SPACE) == 0)
        key[' '] = false;

    if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) && !key['['])
    {
        key['['] = true;
        switch (state) {
        case inPaused:
        case inGame:
            if (state == inPaused) state = inGame;
            if (state == inGame) state = inPaused;
            paused = !paused;
            cursor = buttons.begin();
            if (snake1.dead)
            {
                state = inGame;
                sound.playError();
                resetGame();
            }
            break;
        case inHighscore:
        case inSetting:
        case inLoad:
            sound.playEnter();
            cursor2 = 0;
            state = inMenu;
            break;
        }
    }
    if (GetAsyncKeyState(VK_ESCAPE) == 0)
        key['['] = false;

    if ((GetAsyncKeyState(VK_DELETE) & 0x8000) && !key['|'])
    {
        key['|'] = true;

        if (state == inLoad) {
            if (save.size())
                save.erase(save.begin() + cursor3 + startLoadIndex);
            if (cursor3 == save.size() - startLoadIndex) cursor3--;
        }
    }
    if (GetAsyncKeyState(VK_DELETE) == 0)
        key['|'] = false;

    if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && !key[']'])
    {
        key[']'] = true;
        switch (state) {
        case gameOver:
            state = inPaused;
            paused = true;
            break;
        case inMenu:
            sound.playEnter();
            switch (cursor2) {
            case 0:
                clear(screen1);
                countDownStartTime = frameN;
                start = true;
                level = 0;
                resetData(snake1);
                nextLevel();
                sound.playReady();
                //activeMenu = false;
                break;
            case 1:
                sound.playEnter();
                if (save.size() > 0) {
                    countDownStartTime = frameN;
                    start = true;
                    sort(save.begin(), save.end(), optionAscendingTime);
                    loadSave(save.back());
                    sound.playReady();
                }
                break;
            case 2:
                if (cursor3 < 0) cursor3 = 0;
                sort(save.begin(), save.end(), optionAscendingTime);
                sound.playEnter();
                state = inLoad;
                break;
            case 3:
                sort(save.begin(), save.end(), optionAscendingScore);
                sound.playEnter();
                state = inHighscore;
                break;
            case 4:
                sound.playEnter();
                state = inSetting;
                break;
            case 5:
                sound.playEnter();
                drawIntroduction();
                break;
            case 6:

                system("color D0");
                ExitGame();
            }
            break;
        case inPaused:
            switch (cursor->index)
            {
            case 0:
                if (!snake1.dead) {
                    sound.playEnter();
                    state = inGame;
                    paused = !paused;
                }
                break;
            case 1:
                sound.playEnter();
                saveGame();
                writeSaveFile();
                //state = inMenu; /// fixed back to menu after save game.
                break;
            case 2:
                sound.playEnter();
                state = inMenu;

                break;
            }
            break;
        case inLoad:
            if (save.size() > 0)
            {
                loadSave(save[cursor3]);
                countDownStartTime = frameN;
                start = true;
                sound.playReady();
            }
            break;
        case inSetting:
            sound.playEnter();
            state = inMenu;
            break;
        }
    }
    if (GetAsyncKeyState(VK_RETURN) == 0)
        key[']'] = false;
}

void spawnPortal()
{
    portalOrientation = rand() % 4;
    coordinate t;
    if (portalOrientation < 2)
        t = findSpace(10, 3);
    else
        t = findSpace(3, 10);
    switch (portalOrientation)
    {
    case 0:
        portalPos = { t.X + 8, t.Y };
        break;
    case 2:
        portalPos = { t.X, t.Y + 8 };
        break;
    case 1:
    case 3:
        portalPos = t;
    }
}

void nextLevel()
{
    sound.playPassLevel();
    level++;
    snake1.speed += 0.1;
    snake1.score = 0;
    snake1.state = goingOut;
    coordinate snakePos;
    draw(screen1, map[level], { 0, 0 });
    spawnPortal();
    switch (portalOrientation)
    {
    case 0:
        snake1.direction = 'A';
        snakePos = { portalPos.X - 1, portalPos.Y + 1 };
        break;
    case 1:
        snake1.direction = 'D';
        snakePos = { portalPos.X + 2, portalPos.Y + 1 };
        break;
    case 2:
        snake1.direction = 'W';
        snakePos = { portalPos.X + 1, portalPos.Y - 1 };
        break;
    case 3:
        snake1.direction = 'S';
        snakePos = { portalPos.X + 1, portalPos.Y + 2 };
    }
    snake1.body.front() = snakePos;
}

void update()
{
    if (snake1.dead)
    {
        paused = true;
    }
    if (snake1.dead && frameN - snake1.deadTime == 120)
        state = gameOver;
    if (!paused)
        move(snake1.direction, snake1);
    if (snake1.score >= levelScore && !snake1.levelFinished)
    {
        spawnPortal();
        portalSpawnTime = frameN;
        food=-1;
        snake1.levelFinished = true;
    }
    else if (snake1.state == inside)
    {
        if (level + 1 > 5)
        {
            snake1.speed += 0.2;
            level = 0;
        }
        if (snake1.body.size() >= maxLength)
            snake1.body.resize(5);
        nextLevel();
    }



}

coordinate findSpace(int sizeX, int sizeY)
{
    int x, y;
    do
    {
        x = rand() % height;
        y = rand() % height;
    } while (!valid(x, y, sizeX, sizeY));
    return { x, y };
}