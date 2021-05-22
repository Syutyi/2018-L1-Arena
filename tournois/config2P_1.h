#ifndef CONFIG_PLAYER_H_INCLUDED
#define CONFIG_PLAYER_H_INCLUDED

#include "../Link.h"

/*
 * CONFIGURATION DE LA PARTIE
 */
#define MAP_LARGEUR      50     // Largeur de la map // Min: 4 * TIR_PORTEE + (NOMBRE_JOUEURS * (TIR_PORTEE + 3)) / 2
#define MAP_HAUTEUR      50     // Hauteur de la map
#define NOMBRE_JOUEURS   6     // Nombre de joueurs
#define NOMBRE_PIRATES   2      // Nombre de pirates
#define TOUR_MAX         120    // Nombre de tours maximum
#define TEMPS_MAX        240000 // Temps maximum
#define TEMPS_INTER_TOUR 600    // Temps entre les tour
#define TEMPS_BOULET     20     // Temps entre deux images de deplacement de boulet
#define NOMS             {"J1", "J2", "J3", "J4", "J5", "J6"}
#define IAS              {test1, test2, test3, test4, test5, test6}

int* test1(int** carte, int largeur, int hauteur);
int* test2(int** carte, int largeur, int hauteur);
int* test3(int** carte, int largeur, int hauteur);
int* test4(int** carte, int largeur, int hauteur);
int* test5(int** carte, int largeur, int hauteur);
int* test6(int** carte, int largeur, int hauteur);

#endif // CONFIG_PLAYER_H_INCLUDED
