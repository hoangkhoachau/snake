#include "Header.h"
#include "game.h"
#include "fileProcessing.h"

using namespace std;

extern snake snake1;
extern bool paused,start;
extern screen screen1,screen2;
extern int level, levelScore,cursor2,cursor3, startLoadIndex, portalOrientation,speedSetting;
extern unsigned long long frameN, portalSpawnTime, countDownStartTime;
extern list<button>::iterator cursor;
extern list<button> buttons;
extern unordered_map<wstring, frame> object;
extern vector<Save> save;
extern gameState state;
extern wstring MSSV;
extern coordinate portalPos;

void drawInfo()
{
    if (snake1.dead)
    {
        paused = true;
        wsprintfW(&screen1.characters[index(35, 13, screen1)], L"Dead");
        for (int i = 35; i < 35 + 4; i++)
            screen1.color[index(i, 13, screen1)] = 4;
    }
    wsprintfW(&screen1.characters[index(35, 8, screen1)], L"LEVEL %d", level);
    drawScore(snake1);
}

void drawSetting() {
    clear(screen2);
    coordinate t = { 35, 26 };
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 12; j++)
            if (i == 0 || j == 0 || i == 9 || j == 11)
            {
                screen1.characters[index(t.X + i, t.Y - j, screen1)] = L'B';
                screen1.color[index(t.X + i, t.Y - j, screen1)] = 255;
            }
            else
            {
                if (j <= speedSetting)
                {
                    screen1.characters[index(t.X + i, t.Y - j, screen1)] = L'B';
                    screen1.color[index(t.X + i, t.Y - j, screen1)] = 10 + 16 * 10;
                }
                else
                    screen1.color[index(t.X + i, t.Y - j, screen1)] = 0;
            }
    }
}

void drawScoreBar()
{
    coordinate t = { 35, 26 };
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 12; j++)
            if (i == 0 || j == 0 || i == 9 || j == 11)
            {
                screen1.characters[index(t.X + i, t.Y - j, screen1)] = L'B';
                screen1.color[index(t.X + i, t.Y - j, screen1)] = 255;
            }
            else
            {
                if (j <= (snake1.score / (float)levelScore) * 10)
                {
                    screen1.characters[index(t.X + i, t.Y - j, screen1)] = L'B';
                    screen1.color[index(t.X + i, t.Y - j, screen1)] = 10 + 16 * 10;
                }
                else
                    screen1.color[index(t.X + i, t.Y - j, screen1)] = 0;
            }
    }
}

void draw(button b, bool selected)
{
    if (b.sizeX - 2 <= wcslen(b.str))
        b.sizeX = wcslen(b.str) + 2;
    for (int i = 0; i < b.sizeX; i++)
        for (int j = 0; j < b.sizeY; j++)
        {
            screen1.characters[index(b.coordi.X + i, b.coordi.Y + j, screen1)] = L' ';
            screen1.color[index(b.coordi.X + i, b.coordi.Y + j, screen1)] = selected ? 6 * 16 : 15 * 16;
        }
    wsprintfW(&screen1.characters[index(b.coordi.X + (b.sizeX - wcslen(b.str)) / 2, b.coordi.Y + b.sizeY / 2, screen1)], b.str);
}

void drawSideBar()
{
    if (paused && !snake1.dead)
    {
        wsprintfW(&screen1.characters[index(35, 5, screen1)], L"PAUSED");
        for (list<button>::iterator b = buttons.begin(); b != buttons.end(); b++)
            draw(*b, b == cursor);
    }
    else
    {
        wsprintfW(&screen1.characters[index(35, 5, screen1)], L"RUNNING");
        drawInfo();
        drawScoreBar();
    }
}

void drawMenu() {
    draw(screen2, object[L"menu"], { 0,0 }, 0, true, true);
    switch (cursor2) {
    case 0:
        draw(screen2, object[L"newGame"], { 33,18 }, 0, false, false);
        break;
    case 1:
        draw(screen2, object[L"continue"], { 35,18 }, 0, false, false);
        break;
    case 2:
        draw(screen2, object[L"loadGame"], { 33, 18 }, 0, false, false);
        break;
    case 3:
        draw(screen2, object[L"introduction"], { 27,18 }, 0, false, false);
        break;
    case 4:
        draw(screen2, object[L"exit"], { 44,18 }, 0, false, false);
        break;
    }
}

void drawLoadMenu() {
    time_t t;
    draw(screen2, object[L"loadGame"], { width - 17,2 }, 0, false);
    draw(screen2, object[L"border"], { 3,6 }, 0, false);
    for (int i = 0; i < min(19, save.size()); i++) {
        t = chrono::system_clock::to_time_t(save[startLoadIndex + i].saveTime);
        char* str = ctime(&t);
        wstring wstr(str, str + strlen(str));
        wstr.pop_back();
        if (i == cursor3)
            for (int k = 4; k <= width * 2 - 5; k++)
                screen2.color[index(k, i + 9, screen2)] = 96;
        wsprintfW(&screen2.characters[index(15, 9 + i, screen2)], &save[startLoadIndex + i].name[0]);
        wsprintfW(&screen2.characters[index(42, 9 + i, screen2)], L"%d", save[startLoadIndex + i].level);
        wsprintfW(&screen2.characters[index(57, 9 + i, screen2)], L"%d", save[startLoadIndex + i].snak.score);
        wsprintfW(&screen2.characters[index(65, 9 + i, screen2)], &wstr[0]);
    }
    wsprintfW(&screen2.characters[index(40, 4, screen2)], L"PRESS ESC TO RETURN MENU");

}

void countDown() {
    if (countDownStartTime + 4 * 60 > frameN && start) {
        clear(screen2);
        float t = (frameN - countDownStartTime) / 60;

        if (t < 1)
            draw(screen2, object[L"three"], { width - 3,height / 2 - 3 });
        else if (t < 2)
            draw(screen2, object[L"two"], { width - 3,height / 2 - 3 });
        else if (t < 3)
            draw(screen2, object[L"one"], { width - 3,height / 2 - 3 });
        else if (t < 4)
            draw(screen2, object[L"go"], { width - 9,height / 2 - 3 }, 0, false, false);
    }
    else if (countDownStartTime + 4 * 60 == frameN && start) {
        state = inGame;
        paused = false;
    }
}

// chưa fix.
extern HANDLE buffer,old;

void showGameOver()
{
    if (state == gameOver) {
        coordinate coordi = { 5, height / 2 }; // fixed
        DWORD BytesWritten = 0;
        int sizeX = 20, sizeY = 4;
        clear(screen1);
        //button t = { 0, {35, 8}, 11, 3, L"GAME OVER!" };
        draw(screen1,object[L"gameOver"],{7,7},0,false);
        if ((frameN/60)%2)
            wsprintfW(&screen1.characters[index(13, 22, screen1)], L"PRESS SPACE TO PLAY AGAIN"); // fixed
    }
    //wsprintfW(&screen1.characters[index(coordi.X + 3, coordi.Y + sizeY / 2, screen1)], L"Do you want to save current game?"); // fixed
}

void draw(snake x)
{
    int j = x.body.size() - 1;
    for (list<coordinate>::reverse_iterator a = x.body.rbegin(); a != x.body.rend(); a++, j--)
        if (a->X >= 0 && a->Y >= 0)
        {
            if (x.dead)
            {
                if (frameN - x.deadTime < 120)
                {
                    screen1.color[index(a->X, a->Y, screen1)] = ((frameN - x.deadTime) / 15) % 2 ? (j == 0 ? 15 + 4 * 16 : 15 + 12 * 16) : (j == 0 ? 7 + 11 * 16 : 7 + 16 * 3);
                }
                else
                {
                    screen1.color[index(a->X, a->Y, screen1)] = j == 0 ? 15 + 4 * 16 : 15 + 12 * 16;
                }
                screen1.characters[index(a->X, a->Y, screen1)] = j == 0 ? L'x' : MSSV[j - 1];
            }
            else
            {
                screen1.color[index(a->X, a->Y, screen1)] = j == 0 ? 7 + 11 * 16 : 7 + 16 * 3;
                screen1.characters[index(a->X, a->Y, screen1)] = j == 0 ? (x.direction == 'D' || x.direction == 'A' ? ':' : '\"') : MSSV[j - 1];
            }
        }
}

void drawScore(snake a)
{
    wsprintfW(&screen1.characters[index(35, 10, screen1)], L"SCORE: %d/%d", a.score, levelScore);
    wsprintfW(&screen1.characters[index(35, 12, screen1)], L"LENGTH: %d", a.body.size());
}

void draw(screen& s, frame a, coordinate w, int orientation , bool drawColor , bool drawSpace)
{
    int k;
    for (int i = 0; i < a.sizeX; i++)
        for (int j = 0; j < a.sizeY; j++)
        {
            switch (orientation)
            {
            case 0:
                k = index(w.X + i, w.Y + j, s);
                break;
            case 1:
                k = index(w.X - i + a.sizeX - 1, w.Y - j + a.sizeY - 1, s);
                break;
            case 2:
                k = index(w.X + j, w.Y + i, s);
                break;
            case 3:
                k = index(w.X - j + a.sizeY - 1, w.Y - i + a.sizeX - 1, s);
            }
            s.characters[k] = a.character[i + j * a.sizeX];
            if (drawColor && (s.characters[k] != ' ' || drawSpace))
                s.color[k] = a.color[i + j * a.sizeX];
        }
}

void drawPortal()
{
    if (portalPos.X >= 0 && portalPos.Y >= 0)
    {
        if (frameN - portalSpawnTime <= 60)
        {
            if (((frameN - portalSpawnTime) / 15) % 2)
                draw(screen1, object[L"portal"], portalPos, portalOrientation);
        }
        else
            draw(screen1, object[L"portal"], portalPos, portalOrientation);
    }
}

// Xoa man hinh
void clear(screen& s)
{
    for (int i = 0; i < s.width * s.height; i++)
    {
        s.characters[i] = L' ';   //Đặt kí tự khoảng trống
        s.color[i] = 14 * 16; // Mặc định chữ trắng, nền đen
    }
}

void drawFood(unordered_set<int> food)
{
    for (int x : food)
    {
        screen1.characters[x] = L'&';
        screen1.color[x] = 12 + 12 * 16;
    }
}