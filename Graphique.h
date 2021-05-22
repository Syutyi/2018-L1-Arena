#ifndef GRAPHIQUE_H_INCLUDED
#define GRAPHIQUE_H_INCLUDED

// Bibliotheques graphiques
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "link.h"

SDL_Surface* initGraphique();
SDL_Surface*** initIMG();
SDL_Surface** initNomsJoueurs(char** listeJoueurs);
void affichageCarte(SDL_Surface* ecran, int** carte, int** joueursStats, SDL_Surface*** images, SDL_Surface** nomsJoueurs, int tours);
void affichageCarteAvecTir(SDL_Surface* ecran, int** carte, int** joueursStats, int** trajectoireTir, int* timing, int* continuer, SDL_Surface*** images, SDL_Surface** nomsJoueurs, int tours);
void affichageClassement(SDL_Surface* ecran, int* listClassement, SDL_Surface** nomsJoueurs, int** joueursStats, int tours, int dureePartie);
int continuPartie();
void pause();
void quitGraphique(SDL_Surface*** images, SDL_Surface** nomsJoueurs);

// Fonctions internes
void tir(SDL_Surface* ecran, int** carte, int** trajectoireTir, int x, int y, int* timing, SDL_Surface*** images, int* continuer);

#endif // GRAPHIQUE_H_INCLUDED
