#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "Link.h"

int** genMap();
void repareMap(int** carte);
void transformMap(int** carte, int** trajectoire, int** joueursStats, int** piratesStats);
void retrecissementMap(int** carte, int** joueursStats, int** piratesStats, int* coordLimites);

// Fonctions internes
int ileValide(int case_tab);
void genMap1(int** tab, int coord1, int coord2, int* nb_case_ile);
void genMap2(int** tab, int coord1, int coord2, int* nb_case_ile);
void genMap3(int** tab, int coord1, int coord2, int* nb_case_ile);
void genMap4(int** tab, int coord1, int coord2, int* nb_case_ile);
void genMap5(int** tab, int coord1, int coord2, int* nb_case_ile);
void genMap6(int** tab, int coord1, int coord2, int* nb_case_ile);

#endif // MAP_H_INCLUDED
