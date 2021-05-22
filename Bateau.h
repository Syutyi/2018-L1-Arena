#ifndef BATEAU_H_INCLUDED
#define BATEAU_H_INCLUDED

#include "Link.h"

int testCollision(int** carte, int x, int y);
void collision(int** carte, int** joueursStats, int** piratesStats, int joueurID, int x, int y);
void repCanonPropulsion(int** joueursStats, int joueurID);
void majVie(int** joueursStats);
void iaPirate(int** carte, int largeur, int hauteur, int** joueursStats, int** piratesStats);
int testVie(int** joueursStats);
void transformBateau(int** carte, int x, int y, int iaID, int typeBateau);

#endif // BATEAU_H_INCLUDED
