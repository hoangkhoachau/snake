#include "Header.h"
#include "sound.h"
#include "externalGraphics.h"
#include "game.h"

#pragma warning( push )
#pragma warning( disable : 4566 )

using namespace std;

void gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Hàm đổi màu chữ
void FixConsoleColor(int k)
{
    HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor, k);
}

// Hàm cố định cửa sổ console
void FixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

// Hàm vẽ bảng thông báo bao gồm (tọa độ góc trái cùng, độ cao và chiều dài)
void DrawMessBoard(int x, int y, int h, int w)
{
    // Vẽ góc
    /*FixConsoleColor(244);*/
    gotoXY(x, y);
    cout << "╔";
    /*FixConsoleColor(244);*/
    gotoXY(x + w, y);
    cout << "╗";
    /*FixConsoleColor(244);*/
    gotoXY(x, y + h);
    cout << "╚";
    /*FixConsoleColor(244);*/
    gotoXY(x + w, y + h);
    cout << "╝";

    for (int i = 1; i < h; i++)
    {
        // Vẽ cột
        /*FixConsoleColor(244);*/
        gotoXY(x, y + i);
        cout << "║";
        /*FixConsoleColor(244);*/
        gotoXY(x + w, y + i);
        cout << "║";
    }

    for (int i = 1; i < w; i++)
    {
        // Vẽ dòng
        /*FixConsoleColor(244);*/
        gotoXY(x + i, y);
        cout << "═";
        /*FixConsoleColor(244);*/
        gotoXY(x + i, y + h);
        cout << "═";
    }
    cout << endl;
}

// Hàm hiển thị tên các thành viên nhóm
void Mes_Exit(int x, int y)
{
    FixConsoleColor(244);
    gotoXY(x, y);
    cout << " Trưởng nhóm:   Vũ Tiến Đạt.";
    FixConsoleColor(244);
    gotoXY(x, y + 2);
    cout << " Thành viên:";
    FixConsoleColor(244);
    gotoXY(x + 15, y + 2);
    cout << " Nguyễn Đức Hoài.";
    FixConsoleColor(244);
    gotoXY(x + 15, y + 3);
    cout << " Nguyễn Gia Huy.";
    FixConsoleColor(244);
    gotoXY(x + 15, y + 4);
    cout << " Châu Hoàng Khoa.";
    FixConsoleColor(244);
    gotoXY(x + 15, y + 5);
    cout << " Trương Thế Hiển.";
}

// show info.
void Mes_exit()
{
    sound.playCredit();
    // 43 - 15 - 50 - 13
    const int Mes_BoardX = 33;
    const int Mes_BoardY = 15;
    const int Mes_BoardH = 13;
    const int X = Mes_BoardX;
    const int Y = Mes_BoardH + Mes_BoardY;
    for (int i = Y; i > -Y + 18; i--)
    {
        int j = 0;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "  Trường Đại học Khoa học Tự nhiên     ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "                                        ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            cout << "        ĐỒ ÁN CUỐI KÌ KTLT      ";

        }; j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "  MÔ PHỎNG RẮN SĂN MỒI - SNAKE GAME ";

        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "                                        ";
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "Lớp:                                    ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "             21CTT4                     ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "                                        ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "Giảng viên hướng dẫn:              ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "             Trương Toàn Thịnh    ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "                                        ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "Nhóm thực hiện:                   ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "             Nhóm 5               ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y) cout << "                                        ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "Các thành viên:                   ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "             Vũ Tiến Đạt. (C)";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "             Trương Thế Hiển.           ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "             Nguyễn Đức Hoài.          ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "             Nguyễn Gia Huy.       ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "             Châu Hoàng Khoa.       ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "                                        ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "                                        ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "                                        ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "                                        ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "                                        ";
            ;
        }j++;
        if (i + j > Mes_BoardY && i + j < Y)
        {
            gotoXY(X, i + (j));
            if (i + j <= Y)
                cout << "                                        ";
            ;
        }j++;
        Sleep(450);
    }
}

// Hàm intro (fixed)
void loading()
{
    // Đổi nền thành màu trắng
    system("color f0");

    // Đổi màu cho các kí tự in ra
    for (int i = 249; i < 253; i++) {
        gotoXY(0, 1);
        FixConsoleColor(i);
        cout << "▓▓░░░░";
        gotoXY(0, 2);
        FixConsoleColor(i);
        cout << "▒▒████";
        gotoXY(0, 3);
        FixConsoleColor(i);
        cout << "▒▒▒▒▒▒████";
        gotoXY(0, 4);
        FixConsoleColor(i);
        cout << "▒▒▒▒░░▒▒▒▒▒▒";
        gotoXY(0, 5);
        FixConsoleColor(i);
        cout << "░░░░▒▒▒▒▒▒▒▒▓▓██";
        gotoXY(0, 6);
        FixConsoleColor(i);
        cout << "▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒████                ██████";
        gotoXY(0, 7);
        FixConsoleColor(i);
        cout << "▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒██████        ██▒▒▒▒▒▒██████████          ████████";
        gotoXY(0, 8);
        FixConsoleColor(i);
        cout << "▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
        gotoXY(0, 9);
        FixConsoleColor(i);
        cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒    ▒▒▒▒▒▒████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████        ██▓▓▒▒▒▒▒▒▓▓██";
        gotoXY(0, 10);
        FixConsoleColor(i);
        cout << "  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓██  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██    ▒▒▒▒▒▒▒▒  ██▒▒▒▒▒▒██";
        gotoXY(0, 11);
        FixConsoleColor(i);
        cout << "▒▒    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓██  ▒▒▒▒██████▒▒▒▒  ██▒▒██▒▒████";
        gotoXY(0, 12);
        FixConsoleColor(i);
        cout << "▒▒▒▒▒▒    ▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████  ▒▒▒▒██░░░░░░██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██";
        gotoXY(0, 13);
        FixConsoleColor(i);
        cout << "▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██░░  ██    ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████";
        gotoXY(0, 14);
        FixConsoleColor(i);
        cout << "▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████░░    ██    ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████";
        gotoXY(0, 15);
        FixConsoleColor(i);
        cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██    ██    ██▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██";
        gotoXY(0, 16);
        FixConsoleColor(i);
        cout << "▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒      ▒▒▒▒████    ██▒▒▒▒▓▓████▒▒██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██";
        gotoXY(0, 17);
        FixConsoleColor(i);
        cout << "██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒  ▒▒▒▒▒▒████▒▒▒▒▒▒██▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██";
        gotoXY(0, 18);
        FixConsoleColor(i);
        cout << "  ██████▓▓▒▒▒▒▒▒▒▒▒▒▒▒  ░░████  ▒▒▒▒  ▒▒▒▒▒▒████  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░██  ▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒██";
        gotoXY(0, 19);
        FixConsoleColor(i);
        cout << "        ████▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓██    ▒▒▒▒▒▒██▓▓▓▓██  ▒▒▒▒▒▒▒▒▒▒    ░░██░░██  ▒▒▒▒▓▓██▒▒▒▒▒▒██";
        gotoXY(0, 20);
        FixConsoleColor(i);
        cout << "            ██▓▓▒▒▓▓▓▓▒▒▒▒▒▒██▓▓▓▓▒▒▒▒▒▒██▓▓▓▓▒▒▓▓▓▓░░▒▒▒▒░░░░▓▓▓▓▓▓░░▓▓██  ░░  ▒▒▒▒▒▒▒▒▓▓░░";
        gotoXY(0, 21);
        FixConsoleColor(i);
        cout << "              ████▒▒▓▓██▒▒▒▒▒▒▒▒▒▒██████▓▓▓▓▓▓▓▓▒▒████░░░░████▓▓▓▓▓▓██▓▓▓▓██████  ██████";
        gotoXY(0, 22);
        FixConsoleColor(i);
        cout << "                  ██▒▒▒▒██▒▒▒▒▒▒▒▒▓▓▒▒▓▓██▓▓▓▓▒▒██░░░░████▓▓▓▓████▓▓▓▓▓▓██      ██";
        gotoXY(0, 23);
        FixConsoleColor(i);
        cout << "                    ██▓▓██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓████▒▒██░░░░░░▒▒████░░░░██████░░    ";
        gotoXY(0, 24);
        FixConsoleColor(i);
        cout << "                          ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓██▓▓▓▓░░░░░░░░░░░░░░░░░░░░██▒▒▓▓  ";
        gotoXY(0, 25);
        FixConsoleColor(i);
        cout << "                            ▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓████░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓";
        gotoXY(0, 26);
        FixConsoleColor(i);
        cout << "                                ██████▒▒▒▒▒▒▒▒▒▒▒▒▓▓██░░░░░░████████░░░░░░░░░░  ██";
        gotoXY(0, 27);
        FixConsoleColor(i);
        cout << "                                      ████▒▒▒▒▒▒▒▒▒▒▓▓██░░██▓▓▓▓██  ██████░░░░░░  ██";
        gotoXY(0, 28);
        FixConsoleColor(i);
        cout << "                                          ████▒▒▒▒▒▒▒▒▓▓████▒▒▒▒██  ██▓▓▓▓████░░░░  ████    ██";
        gotoXY(0, 29);
        FixConsoleColor(i);
        cout << "                                              ████▒▒▒▒▒▒▒▒▒▒██▒▒██    ████▓▓▓▓██░░░░    ████  ██";
        gotoXY(0, 30);
        FixConsoleColor(i);
        cout << "                                                      ██▒▒▒▒▒▒▒▒▓▓██░░░░████▓▓▒▒██  ▓▓██░░░░░░░░░░██";
        gotoXY(0, 31);
        FixConsoleColor(i);
        cout << "                                                        ████▒▒▒▒▒▒▓▓████▓▓▓▓▒▒██        ████░░░░██";
        gotoXY(0, 32);
        FixConsoleColor(i);
        cout << "                                                          ░░░░▓▓▒▒▒▒▒▒▓▓▓▓▒▒████░░          ░░██▓▓░░";
        gotoXY(0, 33);
        FixConsoleColor(i);
        cout << "                                                              ████▒▒▒▒████";
        gotoXY(0, 34);
        FixConsoleColor(i);
        cout << "                                                                                            ████";

        Sleep(1000);
    }
    system("cls");
    system("color f0");
    gotoXY(12, 1);
    FixConsoleColor(244);
    cout << "░██████╗███╗░░██╗░█████╗░██╗░░██╗███████╗  ░██████╗░░█████╗░███╗░░░███╗███████╗";
    gotoXY(12, 2);
    FixConsoleColor(244);
    cout << "██╔════╝████╗░██║██╔══██╗██║░██╔╝██╔════╝  ██╔════╝░██╔══██╗████╗░████║██╔════╝";
    gotoXY(12, 3);
    FixConsoleColor(244);
    cout << "╚█████╗░██╔██╗██║███████║█████═╝░█████╗░░  ██║░░██╗░███████║██╔████╔██║█████╗░░";
    gotoXY(12, 4);
    FixConsoleColor(244);
    cout << "░╚═══██╗██║╚████║██╔══██║██╔═██╗░██╔══╝░░  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░";
    gotoXY(12, 5);
    FixConsoleColor(244);
    cout << "██████╔╝██║░╚███║██║░░██║██║░╚██╗███████╗  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗";
    gotoXY(12, 6);
    FixConsoleColor(244);
    cout << "╚═════╝░╚═╝░░╚══╝╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝";


    gotoXY(35, 9);
    FixConsoleColor(244);
    cout << " █▄░▒█ ▒█░▒█ ▒█▀▀▀█ ▒█▀▄▀█   █▀▀";
    gotoXY(35, 10);
    FixConsoleColor(244);
    cout << "▒█▒█▒█ ▒█▀▀█ ▒█░░▒█ ▒█▒█▒█   ▀▀▄";
    gotoXY(35, 11);
    FixConsoleColor(244);
    cout << "▒█░░▀█ ▒█░▒█ ▒█▄▄▄█ ▒█░░▒█   ▄▄▀";



    gotoXY(25, 18);
    cout << " Loading...\n";
    gotoXY(25, 20);
    for (int i = 1; i <= 50; i++)
    {
        for (int t = 0; t <= 88888888; t++);
        FixConsoleColor(244);
        cout << "█";
    }
    Sleep(500);
    gotoXY(40, 22);
    cout << "PRESS ENTER TO BEGIN" << endl;
    for (int i = 1; i <= 2; ++i)
    {
        Sleep(250);
        gotoXY(40, 22);
        cout << "                          ";
        Sleep(250);
        gotoXY(40, 22);
        cout << "PRESS ENTER TO BEGIN" << endl;
    }
    while (true)
    {
        if (GetAsyncKeyState(VK_RETURN))
        {
            Sleep(200);
            break;
        }
    }

}

// thank for playing (fixed)
void ExitGame()
{
    system("cls");
    FixConsoleColor(208);
    gotoXY(3, 5);
    cout << "▀▀█▀▀▒█░▒█░█▀▀█▒█▄░▒█▒█░▄▀▒█▀▀▀█   ▒█▀▀▀▒█▀▀▀█▒█▀▀█   ▒█▀▀█▒█░░░░█▀▀█▒█░░▒█▀█▀▒█▄░▒█▒█▀▀█";
    gotoXY(3, 6);
    cout << "░▒█░░▒█▀▀█▒█▄▄█▒█▒█▒█▒█▀▄░░▀▀▀▄▄   ▒█▀▀▀▒█░░▒█▒█▄▄▀   ▒█▄▄█▒█░░░▒█▄▄█▒█▄▄▄█▒█░▒█▒█▒█▒█░▄▄";
    gotoXY(3, 7);
    cout << "░▒█░░▒█░▒█▒█░▒█▒█░░▀█▒█░▒█▒█▄▄▄█   ▒█░░░▒█▄▄▄█▒█░▒█   ▒█░░░▒█▄▄█▒█░▒█░░▒█░░▄█▄▒█░░▀█▒█▄▄█";
    gotoXY(3, 8);
    cout << "";
    gotoXY(20, 9);
    cout << "";
    gotoXY(20, 10);
    cout << "";

    FixConsoleColor(209);
    DrawMessBoard(25, 13, 16, 50);
    FixConsoleColor(208);
    Mes_exit();
    gotoXY(35, 19);
    FixConsoleColor(208);
    cout << "█▀▀ █▀█ █▀█ █▀▄   █▄▄ █▄█ █▀▀ █";
    gotoXY(35, 20);
    cout << "█▄█ █▄█ █▄█ █▄▀   █▄█ ░█░ ██▄ ▄";
    gotoXY(41, 29);
    cout << "⃝ PRESS ESC TO END ⃝" << endl;
    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
    }
    //Mes_Exit(45, 15);
    writeSaveFile();
    SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
    exit(0);
}

void setTextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawBoard(int height, int width, int posX, int posY)
{
    gotoXY(posX, posY); cout << "╔";
    for (int i = 1, j = 1; i < height + width; i++, j++)
    {
        if (i < width) { gotoXY(posX + i, posY + 0); cout << "═"; }
        else if (i == width) { gotoXY(posX + width, posY + 0); cout << "╗"; }
        else { gotoXY(posX + width, posY + i - width); cout << "║"; }

        if (j < height) { gotoXY(posX + 0, posY + j); cout << "║"; }
        else if (i == height) { gotoXY(posX + 0, posY + height); cout << "╚"; }
        else { gotoXY(posX + j - height, posY + height); cout << "═"; }
    }
    gotoXY(posX + width, posY + height); cout << "╝";
}

// fixed.
void drawIntroduction()
{
    system("cls");
    system("color D0");
    Sleep(50);
    //chỉ số bảng thông tin của ae
    const int BoardLeftX = InteractOrigin_x + 3;
    const int BoardLeftY = InteractOrigin_y + 2 + 4 + 2;
    const int BoardLeftW = GameWidth / 3 + 10;
    const int BoardLeftH = GameHeight - 4 - 4 - 2;
    const int MemX = BoardLeftX + 5;
    const int FirstMemY = BoardLeftY + 5;
    const int SecMemY = BoardLeftY + 7;
    const int ThirdMemY = BoardLeftY + 9;
    const int FourthMemY = BoardLeftY + 11;
    const int FifthMemy = BoardLeftY + 13;

    //Chỉ số bảng HowToPlay
    const int BoardRightW = GameWidth - BoardLeftW - 6;
    const int BoardRightH = GameHeight - 4;
    const int BoardRightX = BoardLeftX + BoardLeftW + 2;
    const int BoardRightY = InteractOrigin_y + 3;
    while (true) {
        //Nội dung bảng Howtoplay
        setTextColor(208);
        /*gotoXY(BoardRightX + BoardRightW / 2 - 6, BoardRightY - 1);*/
        gotoXY(BoardRightX + BoardRightW / 2 - 20, BoardRightY - 2);
        /*cout << "HOW TO PLAY";*/
        cout << "█░█ █▀█ █░█░█  ▀█▀ █▀█  █▀█ █░░ ▄▀█ █▄█";
        gotoXY(BoardRightX + BoardRightW / 2 - 20, BoardRightY - 1);
        cout << "█▀█ █▄█ ▀▄▀▄▀  ░█░ █▄█  █▀▀ █▄▄ █▀█ ░█░";
        setTextColor(209);
        drawBoard(BoardRightH, BoardRightW, BoardRightX - 1, BoardRightY);
        setTextColor(208);
        gotoXY(BoardRightX + 9, BoardRightY + 3);
        cout << "                          W   ";
        gotoXY(BoardRightX + 9, BoardRightY + 4);
        cout << "Control your snake with A   D ";
        gotoXY(BoardRightX + 9, BoardRightY + 5);
        cout << "                          S   ";
        gotoXY(BoardRightX + 9, BoardRightY + 7);
        cout << "Avoid hitting walls";
        gotoXY(BoardRightX + 9, BoardRightY + 9);
        cout << "Avoid hitting yourself";
        gotoXY(BoardRightX + 9, BoardRightY + 11);
        cout << "Try to eat enough food";
        gotoXY(BoardRightX + 9 + 10, BoardRightY + 12);
        cout << " to pass each level";
        gotoXY(BoardRightX + 9, BoardRightY + 14);
        cout << "Press Space to pause the game";
        gotoXY(BoardRightX + 5, BoardRightY + 18);
        setTextColor(214);
        cout << "FROM GROUP 5 - 21CTT4 - HCMUS WITH LOVE";
        //Nội dung bảng thông tin

        setTextColor(208);
        gotoXY(BoardLeftX + 3, BoardLeftY - 4);
        cout << "▄▄▄▄▄ ▄▄▄  ▄▄▄   ▄▄  ▄▄     ▄▄▄▄▄▄ ";
        gotoXY(BoardLeftX + 3, BoardLeftY - 3);
        cout << "  █   █■■ ▄█■█▄  █▀▄▄▀█     █▄▄▄▄▄ ";
        gotoXY(BoardLeftX + 3, BoardLeftY - 2);
        cout << "  ▀   ▀▀▀ ▀   ▀  ▀ ▀▀ ▀     ▄▄▄▄▄█ ";
        gotoXY(BoardLeftX + 3, BoardLeftY - 1);

        setTextColor(209);
        drawBoard(BoardLeftH, BoardLeftW, BoardLeftX - 1, BoardLeftY);
        setTextColor(208);
        gotoXY(MemX, FirstMemY);  cout << "Vũ Tiến Đạt             21120432";
        gotoXY(MemX, SecMemY); cout << "Trương Thế Hiển         21120450";
        gotoXY(MemX, ThirdMemY);    cout << "Nguyễn Đức Hoài         21120454";
        gotoXY(MemX, FourthMemY);  cout << "Nguyễn Gia Huy          21120468";
        gotoXY(MemX, FifthMemy); cout << "Châu Hoàng Khoa         21120481";
        setTextColor(208);
        gotoXY(BoardRightX + 10, BoardRightY + 23);
        cout << "PRESS ENTER TO RETURN MENU" << endl;
        if (GetAsyncKeyState(VK_RETURN))
            return;
    }
}

#pragma warning( pop )