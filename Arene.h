#ifndef ARENE_H_INCLUDED
#define ARENE_H_INCLUDED

#include "Link.h"

void arene();

// Fonctions internes
void desallocOrdre(int* ordre);
void desallocTrajectoire(int** trajectoire);
void desalloc(int** carte, int** carteCopie, int** joueursStats, int** piratesStats, int* listClassement);

#endif // ARENE_H_INCLUDED
