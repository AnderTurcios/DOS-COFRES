#pragma once
#include "cofres.h" //NO DEBE INCLUIR

int playerX = 1; // la posicion inicial
int playerY = 3;
bool cofre_abierto = false;

void moverJugador(char tecla)
{
    int nuevoX = playerX;
    int nuevoY = playerY;

    if (tecla == 'w')
        nuevoY--;
    else if (tecla == 's')
        nuevoY++;
    else if (tecla == 'a')
        nuevoX--;
    else if (tecla == 'd')
        nuevoX++;

    char lugar = mapa[nuevoY][nuevoX];

    if (lugar == '#' || lugar == '|') // colisiones de pared
    {
        return;
    }

    if (!cofre_abierto && esPosicionCofre(nuevoX, nuevoY)) // verifica si esta sobre el cofre
    {
        int cofre = estaEnCofre(nuevoX, nuevoY);
        if (cofre != 0)
        {
            interactuarConCofre(cofre);
        }
        return;
    }

    playerX = nuevoX; // actualiza la posicion
    playerY = nuevoY;
}

