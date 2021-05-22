#include "Map.h"

int** genMap() {
    // Initialisation des variables
    int **tab       = NULL,                    // Tableau contenant la map
        i           = 0,                       // Variable incrementatrice
        j           = 0,                       // Variable incrementatrice
        nb_case_tot = MAP_HAUTEUR*MAP_LARGEUR, // Nombres de cases sur la map
        nb_case_ile = 0,                       // Nombre de cases d'iles
        modele      = 0,                       // Modele utilise, 6 modèles au total: 1 de 1 case, 1 de 3 cases, 1 de 6 cases, 2 de 9 cases et 1 de 13 cases
        coord1      = 0,                       // Abscisse du centre de l'ile
        coord2      = 0;                       // Ordonnee du centre de l'ile

    // Generation de la map de base
    tab = (int**)malloc(MAP_HAUTEUR * sizeof(int*));
    for(i = 0; i < MAP_HAUTEUR; i++) {
        tab[i] = (int*)malloc(MAP_LARGEUR * sizeof(int));
        for(j = 0; j < MAP_LARGEUR; j++) {
            // Gestion des iles de contour
            if(i == 0 || j == 0 || i == (MAP_HAUTEUR - 1) || j == (MAP_LARGEUR - 1)) {
                tab[i][j] = MAP_LIMITE;
            } else {
                tab[i][j] = MAP_VIDE;
            }
        }
    }

    // Determination du nombre d'iles a creer
    nb_case_ile = (rand() % ((int)(nb_case_tot/18))) + (int)(nb_case_tot/6);

    // Creation du nombre d'ile determine ci-dessus
    while(nb_case_ile > 0) {
        // Determoination du modele a appliquer, selon le nombre de case d'ile restant a creer
        if(nb_case_ile == 1 || nb_case_ile == 2) {
            modele = 1;
        } else if(nb_case_ile == 3 || nb_case_ile == 4 || nb_case_ile == 5) {
            modele = (rand() % 2) + 1;
        } else if(nb_case_ile == 6 || nb_case_ile == 7 || nb_case_ile == 8) {
            modele = (rand() % 3) + 1;
        } else if(nb_case_ile == 9 || nb_case_ile == 10 || nb_case_ile == 11 || nb_case_ile == 12) {
            modele = (rand() % 5) + 1;
        } else {
            modele = (rand() % 6)+1;
        }

        // Generation des cooronnees du centre de l'ile a generer
        coord1 = (rand() % (MAP_HAUTEUR - 2)) + 1;
        coord2 = (rand() % (MAP_LARGEUR - 2)) + 1;

        // Dessin du modele
        switch(modele) {
            case 1:
                genMap1(tab, coord1, coord2, &nb_case_ile);
            break;
            case 2:
                genMap2(tab, coord1, coord2, &nb_case_ile);
            break;
            case 3:
                genMap3(tab, coord1, coord2, &nb_case_ile);
            break;
            case 4:
                genMap4(tab, coord1, coord2, &nb_case_ile);
            break;
            case 5:
                genMap5(tab, coord1, coord2, &nb_case_ile);
            break;
            case 6:
                genMap6(tab, coord1, coord2, &nb_case_ile);
            break;
        }
    }

    return tab;
}

void repareMap(int** carte) {
    // Initialisation des variables
    int i = 0, // Variable incrementatrice
        j = 0; // Variable incrementatrice

    // Parcours de la map
    for(i = 0; i < MAP_HAUTEUR; i++) {
        for(j = 0; j < MAP_LARGEUR; j++) {
            // Si la case doit etre repare, on la repare
            if(carte[i][j] >= MAP_DEBRIS && carte[i][j] < MAP_VIDE) {
                carte[i][j] ++;
            }
        }
    }
}

void transformMap(int** carte, int** trajectoire, int** joueursStats, int** piratesStats) {
    // Initialisation des variables
    int x = 0, // Abscisse cible
        y = 0; // Ordonnee cible

    // Recuperation des coordonnees cibles
    x = trajectoire[0][0];
    y = trajectoire[0][1];

    // Verification du type de case pour la transformation en debris
    if(carte[y][x] != MAP_LIMITE && carte[y][x] <= MAP_VIDE) {
        // Il s'agit d'une ile ou de l'eau
        carte[y][x] = MAP_DEBRIS;
    } else if(carte[y][x] >= MAP_IA) {
        // Il s'agit d'un joueur

        // Initialisation des variables internes
        int ia_touche = recupJoueurID(carte[y][x], BATEAU_JOUEURS); // Joueur touche

        // Verification du statut de joueur ou de pirate
        if(ia_touche < BATEAU_PIRATES) {
            // Il s'agit d'un joueur

            // Recuperation de la position du joueur touche
            x = joueursStats[ia_touche][ID_STAT_X];
            y = joueursStats[ia_touche][ID_STAT_Y];

            // Verification de la mort du pirate
            if(joueursStats[ia_touche][ID_STAT_VIE] <= 0) {
                transformBateau(carte, x, y, ia_touche, BATEAU_JOUEURS);
            }
        } else {
            // Il s'agit d'un pirate

            // Recuperation de l'ID du pirate touche, de sa position
            ia_touche -= BATEAU_PIRATES;
            x          = joueursStats[ia_touche][ID_STAT_X];
            y          = joueursStats[ia_touche][ID_STAT_Y];

            // Verification de la mort du pirate
            if(piratesStats[ia_touche][ID_STAT_VIE] <= 0) {
                transformBateau(carte, x, y, ia_touche, BATEAU_PIRATES);
            }
        }
    }
}

void retrecissementMap(int** carte, int** joueursStats, int** piratesStats, int* coordLimites) {
	// Initialisation des variables
	int dir = 0, // Direction a enlever
        i   = 0; // Variable incrementatrice

    // Generation de la dirrection
    dir = rand() % 4;

    // Verification de la dirrection
    switch(dir) {
		case 0:
			// On veut supprimer le haut de la map

			// Parcours sur la longueur
			for(i = 0; i < MAP_LARGEUR; i++) {
                // Verification de l'etat ou non d'IA
                if(carte[coordLimites[MAP_LIMITE_HAUT]][i] >= MAP_IA) {
                    // On verifie l'etat de pirate
                    if(recupJoueurID(carte[coordLimites[MAP_LIMITE_HAUT]][i], BATEAU_JOUEURS) >= BATEAU_PIRATES) {
                        // On supprime le pirate
                        piratesStats[recupJoueurID(carte[coordLimites[MAP_LIMITE_HAUT]][i], BATEAU_PIRATES)][ID_STAT_VIE] = 0;
                        transformBateau(carte, i, coordLimites[MAP_LIMITE_HAUT], recupJoueurID(carte[coordLimites[MAP_LIMITE_HAUT]][i], BATEAU_PIRATES), BATEAU_PIRATES);
                    } else {
                        // On supprime le joueur
                        joueursStats[recupJoueurID(carte[coordLimites[MAP_LIMITE_HAUT]][i], BATEAU_JOUEURS)][ID_STAT_VIE] = 0;
                        transformBateau(carte, i, coordLimites[MAP_LIMITE_HAUT], recupJoueurID(carte[coordLimites[MAP_LIMITE_HAUT]][i], BATEAU_JOUEURS), BATEAU_JOUEURS);
                    }
                }

                // On supprime la ligne de la Map
                carte[coordLimites[MAP_LIMITE_HAUT]][i] = MAP_LIMITE;
			}

			// MAJ des nouvelles coordonnees des limites
			coordLimites[MAP_LIMITE_HAUT] ++;
		break;
		case 1:
			// On veut supprimer le bas de la map

			// Parcours sur la longueur
			for(i = 0; i < MAP_LARGEUR; i++) {
                // Verification de l'etat ou non d'IA
                if(carte[coordLimites[MAP_LIMITE_BAS]][i] >= MAP_IA) {
                    // On verifie l'etat de pirate
                    if(recupJoueurID(carte[coordLimites[MAP_LIMITE_BAS]][i], BATEAU_JOUEURS) >= BATEAU_PIRATES) {
                        // On supprime le pirate
                        piratesStats[recupJoueurID(carte[coordLimites[MAP_LIMITE_BAS]][i], BATEAU_PIRATES)][ID_STAT_VIE] = 0;
                        transformBateau(carte, i, coordLimites[MAP_LIMITE_BAS], recupJoueurID(carte[coordLimites[MAP_LIMITE_BAS]][i], BATEAU_PIRATES), BATEAU_PIRATES);
                    } else {
                        // On supprime le joueur
                        joueursStats[recupJoueurID(carte[coordLimites[MAP_LIMITE_BAS]][i], BATEAU_JOUEURS)][ID_STAT_VIE] = 0;
                        transformBateau(carte, i, coordLimites[MAP_LIMITE_BAS], recupJoueurID(carte[coordLimites[MAP_LIMITE_BAS]][i], BATEAU_JOUEURS), BATEAU_JOUEURS);
                    }
                }

                // On supprime la ligne de la Map
                carte[coordLimites[MAP_LIMITE_BAS]][i] = MAP_LIMITE;
			}

			// MAJ des nouvelles coordonnees des limites
			coordLimites[MAP_LIMITE_BAS] --;
		break;
		case 2:
			// On veut supprimer la gauche de la map

			// Parcours sur la hauteur
			for(i = 0; i < MAP_HAUTEUR; i++) {
                // Verification de l'etat ou non d'IA
                if(carte[i][coordLimites[MAP_LIMITE_GAUCHE]] >= MAP_IA) {
                    // On verifie l'etat de pirate
                    if(recupJoueurID(carte[i][coordLimites[MAP_LIMITE_GAUCHE]], BATEAU_JOUEURS) >= BATEAU_PIRATES) {
                        // On supprime le pirate
                        piratesStats[recupJoueurID(carte[i][coordLimites[MAP_LIMITE_GAUCHE]], BATEAU_PIRATES)][ID_STAT_VIE] = 0;
                        transformBateau(carte, i, coordLimites[MAP_LIMITE_GAUCHE], recupJoueurID(carte[i][coordLimites[MAP_LIMITE_GAUCHE]], BATEAU_PIRATES), BATEAU_PIRATES);
                    } else {
                        // On supprime le joueur
                        joueursStats[recupJoueurID(carte[i][coordLimites[MAP_LIMITE_GAUCHE]], BATEAU_JOUEURS)][ID_STAT_VIE] = 0;
                        transformBateau(carte, i, coordLimites[MAP_LIMITE_GAUCHE], recupJoueurID(carte[i][coordLimites[MAP_LIMITE_GAUCHE]], BATEAU_JOUEURS), BATEAU_JOUEURS);
                    }
                }

                // On supprime la ligne de la Map
                carte[i][coordLimites[MAP_LIMITE_GAUCHE]] = MAP_LIMITE;
			}

			// MAJ des nouvelles coordonnees des limites
			coordLimites[MAP_LIMITE_GAUCHE] ++;
		break;
		default:
			// On veut supprimer la droite de la map

			// Parcours sur la hauteur
			for(i = 0; i < MAP_HAUTEUR; i++) {
                // Verification de l'etat ou non d'IA
                if(carte[i][coordLimites[MAP_LIMITE_DROITE]] >= MAP_IA) {
                    // On verifie l'etat de pirate
                    if(recupJoueurID(carte[i][coordLimites[MAP_LIMITE_DROITE]], BATEAU_JOUEURS) >= BATEAU_PIRATES) {
                        // On supprime le pirate
                        piratesStats[recupJoueurID(carte[i][coordLimites[MAP_LIMITE_DROITE]], BATEAU_PIRATES)][ID_STAT_VIE] = 0;
                        transformBateau(carte, i, coordLimites[MAP_LIMITE_DROITE], recupJoueurID(carte[i][coordLimites[MAP_LIMITE_DROITE]], BATEAU_PIRATES), BATEAU_PIRATES);
                    } else {
                        // On supprime le joueur
                        joueursStats[recupJoueurID(carte[i][coordLimites[MAP_LIMITE_DROITE]], BATEAU_JOUEURS)][ID_STAT_VIE] = 0;
                        transformBateau(carte, i, coordLimites[MAP_LIMITE_DROITE], recupJoueurID(carte[i][coordLimites[MAP_LIMITE_DROITE]], BATEAU_JOUEURS), BATEAU_JOUEURS);
                    }
                }

                // On supprime la ligne de la Map
                carte[i][coordLimites[MAP_LIMITE_DROITE]] = MAP_LIMITE;
			}

			// MAJ des nouvelles coordonnees des limites
			coordLimites[MAP_LIMITE_DROITE] --;
		break;
    }
}

int ileValide(int case_tab) {
    // Initialisation des variables
    int valide = 0; // Test la validite d'une case

    // Verifie la validite de la case
    if(case_tab == MAP_VIDE) {
        valide = 1;
    } else if(case_tab == MAP_ILE) {
        valide = 0;
    } else if(case_tab == MAP_LIMITE) {
        valide = -1;
    }

    return valide;
}

void genMap1(int** tab, int coord1, int coord2, int* nb_case_ile) {
    // Verification de la validite de l'ile
    if(ileValide(tab[coord1][coord2]) == 1) {
        // Creation de la case ILE
        tab[coord1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
}

void genMap2(int** tab, int coord1, int coord2, int* nb_case_ile) {
    // Verification de la validite de l'ile
    if(ileValide(tab[coord1][coord2]) == 1) {
        // Creation de la case ILE
        tab[coord1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
    // Ligne de 3 cases, soit les cases a cote du centre sont des cases vide, soit il s'agit d'une limite de map, on doit donc verifier
    if(ileValide(tab[coord1][coord2 - 1]) == 1) {
        tab[coord1][coord2 - 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1][coord2+1])==1) {
        tab[coord1][coord2 + 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
}

void genMap3(int** tab, int coord1, int coord2, int* nb_case_ile) {
    // Verification de la validite de l'ile
    if(ileValide(tab[coord1][coord2]) == 1) {
        // Creation de la case ILE
        tab[coord1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
    // Forme d'escalier de 6 cases montant vers la droite, avec pour centre la deuxieme marche (exterieur) de l'escalier
    if(ileValide(tab[coord1 - 1][coord2 + 1]) == 1) {
        tab[coord1 - 1][coord2 + 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1][coord2 + 1]) == 1) {
        tab[coord1][coord2 + 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 + 1][coord2 - 1]) == 1) {
        tab[coord1 + 1][coord2 - 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 + 1][coord2]) == 1) {
        tab[coord1 + 1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 + 1][coord2 + 1]) == 1) {
        tab[coord1 + 1][coord2 + 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
}

void genMap4(int** tab, int coord1, int coord2, int* nb_case_ile) {
    // Verification de la validite de l'ile
    if(ileValide(tab[coord1][coord2]) == 1) {
        // Creation de la case ILE
        tab[coord1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
    // Carré de 3x3
    if(ileValide(tab[coord1 - 1][coord2 - 1]) == 1) {
        tab[coord1 - 1][coord2 - 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 - 1][coord2]) == 1) {
        tab[coord1-1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 - 1][coord2 + 1]) == 1) {
        tab[coord1 - 1][coord2 + 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1][coord2 - 1]) == 1) {
        tab[coord1][coord2 - 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1][coord2 + 1]) == 1) {
        tab[coord1][coord2 + 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 + 1][coord2 - 1]) == 1) {
        tab[coord1 + 1][coord2 - 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 + 1][coord2]) == 1) {
        tab[coord1 + 1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 + 1][coord2 + 1]) == 1) {
        tab[coord1 + 1][coord2 + 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
}

void genMap5(int** tab, int coord1, int coord2, int* nb_case_ile) {
    // Verification de la validite de l'ile
    if(ileValide(tab[coord1][coord2]) == 1) {
        // Creation de la case ILE
        tab[coord1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
    // Triangle de 3 etages de 1/3/5 carres centre au deuxieme etage, 2e case
    if(ileValide(tab[coord1 - 1][coord2]) == 1) {
        tab[coord1 - 1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1][coord2 - 1]) == 1) {
        tab[coord1][coord2 - 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1][coord2 + 1]) == 1) {
        tab[coord1][coord2 + 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 + 1][coord2 - 1]) != -1) { // Car ici on veut mettre 2 case
        tab[coord1 + 1][coord2 - 1] = MAP_ILE;
        (*nb_case_ile) --;
        // Verification du non depassement de la map
        if(coord2 - 2 >= 0) {
            if(ileValide(tab[coord1 + 1][coord2 - 2]) == 1) { // Si seulement, la case a cote est valide, on peut se permettre de verifier si celle la est valide, pour ne pas sortir du tableau ou ecrire sur une limite de map
                tab[coord1 + 1][coord2 - 2] = MAP_ILE;
                (*nb_case_ile) --;
            }
        }
    }
    if(ileValide(tab[coord1 + 1][coord2]) == 1) {
        tab[coord1 + 1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 + 1][coord2 + 1]) != -1) { // De même
        if(ileValide(tab[coord1 + 1][coord2 + 1]) == 1) {
            tab[coord1 + 1][coord2 + 1] = MAP_ILE;
            (*nb_case_ile) --;
        }
        // Verification du non depassement de la map
        if(coord2 + 2 < MAP_LARGEUR) {
            if(ileValide(tab[coord1 + 1][coord2 + 2]) == 1) { // Idem
                tab[coord1 + 1][coord2 + 2] = MAP_ILE;
                (*nb_case_ile) --;
            }
        }
    }
}

void genMap6(int** tab, int coord1, int coord2, int* nb_case_ile) {
    // Verification de la validite de l'ile
    if(ileValide(tab[coord1][coord2]) == 1) {
        // Creation de la case ILE
        tab[coord1][coord2] = MAP_ILE;
        (*nb_case_ile) --;
    }
    // Losange
    if(ileValide(tab[coord1 - 1][coord2]) != -1) {
        if(ileValide(tab[coord1 - 1][coord2]) == 1) {
            tab[coord1 - 1][coord2] = MAP_ILE;
            (*nb_case_ile) --;
        }
        // Verification du non depassement de la map
        if(coord1 - 2 >= 0) {
            if(ileValide(tab[coord1 - 2][coord2]) == 1) {
                tab[coord1 - 2][coord2] = MAP_ILE;
                (*nb_case_ile) --;
            }
        }
    }
    if(ileValide(tab[coord1 - 1][coord2 - 1]) == 1) {
        tab[coord1 - 1][coord2 - 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 - 1][coord2 + 1]) == 1) {
        tab[coord1 - 1][coord2 + 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1][coord2 - 1]) != -1) {
        if(ileValide(tab[coord1][coord2 - 1]) == 1) {
            tab[coord1][coord2 - 1] = MAP_ILE;
            (*nb_case_ile) --;
        }
        // Verification du non depassement de la map
        if(coord2 - 2 >= 0) {
            if(ileValide(tab[coord1][coord2 - 2]) == 1) {
                tab[coord1][coord2 - 2] = MAP_ILE;
                (*nb_case_ile) --;
            }
        }
    }
    if(ileValide(tab[coord1][coord2 + 1]) != -1) {
        if(ileValide(tab[coord1][coord2 + 1]) == 1) {
            tab[coord1][coord2 + 1] = MAP_ILE;
            (*nb_case_ile) --;
        }
        // Verification du non depassement de la map
        if(coord2 + 2 < MAP_LARGEUR) {
            if(ileValide(tab[coord1][coord2 + 2]) == 1) {
                tab[coord1][coord2 + 2] = MAP_ILE;
                (*nb_case_ile) --;
            }
        }
    }
    if(ileValide(tab[coord1 + 1][coord2 - 1]) == 1) {
        tab[coord1 + 1][coord2 - 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
    if(ileValide(tab[coord1 + 1][coord2]) != -1) {
        if(ileValide(tab[coord1 + 1][coord2]) == 1) {
            tab[coord1 + 1][coord2] = MAP_ILE;
            (*nb_case_ile) --;
        }
        // Verification du non depassement de la map
        if(coord1 + 2 < MAP_HAUTEUR) {
            if(ileValide(tab[coord1 + 2][coord2]) == 1) {
                tab[coord1 + 2][coord2] = MAP_ILE;
                (*nb_case_ile) --;
            }
        }
    }
    if(ileValide(tab[coord1 + 1][coord2 + 1]) == 1) {
        tab[coord1 + 1][coord2 + 1] = MAP_ILE;
        (*nb_case_ile) --;
    }
}
