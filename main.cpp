#include "Header.h"
#include "sound.h"
#include "game.h"
#include "externalGraphics.h"
#include "fileProcessing.h"

using namespace std;

extern wifstream fin;
snake snake1;
gameState state = inMenu;
frame map[10];

unordered_map<wstring, frame> object;

list<button> buttons{
    {0, {35, 8}, 11, 3, L"RESUME"},
    {1, {35, 14}, 11, 3, L"SAVE GAME"},
    {2, {35, 20}, 11, 3, L"MAIN MENU"} };
list<button>::iterator cursor = buttons.begin();
int cursor2 = 0;
int cursor3 = 0;
int cursor4 = 0;
unsigned long long frameN = 0;
int level = 0, levelScore = 5;
bool paused = true;
bool start = false;
unsigned long long countDownStartTime = 0;

int color[5] = { 7+16*3 ,7+16*2 ,7+16*1 ,7+16*6 ,7+16*12 };
screen screen1(width, height), screen2(width * 2, height);
// Khai bao 2 ma tran
// Hàm đổi từ mảng 2 chiều sang mảng 1 chiều


// Trên bản đồ có đồ ăn ko
// Tạo đồ ăn
int food=-1;
wstring animationSnake[8] = { L"snakeMoving1",L"snakeMoving2",L"snakeMoving3" ,L"snakeMoving2", L"snakeMoving1", L"snakeMoving2",L"snakeMoving3",L"snakeMoving4" };
int speedSetting = 2;
coordinate portalPos = { -1, -1 };
int portalOrientation = 0;
unsigned long long portalSpawnTime = 0;
wstring MSSV = L"2112043221120450211204542112048121120468";
int maxLength = 40;
// Lấy các lệnh di chuyển
unordered_map<char, bool> key = { {'W', false}, {'S', false}, {'A', false}, {'D', false}, {' ', false},{'[', false},{']', false},{'|',false} };
extern vector<Save> save;
int startLoadIndex = 0;
HANDLE old = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);


int main()
{
    sound.playBackground();
    SetConsoleOutputCP(CP_UTF8);
    

    //-----------------------------------------------------------------
    // Thiet lap buffer
    LPCWSTR title = L"SNAKE - GROUP 5 - 21CTT4 - HCMUS";
    SetConsoleTitleW(title);
    
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    SMALL_RECT rect = { 0, 0, width - 1, height - 1 };
    SMALL_RECT rect2 = { 0, 0, width * 2 - 1, height - 1 };
    
    SetConsoleWindowInfo(buffer, TRUE, &rect);
    SetConsoleWindowInfo(old, TRUE, &rect2);
    SetConsoleScreenBufferSize(buffer, { width, height });
    SetConsoleScreenBufferSize(old, { width * 2, height });
    DWORD BytesWritten = 0;
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 18; // Width of each character in the font
    cfi.dwFontSize.Y = 18; // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_REGULAR;
    wcscpy(cfi.FaceName, L"Terminal"); // Choose your font
    SetCurrentConsoleFontEx(buffer, FALSE, &cfi);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(buffer, &info);
    SetConsoleCursorInfo(old, &info);

    _setmode(_fileno(stdin), _O_U8TEXT);
    //_setmode(_fileno(stdout), _O_U8TEXT);
    loading();
    
    //-----------------------------------------------------------------

    loadMics();
    loadMap();
    loadSaveFile();
    init(snake1);

    srand(chrono::system_clock::now().time_since_epoch().count());
    clear(screen1);
    clear(screen2);

    using clock = std::chrono::steady_clock;
    chrono::nanoseconds deltaTime(0ms), accumulator(0ms), accumulator1(0ms);
    auto t1 = clock::now();
    chrono::nanoseconds timestep(16ms);



    while (true)
    {
        deltaTime = clock::now() - t1;
        t1 = clock::now();
        accumulator += deltaTime;
        accumulator1 += deltaTime;
        input(); // Nhập các lệnh di chuyển

        switch (state) {
        case inMenu:
            if (accumulator > 120ms * (1.0 / (snake1.speed + speedSetting / 10)))
                accumulator -= chrono::duration_cast<chrono::nanoseconds>(120ms * (1.0 / (snake1.speed + speedSetting / 10)));
            SetConsoleActiveScreenBuffer(old);
            if (accumulator1 > timestep)
            {
                frameN++;
                accumulator1 -= timestep;
                clear(screen2);
                drawMenu();
                countDown();
                WriteConsoleOutputCharacterW(old, screen2.characters, width * height * 2, { 0, 0 }, &BytesWritten);
                WriteConsoleOutputAttribute(old, screen2.color, width * height * 2, { 0, 0 }, &BytesWritten);
            }
            break;
        case inGame:
        case inPaused:
        case gameOver:
            SetConsoleActiveScreenBuffer(buffer);

            // Nếu nếu khoảng thời gian từ mốc thời gian trước đến hiện tại bé hơn một khoảng thời gian thì thực hiện việc di chuyển rắn
            if (accumulator > 120ms * (1.0 / (snake1.speed + speedSetting / 10)))
            {
                accumulator -= chrono::duration_cast<chrono::nanoseconds>(120ms * (1.0 / (snake1.speed + speedSetting / 10)));
                update();
            }

            if (accumulator1 > timestep)
            {
                frameN++;
                accumulator1 -= timestep;
                clear(screen1); // Xoa man hinh
                draw(screen1, map[level], { 0, 0 }, 0, 1, 1);
                drawPortal();
                drawFood(food);
                draw(snake1); // Vẽ rắn
                drawSideBar();
                //countDown();
                showGameOver();
                // wsprintf(&screen1.characters[index(31, 0)], "FRAME: %d", frameN);
                WriteConsoleOutputCharacterW(buffer, screen1.characters, width * height, { 0, 0 }, &BytesWritten);
                WriteConsoleOutputAttribute(buffer, screen1.color, width * height, { 0, 0 }, &BytesWritten);
            }
            break;
        case inLoad:
            if (accumulator > 120ms * (1.0 / (snake1.speed + speedSetting / 10)))
                accumulator -= chrono::duration_cast<chrono::nanoseconds>(120ms * (1.0 / (snake1.speed + speedSetting / 10)));
            SetConsoleActiveScreenBuffer(old);
            if (accumulator1 > timestep)
            {
                frameN++;
                accumulator1 -= timestep;
                clear(screen2);
                drawLoadMenu();
                countDown();
                WriteConsoleOutputCharacterW(old, screen2.characters, width * height * 2, { 0, 0 }, &BytesWritten);
                WriteConsoleOutputAttribute(old, screen2.color, width * height * 2, { 0, 0 }, &BytesWritten);
            }
            break;
        case inHighscore:
        case inSetting:
            if (accumulator > 120ms * (1.0 / (snake1.speed + speedSetting / 10)))
                accumulator -= chrono::duration_cast<chrono::nanoseconds>(120ms * (1.0 / (snake1.speed + speedSetting/10)));
            SetConsoleActiveScreenBuffer(old);
            if (accumulator1 > timestep)
            {
                frameN++;
                accumulator1 -= timestep;
                clear(screen2);
                if (state == inSetting)
                    drawSetting();
                else
                    drawHighScore();
                WriteConsoleOutputCharacterW(old, screen2.characters, width * height * 2, { 0, 0 }, &BytesWritten);
                WriteConsoleOutputAttribute(old, screen2.color, width * height * 2, { 0, 0 }, &BytesWritten);
            }
            break;
        }

        
    }
    
    writeSaveFile();
    SetConsoleActiveScreenBuffer(old); // Trả lại buffer
    return 0;
}