#include "Graphique.h"

SDL_Surface* initGraphique() {
    // Initialisation des variables
    SDL_Surface *ecran = NULL; // Surface de l'ecran

    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Initialisation de l'ecran
    ecran = SDL_SetVideoMode(ECRAN_LARGEUR, ECRAN_HAUTEUR, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    if(ecran == NULL) {
        fprintf(stderr, "Impossible de charger le mode video : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Modification du nom du programme
    SDL_WM_SetCaption("Les Bermudes", NULL);

    // Initialisation de SDL_TTF
    if(TTF_Init() == -1) {
        fprintf(stderr, "Erreur d'initialisation de SDL_TTF : %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    return ecran;
}

SDL_Surface*** initIMG() {
    // Initialisation des variables
    SDL_Surface ***imagesDeMap; // Tableau des images

    // Generation des images
    imagesDeMap = (SDL_Surface***)malloc(NBR_IMAGES * sizeof(SDL_Surface**));

    // Allocation des images
    imagesDeMap[IMG_MAP_VIDE]                    = (SDL_Surface**)malloc(1 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_0C]                  = (SDL_Surface**)malloc(1 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_1C]                  = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_2C_LIGNE]            = (SDL_Surface**)malloc(2 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_2C_0_DIAG]           = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_2C_1_DIAG]           = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_3C_0_DIAG]           = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_3C_2_DIAG]           = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT]  = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT] = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_4C_0_DIAG]           = (SDL_Surface**)malloc(1 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_4C_1_DIAG]           = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_4C_2_DIAG_ADJ]       = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_4C_2_DIAG_OPP]       = (SDL_Surface**)malloc(2 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_4C_3_DIAG]           = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_ILE_4C_4_DIAG]           = (SDL_Surface**)malloc(1 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_LIM_2C_LIGNE]            = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_LIM_2C_DIRECT]           = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_LIM_COMPLET]             = (SDL_Surface**)malloc(1 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_DEBRIS]                  = (SDL_Surface**)malloc(1 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_BOULET]                  = (SDL_Surface**)malloc(1 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_MAP_EXPLOSION]               = (SDL_Surface**)malloc(1 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_BATEAU_PIRATE_AVANT]         = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_BATEAU_PIRATE_MILIEU]        = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_BATEAU_PIRATE_ARRIERE]       = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_BATEAU_JOUEUR_AVANT]         = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_BATEAU_JOUEUR_MILIEU]        = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));
    imagesDeMap[IMG_BATEAU_JOUEUR_ARRIERE]       = (SDL_Surface**)malloc(4 * sizeof(SDL_Surface*));

    // Chargement des images a 1 orientation
    imagesDeMap[IMG_MAP_VIDE][0]          = IMG_Load("images/0/vide.png");
    imagesDeMap[IMG_MAP_ILE_0C][0]        = IMG_Load("images/0/ile0C.png");
    imagesDeMap[IMG_MAP_ILE_4C_0_DIAG][0] = IMG_Load("images/0/ile4C_0_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_4C_4_DIAG][0] = IMG_Load("images/0/ile4C_4_DIAG.png");
    imagesDeMap[IMG_MAP_LIM_COMPLET][0]   = IMG_Load("images/0/contour.png");
    imagesDeMap[IMG_MAP_DEBRIS][0]        = IMG_Load("images/0/debris.png");
    imagesDeMap[IMG_MAP_BOULET][0]        = IMG_Load("images/0/boulet.png");
    imagesDeMap[IMG_MAP_EXPLOSION][0]     = IMG_Load("images/0/boulet.png");

    // Chargement des images a 2 orientations
    imagesDeMap[IMG_MAP_ILE_2C_LIGNE][0]      = IMG_Load("images/0/ile2C_ligne.png");
    imagesDeMap[IMG_MAP_ILE_2C_LIGNE][1]      = IMG_Load("images/1/ile2C_ligne.png");
    imagesDeMap[IMG_MAP_ILE_4C_2_DIAG_OPP][0] = IMG_Load("images/0/ile4C_2_DIAG_OPP.png");
    imagesDeMap[IMG_MAP_ILE_4C_2_DIAG_OPP][1] = IMG_Load("images/1/ile4C_2_DIAG_OPP.png");

    // Chargement des images a 4 orientations
    imagesDeMap[IMG_MAP_ILE_1C][0]                  = IMG_Load("images/0/ile1C.png");
    imagesDeMap[IMG_MAP_ILE_1C][1]                  = IMG_Load("images/1/ile1C.png");
    imagesDeMap[IMG_MAP_ILE_1C][2]                  = IMG_Load("images/2/ile1C.png");
    imagesDeMap[IMG_MAP_ILE_1C][3]                  = IMG_Load("images/3/ile1C.png");
    imagesDeMap[IMG_MAP_ILE_2C_0_DIAG][0]           = IMG_Load("images/0/ile2C_0_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_2C_0_DIAG][1]           = IMG_Load("images/1/ile2C_0_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_2C_0_DIAG][2]           = IMG_Load("images/2/ile2C_0_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_2C_0_DIAG][3]           = IMG_Load("images/3/ile2C_0_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_2C_1_DIAG][0]           = IMG_Load("images/0/ile2C_1_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_2C_1_DIAG][1]           = IMG_Load("images/1/ile2C_1_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_2C_1_DIAG][2]           = IMG_Load("images/2/ile2C_1_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_2C_1_DIAG][3]           = IMG_Load("images/3/ile2C_1_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_3C_0_DIAG][0]           = IMG_Load("images/0/ile3C_0_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_3C_0_DIAG][1]           = IMG_Load("images/1/ile3C_0_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_3C_0_DIAG][2]           = IMG_Load("images/2/ile3C_0_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_3C_0_DIAG][3]           = IMG_Load("images/3/ile3C_0_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_3C_2_DIAG][0]           = IMG_Load("images/0/ile3C_2_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_3C_2_DIAG][1]           = IMG_Load("images/1/ile3C_2_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_3C_2_DIAG][2]           = IMG_Load("images/2/ile3C_2_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_3C_2_DIAG][3]           = IMG_Load("images/3/ile3C_2_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT][0]  = IMG_Load("images/0/ile3C_1_DIAG_TOP_LEFT.png");
    imagesDeMap[IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT][1]  = IMG_Load("images/1/ile3C_1_DIAG_TOP_LEFT.png");
    imagesDeMap[IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT][2]  = IMG_Load("images/2/ile3C_1_DIAG_TOP_LEFT.png");
    imagesDeMap[IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT][3]  = IMG_Load("images/3/ile3C_1_DIAG_TOP_LEFT.png");
    imagesDeMap[IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT][0] = IMG_Load("images/0/ile3C_1_DIAG_TOP_RIGHT.png");
    imagesDeMap[IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT][1] = IMG_Load("images/1/ile3C_1_DIAG_TOP_RIGHT.png");
    imagesDeMap[IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT][2] = IMG_Load("images/2/ile3C_1_DIAG_TOP_RIGHT.png");
    imagesDeMap[IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT][3] = IMG_Load("images/3/ile3C_1_DIAG_TOP_RIGHT.png");
    imagesDeMap[IMG_MAP_ILE_4C_1_DIAG][0]           = IMG_Load("images/0/ile4C_1_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_4C_1_DIAG][1]           = IMG_Load("images/1/ile4C_1_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_4C_1_DIAG][2]           = IMG_Load("images/2/ile4C_1_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_4C_1_DIAG][3]           = IMG_Load("images/3/ile4C_1_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_4C_2_DIAG_ADJ][0]       = IMG_Load("images/0/ile4C_2_DIAG_ADJ.png");
    imagesDeMap[IMG_MAP_ILE_4C_2_DIAG_ADJ][1]       = IMG_Load("images/1/ile4C_2_DIAG_ADJ.png");
    imagesDeMap[IMG_MAP_ILE_4C_2_DIAG_ADJ][2]       = IMG_Load("images/2/ile4C_2_DIAG_ADJ.png");
    imagesDeMap[IMG_MAP_ILE_4C_2_DIAG_ADJ][3]       = IMG_Load("images/3/ile4C_2_DIAG_ADJ.png");
    imagesDeMap[IMG_MAP_ILE_4C_3_DIAG][0]           = IMG_Load("images/0/ile4C_3_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_4C_3_DIAG][1]           = IMG_Load("images/1/ile4C_3_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_4C_3_DIAG][2]           = IMG_Load("images/2/ile4C_3_DIAG.png");
    imagesDeMap[IMG_MAP_ILE_4C_3_DIAG][3]           = IMG_Load("images/3/ile4C_3_DIAG.png");
    imagesDeMap[IMG_MAP_LIM_2C_LIGNE][0]            = IMG_Load("images/0/limite2C_ligne.png");
    imagesDeMap[IMG_MAP_LIM_2C_LIGNE][1]            = IMG_Load("images/1/limite2C_ligne.png");
    imagesDeMap[IMG_MAP_LIM_2C_LIGNE][2]            = IMG_Load("images/2/limite2C_ligne.png");
    imagesDeMap[IMG_MAP_LIM_2C_LIGNE][3]            = IMG_Load("images/3/limite2C_ligne.png");
    imagesDeMap[IMG_MAP_LIM_2C_DIRECT][0]           = IMG_Load("images/0/limite2C_direct.png");
    imagesDeMap[IMG_MAP_LIM_2C_DIRECT][1]           = IMG_Load("images/1/limite2C_direct.png");
    imagesDeMap[IMG_MAP_LIM_2C_DIRECT][2]           = IMG_Load("images/2/limite2C_direct.png");
    imagesDeMap[IMG_MAP_LIM_2C_DIRECT][3]           = IMG_Load("images/3/limite2C_direct.png");
    imagesDeMap[IMG_BATEAU_PIRATE_AVANT][0]         = IMG_Load("images/0/bateau_pirate_avant.png");
    imagesDeMap[IMG_BATEAU_PIRATE_AVANT][1]         = IMG_Load("images/1/bateau_pirate_avant.png");
    imagesDeMap[IMG_BATEAU_PIRATE_AVANT][2]         = IMG_Load("images/2/bateau_pirate_avant.png");
    imagesDeMap[IMG_BATEAU_PIRATE_AVANT][3]         = IMG_Load("images/3/bateau_pirate_avant.png");
    imagesDeMap[IMG_BATEAU_PIRATE_MILIEU][0]        = IMG_Load("images/0/bateau_pirate_milieu.png");
    imagesDeMap[IMG_BATEAU_PIRATE_MILIEU][1]        = IMG_Load("images/1/bateau_pirate_milieu.png");
    imagesDeMap[IMG_BATEAU_PIRATE_MILIEU][2]        = IMG_Load("images/2/bateau_pirate_milieu.png");
    imagesDeMap[IMG_BATEAU_PIRATE_MILIEU][3]        = IMG_Load("images/3/bateau_pirate_milieu.png");
    imagesDeMap[IMG_BATEAU_PIRATE_ARRIERE][0]       = IMG_Load("images/0/bateau_pirate_arriere.png");
    imagesDeMap[IMG_BATEAU_PIRATE_ARRIERE][1]       = IMG_Load("images/1/bateau_pirate_arriere.png");
    imagesDeMap[IMG_BATEAU_PIRATE_ARRIERE][2]       = IMG_Load("images/2/bateau_pirate_arriere.png");
    imagesDeMap[IMG_BATEAU_PIRATE_ARRIERE][3]       = IMG_Load("images/3/bateau_pirate_arriere.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_AVANT][0]         = IMG_Load("images/0/bateau_joueur_avant.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_AVANT][1]         = IMG_Load("images/1/bateau_joueur_avant.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_AVANT][2]         = IMG_Load("images/2/bateau_joueur_avant.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_AVANT][3]         = IMG_Load("images/3/bateau_joueur_avant.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_MILIEU][0]        = IMG_Load("images/0/bateau_joueur_milieu.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_MILIEU][1]        = IMG_Load("images/1/bateau_joueur_milieu.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_MILIEU][2]        = IMG_Load("images/2/bateau_joueur_milieu.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_MILIEU][3]        = IMG_Load("images/3/bateau_joueur_milieu.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_ARRIERE][0]       = IMG_Load("images/0/bateau_joueur_arriere.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_ARRIERE][1]       = IMG_Load("images/1/bateau_joueur_arriere.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_ARRIERE][2]       = IMG_Load("images/2/bateau_joueur_arriere.png");
    imagesDeMap[IMG_BATEAU_JOUEUR_ARRIERE][3]       = IMG_Load("images/3/bateau_joueur_arriere.png");

    return imagesDeMap;
}

SDL_Surface** initNomsJoueurs(char** listeJoueurs) {
    // Initialisation des variables
    int i                  = 0;                              // Variable incrementatrice
    SDL_Color couleurBleu  = {0, 0, 255},                    // Couleur d'ecriture
              couleurNoire = {0, 0, 0};                      // Couleur de fond
    TTF_Font* police       = TTF_OpenFont("Blazed.ttf", 20); // Police d'ecriture
    SDL_Surface **nomsJoueurs;                               // Tableau des noms des joueurs

    // Generation des noms des joueurs
    nomsJoueurs = (SDL_Surface**)malloc((NOMBRE_JOUEURS + 2) * sizeof(SDL_Surface*));

    // Chargement des noms des joueurs et des textes speciaux d'affichage
    for(i = 0; i < NOMBRE_JOUEURS; i++) {
        nomsJoueurs[i] = TTF_RenderText_Shaded(police, listeJoueurs[i], couleurBleu, couleurNoire);
    }
    TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE);
    nomsJoueurs[NOMBRE_JOUEURS]     = TTF_RenderText_Shaded(police, "Liste des survivants:", couleurBleu, couleurNoire);
    nomsJoueurs[NOMBRE_JOUEURS + 1] = TTF_RenderText_Shaded(police, "Classement:", couleurBleu, couleurNoire);
    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);

    // Liberation de la police
    TTF_CloseFont(police);

    return nomsJoueurs;
}

void affichageCarte(SDL_Surface* ecran, int** carte, int** joueursStats, SDL_Surface*** images, SDL_Surface** nomsJoueurs, int tours) {
    // Initialisation des variables
    int i                  = 0,                              // Variable incrementatrice
        j                  = 0,                              // Variable incrementatrice
        angle              = 0,                              // Angle d'affichage
        codeIMG            = 0,                              // Code de l'image afficher
        comp1              = 0,                              // Comparaison 1, dans le cas des iles limites
        comp2              = 0,                              // Comparaison 2, dans le cas des iles limites
        comp3              = 0,                              // Comparaison 3, dans le cas des iles limites
        compteIles         = 0,                              // Compteur du nombre d'iles autour, dans les axes orthogonaux
        compteDiag         = 0,                              // Compteur du nombre d'iles autour, dans les axes diagonaux
        codeIles           = 0,                              // Code representant les iles autour dans les axes orthogonaux
        codeIlesDiag       = 0,                              // Code representant les iles autour dans les axes diagonaux
        largeurMax         = 0;                              // Largeur maximale utilise pour l'affichage d'un nom sur la colonne courante
    char textTemp[255]     = "";                             // Chaine de carractere temporaire
    SDL_Color couleurBleu  = {0, 0, 255},                    // Couleur d'ecriture
              couleurNoire = {0, 0, 0};                      // Couleur de fond
    TTF_Font* police       = TTF_OpenFont("Blazed.ttf", 18); // Police d'ecriture
    SDL_Surface *surfaceSDL;                                 // Surface temporaire
    SDL_Rect pos;                                            // Conteneur de la position d'affichage

    // Reinitialisation de l'ecran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    // Parcours de la map
    for(i = 0; i < MAP_HAUTEUR; i++) {
        for(j = 0; j < MAP_LARGEUR; j++) {
            // Determination de la position de la case actuelle et reinitialisation de l'angle et du code image
            pos.x   = j * TAILLE_IMAGES;
            pos.y   = i * TAILLE_IMAGES;
            angle   = 0;
            codeIMG = 0;

            // Determination de l'element a afficher
            SDL_BlitSurface(images[IMG_MAP_VIDE][0], NULL, ecran, &pos); // L'eau est toujours affiche, ensuite on complemente avec le bon element
            if(carte[i][j] == MAP_LIMITE) {
                // Il s'agit d'une ile limite

                // Recuperation de la zone pour bien chercher
                if(i < MAP_HAUTEUR / 2) {
                    if(j < MAP_LARGEUR / 2) {
                        // Zone superieure gauche

                        // Initialisation des variables de comparaison
                        comp1 = (carte[i][j + 1] == MAP_LIMITE);
                        comp2 = (carte[i + 1][j] == MAP_LIMITE);
                        comp3 = (carte[i + 1][j + 1] == MAP_LIMITE);

                        // Recuperation de la bonne image
                        if(comp1 && comp2 && comp3) {
                            codeIMG = IMG_MAP_LIM_COMPLET;
                            angle   = ORIENTATION_0;
                        } else if(comp1 && comp2) {
                            codeIMG = IMG_MAP_LIM_2C_DIRECT;
                            angle   = ORIENTATION_180;
                        } else if(comp1){
                            codeIMG = IMG_MAP_LIM_2C_LIGNE;
                            angle   = ORIENTATION_270;
                        } else {
                            codeIMG = IMG_MAP_LIM_2C_LIGNE;
                            angle   = ORIENTATION_0;
                        }
                    } else {
                        // Zone superieure droite

                        // Initialisation des variables de comparaison
                        comp1 = (carte[i][j - 1] == MAP_LIMITE);
                        comp2 = (carte[i + 1][j] == MAP_LIMITE);
                        comp3 = (carte[i + 1][j - 1] == MAP_LIMITE);

                        // Recuperation de la bonne image
                        if(comp1 && comp2 && comp3) {
                            codeIMG = IMG_MAP_LIM_COMPLET;
                            angle   = ORIENTATION_0;
                        } else if(comp1 && comp2) {
                            codeIMG = IMG_MAP_LIM_2C_DIRECT;
                            angle   = ORIENTATION_90;
                        } else if(comp1){
                            codeIMG = IMG_MAP_LIM_2C_LIGNE;
                            angle   = ORIENTATION_270;
                        } else {
                            codeIMG = IMG_MAP_LIM_2C_LIGNE;
                            angle   = ORIENTATION_180;
                        }
                    }
                } else {
                    if(j < MAP_LARGEUR / 2) {
                        // Zone inferieure gauche

                        // Initialisation des variables de comparaison
                        comp1 = (carte[i][j + 1] == MAP_LIMITE);
                        comp2 = (carte[i - 1][j] == MAP_LIMITE);
                        comp3 = (carte[i - 1][j + 1] == MAP_LIMITE);

                        // Recuperation de la bonne image
                        if(comp1 && comp2 && comp3) {
                            codeIMG = IMG_MAP_LIM_COMPLET;
                            angle   = ORIENTATION_0;
                        } else if(comp1 && comp2) {
                            codeIMG = IMG_MAP_LIM_2C_DIRECT;
                            angle   = ORIENTATION_270;
                        } else if(comp1){
                            codeIMG = IMG_MAP_LIM_2C_LIGNE;
                            angle   = ORIENTATION_90;
                        } else {
                            codeIMG = IMG_MAP_LIM_2C_LIGNE;
                            angle   = ORIENTATION_0;
                        }
                    } else {
                        // Zone inferieure droite

                        // Initialisation des variables de comparaison
                        comp1 = (carte[i][j - 1] == MAP_LIMITE);
                        comp2 = (carte[i - 1][j] == MAP_LIMITE);
                        comp3 = (carte[i - 1][j - 1] == MAP_LIMITE);

                        // Recuperation de la bonne image
                        if(comp1 && comp2 && comp3) {
                            codeIMG = IMG_MAP_LIM_COMPLET;
                            angle   = ORIENTATION_0;
                        } else if(comp1 && comp2) {
                            codeIMG = IMG_MAP_LIM_2C_DIRECT;
                            angle   = ORIENTATION_0;
                        } else if(comp1){
                            codeIMG = IMG_MAP_LIM_2C_LIGNE;
                            angle   = ORIENTATION_90;
                        } else {
                            codeIMG = IMG_MAP_LIM_2C_LIGNE;
                            angle   = ORIENTATION_180;
                        }
                    }
                }
            } else if(carte[i][j] == MAP_ILE) {
                // Il s'agit d'une ile

                // Reinitialisation des variables
                compteIles   = 0;
                compteDiag   = 0;
                codeIles     = 0;
                codeIlesDiag = 0;

                // Recuperation du nombre d'iles environnants et leurs positions
                if(carte[i - 1][j] == MAP_ILE) {
                    // Il y a une ile au dessus de celle-ci
                    compteIles ++;
                    codeIles   += POS_HAUT;
                }
                if(carte[i][j + 1] == MAP_ILE) {
                    // Il y a une ile a droite de celle-ci
                    compteIles ++;
                    codeIles   += POS_DROITE;
                }
                if(carte[i + 1][j] == MAP_ILE) {
                    // Il y a une ile en dessous de celle-ci
                    compteIles ++;
                    codeIles   += POS_BAS;
                }
                if(carte[i][j - 1] == MAP_ILE) {
                    // Il y a une ile a gauche de celle-ci
                    compteIles ++;
                    codeIles   += POS_GAUCHE;
                }

                // Recuperation des iles diagonales
                if(compteIles >= 2) {
                    if(carte[i - 1][j - 1] == MAP_ILE) {
                        // Il y a une ile au dessus a gauche de celle-ci
                        compteDiag   ++;
                        codeIlesDiag += POS_HAUT_G;
                    }
                    if(carte[i - 1][j + 1] == MAP_ILE) {
                        // Il y a une ile au dessus a droite de celle-ci
                        compteDiag   ++;
                        codeIlesDiag += POS_HAUT_D;
                    }
                    if(carte[i + 1][j - 1] == MAP_ILE) {
                        // Il y a une ile en dessous a gauche de celle-ci
                        compteDiag   ++;
                        codeIlesDiag += POS_BAS_G;
                    }
                    if(carte[i + 1][j + 1] == MAP_ILE) {
                        // Il y a une ile a gauche de celle-ci
                        compteDiag   ++;
                        codeIlesDiag += POS_BAS_D;
                    }
                }

                // Determination de l'image a afficher
                switch(compteIles) {
                    case 1:
                        // Il y a une ile autour
                        codeIMG = IMG_MAP_ILE_1C;

                        switch(codeIles) {
                            case POS_HAUT:
                                angle = ORIENTATION_0;
                            break;
                            case POS_DROITE:
                                angle = ORIENTATION_270;
                            break;
                            case POS_BAS:
                                angle = ORIENTATION_180;
                            break;
                            case POS_GAUCHE:
                                angle = ORIENTATION_90;
                            break;
                        }
                    break;
                    case 2:
                        // Il y a deux iles autour

                        // Filtrage des iles "lignes" et doubles
                        if(codeIles == POS_HAUT + POS_BAS) {
                            // Ile "ligne" verticale
                            codeIMG = IMG_MAP_ILE_2C_LIGNE;
                            angle   = ORIENTATION_0;
                        } else if(codeIles == POS_GAUCHE + POS_DROITE) {
                            // Ile "ligne" horrizontale
                            codeIMG = IMG_MAP_ILE_2C_LIGNE;
                            angle   = ORIENTATION_90;
                        } else if(codeIles == POS_HAUT + POS_DROITE) {
                            // Ile doubles HAUT et DROITE
                            angle   = ORIENTATION_0;

                            // Test d'iles dans la diagonale
                            codeIMG = ((codeIlesDiag & POS_HAUT_D) == POS_HAUT_D)?IMG_MAP_ILE_2C_1_DIAG:IMG_MAP_ILE_2C_0_DIAG;
                        } else if(codeIles == POS_HAUT + POS_GAUCHE) {
                            // Ile doubles HAUT et GAUCHE
                            angle   = ORIENTATION_90;

                            // Test d'iles dans la diagonale
                            codeIMG = ((codeIlesDiag & POS_HAUT_G) == POS_HAUT_G)?IMG_MAP_ILE_2C_1_DIAG:IMG_MAP_ILE_2C_0_DIAG;
                        } else if(codeIles == POS_BAS + POS_GAUCHE) {
                            // Ile doubles BAS et GAUCHE
                            angle   = ORIENTATION_180;

                            // Test d'iles dans la diagonale
                            codeIMG = ((codeIlesDiag & POS_BAS_G) == POS_BAS_G)?IMG_MAP_ILE_2C_1_DIAG:IMG_MAP_ILE_2C_0_DIAG;
                        } else {
                            // Ile doubles BAS et DROITE
                            angle   = ORIENTATION_270;

                            // Test d'iles dans la diagonale
                            codeIMG = ((codeIlesDiag & POS_BAS_D) == POS_BAS_D)?IMG_MAP_ILE_2C_1_DIAG:IMG_MAP_ILE_2C_0_DIAG;
                        }
                    break;
                    case 3:
                        // Il y a 3 iles autour

                        // Determination de l'orientation de l'ile
                        if((codeIles ^ POS_HAUT) == POS_MAX) {
                            angle = ORIENTATION_180;
                        } else if((codeIles ^ POS_DROITE) == POS_MAX) {
                            angle = ORIENTATION_90;
                        } else if((codeIles ^ POS_BAS) == POS_MAX) {
                            angle = ORIENTATION_0;
                        } else {
                            angle = ORIENTATION_270;
                        }

                        // Determiner l'image a afficher
                        switch(angle) {
                            case ORIENTATION_0:
                                if((codeIlesDiag & POS_HAUT_G) == POS_HAUT_G && (codeIlesDiag & POS_HAUT_D) == POS_HAUT_D) {
                                    codeIMG = IMG_MAP_ILE_3C_2_DIAG;
                                } else if((codeIlesDiag & POS_HAUT_G) == POS_HAUT_G) {
                                    codeIMG = IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT;
                                } else if((codeIlesDiag & POS_HAUT_D) == POS_HAUT_D) {
                                    codeIMG = IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT;
                                } else {
                                    codeIMG = IMG_MAP_ILE_3C_0_DIAG;
                                }
                            break;
                            case ORIENTATION_90:
                                if((codeIlesDiag & POS_HAUT_G) == POS_HAUT_G && (codeIlesDiag & POS_BAS_G) == POS_BAS_G) {
                                    codeIMG = IMG_MAP_ILE_3C_2_DIAG;
                                } else if((codeIlesDiag & POS_BAS_G) == POS_BAS_G) {
                                    codeIMG = IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT;
                                } else if((codeIlesDiag & POS_HAUT_G) == POS_HAUT_G) {
                                    codeIMG = IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT;
                                } else {
                                    codeIMG = IMG_MAP_ILE_3C_0_DIAG;
                                }
                            break;
                            case ORIENTATION_180:
                                if((codeIlesDiag & POS_BAS_G) == POS_BAS_G && (codeIlesDiag & POS_BAS_D) == POS_BAS_D) {
                                    codeIMG = IMG_MAP_ILE_3C_2_DIAG;
                                } else if((codeIlesDiag & POS_BAS_D) == POS_BAS_D) {
                                    codeIMG = IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT;
                                } else if((codeIlesDiag & POS_BAS_G) == POS_BAS_G) {
                                    codeIMG = IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT;
                                } else {
                                    codeIMG = IMG_MAP_ILE_3C_0_DIAG;
                                }
                            break;
                            default:
                                if((codeIlesDiag & POS_HAUT_D) == POS_HAUT_D && (codeIlesDiag & POS_BAS_D) == POS_BAS_D) {
                                    codeIMG = IMG_MAP_ILE_3C_2_DIAG;
                                } else if((codeIlesDiag & POS_HAUT_D) == POS_HAUT_D) {
                                    codeIMG = IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT;
                                } else if((codeIlesDiag & POS_BAS_D) == POS_BAS_D) {
                                    codeIMG = IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT;
                                } else {
                                    codeIMG = IMG_MAP_ILE_3C_0_DIAG;
                                }
                            break;
                        }
                    break;
                    case 4:
                        // Il y a 4 iles autour

                        // Determination des images a afficher et de leur orientation selon le nombre de diagonales
                        switch(compteDiag) {
                            case 1:
                                // Il y a une diagonale
                                codeIMG = IMG_MAP_ILE_4C_1_DIAG;

                                // Determination de l'orientation de l'ile
                                if((codeIlesDiag & POS_HAUT_G) == POS_HAUT_G) {
                                    angle = ORIENTATION_180;
                                } else if((codeIlesDiag & POS_HAUT_D) == POS_HAUT_D) {
                                    angle = ORIENTATION_90;
                                } else if((codeIlesDiag & POS_BAS_G) == POS_BAS_G) {
                                    angle = ORIENTATION_270;
                                } else {
                                    angle = ORIENTATION_0;
                                }
                            break;
                            case 2:
                                // Il y a deux diagonales

                                // Determination du type de diagonale
                                if(codeIlesDiag == POS_HAUT_G + POS_HAUT_D) {
                                    codeIMG = IMG_MAP_ILE_4C_2_DIAG_ADJ;
                                    angle   = ORIENTATION_180;
                                } else if(codeIlesDiag == POS_HAUT_D + POS_BAS_D) {
                                    codeIMG = IMG_MAP_ILE_4C_2_DIAG_ADJ;
                                    angle   = ORIENTATION_90;
                                } else if(codeIlesDiag == POS_BAS_D + POS_BAS_G) {
                                    codeIMG = IMG_MAP_ILE_4C_2_DIAG_ADJ;
                                    angle   = ORIENTATION_0;
                                } else if(codeIlesDiag == POS_BAS_G + POS_HAUT_G) {
                                    codeIMG = IMG_MAP_ILE_4C_2_DIAG_ADJ;
                                    angle   = ORIENTATION_270;
                                } else {
                                    // Il ne s'agit pas de diagonale adjascentes
                                    codeIMG = IMG_MAP_ILE_4C_2_DIAG_OPP;

                                    // Determination de l'orientation de l'ile
                                    if((codeIlesDiag & POS_HAUT_D) == POS_HAUT_D) {
                                        angle = ORIENTATION_0;
                                    } else {
                                        angle = ORIENTATION_90;
                                    }
                                }
                            break;
                            case 3:
                                // Il y a trois diagonales
                                codeIMG = IMG_MAP_ILE_4C_3_DIAG;

                                // Determination de l'orientation de l'ile
                                if((codeIlesDiag ^ POS_HAUT_G) == POS_MAX) {
                                    angle = ORIENTATION_0;
                                } else if((codeIlesDiag ^ POS_HAUT_D) == POS_MAX) {
                                    angle = ORIENTATION_270;
                                } else if((codeIlesDiag ^ POS_BAS_G) == POS_MAX) {
                                    angle = ORIENTATION_90;
                                } else {
                                    angle = ORIENTATION_180;
                                }
                            break;
                            case 4:
                                // Il y a 4 diagonales
                                angle   = ORIENTATION_0;
                                codeIMG = IMG_MAP_ILE_4C_4_DIAG;
                            break;
                            default:
                                // Il n'y a aucune diagonale
                                angle   = ORIENTATION_0;
                                codeIMG = IMG_MAP_ILE_4C_0_DIAG;
                            break;
                        }
                    break;
                    default:
                        // Il n'y a pas d'iles autour
                        codeIMG = IMG_MAP_ILE_0C;
                        angle   = ORIENTATION_0;
                    break;
                }
            } else if(carte[i][j] >= MAP_DEBRIS && carte[i][j] < MAP_VIDE) {
                // Il s'agit d'un debris
                codeIMG = IMG_MAP_DEBRIS;
            } else if(carte[i][j] >= 0) {
                // Il s'agit d'un joueur/pirate

                // Recuperation de l'orientation
                switch(recupOrientation(carte, j, i)) {
                    case BATEAU_HAUT:
                        // Le bateau est oriente vers le haut
                        angle = ORIENTATION_0;
                    break;
                    case BATEAU_BAS:
                        // Le bateau est oriente vers le bas
                        angle = ORIENTATION_180;
                    break;
                    case BATEAU_GAUCHE:
                        // Le bateau est oriente vers la gauche
                        angle = ORIENTATION_90;
                    break;
                    case BATEAU_DROITE:
                        // Le bateau est oriente vers la droite
                        angle = ORIENTATION_270;
                    break;
                }

                if(recupJoueurID(carte[i][j], BATEAU_JOUEURS) < BATEAU_PIRATES) {
                    // Il s'agit d'un joueur
                    if(recupElementBateau(carte[i][j], BATEAU_JOUEURS) == BATEAU_AVANT) {
                        // Il s'agit de l'avant du bateau
                        codeIMG = IMG_BATEAU_JOUEUR_AVANT;
                    } else if(recupElementBateau(carte[i][j], BATEAU_JOUEURS) == BATEAU_MILIEU) {
                        // Il s'agit du milieu du bateau
                        codeIMG = IMG_BATEAU_JOUEUR_MILIEU;
                    } else {
                        // Il s'agit de l'arriere du bateau
                        codeIMG = IMG_BATEAU_JOUEUR_ARRIERE;
                    }
                } else {
                    // Il s'agit d'un pirate
                    if(recupElementBateau(carte[i][j], BATEAU_JOUEURS) == BATEAU_AVANT) {
                        // Il s'agit de l'avant du bateau
                        codeIMG = IMG_BATEAU_PIRATE_AVANT;
                    } else if(recupElementBateau(carte[i][j], BATEAU_JOUEURS) == BATEAU_MILIEU) {
                        // Il s'agit du milieu du bateau
                        codeIMG = IMG_BATEAU_PIRATE_MILIEU;
                    } else {
                        // Il s'agit de l'arriere du bateau
                        codeIMG = IMG_BATEAU_PIRATE_ARRIERE;
                    }
                }
            }

            // Ajout de la case a l'image
            SDL_BlitSurface(images[codeIMG][angle], NULL, ecran, &pos);
        }
    }

    // Initialisation de la position de la liste des survivants
    pos.x = TAILLE_IMAGES * MAP_LARGEUR;
    pos.y = 0;

    // Affichage du descriptif de la liste des survivants et mise a jour de la nouvelle ordonnee
    SDL_BlitSurface(nomsJoueurs[NOMBRE_JOUEURS], NULL, ecran, &pos);
    pos.y += nomsJoueurs[NOMBRE_JOUEURS]->h;

    // Affichage de la liste des survivants
    for(i = 0; i < NOMBRE_JOUEURS; i++) {
        // Verification de l'etat de survivant
        if(joueursStats[i][ID_STAT_VIE] > 0) {
            // Affichage sur la seconde colone en cas de depassement
            if(pos.y + nomsJoueurs[i]->h >= ECRAN_HAUTEUR) {
                pos.x = largeurMax;
                pos.y = nomsJoueurs[NOMBRE_JOUEURS]->h;
            }

            // Affichage du nom
            SDL_BlitSurface(nomsJoueurs[i], NULL, ecran, &pos);

            // Generation de la surface des stats du joueur
            sprintf(textTemp, "(%dpv et %dpts)", joueursStats[i][ID_STAT_VIE], joueursStats[i][ID_STAT_PTS]);
            surfaceSDL = TTF_RenderText_Shaded(police, textTemp, couleurBleu, couleurNoire);

            // Recuperation de la position
            pos.x += nomsJoueurs[i]->w;

            // Affichage des stats
            SDL_BlitSurface(surfaceSDL, NULL, ecran, &pos);

            // Reinitialisation de la position
            pos.x -= nomsJoueurs[i]->w;

            // MAJ de la largeur maximale
            if(largeurMax < nomsJoueurs[i]->w + surfaceSDL->w) {
                largeurMax = nomsJoueurs[i]->w + surfaceSDL->w;
            }

            // MAJ de l'ordonnee pour ne pas superposer les noms
            pos.y += nomsJoueurs[i]->h;
        }
    }

    // Generation du message du nombre de tours
    sprintf(textTemp, "%d tours", tours);
    surfaceSDL = TTF_RenderText_Shaded(police, textTemp, couleurBleu, couleurNoire);

    // Recuperation de la position
    pos.x = ECRAN_LARGEUR - surfaceSDL->w;
    pos.y = ECRAN_HAUTEUR - surfaceSDL->h;

    // Affichage du nombre de tours
    SDL_BlitSurface(surfaceSDL, NULL, ecran, &pos);

    // Liberation de la surface SDL
    SDL_FreeSurface(surfaceSDL);

    // Liberation de la police
    TTF_CloseFont(police);

    // MAJ de l'ecran
    SDL_Flip(ecran);
}

void affichageCarteAvecTir(SDL_Surface* ecran, int** carte, int** joueursStats, int** trajectoireTir, int* timing, int* continuer, SDL_Surface*** images, SDL_Surface** nomsJoueurs, int tours) {
    // Affichage de la carte normale
    affichageCarte(ecran, carte, joueursStats, images, nomsJoueurs, tours);

    // Affichage du tir avec une fonction recursive
    tir(ecran, carte, trajectoireTir, trajectoireTir[0][0], trajectoireTir[0][1], timing, images, continuer);
}

void affichageClassement(SDL_Surface* ecran, int* listClassement, SDL_Surface** nomsJoueurs, int** joueursStats, int tours, int dureePartie) {
    // Initialisation des variables
    int largeurMax         = 0,                              // Largeur maximale utilise pour afficher un nom sur la colonne
        joueurCourant      = 0,                              // ID du joueur courant
        i                  = 0;                              // Variable incrementatrice
    char textTemp[255]     = "";                             // Chaine de carractere temporaire
    SDL_Color couleurBleu  = {0, 0, 255},                    // Couleur d'ecriture
              couleurNoire = {0, 0, 0};                      // Couleur de fond
    TTF_Font* police       = TTF_OpenFont("Blazed.ttf", 18); // Police d'ecriture
    SDL_Surface *surfaceSDL;                                 // Surface temporaire
    SDL_Rect pos;                                            // Conteneur de la position d'affichage

    // Effacer l'ecran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    // Initialisation de la position du classement
    pos.x = 0;
    pos.y = 0;

    // Affichage du descriptif du classement et mise a jour de l'ordonnee
    SDL_BlitSurface(nomsJoueurs[NOMBRE_JOUEURS + 1], NULL, ecran, &pos);
    pos.y += nomsJoueurs[NOMBRE_JOUEURS + 1]->h;

    // Affichage des classes
    for(i = 0; i < NOMBRE_JOUEURS; i++) {
        // Identification du joueur courant
        joueurCourant = listClassement[i];

        // Affichage sur la seconde colone en cas de depassement
        if(pos.y + nomsJoueurs[joueurCourant]->h >= ECRAN_HAUTEUR) {
            pos.x = largeurMax;
            pos.y = nomsJoueurs[NOMBRE_JOUEURS + 1]->h;
        }

        // Affichage du nom
        SDL_BlitSurface(nomsJoueurs[joueurCourant], NULL, ecran, &pos);

        // Generation de la surface des stats du joueur
        sprintf(textTemp, "(%dpv et %dpts)", joueursStats[joueurCourant][ID_STAT_VIE], joueursStats[joueurCourant][ID_STAT_PTS]);
        surfaceSDL = TTF_RenderText_Shaded(police, textTemp, couleurBleu, couleurNoire);

        // Recuperation de la position
        pos.x += nomsJoueurs[joueurCourant]->w;

        // Affichage des stats
        SDL_BlitSurface(surfaceSDL, NULL, ecran, &pos);

        // Reinitialisation de la position
        pos.x -= nomsJoueurs[joueurCourant]->w;

        // MAJ de la largeur maximale
        if(largeurMax < nomsJoueurs[joueurCourant]->w + surfaceSDL->w) {
            largeurMax = nomsJoueurs[joueurCourant]->w + surfaceSDL->w;
        }

        // MAJ de l'ordonnee pour ne pas superposer les noms
        pos.y += nomsJoueurs[joueurCourant]->h;
    }

    // Generation du message du nombre de tours
    sprintf(textTemp, "%d tours", tours);
    surfaceSDL = TTF_RenderText_Shaded(police, textTemp, couleurBleu, couleurNoire);

    // Recuperation de la position
    pos.x = ECRAN_LARGEUR - surfaceSDL->w;
    pos.y = ECRAN_HAUTEUR - surfaceSDL->h;

    // Affichage du nombre de tours
    SDL_BlitSurface(surfaceSDL, NULL, ecran, &pos);

    // Generation du message de la duree de la partie
    sprintf(textTemp, "%d secondes", dureePartie);
    surfaceSDL = TTF_RenderText_Shaded(police, textTemp, couleurBleu, couleurNoire);

    // Recuperation de la position
    pos.x  = ECRAN_LARGEUR - surfaceSDL->w;
    pos.y -= surfaceSDL->h;

    // Affichage du nombre de tours
    SDL_BlitSurface(surfaceSDL, NULL, ecran, &pos);

    // Liberation de la surface SDL
    SDL_FreeSurface(surfaceSDL);

    // Liberation de la police
    TTF_CloseFont(police);

    // MAJ de l'ecran
    SDL_Flip(ecran);
}

int continuPartie() {
    // Initialisation des variables
    int continuer = TRUE; // BOOLEEN indiquant s'il faut ou non continuer la partie
    SDL_Event event;      // Evenement recupere

    // Verification de la demande de quitter la partie, sans arret du programme
    SDL_PollEvent(&event);

    // Analyse de l'evenement
    switch(event.type)
    {
        case SDL_QUIT:
            // En cas de demande d'arrêt
            continuer = FALSE;
        break;
        case SDL_KEYDOWN:
            // En cas d'appui sur ECHAP
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                continuer = FALSE;
            }
        break;
    }

    return continuer;
}

void pause() {
    // Initialisation des variables
    int continuer = TRUE; // BOOLEEN indiquant s'il faut ou non continuer la partie
    SDL_Event event;      // Evenement recupere

    // Attente de la demande de continuer
    while(continuer) {
        // Attente d'evenement avec arret du programme
        SDL_WaitEvent(&event);

        // Analyse de l'evenement
        switch(event.type)
        {
            case SDL_KEYDOWN:
                // En cas d'appui sur une touche
                continuer = FALSE;
            break;
        }
    }
}

void quitGraphique(SDL_Surface*** images, SDL_Surface** nomsJoueurs) {
    // Initialisation des variables
    int i = 0; // Variable incrementatrice

    // Liberation des images
    SDL_FreeSurface(images[IMG_MAP_VIDE][0]);
    SDL_FreeSurface(images[IMG_MAP_ILE_0C][0]);
    SDL_FreeSurface(images[IMG_MAP_ILE_4C_0_DIAG][0]);
    SDL_FreeSurface(images[IMG_MAP_ILE_4C_4_DIAG][0]);
    SDL_FreeSurface(images[IMG_MAP_LIM_COMPLET][0]);
    SDL_FreeSurface(images[IMG_MAP_DEBRIS][0]);
    SDL_FreeSurface(images[IMG_MAP_BOULET][0]);
    SDL_FreeSurface(images[IMG_MAP_EXPLOSION][0]);
    for(i = 0; i < 2; i++) {
        SDL_FreeSurface(images[IMG_MAP_ILE_2C_LIGNE][i]);
        SDL_FreeSurface(images[IMG_MAP_ILE_4C_2_DIAG_OPP][i]);
    }
    for(i = 0; i < 4; i++) {
        SDL_FreeSurface(images[IMG_MAP_ILE_1C][i]);
        SDL_FreeSurface(images[IMG_MAP_ILE_2C_0_DIAG][i]);
        SDL_FreeSurface(images[IMG_MAP_ILE_2C_1_DIAG][i]);
        SDL_FreeSurface(images[IMG_MAP_ILE_3C_0_DIAG][i]);
        SDL_FreeSurface(images[IMG_MAP_ILE_3C_2_DIAG][i]);
        SDL_FreeSurface(images[IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT][i]);
        SDL_FreeSurface(images[IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT][i]);
        SDL_FreeSurface(images[IMG_MAP_ILE_4C_1_DIAG][i]);
        SDL_FreeSurface(images[IMG_MAP_ILE_4C_2_DIAG_ADJ][i]);
        SDL_FreeSurface(images[IMG_MAP_ILE_4C_3_DIAG][i]);
        SDL_FreeSurface(images[IMG_MAP_LIM_2C_LIGNE][i]);
        SDL_FreeSurface(images[IMG_MAP_LIM_2C_DIRECT][i]);
        SDL_FreeSurface(images[IMG_BATEAU_PIRATE_AVANT][i]);
        SDL_FreeSurface(images[IMG_BATEAU_PIRATE_MILIEU][i]);
        SDL_FreeSurface(images[IMG_BATEAU_PIRATE_ARRIERE][i]);
        SDL_FreeSurface(images[IMG_BATEAU_JOUEUR_AVANT][i]);
        SDL_FreeSurface(images[IMG_BATEAU_JOUEUR_MILIEU][i]);
        SDL_FreeSurface(images[IMG_BATEAU_JOUEUR_ARRIERE][i]);
    }
    for(i = 0; i < NBR_IMAGES; i++) {
        free(images[i]);
    }
    free(images);

    // Liberation des noms des joueurs
    for(i = 0; i < NOMBRE_JOUEURS + 2; i++) {
        SDL_FreeSurface(nomsJoueurs[i]);
    }
    free(nomsJoueurs);

    // Fermeture de SDL_TTF
    TTF_Quit();

    // Fermeture de la SDL
    SDL_Quit();
}

void tir(SDL_Surface* ecran, int** carte, int** trajectoireTir, int x, int y, int* timing, SDL_Surface*** images, int* continuer) {
    // Initialisation des varaibles
    int xCourant = 0, // Abscisse courante
        yCourant = 0; // Ordonnee courante
    SDL_Rect pos;     // Conteneur de la position d'affichage

    // Rendu normal de la case precedente
    pos.x = x * TAILLE_IMAGES;
    pos.y = y * TAILLE_IMAGES;
    if(carte[y][x] == MAP_VIDE) {
        SDL_BlitSurface(images[IMG_MAP_VIDE][ORIENTATION_0], NULL, ecran, &pos);
    } else if(carte[y][x] != MAP_LIMITE) {
        SDL_BlitSurface(images[IMG_MAP_DEBRIS][ORIENTATION_0], NULL, ecran, &pos);
    }

    // Recursif: Tant que le boulet de canon a du chemin a parcourir
    if(trajectoireTir[0][0] != trajectoireTir[1][0] || trajectoireTir[0][1] != trajectoireTir[1][1]) {
        // Affiche du boulet sur la nouvelle case
        pos.x = trajectoireTir[0][0] * TAILLE_IMAGES;
        pos.y = trajectoireTir[0][1] * TAILLE_IMAGES;
        SDL_BlitSurface(images[IMG_MAP_BOULET][0], NULL, ecran, &pos);

        // Enregistrement des coordonnees courantes
        xCourant = trajectoireTir[0][0];
        yCourant = trajectoireTir[0][1];

        // Affichage du nouvel etat
        SDL_Flip(ecran);
        SDL_Delay((Uint32)TEMPS_BOULET);

        // Verification de la continuation
        if((*continuer)) {
            (*continuer) = continuPartie();
        }

        // MAJ du timing
        (*timing) -= TEMPS_BOULET;

        // Mise a jour de la nouvelle trajectoire
        if(trajectoireTir[0][0] == trajectoireTir[1][0]) {
            if(trajectoireTir[0][1] > trajectoireTir[1][1]) {
                trajectoireTir[0][1] --;
            } else {
                trajectoireTir[0][1] ++;
            }
        } else {
            if(trajectoireTir[0][0] > trajectoireTir[1][0]) {
                trajectoireTir[0][0] --;
            } else {
                trajectoireTir[0][0] ++;
            }
        }

        // Appel recursif
        tir(ecran, carte, trajectoireTir, xCourant, yCourant, timing, images, continuer);
    } else {
        // Recuperation des coordonnees actuelles du boulet
        xCourant = trajectoireTir[0][0];
        yCourant = trajectoireTir[0][1];

		// Generation de la position d'affichage
		pos.x = xCourant * TAILLE_IMAGES;
		pos.y = yCourant * TAILLE_IMAGES;

        // Verification que le boulet de canon n'atterrise pas dans l'eau ou sur une ile
        if(carte[yCourant][xCourant] >= MAP_IA) {
            // Affichage d'une explosion
            SDL_BlitSurface(images[IMG_MAP_EXPLOSION][ORIENTATION_0], NULL, ecran, &pos);
        } else if(carte[yCourant][xCourant] >= MAP_DEBRIS && carte[yCourant][xCourant] <= MAP_VIDE) {
			// Affiche du debris
            SDL_BlitSurface(images[IMG_MAP_DEBRIS][ORIENTATION_0], NULL, ecran, &pos);
        } else if(carte[yCourant][xCourant] <= MAP_VIDE) {
            // Affiche du debris
            SDL_BlitSurface(images[IMG_MAP_BOULET][ORIENTATION_0], NULL, ecran, &pos);
        }

        // Affichage du nouvel etat
        SDL_Flip(ecran);
        SDL_Delay((Uint32)TEMPS_BOULET);

        // Verification de la continuation
        if((*continuer)) {
            (*continuer) = continuPartie();
        }

        // MAJ du timing et verification
        (*timing) -= TEMPS_BOULET;
        if(timing < 0) {
            (*timing) = 0;
        }
    }
}
