#include "fileProcessing.h"
#include "game.h"
extern screen screen1;
bool optionAscendingTime(Save& a, Save& b) {
    return a.saveTime > b.saveTime;
}
bool optionAscendingScore(Save& a, Save& b) {
    return a.snak.totalScore > b.snak.totalScore;

}
int index(const int& x, const int& y, screen& s)
{
    return y * s.width + x;
}
bool valid(int x, int y, int sizeX, int sizeY)
{
    for (int i = x; i < x + sizeX; i++)
        for (int j = y; j < y + sizeY; j++)
            if (screen1.characters[index(i, j, screen1)] != ' ')
                return false;
    return true;
}