#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "cursor.h"

using namespace std;

const int WIDTH = 35;
const int HEIGHT = 10;
char mapa[HEIGHT][WIDTH + 1]; //el mapa

bool cargarMapaDesdeArchivo(const string &nombreArchivo, char mapaDestino[HEIGHT][WIDTH + 1])
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) // si no fue posible abrir el archivo
    {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return false;
    }

    string linea;
    for (int y = 0; y < HEIGHT; ++y)
    {
        if (!getline(archivo, linea)) // Para verificar si ha fallado al leer una linea
        {
            cerr << "Error: el archivo tiene menos de " << HEIGHT << " líneas." << endl;
            return false;
        }
        if (linea.length() != WIDTH)
        {
            cerr << "Error: la línea " << y + 1 << " no tiene exactamente " << WIDTH << " caracteres." << endl;
            return false;
        }
        strcpy(mapaDestino[y], linea.c_str()); // copia la linea leida al destino
    }

    archivo.close();
    return true; // cierra el archivo y retorna
}
