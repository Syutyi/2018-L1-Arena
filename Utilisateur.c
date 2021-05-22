#include "Utilisateur.h"

int* classement(int** joueursStats, int dernierJoueurID) {
    // Initialisation des variables
    int *listClassement = NULL, // Tableau du classement
        changements     = 0,    // Compteur denombrant le nombre de changements
        temp            = 0,    // Variable temporaire
        nbrPremierEx    = 0,    // Nombre d'exequos en premiere position
        continuer       = TRUE, // BOOLEEN indiquant s'il faut ou non continuer
        i               = 0;    // Variable incrementatrice

    // Generation du tableau
    listClassement = (int*)malloc(NOMBRE_JOUEURS * sizeof(int));

    // Initialisation du tableau
    for(i = 0; i < NOMBRE_JOUEURS; i++) {
        listClassement[i] = i;
    }

    // Classement des joueurs selon la vie
    do {
        // Reinitialisation du nombre de changement
        changements = 0;

        // Remise a l'ordre des joueurs
        for(i = 0; i < NOMBRE_JOUEURS - 1; i++) {
            // Comparaison de la vie du joueur classe en position i et du joueur classe en position i+1
            if(joueursStats[listClassement[i]][ID_STAT_VIE] < joueursStats[listClassement[i + 1]][ID_STAT_VIE]) {
                // Changement en cas de mauvais classement
                temp                  = listClassement[i];
                listClassement[i]     = listClassement[i + 1];
                listClassement[i + 1] = temp;
                changements           ++;
            }
        }
    } while(changements > 0);

    // Classement des joueurs selon les points
    do {
        // Reinitialisation du nombre de changement
        changements = 0;

        // Remise a l'ordre des joueurs
        for(i = 0; i < NOMBRE_JOUEURS - 1; i++) {
            // Les deux joueurs adjacents ont autant de points de vie
            if(joueursStats[listClassement[i]][ID_STAT_VIE] == joueursStats[listClassement[i + 1]][ID_STAT_VIE]) {
                // Comparaison des points du joueur classe en position i et du joueur classe en position i+1
                if(joueursStats[listClassement[i]][ID_STAT_PTS] < joueursStats[listClassement[i + 1]][ID_STAT_PTS]) {
                    // Changement en cas de mauvais classement
                    temp                  = listClassement[i];
                    listClassement[i]     = listClassement[i + 1];
                    listClassement[i + 1] = temp;
                    changements           ++;
                }
            }
        }
    } while(changements > 0);

    // Reinitialisation des variables
    i            = 1;
    nbrPremierEx = 0;
    continuer    = TRUE;

    // Verification de l'existance d'exequos en premiere position
    while(continuer) {
        // Parcours des joueurs
        if(i < NOMBRE_JOUEURS) {
            // Verification de l'exequos du premier joueurs et du joueur classe en position i
            if(joueursStats[listClassement[0]][ID_STAT_VIE] == joueursStats[listClassement[i]][ID_STAT_VIE] &&
               joueursStats[listClassement[0]][ID_STAT_PTS] == joueursStats[listClassement[i]][ID_STAT_PTS]) {
                nbrPremierEx ++;
                i            ++;
            } else {
                continuer = FALSE;
            }
        } else {
            continuer = FALSE;
        }
    }

    // En cas d'egalite en premiere position
    if(nbrPremierEx > 0) {
        // Reinitialisation des variables
        int tempID = 0;
        i          = 0;
        continuer  = TRUE;

        // Recuperation du classement du dernier joueur ayant joue a la partie
        while(i < NOMBRE_JOUEURS && continuer) {
            if(listClassement[i] == dernierJoueurID) {
                tempID    = i;
                continuer = FALSE;
            }
            i ++;
        }

        // Remplacement des joueurs
        for(i = tempID; i > 0; i--) {
            listClassement[i] = listClassement[i - 1];
        }
        listClassement[0] = dernierJoueurID;
    }

    return listClassement;
}

int genBateauID(int iaID, int elementBateau, int type) {
    // Generation du code du bateau
    return (elementBateau * CODE_BATEAU) + type + iaID;
}

int recupJoueurID(int bateauID, int type) {
    // Recuperation de l'ID du joueur
    return (bateauID & FILTRAGE_JOUEUR_ID) - type;
}

int recupElementBateau(int bateauID, int type) {
    // Recuperation de l'ID de l'element du bateau
    return (bateauID & FILTRAGE_BATEAU_ID) / CODE_BATEAU;
}

int** genTabJoueur(int** carte) {
    // Initialisation des variables
    int **tab = NULL, // Tableau a transmettre au joueur
        i     = 0,    // Variable incrementatrice
        j     = 0;    // Variable incrementatrice

    // Generation du tableau
    tab = (int**)malloc((MAP_HAUTEUR + 1) * sizeof(int*));
    for(i = 0; i < MAP_HAUTEUR; i++) {
        tab[i] = (int*)malloc(MAP_LARGEUR * sizeof(int));
    }
    tab[MAP_HAUTEUR] = (int*)malloc(8 * sizeof(int));


    // Recuperation de la map
    for(i = 0; i < MAP_HAUTEUR; i++) {
        for(j = 0; j < MAP_LARGEUR; j++) {
            tab[i][j] = carte[i][j];
        }
    }

    // Initialisation des cases stats
    for(i = 0; i < 8; i++) {
        tab[MAP_HAUTEUR][i] = 0;
    }

    return tab;
}

void compTabJoueur(int** tabJoueur, int** carte, int** joueursStats, int joueurID) {
    // Initialisation des variables
    int i = 0, // Variable incrementatrice
        j = 0; // Variable incrementatrice

    // Veririfcation de la map
    for(i = 0; i < MAP_HAUTEUR; i++) {
        for(j = 0; j < MAP_LARGEUR; j++) {
            if(tabJoueur[i][j] != carte[i][j]) {
                tabJoueur[i][j] = carte[i][j];
            }
        }
    }

    // Modification des donnees joueurs
    for(i = 0; i < 8; i++) {
        tabJoueur[MAP_HAUTEUR][i] = joueursStats[joueurID][i];
    }
}

void modifierNomCombattant(char** nomsCombattant, int joueurID, char* nouveauNom) {
    // A CHANGER****************************************
}

int recupOrientation(int** carte, int x, int y) {
    // Initialisation des variables
    int i             = 0,    // Variable incrementatrice
        continuer     = TRUE, // Test de la continuation
        elementBateau = 0,    // Element du bateau
        iaID          = 0,    // ID de l'IA
        typeIA        = 0,    // Type de bateau
        xCourant      = 0,    // Abscisse courante
        yCourant      = 0,    // Ordonnee courante
        orientation   = 0;    // Orientation

	// Recuperation des elements de base
	elementBateau = recupElementBateau(carte[y][x], BATEAU_JOUEURS);
	iaID          = recupJoueurID(carte[y][x], BATEAU_JOUEURS);
	typeIA        = BATEAU_JOUEURS;

	// Verification du non etat de pirate
	if(iaID >= BATEAU_PIRATES) {
		iaID   -= BATEAU_PIRATES;
		typeIA =  BATEAU_PIRATES;
	}

    // Test de l'orientation
    while(i < 4 && continuer) {
        // Reinitialisation des coordonnees courantes
        xCourant = x;
        yCourant = y;

        // Verification de l'autorisation d'acces a la case
        switch(i) {
            case 0:
                if(x - 1 >= 0) {
                    xCourant = x - 1;
                }
            break;
            case 1:
                if(x + 1 < MAP_LARGEUR) {
                    xCourant = x + 1;
                }
            break;
            case 2:
                if(y - 1 >= 0) {
                    yCourant = y - 1;
                }
            break;
            case 3:
                if(y + 1 < MAP_HAUTEUR) {
                    yCourant = y + 1;
                }
            break;
        }

        // Test de l'appartenance de la case
        if((carte[yCourant][xCourant] == genBateauID(iaID, BATEAU_MILIEU, typeIA) && (elementBateau == BATEAU_AVANT || elementBateau == BATEAU_ARRIERE)) ||
           (carte[yCourant][xCourant] == genBateauID(iaID, BATEAU_AVANT, typeIA) && elementBateau == BATEAU_MILIEU)) {
            // Determination de l'orientation
            switch(i) {
                case 0:
                    if(elementBateau == BATEAU_AVANT) {
                        orientation = BATEAU_DROITE;
                    } else if(elementBateau == BATEAU_MILIEU || elementBateau == BATEAU_ARRIERE) {
                        orientation = BATEAU_GAUCHE;
                    }
                break;
                case 1:
                    if(elementBateau == BATEAU_AVANT) {
                        orientation = BATEAU_GAUCHE;
                    } else if(elementBateau == BATEAU_MILIEU || elementBateau == BATEAU_ARRIERE) {
                        orientation = BATEAU_DROITE;
                    }
                break;
                case 2:
                    if(elementBateau == BATEAU_AVANT) {
                        orientation = BATEAU_BAS;
                    } else if(elementBateau == BATEAU_MILIEU || elementBateau == BATEAU_ARRIERE) {
                        orientation = BATEAU_HAUT;
                    }
                break;
                case 3:
                    if(elementBateau == BATEAU_AVANT) {
                        orientation = BATEAU_HAUT;
                    } else if(elementBateau == BATEAU_MILIEU || elementBateau == BATEAU_ARRIERE) {
                        orientation = BATEAU_BAS;
                    }
                break;
            }

            // Demande de sortie de boucle
            continuer = FALSE;
        }

        i ++;
    }

    return orientation;
}
