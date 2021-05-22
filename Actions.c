#include "Actions.h"

void avancer(int** carte, int** joueursStats, int** piratesStats, int joueurID, int distance) {
    // Initialisation des variables
    int orientation    = 0,     // Orientation du joueur
        aCollision     = FALSE, // BOOLEEN de verification de collision
        x              = 0,     // Abscisse de l'avant du bateau
        y              = 0,     // Ordonnee de l'avant du bateau
        xJ0            = 0,     // Abscisse de depart du bateau
        yJ0            = 0,     // Ordonnee de depart du bateau
        xJft           = 0,     // Abscisse d'arrive theorique
        yJft           = 0,     // Ordonnee d'arrive theorique
        xJCt           = 0,     // Abscisse de collision theorique
        yJCt           = 0,     // Ordonnee de collision theorique
        xJf            = 0,     // Abscisse d'arrive du bateau
        yJf            = 0;     // Ordonnee d'arrive du bateau

    // Recuperation des informations sur le joueur
    x           = joueursStats[joueurID][ID_STAT_X];
    y           = joueursStats[joueurID][ID_STAT_Y];
    orientation = recupOrientation(carte, x, y);

    // Verification de l'orientation pour connaitre les positions d'arrives
    if(orientation == BATEAU_HAUT || orientation == BATEAU_BAS) {
        // Trajectoire verticale, donc pas de modification de l'abscisse
        xJ0  = x;
        xJf  = x;
        xJft = xJf;
        xJCt = xJf;

        // Affinnage de l'orientation pour determiner les positions d'arrive theoriques
        if(orientation == BATEAU_HAUT) {
            // Le bateau part vers le haut
            yJ0  = y - 1;
            yJft = y - distance;
        } else {
            // Le bateau part vers le bas
            yJ0  = y + 1;
            yJft = y + distance;
        }
    } else {
        // Trajectoire horrizontale, donc pas de modification de l'ordonnee
        yJ0  = y;
        yJf  = y;
        yJft = yJf;
        yJCt = yJf;

        // Affinnage de l'orientation pour determiner les positions d'arrive theoriques
        if(orientation == BATEAU_GAUCHE) {
            // Le bateau part vers la gauche
            xJ0  = x - 1;
            xJft = x - distance;
        } else {
            // Le bateau part vers la droite
            xJ0  = x + 1;
            xJft = x + distance;
        }
    }

    // Determination de l'orientation pour deplacer le bateau
    switch(orientation) {
        case BATEAU_HAUT:
            // Reinitialisation de l'ordonnee finale
            yJf = yJ0;

            // Parcours de la trajectoire
            while(yJf >= yJft && !aCollision && yJf >= 0) {
                // Teste de collision
                if(testCollision(carte, xJf, yJf)) {
                    aCollision = TRUE;
                    yJCt       = yJf;
                } else {
                    yJf --;
                }
            }

            // Verification du non depassement
            if(yJf < yJft || aCollision) {
				yJf ++;
            }
        break;
        case BATEAU_BAS:
            // Reinitialisation de l'ordonnee finale
            yJf = yJ0;

            // Parcours de la trajectoire
            while(yJf <= yJft && !aCollision && yJf < MAP_HAUTEUR) {
                // Teste de collision
                if(testCollision(carte, xJf, yJf)) {
                    aCollision = TRUE;
                    yJCt       = yJf;
                } else {
                    yJf ++;
                }
            }

            // Verification du non depassement
            if(yJf > yJft || aCollision) {
				yJf --;
            }
        break;
        case BATEAU_GAUCHE:
            // Reinitialisation de l'abscisse finale
            xJf = xJ0;

            // Parcours de la trajectoire
            while(xJf >= xJft && !aCollision && xJf >= 0) {
                // Teste de collision
                if(testCollision(carte, xJf, yJf)) {
                    aCollision = TRUE;
                    xJCt       = xJf;
                } else {
                    xJf --;
                }
            }

            // Verification du non depassement
            if(xJf < xJft || aCollision) {
				xJf ++;
            }
        break;
        default:
            // Reinitialisation de l'abscisse finale
            xJf = xJ0;

            // Parcours de la trajectoire
            while(xJf <= xJft && !aCollision && xJf < MAP_LARGEUR) {
                // Teste de collision
                if(testCollision(carte, xJf, yJf)) {
                    aCollision = TRUE;
                    xJCt       = xJf;
                } else {
                    xJf ++;
                }
            }

            // Verification du non depassement
            if(xJf > xJft || aCollision) {
				xJf --;
            }
        break;
    }

    // Verification de l'orientation
    switch(orientation) {
        case BATEAU_HAUT:
            // Suppression du bateau actuel
            carte[y][x]     = MAP_VIDE;
            carte[y + 1][x] = MAP_VIDE;
            carte[y + 2][x] = MAP_VIDE;

            // Creation du nouveau bateau
            carte[yJf][xJf]     = genBateauID(joueurID, BATEAU_AVANT, BATEAU_JOUEURS);
            carte[yJf + 1][xJf] = genBateauID(joueurID, BATEAU_MILIEU, BATEAU_JOUEURS);
            carte[yJf + 2][xJf] = genBateauID(joueurID, BATEAU_ARRIERE, BATEAU_JOUEURS);
        break;
        case BATEAU_BAS:
            // Suppression du bateau actuel
            carte[y][x]     = MAP_VIDE;
            carte[y - 1][x] = MAP_VIDE;
            carte[y - 2][x] = MAP_VIDE;

            // Creation du nouveau bateau
            carte[yJf][xJf]     = genBateauID(joueurID, BATEAU_AVANT, BATEAU_JOUEURS);
            carte[yJf - 1][xJf] = genBateauID(joueurID, BATEAU_MILIEU, BATEAU_JOUEURS);
            carte[yJf - 2][xJf] = genBateauID(joueurID, BATEAU_ARRIERE, BATEAU_JOUEURS);
        break;
        case BATEAU_GAUCHE:
            // Suppression du bateau actuel
            carte[y][x]     = MAP_VIDE;
            carte[y][x + 1] = MAP_VIDE;
            carte[y][x + 2] = MAP_VIDE;

            // Creation du nouveau bateau
            carte[yJf][xJf]     = genBateauID(joueurID, BATEAU_AVANT, BATEAU_JOUEURS);
            carte[yJf][xJf + 1] = genBateauID(joueurID, BATEAU_MILIEU, BATEAU_JOUEURS);
            carte[yJf][xJf + 2] = genBateauID(joueurID, BATEAU_ARRIERE, BATEAU_JOUEURS);
        break;
        default:
            // Suppression du bateau actuel
            carte[y][x]     = MAP_VIDE;
            carte[y][x - 1] = MAP_VIDE;
            carte[y][x - 2] = MAP_VIDE;

            // Creation du nouveau bateau
            carte[yJf][xJf]     = genBateauID(joueurID, BATEAU_AVANT, BATEAU_JOUEURS);
            carte[yJf][xJf - 1] = genBateauID(joueurID, BATEAU_MILIEU, BATEAU_JOUEURS);
            carte[yJf][xJf - 2] = genBateauID(joueurID, BATEAU_ARRIERE, BATEAU_JOUEURS);
        break;
    }

    // Verification de non collision
    if(!aCollision) {
		// MAJ des coordonnees du joueur
		joueursStats[joueurID][ID_STAT_X] = xJf;
		joueursStats[joueurID][ID_STAT_Y] = yJf;

        // Augmentation du nombre de points du joueur
        joueursStats[joueurID][ID_STAT_PTS] += PTS_ACTION_DEPLACEMENT;
    } else {
        // On effectue le necessaire pour une collision
        collision(carte, joueursStats, piratesStats, joueurID, xJCt, yJCt);
    }
}

int** tirer(int** carte, int** joueursStats, int** piratesStats, int joueurID) {
    // Initialisation des variables
    int **trajectoire  = NULL,  // Tableau des coordonnees de la zonne de tir(coordonnees de depart et d'arrivee)
        x              = 0,     // Abscisse du joueur
        y              = 0,     // Ordonnee du joueur
        orientation    = 0,     // Orientation du joueur
        atteintCible   = FALSE, // BOOLEEN de verification d'atteinte de cible
        ia_touche      = 0,     // ID de l'IA touche
        partie_touche  = 0,     // Element du bateau touche
        xB0            = 0,     // Abscisse de depart du boulet
        yB0            = 0,     // Ordonnee de depart du boulet
        xBft           = 0,     // Abscisse d'arrive theorique
        yBft           = 0,     // Ordonnee d'arrive theorique
        xBf            = 0,     // Abscisse d'arrive du boulet
        yBf            = 0;     // Ordonnee d'arrive du boulet

    // Recuperation des informations sur le joueur
    x           = joueursStats[joueurID][ID_STAT_X];
    y           = joueursStats[joueurID][ID_STAT_Y];
    orientation = recupOrientation(carte, x, y);

    // Verification de l'orientation pour connaitre la position de depart et les positions d'arrives
    if(orientation == BATEAU_HAUT || orientation == BATEAU_BAS) {
        // Trajectoire verticale, donc pas de modification de l'abscisse
        xB0  = x;
        xBf  = x;
        xBft = xBf;

        // Affinnage de l'orientation pour determiner les positions de depart et d'arrive theoriques
        if(orientation == BATEAU_HAUT) {
            // Le boulet part vers le haut
            yB0  = y - 1;
            yBft = y - TIR_PORTEE;
        } else {
            // Le boulet part vers le bas
            yB0  = y + 1;
            yBft = y + TIR_PORTEE;
        }
    } else {
        // Trajectoire horrizontale, donc pas de modification de l'ordonnee
        yB0  = y;
        yBf  = y;
        yBft = yBf;

        // Affinnage de l'orientation pour determiner les positions de depart et d'arrive theoriques
        if(orientation == BATEAU_GAUCHE) {
            // Le boulet part vers la gauche
            xB0  = x - 1;
            xBft = x - TIR_PORTEE;
        } else {
            // Le boulet part vers la droite
            xB0  = x + 1;
            xBft = x + TIR_PORTEE;
        }
    }

    // Determination de l'orientation pour deplacer le boulet
    switch(orientation) {
        case BATEAU_HAUT:
            // Reinitialisation de l'ordonnee finale
            yBf = yB0;

            // Parcours de la trajectoire
            while(yBf >= yBft && !atteintCible && yBf >= 0) {
                // Teste de collision avec une ile ou un bateau
                if(carte[yBf][xBf] < MAP_DEBRIS || carte[yBf][xBf] >= 0) {
                    atteintCible = TRUE;
                } else {
                    yBf --;
                }
            }

            // Verification du non depassement
            if(yBf < yBft) {
				yBf ++;
            }
        break;
        case BATEAU_BAS:
            // Reinitialisation de l'ordonnee finale
            yBf = yB0;

            // Parcours de la trajectoire
            while(yBf <= yBft && !atteintCible && yBf < MAP_HAUTEUR) {
                // Teste de collision avec une ile ou un bateau
                if(carte[yBf][xBf] < MAP_DEBRIS || carte[yBf][xBf] >= 0) {
                    atteintCible = TRUE;
                } else {
                    yBf ++;
                }
            }

            // Verification du non depassement
            if(yBf > yBft) {
				yBf --;
            }
        break;
        case BATEAU_GAUCHE:
            // Reinitialisation de l'abscisse finale
            xBf = xB0;

            // Parcours de la trajectoire
            while(xBf >= xBft && !atteintCible && xBf >= 0) {
                // Teste de collision avec une ile ou un bateau
                if(carte[yBf][xBf] < MAP_DEBRIS || carte[yBf][xBf] >= 0) {
                    atteintCible = TRUE;
                } else {
                    xBf --;
                }
            }

            // Verification du non depassement
            if(xBf < xBft) {
				xBf ++;
            }
        break;
        default:
            // Reinitialisation de l'abscisse finale
            xBf = xB0;

            // Parcours de la trajectoire
            while(xBf <= xBft && !atteintCible && xBf < MAP_LARGEUR) {
                // Teste de collision avec une ile ou un bateau
                if(carte[yBf][xBf] < MAP_DEBRIS || carte[yBf][xBf] >= 0) {
                    atteintCible = TRUE;
                } else {
                    xBf ++;
                }
            }

            // Verification du non depassement
            if(xBf > xBft) {
				xBf --;
            }
        break;
    }

    // Generation du tableau de trajectoire
    trajectoire    = (int**)malloc(2 * sizeof(int*));
    trajectoire[0] = (int*)malloc(2 * sizeof(int));
    trajectoire[1] = (int*)malloc(2 * sizeof(int));

    // Recuperation de la trajectoire
    trajectoire[0][0] = xB0;
    trajectoire[0][1] = yB0;
    trajectoire[1][0] = xBf;
    trajectoire[1][1] = yBf;

    // Verification de l'atteinte d'une cible
    if(atteintCible) {
        // Verification de l'atteinte d'un joueur
        if(carte[yBf][xBf] >= MAP_IA) {
            // Recuperation des informations sur le joueur touche
            ia_touche     = recupJoueurID(carte[yBf][xBf], BATEAU_JOUEURS);
            partie_touche = recupElementBateau(carte[yBf][xBf], BATEAU_JOUEURS);

            // Augmentation du nombre de points du joueur
            if(partie_touche == BATEAU_MILIEU) {
                joueursStats[joueurID][ID_STAT_PTS] += PTS_ACTION_TIR_MILIEU;
            } else {
                joueursStats[joueurID][ID_STAT_PTS] += PTS_ACTION_TIR_REUSSI;
            }

            // Verification de l'etat ou non de pirate
            if(ia_touche < BATEAU_PIRATES) {
                // Il s'agit d'un joueur

                // Verification de la mort certaine du joueur MAP_IA
                if(joueursStats[ia_touche][ID_STAT_VIE] <= VIE_ATTAQUE_AV_AR || partie_touche == BATEAU_MILIEU) {
                    joueursStats[ia_touche][ID_STAT_VIE] = VIE_FINAL_ATTAQUE_MILIEU;
                } else {
                    // Perte de la moitie de la vie
                    joueursStats[ia_touche][ID_STAT_VIE] -= VIE_ATTAQUE_AV_AR;

                    // Verification de la mort du bateau touche
                    if(joueursStats[ia_touche][ID_STAT_VIE] <= 0) {
                        // Transformation du bateau en debris
                        transformBateau(carte, x, y, ia_touche, BATEAU_JOUEURS);
                    } else {
                        // Verification de l'element touche pour perdre l'utilisation de cette fonction
                        if(partie_touche == BATEAU_AVANT) {
                            joueursStats[ia_touche][ID_STAT_SHOOT] = TPS_RECONSTRUCTION;
                        } else {
                            joueursStats[ia_touche][ID_STAT_MOVE]  = TPS_RECONSTRUCTION;
                        }
                    }
                }
            } else {
                // Il s'agit d'un pirate

                // MAJ de l'ID de l'IA
                ia_touche -= BATEAU_PIRATES;

                // Verification de la mort certaine du pirate
                if(piratesStats[ia_touche][ID_STAT_VIE] <= VIE_ATTAQUE_AV_AR || partie_touche == BATEAU_MILIEU) {
                    piratesStats[ia_touche][ID_STAT_VIE] = VIE_FINAL_ATTAQUE_MILIEU;
                } else {
                    // Perte de la moitie de la vie
                    piratesStats[ia_touche][ID_STAT_VIE] -= VIE_ATTAQUE_AV_AR;

                    // Verification de la mort du bateau touche
                    if(piratesStats[ia_touche][ID_STAT_VIE] <= 0) {
                        // Transformation du bateau en debris
                        transformBateau(carte, x, y, ia_touche, BATEAU_PIRATES);
                    } else {
                        // Verification de l'element touche pour perdre l'utilisation de cette fonction
                        if(partie_touche == BATEAU_AVANT) {
                            piratesStats[ia_touche][ID_STAT_SHOOT] = TPS_RECONSTRUCTION;
                        } else {
                            piratesStats[ia_touche][ID_STAT_MOVE]  = TPS_RECONSTRUCTION;
                        }
                    }
                }
            }
        }
    }

    // Perte de la possibilite de tirer
    joueursStats[joueurID][ID_STAT_SHOOT] = TPS_RECHARGEMENT;

    return trajectoire;
}

void tourner(int** carte, int** joueursStats, int** piratesStats, int joueurID, int dirrection) {
    // Initialisation des variables
    int xAv         = 0, // Abscisse de l'avant du bateau du joueur
		yAv         = 0, // Ordonnee de l'avant du bateau du joueur
		xAr         = 0, // Abscisse de l'arriere du bateau du joueur
		yAr         = 0, // Ordonnee de l'arriere du bateau du joueur
		xAvTh       = 0, // Abscisse theorique de l'avant du bateau du joueur
		yAvTh       = 0, // Ordonnee theorique de l'avant du bateau du joueur
		xArTh       = 0, // Abscisse theorique de l'arriere du bateau du joueur
		yArTh       = 0, // Ordonnee theorique de l'arriere du bateau du joueur
		orientation = 0; // Orientation du bateau du joueur

	// Recuperation des informations sur le joueur
	xAv         = joueursStats[joueurID][ID_STAT_X];
	yAv         = joueursStats[joueurID][ID_STAT_Y];
	orientation = recupOrientation(carte, xAv, yAv);

	// Determination des coordonnes du bateau et des coordonnees finales
	switch(orientation) {
		case BATEAU_HAUT:
            // Le bateau est oriente vers le haut
            xAr = xAv;
            yAr = yAv + 2;

            // Recuperation de la dirrection de tournage
            if(dirrection == TOURNER_GAUCHE) {
				// Le joueur veut tourner a gauche
				xAvTh = xAv - 1;
				yAvTh = yAv + 1;
				xArTh = xAvTh + 2;
				yArTh = yAvTh;
            } else {
				// Le joueur veut tourner a droite
				xAvTh = xAv + 1;
				yAvTh = yAv + 1;
				xArTh = xAvTh - 2;
				yArTh = yAvTh;
            }
		break;
		case BATEAU_BAS:
            // Le bateau est oriente vers le bas
            xAr = xAv;
            yAr = yAv - 2;

            // Recuperation de la dirrection de tournage
            if(dirrection == TOURNER_GAUCHE) {
				// Le joueur veut tourner a gauche
				xAvTh = xAv + 1;
				yAvTh = yAv - 1;
				xArTh = xAvTh - 2;
				yArTh = yAvTh;
            } else {
				// Le joueur veut tourner a droite
				xAvTh = xAv - 1;
				yAvTh = yAv - 1;
				xArTh = xAvTh + 2;
				yArTh = yAvTh;
            }
		break;
		case BATEAU_GAUCHE:
            // Le bateau est oriente vers la gauche
            xAr = xAv + 2;
            yAr = yAv;

            // Recuperation de la dirrection de tournage
            if(dirrection == TOURNER_GAUCHE) {
				// Le joueur veut tourner a gauche
				xAvTh = xAv + 1;
				yAvTh = yAv + 1;
				xArTh = xAvTh;
				yArTh = yAvTh - 2;
            } else {
				// Le joueur veut tourner a droite
				xAvTh = xAv + 1;
				yAvTh = yAv - 1;
				xArTh = xAvTh;
				yArTh = yAvTh + 2;
            }
		break;
		default:
            // Le bateau est oriente vers la droite
            xAr = xAv - 2;
            yAr = yAv;

            // Recuperation de la dirrection de tournage
            if(dirrection == TOURNER_GAUCHE) {
				// Le joueur veut tourner a gauche
				xAvTh = xAv - 1;
				yAvTh = yAv - 1;
				xArTh = xAvTh;
				yArTh = yAvTh + 2;
            } else {
				// Le joueur veut tourner a droite
				xAvTh = xAv - 1;
				yAvTh = yAv + 1;
				xArTh = xAvTh;
				yArTh = yAvTh - 2;
            }
		break;
	}

	// Verification de collision
	if(testCollision(carte, xAvTh, yAvTh)) {
		// Collision par l'avant theorique
		collision(carte, joueursStats, piratesStats, joueurID, xAvTh, yAvTh);
	} else if(testCollision(carte, xArTh, yArTh)) {
		// Collision par l'arriere theorique
		collision(carte, joueursStats, piratesStats, joueurID, xArTh, yArTh);
	} else {
		// On place les nouveaux avant et arriere du bateau
		carte[yAvTh][xAvTh] = carte[yAv][xAv];
		carte[yArTh][xArTh] = carte[yAr][xAr];

		// On supprime l'avant et l'arriere actuel du bateau
		carte[yAv][xAv] = MAP_VIDE;
		carte[yAr][xAr] = MAP_VIDE;

		// MAJ des coordonnees du joueur
		joueursStats[joueurID][ID_STAT_X] = xAvTh;
		joueursStats[joueurID][ID_STAT_Y] = yAvTh;
	}
}
