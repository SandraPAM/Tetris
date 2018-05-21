//
//  Figuras.h
//  Tetris
//
//  Created by Sandra Bravo Marmolejo on 28/11/17.
//  Copyright © 2017 Sandra Bravo Marmolejo. All rights reserved.
//

#ifndef Figuras_h
#define Figuras_h

#include <stdio.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>

typedef  enum {
    NEGRO,              AZUL_MARINO,        AZUL_FUERTE,
    VERDE_PASTO,        VERDE_PERRY,       AZUL,
    VERDE_BRILLANTE,    VERDE_SHINE_O,      CYAN,
    MARRON,             MORADO_FUERTE,      MORADO,
    VERDE_PISTACHE,     GRIS,               LILA,
    VERDE_CLARO,        VERDE_CLARO_O,      AZUL_CYAN,
    ROJO,               ROSA_FUERTE,        MAGENTA,
    NARANJA,            NARANJA_OPACO,      ROSA,
    AMARILLO,           AMARILLO_OPACO,     BLANCO,
    GRIS1,              GRIS2,              GRIS3
}COLOR27;

typedef struct
{
    float x,y;
}PUNTO;

typedef struct FIGURA
{
    int indexType;
    PUNTO vertices[14]; //10 de estos vértices rperesentan los vértices en los 4 cuadrados que forman a la figura
    //Los ultimos 4 son los puntos medios de estos cuadrados
    int Limits[4];
    struct FIGURA *next;
}FIGURA;

void GiveColor(COLOR27 color);
FIGURA* CrearFigura(void);
FIGURA *IngresaFigura(FIGURA *fig, FIGURA *newF);
void DatosFigura(FIGURA *newF, int indexType);
void DrawFig(FIGURA *fig);
void LiberarMemoria(FIGURA *figArray);
FIGURA *DeleteLast(FIGURA * figArray);
void LImits( FIGURA *fig,int xmin, int ymin, int xmax, int ymax);

void Rotation(float angle,int x, int y);
void Traslation(int Tx, int Ty, int x, int y);
#endif /* Figuras_h */

