#pragma once // permite que el .h funcione
#include <windows.h>

const int x = 1, y = 1;

void moverCursor(int x, int y)
{
    COORD pos = {(SHORT)x, (SHORT)y};

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}