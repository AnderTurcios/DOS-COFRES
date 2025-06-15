#pragma once
#include <iostream>
#include <string>
#include "cursor.h"
#include "mapa.h"

using namespace std;

void dibujarDialogo(const string &texto, int offsetY = 1)
{
    int ancho = texto.length() + 4; // la longitud del texto
    int startX = (WIDTH - ancho) / 2;
    int startY = offsetY;

    moverCursor(startX, startY);
    cout << char(201);
    for (int i = 0; i < ancho - 2; i++)
        cout << char(205);
    cout << char(187);
    moverCursor(startX, startY + 1);
    cout << char(186) << " " << texto << " " << char(186);
    moverCursor(startX, startY + 2);
    cout << char(200);
    for (int i = 0; i < ancho - 2; i++)
        cout << char(205);
    cout << char(188);
}
