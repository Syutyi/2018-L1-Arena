#ifndef UTILISATEUR_H_INCLUDED
#define UTILISATEUR_H_INCLUDED

#include "Link.h"

int* classement(int** joueursStats, int dernierJoueurID);
int genBateauID(int iaID, int elementBateau, int type);
int recupJoueurID(int bateauID, int type);
int recupElementBateau(int bateauID, int type);
int** genTabJoueur(int** carte);
void compTabJoueur(int** tabJoueur, int** carte, int** joueursStats, int joueurID);
void modifierNomCombattant(char** nomsCombattant, int joueurID, char* nouveauNom);
int recupOrientation(int** carte, int x, int y);

#endif // UTILISATEUR_H_INCLUDED
