#pragma once
#include "game.h"

struct Save
{
    std::wstring name;
    int level;
    std::chrono::system_clock::time_point saveTime;
    snake snak;
};
void writeSaveFile();
void loadSaveFile();
void loadSave(Save& save);
void saveGame();
bool optionAscendingTime(Save& a, Save& b);
bool optionAscendingScore(Save& a, Save& b);
int loadMap();
int loadMics();