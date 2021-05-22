#include "Arene.h"

void arene() {
    // Initialisation des variables
    int **carte                                  = NULL,               // MAP de jeu
        **carteCopie                             = NULL,               // MAP copie du jeu
        **joueursStats                           = NULL,               // Tableau des stats des joueurs
        **piratesStats                           = NULL,               // Tableau des stats des pirates
        **trajectoire                            = NULL,               // Tableau contenant la trajectoire du projectile
        *listClassement                          = NULL,               // Classement des joueurs a l'aide de leur id
        *ordre                                   = NULL,               // Conteneur de l'ordre de l'IA
        *(*ias[NOMBRE_JOUEURS])(int**, int, int) = IAS,                // Tableau des IAs
        coordLimites[4]                          = {0, 0, 0, 0},       // Conteneur des coordonnees des limites de Map
        dernierJoueurID                          = 0,                  // ID du dernier joueur ayant le maximum de points
        dernierJoueurPts                         = 0,                  // Points du dernier joueur
        debutJeu                                 = 0,                  // Duree s'etant ecoule depuis le debut du programme avant le debut de la partie
        finJeu                                   = 0,                  // Duree s'etant ecoule depuis le debut du programme avant la fin de la partie
        tours                                    = 0,                  // Nombre de tours s'etant ecoules
        premierJoueur                            = 0,                  // ID du premier joueur
        joueurCourant                            = 0,                  // ID du joueur courant
        tir                                      = FALSE,              // BOOLEEN indiquant s'il y a eu un tir
        tempsPause                               = TEMPS_INTER_TOUR,   // Duree d'arret entre deux tours de joueurs
        tourAvRetrecissement                     = TPS_RETRECISSEMENT, // Duree d'arret entre deux tours de joueurs
        continuer                                = TRUE;               // BOOLEEN indiquant s'il faut ou non continuer de jouer
    char *noms[NOMBRE_JOUEURS]                   = NOMS;               // Tableau contenant les noms des joueurs
    SDL_Surface ***imagesMap                     = NULL,               // Tableau contenant les images de la map
                **nomsJoueurs                    = NULL,               // Tableau contenant les images des noms des joueurs
                *ecran                           = NULL;               // Surface SDL representant l'ecran

    // Ouverture de l'interface graphique et chargement des images
    ecran       = initGraphique();
    imagesMap   = initIMG();
    nomsJoueurs = initNomsJoueurs(noms);

    // Generation de la map et de sa copie
    carte      = genMap();
    carteCopie = genTabJoueur(carte);

    // Initialisation des limites et de la variable de decrement
    coordLimites[MAP_LIMITE_HAUT]   = 1;
    coordLimites[MAP_LIMITE_BAS]    = MAP_HAUTEUR - 2;
    coordLimites[MAP_LIMITE_GAUCHE] = 1;
    coordLimites[MAP_LIMITE_DROITE] = MAP_LARGEUR - 2;
    tourAvRetrecissement            = TPS_RETRECISSEMENT;

    // Initialisation des joueurs et des pirates
    joueursStats = initJoueur(carte);
    piratesStats = initPirate(carte);

    // Initialisation des tours
    debutJeu      = SDL_GetTicks();          // Recuperation du moment de debut du jeu
    premierJoueur = rand() % NOMBRE_JOUEURS; // Generation du premier joueur
    tours         = 0;                       // Initialisation des tours

    /* Gestion des tours:
     * Tant que:
     * - le nombre de tours est correcte
     * - la duree de jeu est correct
     * - il y a au moins deux joueurs en vie
     * - on ne veut pas arreter la partie
     */
    while(tours < TOUR_MAX && SDL_GetTicks() - debutJeu < TEMPS_MAX && testVie(joueursStats) && continuer) {
        // Reinitialisation du dernier meilleur score en points
        dernierJoueurPts = 0;

        // Gestion de l'IA pirate
        iaPirate(carte, MAP_LARGEUR, MAP_HAUTEUR, joueursStats, piratesStats);

        // Gestion de l'ordre de passage
        joueurCourant = premierJoueur;
        do {
            // Reinitialisation des variables
            tir        = FALSE;
            tempsPause = TEMPS_INTER_TOUR;

            // Verification de la vie du joueur
            if(joueursStats[joueurCourant][ID_STAT_VIE] > 0) {
                // Gestion du deplacement automatique
                avancer(carte, joueursStats, piratesStats, joueurCourant, 1);
            }

            // Verification que le joueur soit toujours en vie
            if(joueursStats[joueurCourant][ID_STAT_VIE] > 0) {
                // Verification et generation de sa carte personnalise
                compTabJoueur(carteCopie, carte, joueursStats, joueurCourant);

                // Recuperation de l'ordre du joueur
                ordre = (*ias[joueurCourant])(carteCopie, MAP_LARGEUR, MAP_HAUTEUR);

                // Traitement de l'ordre du joueur
                switch(ordre[ORDRE_PRINCIPAL]) {
                    // Avancer le bateau du joueur
                    case AVANCER:
                        // Droit de deplacement
                        if(joueursStats[joueurCourant][ID_STAT_MOVE] <= 0) {
                            // Droit d'utilisation de la capacite speciale de deplacement
                            if(ordre[COMPLEMENT_ORDRE] > 1 && joueursStats[joueurCourant][ID_STAT_CAPACITE] <= 0) {
                                // Gestion du depassement d'utilisation de la capacite
                                if(ordre[COMPLEMENT_ORDRE] > LIMITE_CAPACITE) {
                                    ordre[COMPLEMENT_ORDRE] = LIMITE_CAPACITE;
                                }

                                // Deplacement du bateau et reinitialisation de la capacite
                                avancer(carte, joueursStats, piratesStats, joueurCourant, ordre[COMPLEMENT_ORDRE]);
                                joueursStats[joueurCourant][ID_STAT_CAPACITE] = TPS_CAPACITE;
                            } else {
                                avancer(carte, joueursStats, piratesStats, joueurCourant, 1);
                            }
                        }
                    break;
                    // Tirer sur l'avant du bateau du joueur
                    case TIRER:
                        // Droit de tir
                        if(joueursStats[joueurCourant][ID_STAT_SHOOT] <= 0) {
                            trajectoire = tirer(carte, joueursStats, piratesStats, joueurCourant);
                            tir = TRUE;
                        }
                    break;
                    // Tourner le bateau du joueur
                    case TOURNER:
                        // Droit de tourner
                        if(joueursStats[joueurCourant][ID_STAT_MOVE] <= 0) {
                            tourner(carte, joueursStats, piratesStats, joueurCourant, ordre[COMPLEMENT_ORDRE]);
                        }
                    break;
                }

                // MAJ du dernier joueur
                if(joueursStats[joueurCourant][ID_STAT_PTS] >= dernierJoueurPts) {
                    dernierJoueurID  = joueurCourant;
                    dernierJoueurPts = joueursStats[joueurCourant][ID_STAT_PTS];
                }

                // Liberation de la memoire
                desallocOrdre(ordre);

                // Gestion de l'affichage
                if(tir) {
                    // Affichage de la map avec l'animation du tir
                    affichageCarteAvecTir(ecran, carte, joueursStats, trajectoire, &tempsPause, &continuer, imagesMap, nomsJoueurs, tours);

                    // Transformation de la map apres tir
                    transformMap(carte, trajectoire, joueursStats, piratesStats);

                    // MAJ vie: Remise de la vie a 0, en cas de vie a -1
                    majVie(joueursStats);

                    // Liberation de la trajectoire
                    desallocTrajectoire(trajectoire);
                } else {
                    // Affichage de la map simple
                    affichageCarte(ecran, carte, joueursStats, imagesMap, nomsJoueurs, tours);
                }

                // Reparation des canons et de la propulsion
                repCanonPropulsion(joueursStats, joueurCourant);

                // Mise en pause du programme et verification de la valeur
                if(tempsPause < 0) {
                    tempsPause = 0;
                }
                SDL_Delay((Uint32)tempsPause);
            }

            // Changement du joueur courant
            joueurCourant ++;
            if(joueurCourant >= NOMBRE_JOUEURS) {
                joueurCourant = 0;
            }

            // Verification de la continuation
            if(continuer) {
                continuer = continuPartie();
            }
        } while(joueurCourant != premierJoueur && continuer);

        tours ++; // Augmentation du tour

        // Reparation de la map
        repareMap(carte);

        // Gestion du retrecissement de Map
        tourAvRetrecissement --;
        if(tourAvRetrecissement <= 0) {
            // Retrecissement de la Map
            retrecissementMap(carte, joueursStats, piratesStats, coordLimites);
            tourAvRetrecissement = TPS_RETRECISSEMENT;
        }
    }

    // Recuperation du moment de fin de partie
    finJeu = SDL_GetTicks();

    // Gestion du classement
    listClassement = classement(joueursStats, dernierJoueurID);

    // Affichage du classement
    affichageClassement(ecran, listClassement, nomsJoueurs, joueursStats, tours, (finJeu - debutJeu) / 1000);
    pause();

    // Liberation de memoire
    desalloc(carte, carteCopie, joueursStats, piratesStats, listClassement);

    // Fermeture de l'interface graphique
    quitGraphique(imagesMap, nomsJoueurs);
}

void desallocOrdre(int* ordre) {
    // Liberation de l'ordre
    free(ordre);
}

void desallocTrajectoire(int** trajectoire) {
    // Liberation de la trajectoire
    free(trajectoire[0]);
    free(trajectoire[1]);
    free(trajectoire);
}

void desalloc(int** carte, int** carteCopie, int** joueursStats, int** piratesStats, int* listClassement) {
    // Initialisation des variables
    int i = 0;

    // Liberation de la map et de sa copie
    for(i = 0; i < MAP_HAUTEUR; i++) {
        free(carte[i]);
        free(carteCopie[i]);
    }
    free(carte);
    free(carteCopie[MAP_HAUTEUR]);
    free(carteCopie);

    // Liberation du tableau des stats des joueurs
    for(i = 0; i < NOMBRE_JOUEURS; i++) {
        free(joueursStats[i]);
    }
    free(joueursStats);

    // Liberation du tableau des stats des pirates
    for(i = 0; i < NOMBRE_PIRATES; i++) {
        free(piratesStats[i]);
    }
    free(piratesStats);

    // Liberation du classement
    free(listClassement);
}
