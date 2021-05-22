#include "Bateau.h"

int testCollision(int** carte, int x, int y) {
    // Initialisation des variables
    int booleen = FALSE; // BOOLEEN testant s'il y a collision

    // Verification de collision, tout ce qui est different de l'eau
    if(carte[y][x] != MAP_VIDE) {
        booleen = TRUE;
    } else {
        booleen = FALSE;
    }

    return booleen;
}

void collision(int** carte, int** joueursStats, int** piratesStats, int joueurID, int x, int y) {
    // Initialisation des variables
    int idIA = 0; // ID de l'IA adverse
    // Test du type de collision afin d'affecter les bons bonus/malus
    if(carte[y][x] == MAP_LIMITE || carte[y][x] == MAP_ILE) {
        // Perte de la vie
        joueursStats[joueurID][ID_STAT_VIE] = VIE_FINAL_COLLISION_ILE;

        // Transformation du bateau en debris
        transformBateau(carte, x, y, joueurID, BATEAU_JOUEURS);
    } else if(carte[y][x] >= MAP_IA) {
        // Recuperation de l'id de l'IA touche
        idIA = recupJoueurID(carte[y][x], BATEAU_JOUEURS);

        // Perte de la vie du bateau ammorcant
        joueursStats[joueurID][ID_STAT_VIE] = VIE_FINAL_COLLISION_BATEAU;

        // Transformation du bateau en debris
        transformBateau(carte, x, y, joueurID, BATEAU_JOUEURS);

        // Verification de l'etat ou non de pirate
        if(idIA >= BATEAU_PIRATES) {
			// Perte de la vie du bateau touche
            piratesStats[idIA - BATEAU_PIRATES][ID_STAT_VIE] = VIE_FINAL_COLLISION_BATEAU;

			// Transformation du bateau en debris
			transformBateau(carte, x, y, idIA, BATEAU_PIRATES);
        } else {
        	// Perte de la vie du bateau touche
            joueursStats[idIA][ID_STAT_VIE] = VIE_FINAL_COLLISION_BATEAU;

			// Transformation du bateau en debris
			transformBateau(carte, x, y, idIA, BATEAU_JOUEURS);
        }

        // Augmentation du nombre de points du joueur
        joueursStats[joueurID][ID_STAT_PTS] += PTS_ACTION_COLLISION;
    } else {
        // Perte de la vie
        joueursStats[joueurID][ID_STAT_VIE] -= VIE_COLLISION_DEBRIS;

        // Verification de la mort
        if(joueursStats[joueurID][ID_STAT_VIE] <= 0) {
			// Transformation du bateau en debris
			transformBateau(carte, x, y, joueurID, BATEAU_JOUEURS);
        }
    }
}

void repCanonPropulsion(int** joueursStats, int joueurID) {
    // Reparation du canon
    if(joueursStats[joueurID][ID_STAT_SHOOT] > 0) {
        joueursStats[joueurID][ID_STAT_SHOOT] --;
    }

    // Reparation de la propulsion
    if(joueursStats[joueurID][ID_STAT_MOVE] > 0) {
        joueursStats[joueurID][ID_STAT_MOVE] --;
    }

    // Reparation de la propultion de capacite
    if (joueursStats[joueurID][ID_STAT_CAPACITE] > 0) {
        joueursStats[joueurID][ID_STAT_CAPACITE] --;
    }
}

void majVie(int** joueursStats) {
    // Initialisation des variables
    int i = 0; // Variable incrementatrice

    // Parcours de tous les joueurs
    for(i = 0; i < NOMBRE_JOUEURS; i++) {
        // Correction de la vie(vie innexacte pour l'annimation graphique)
        if(joueursStats[i][ID_STAT_VIE] < 0) {
            joueursStats[i][ID_STAT_VIE] = 0;
        }
    }
}

void iaPirate(int** carte, int largeur, int hauteur, int** joueursStats, int** piratesStats) {
    // A CHANGER****************************************
}

int testVie(int** joueursStats) {
    // Initialisation des variables
    int i        = 0,     // Variable incrementatrice
        testVie1 = FALSE, // Test la vie d'un premier joueur
        testVie2 = FALSE; // Test la vie d'un second joueur, si un premier l'est

    // Verifie qu'au moins 2 joueur soient en vie
    for(i = 0; i < NOMBRE_JOUEURS; i++) {
        if(joueursStats[i][ID_STAT_VIE] > 0) {
            if(testVie1 == TRUE) {
                testVie2 = TRUE;
            }
            testVie1 = TRUE;
        }
    }

    return (testVie1 & testVie2);
}

void transformBateau(int** carte, int x, int y, int iaID, int typeBateau) {
    // Initialisation des variables
    int xCourant   = 0, // Variable d'increment representant l'abscisse
        yCourant   = 0; // Variable d'increment representant l'ordonnee

	// Transformation du bateau en debris
	for(yCourant = y - 4; yCourant < y + 4; yCourant++) {
		for(xCourant = x - 4; xCourant < x + 4; xCourant++) {
			// Si la case est accessible
			if(xCourant > 0 && xCourant < MAP_LARGEUR && yCourant > 0 && yCourant < MAP_HAUTEUR) {
				// Si la case contient un element du bateau de l'ia
				if(recupJoueurID(carte[yCourant][xCourant], BATEAU_JOUEURS) == iaID + typeBateau) {
					carte[yCourant][xCourant] = MAP_DEBRIS;
				}
			}
		}
	}
}
