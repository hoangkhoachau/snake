#include "Header.h"
#include "fileProcessing.h"
#include "game.h"
#include "sound.h"

using namespace std;
 
extern screen screen1;
wifstream fin;
vector<Save> save;
extern snake snake1;
extern int level,cursor3;
extern int food;

void writeSaveFile()
{
    fin.close();
    wofstream fout;
    fout.open("resources//save.txt");
    fout << save.size() << '\n';
    for (auto i : save)
    {
        fout << i.name << '\n';
        fout << i.level << '\n';
        fout << chrono::system_clock::to_time_t(i.saveTime) << '\n';
        fout << i.snak.score << '\n';
        fout << i.snak.totalScore << '\n';
        fout << i.snak.deadTime << '\n';
        fout << i.snak.levelFinished << '\n';
        fout << i.snak.state << '\n';
        fout << (int)i.snak.direction << '\n';
        fout << i.snak.speed << '\n';
        fout << i.snak.dead << '\n';
        fout << i.snak.body.size() << '\n';
        list<coordinate>::iterator it;
        for (it = i.snak.body.begin(); it != i.snak.body.end(); it++)
            fout << it->X << ' ' << it->Y << '\n';
    }
    fout.close();
}

void loadSaveFile()
{
    fin.close();
    fin.open("resources//save.txt");
    int n, t;
    time_t T;
    coordinate coordi;
    fin >> n;
    if (n > 0)
        save.resize(n);
    for (int i = 0; i < n; i++)
    {
        fin >> save[i].name;
        fin >> save[i].level;
        fin >> T;
        save[i].saveTime = chrono::system_clock::from_time_t(T);
        fin >> save[i].snak.score;
        fin >> save[i].snak.totalScore;
        fin >> save[i].snak.deadTime;
        fin >> save[i].snak.levelFinished;
        fin >> t;
        save[i].snak.state = (snakeState)t;
        fin >> t;
        save[i].snak.direction = (char)t;
        fin >> save[i].snak.speed;
        fin >> save[i].snak.dead;
        fin >> t;
        save[i].snak.body.clear();
        for (int j = 0; j < t; j++)
        {
            fin >> coordi.X >> coordi.Y;
            save[i].snak.body.push_back(coordi);
        }
    }
}

void loadSave(Save& save)
{
    if (food > 0) {
        screen1.characters[food] = L' ';
        screen1.color[food] = 14 * 16;
        food=-1;
    }
    snake1 = snake(save.snak);
    level = save.level;
    coordinate t = findSpace();
    food=index(t.X, t.Y, screen1);
}

extern HANDLE buffer, old;

void saveGame()
{
    coordinate coordi = { 5, height / 2 }; // fixed
    DWORD BytesWritten = 0;
    int sizeX = 20, sizeY = 4;
    for (int i = 0; i < sizeX; i++)
        for (int j = 0; j < sizeY; j++)
        {
            screen1.characters[index(coordi.X + i, coordi.Y + j, screen1)] = ' ';
            screen1.color[index(coordi.X + i, coordi.Y + j, screen1)] = j == 2 && !(i == 0 || i == sizeX - 1) ? 15 : 15 * 16;
        }
    wsprintfW(&screen1.characters[index(coordi.X + 3, coordi.Y + sizeY / 2 - 1, screen1)], L"ENTER YOUR NAME"); // fixed
    WriteConsoleOutputCharacterW(buffer, screen1.characters, width * height, { 0, 0 }, &BytesWritten);
    WriteConsoleOutputAttribute(buffer, screen1.color, width * height, { 0, 0 }, &BytesWritten);
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    SetConsoleCursorPosition(buffer, { (SHORT)(coordi.X + 2), (SHORT)(coordi.Y + 2) });
    save.resize(save.size() + 1);
    wcin >> save.back().name;
    save.back().snak = snake1;
    save.back().level = level;
    save.back().saveTime = chrono::system_clock::now();
    sound.playEnter();
    clear(screen1);
    //wsprintfW(&screen1.characters[index(coordi.X + 6, coordi.Y + sizeY / 2, screen1)], L"Success!"); // fixed
    wsprintfW(&screen1.characters[index(width/2-4, height/2, screen1)], L"Success!");
    WriteConsoleOutputCharacterW(buffer, screen1.characters, width * height, { 0, 0 }, &BytesWritten);
    WriteConsoleOutputAttribute(buffer, screen1.color, width * height, { 0, 0 }, &BytesWritten);
    Sleep(1000);
}

extern unordered_map<wstring, frame> object;
extern frame map[10];

int loadMics()
{
    fin.close();
    fin.open("resources//misc.txt");
    fin.imbue(locale(fin.getloc(), new codecvt_utf8_utf16<wchar_t>));
    int n, x, y;
    wstring t;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        fin >> t;
        fin >> x >> y;
        object[t] = frame(x, y);
        object[t].inputFrame();
    }
    return n;
}

int loadMap()
{
    fin.close();
    fin.open("resources//maps.txt");
    int n, x, y;
    fin >> n;
    for (int i = 1; i <= n + 1; i++)
    {
        fin >> x >> y;
        map[i] = frame(x, y);
        map[i].inputFrame();
    }
    return n;
}
