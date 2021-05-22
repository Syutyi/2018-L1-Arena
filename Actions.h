#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include "Link.h"

void avancer(int** carte, int** joueursStats, int** piratesStats, int joueurID, int distance);
int** tirer(int** carte, int** joueursStats, int** piratesStats, int joueurID);
void tourner(int** carte, int** joueursStats, int** piratesStats, int joueurID, int dirrection);

#endif // ACTIONS_H_INCLUDED
