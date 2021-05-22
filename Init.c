#include "Init.h"

int** initJoueur(int** carte) {
    // Initialisation des variables
    int **stat        = NULL, // Tableau des stats du joueur
        i             = 0,    // Variable incrementatrice
        repartJoueurs = 0,    // Repartition des joueurs
        orientation   = 0,    // Orientation du joueur
        coord1        = 0,    // Abscisse du joueur
        coord2        = 0;    // Ordonnee du joueur

    // Determination de la repartition des joueurs
    repartJoueurs = (int)ceil(NOMBRE_JOUEURS/4.0);

    // Generation du tableau des stats des joueurs
    stat = (int**)malloc(NOMBRE_JOUEURS * sizeof(int*));

    // Determination des informations des joueurs
    for(i = 0; i < NOMBRE_JOUEURS; i++) {
        // Generation du tableau des stats
        stat[i] = (int*)malloc(8 * sizeof(int));

        // Initialisation du tableau des stats
        stat[i][ID_STAT_VIE]      = 100;
        stat[i][ID_STAT_PTS]      = 0;
        stat[i][ID_STAT_SHOOT]    = 0;
        stat[i][ID_STAT_MOVE]     = 0;
        stat[i][ID_STAT_X]        = 0;
        stat[i][ID_STAT_Y]        = 0;
        stat[i][ID_STAT_CAPACITE] = 0;
        stat[i][ID_JOUEUR_ID]     = i;

        // Determination de la position du joueur
        if(i < repartJoueurs) {
            // On positione le joueur sur l'horizontale haute
            coord1      = (MAP_LARGEUR - (TIR_PORTEE + 2) * (repartJoueurs - 1)) / 2 + (TIR_PORTEE + 2) * i;
            coord2      = (MAP_HAUTEUR - (TIR_PORTEE + 3) * (repartJoueurs)) / 2;
            orientation = BATEAU_HAUT;
        } else if(i < 2 * repartJoueurs) {
            // On positione le joueur sur l'horizontale basse
            coord1      = (MAP_LARGEUR - (TIR_PORTEE + 2) * (repartJoueurs - 1)) / 2 + (TIR_PORTEE + 2) * (i - repartJoueurs);
            coord2      = (MAP_HAUTEUR + (TIR_PORTEE + 3) * (repartJoueurs)) / 2;
            orientation = BATEAU_BAS;
        } else {
            // On positionne le joueur alternativement sur la verticale gauche, puis droite
            if(i%2 == 0) {
                // Positionnement sur la verticale gauche
                coord1      = (MAP_LARGEUR - (TIR_PORTEE + 3) * (repartJoueurs)) / 2;
                coord2      = (MAP_HAUTEUR - (TIR_PORTEE + 2) * (repartJoueurs - 1) + (TIR_PORTEE + 2) * (i - 2 * repartJoueurs)) / 2;
                orientation = BATEAU_GAUCHE;
            } else {
                // Positionnement sur la verticale droite
                coord1      = (MAP_LARGEUR + (TIR_PORTEE + 3) * (repartJoueurs)) / 2;
                coord2      = (MAP_HAUTEUR - (TIR_PORTEE + 2) * (repartJoueurs - 1) + (TIR_PORTEE + 2) * (i - 2 * repartJoueurs)) / 2;
                orientation = BATEAU_DROITE;
            }
        }

        // Recuperation des coordonnees
        stat[i][ID_STAT_X] = coord1;
        stat[i][ID_STAT_Y] = coord2;

        // Placement du joueur sur la map
        placementIA(carte, coord1, coord2, i, orientation, BATEAU_JOUEURS);
    }

    return stat;
}

int** initPirate(int** carte) {
    // Initialisation des variables
    int **tab       = NULL, // Tableau des stats des pirates
        i           = 0,    // Variable incrementatrice
        orientation = 0,    // Orientation du bateau du pirate
        coord1      = 0,    // Abscisse de l'avant du bateau
        coord2      = 0;    // Oronneee de l'avant du bateau

    // Generation du tableau des stats des pirates
    tab = (int**)malloc(NOMBRE_PIRATES * sizeof(int*));

    // Determination des informations des pirates
    for(i = 0; i < NOMBRE_PIRATES; i++) {
        // Generation du tableau des stats
        tab[i] = (int*)malloc(6 * sizeof(int));

        // Initialisation du tableau des stats
        tab[i][ID_STAT_VIE]   = 100;
        tab[i][ID_STAT_PTS]   = 0;
        tab[i][ID_STAT_SHOOT] = 0;
        tab[i][ID_STAT_MOVE]  = 0;
        tab[i][ID_STAT_X]     = 0;
        tab[i][ID_STAT_Y]     = 0;

        // Verification d'un placement valide
        do {
            // Generation de la position relative aleatoire
            coord1 = rand() % (MAP_LARGEUR / 2) - (MAP_LARGEUR / 4);

            // Placement du pirate de l'autre cote de la map
            if(coord1 <= 0) {
                coord1 += MAP_LARGEUR - 2;
            }

            // Generation de la position relative aleatoire
            coord2 = rand() % (MAP_HAUTEUR / 2) - (MAP_HAUTEUR / 4);

            // Placement du pirate de l'autre cote de la map
            if(coord2 <= 0) {
                coord2 += MAP_HAUTEUR - 2;
            }

            // Determination de l'orientation
            orientation = rand() % 4;
        } while(!placementValide(carte, coord1, coord2, orientation));

        // Recuperation des coordonnees
        tab[i][ID_STAT_X] = coord1;
        tab[i][ID_STAT_Y] = coord2;

        // Placement du pirate sur la map
        placementIA(carte, coord1, coord2, i, orientation, BATEAU_PIRATES);
    }

    return tab;
}

void placementIA(int** carte, int x, int y, int iaID, int orientation, int ia) {
    // Placement de l'avant du bateau
    carte[y][x] = genBateauID(iaID, BATEAU_AVANT, ia);

    // Placement du reste selon l'orientation choisie
    if(orientation == BATEAU_HAUT) {
        carte[y + 1][x] = genBateauID(iaID, BATEAU_MILIEU, ia);
        carte[y + 2][x] = genBateauID(iaID, BATEAU_ARRIERE, ia);
    } else if(orientation == BATEAU_BAS) {
        carte[y - 1][x] = genBateauID(iaID, BATEAU_MILIEU, ia);
        carte[y - 2][x] = genBateauID(iaID, BATEAU_ARRIERE, ia);
    } else if(orientation == BATEAU_GAUCHE) {
        carte[y][x + 1] = genBateauID(iaID, BATEAU_MILIEU, ia);
        carte[y][x + 2] = genBateauID(iaID, BATEAU_ARRIERE, ia);
    } else if(orientation == BATEAU_DROITE) {
        carte[y][x - 1] = genBateauID(iaID, BATEAU_MILIEU, ia);
        carte[y][x - 2] = genBateauID(iaID, BATEAU_ARRIERE, ia);
    }

    // Vider le contour du joueur
    videContour(carte, x, y);
}

int placementValide(int** carte, int x, int y, int orientation) {
    // Initialisation des variables
    int valide = TRUE; // Test la validite de la position

    // Test par l'orientation et les limites de la map
    if(orientation == BATEAU_HAUT && (y <= 2 || x <= 1 || x >= MAP_LARGEUR - 2)) {
        valide = FALSE;
    } else if(orientation == BATEAU_BAS && (y >= MAP_HAUTEUR - 3 || x <= 1 || x >= MAP_LARGEUR - 2)) {
        valide = FALSE;
    } else if(orientation == BATEAU_DROITE && (x >= MAP_LARGEUR - 3 || y <= 1 || y >= MAP_HAUTEUR - 2)) {
        valide = FALSE;
    } else if(orientation == BATEAU_GAUCHE && (x <= 2 || y <= 1 || y >= MAP_HAUTEUR - 2)) {
        valide = FALSE;
    } else {
        // Test par la place occupe apres placement avec verification d'une possibilite de deplacement au premier tour
        if(carte[y][x] == MAP_VIDE) {
            if(orientation == BATEAU_HAUT && (carte[y+1][x] != MAP_VIDE || carte[y+2][x] != MAP_VIDE || carte[y-1][x-1] != MAP_VIDE || carte[y-1][x] != MAP_VIDE || carte[y-1][x+1] != MAP_VIDE)) {
                valide = FALSE;
            } else if(orientation == BATEAU_BAS && (carte[y-1][x] != MAP_VIDE || carte[y-2][x] != MAP_VIDE || carte[y+1][x-1] != MAP_VIDE || carte[y+1][x] != MAP_VIDE || carte[y+1][x+1] != MAP_VIDE)) {
                valide = FALSE;
            } else if(orientation == BATEAU_DROITE && (carte[y][x-1] != MAP_VIDE || carte[y][x-2] != MAP_VIDE || carte[y-1][x+1] != MAP_VIDE || carte[y][x+1] != MAP_VIDE || carte[y+1][x+1] != MAP_VIDE)) {
                valide = FALSE;
            } else if(orientation == BATEAU_GAUCHE && (carte[y][x+1] != MAP_VIDE || carte[y][x+2] != MAP_VIDE || carte[y-1][x-1] != MAP_VIDE || carte[y][x-1] != MAP_VIDE || carte[y+1][x-1] != MAP_VIDE)) {
                valide = FALSE;
            }
        } else {
            valide = FALSE;
        }
    }

    return valide;
}

void videContour(int** carte, int x, int y) {
    // Initialisation des variables
    int i = 0, // Variable incrementatrice
        j = 0; // Variable incrementatrice

    // Vidage du contour du joueur
    for(i = y - 3; i <= y + 3; i++) {
        for(j = x - 3; j <= x + 3; j++) {
            // Verification du droit d'acces a la case
            if(i > 0 && j > 0 && i < MAP_HAUTEUR && j < MAP_LARGEUR) {
                // Si la case n'est pas une IA, ni une limite, on la vide
                if(carte[i][j] < MAP_VIDE && carte[i][j] != MAP_LIMITE) {
                    carte[i][j] = MAP_VIDE;
                }
            }
        }
    }
}
