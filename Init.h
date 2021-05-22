#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "Link.h"

int** initJoueur(int** carte);
int** initPirate(int** carte);

// Fonctions internes
void placementIA(int** carte, int x, int y, int iaID, int orientation, int ia);
int placementValide(int** carte, int x, int y, int orientation);
void videContour(int** carte, int x, int y);

#endif // INIT_H_INCLUDED
