#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cstring>
#include <iomanip> //para limpiar lineas
#include "cursor.h"
#include "mapa.h"
#include "dialogo.h" //esto es para los cuadros de texto

using namespace std;

int playerX = 1; // la posicion inicial
int playerY = 3;
bool cofre_abierto = false;

const int cofreX1[3] = {8, 9, 10}; // la posicion de los dos cofres
const int cofreX2[3] = {20, 21, 22};
const int cofreY[2] = {1, 1};

void moverCursor();

void limpiar() // limpiar las lineas
{

    moverCursor(0, HEIGHT + 3);
    std::cout << std::setfill(' ') << std::setw(WIDTH + 7) << " " << std::flush;
    // llena la linea con espacios, en base al ancho
}

void esperarConfirmacion()
{
    moverCursor(0, HEIGHT + 3);
    cout << "Presiona cualquier tecla para continuar...";
    _getch();

    limpiar(); // para quitar la linea
}

void mostrarMapa()
{
    moverCursor(0, 0);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (x == playerX && y == playerY)
                cout << "@"; // Main character
            else
                cout << mapa[y][x];
        }
        cout << '\n';
    }

    cout << "\nUsa W A S D para moverte. Q para salir.\n";
}

void interactuarConCofre(int num_cofre)
{
    dibujarDialogo("Desea abrir el cofre? (y/n)");
    char respuesta;
    do
    {
        respuesta = tolower(_getch()); // obtiene la respuesta

    } while (respuesta != 'y' && respuesta != 'n');

    if (respuesta == 'y')
    {
        cofre_abierto = true;

        if (num_cofre == 1) // el primer cofre
        {
            for (int i = 0; i < 3; i++)
            {
                mapa[cofreY[0]][cofreX1[i]] = ' '; // quitar cofres
            }

            for (int i = 0; i < 3; i++)
            {
                mapa[cofreY[1]][cofreX2[i]] = ' ';
            }
            mostrarMapa();
            dibujarDialogo("Encontraste una pocion!", 6);
            esperarConfirmacion();
        }

        else if (num_cofre == 2) // el segundo cofre
        {
            for (int i = 0; i < 3; i++)
            {
                mapa[cofreY[1]][cofreX2[i]] = ' ';
            }
            for (int i = 0; i < 3; i++)
            {
                mapa[cofreY[0]][cofreX1[i]] = ' ';
            }
            mostrarMapa();
            dibujarDialogo("Encontraste un mounstro", 4);
            dibujarDialogo("Mala suerte!", 7);
            esperarConfirmacion();
        }
    }
    else
    {
        dibujarDialogo("No has abierto el cofre", 5);
    }
    esperarConfirmacion(); // para continuar
}

int estaEnCofre(int x, int y) // saber si el jugador esta en un cofre
{
    if (y == cofreY[0]) // primer cofre
    {
        for (int i = 0; i < 3; i++)
        {
            if (x == cofreX1[i])
            {
                playerX = playerX; // para no quedar sobre el cofre
                playerY = playerY;
                return 1; // devuelve el valor en caso si este en el cofre
            }
        }
    }
    if (y == cofreY[1]) // segundo cofre
    {
        for (int i = 0; i < 3; i++)
        {
            if (x == cofreX2[i])
            {
                playerX = playerX;
                playerY = playerY;
                return 2;
            }
        }
    }
    return 0; // esto si no esta en ninguno
}

bool esPosicionCofre(int x, int y)
{
    if (y == cofreY[0])
    {
        for (int i = 0; i < 3; i++)
        {
            if (x == cofreX1[i])
                return true;
        }
    }
    if (y == cofreY[1])
    {
        for (int i = 0; i < 3; i++)
        {
            if (x == cofreX2[i])
                return true;
        }
    }
    return false;
}

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

int main()
{
    if (!cargarMapaDesdeArchivo("mapa.txt", mapa)) //llamado de mapa.h
    {
        return 1; // en dado caso no se cargue el mapa
    }

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);

    char tecla;
    do
    {
        mostrarMapa();
        tecla = tolower(_getch());
        moverJugador(tecla);
    } while (tecla != 'q');

    return 0;
}
