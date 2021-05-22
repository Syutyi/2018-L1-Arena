#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

/*
 * BOOLEEN
 */
#define TRUE  1 // BOOLEEN indiquant VRAI
#define FALSE 0 // BOOLEEN indiquant FAUX

/*
 * Element de MAP
 */
#define MAP_IA     0   // Identifiant minimale d'une IA de la map
#define MAP_VIDE   -1  // Identifiant d'un element neutre de la map
#define MAP_ILE    -10 // Identifiant d'un element representant une ile sur la map
#define MAP_LIMITE -20 // Identifiant d'un element representant un contour de la map
#define MAP_DEBRIS -4  // Identifiant d'un element representant un debris, du au naufrage ou a la tombe d'un boulet

/*
 * Index des STATS
 */
#define ID_STAT_VIE      0 // Index de la vie du joueur
#define ID_STAT_PTS      1 // Index des points du joueur
#define ID_STAT_SHOOT    2 // Index du nombre de tours restant avant la possibilite de tirer
#define ID_STAT_MOVE     3 // Index du nombre de tours restant avant la possibilite de bouger
#define ID_STAT_X        4 // Index de la coordonnee en X de l'avant du bateau du joueur
#define ID_STAT_Y        5 // Index de la coordonnee en Y de l'avant du bateau du joueur
#define ID_STAT_CAPACITE 6 // Index du nombre de tours restant avant la possibilite d'utiliser la capacite
#define ID_JOUEUR_ID     7 // Index de l'ID du joueur

/*
 * Dirrection du BATEAU
 */
#define BATEAU_HAUT   0 // Orientation du bateau vers le haut
#define BATEAU_BAS    1 // Orientation du bateau vers le bas
#define BATEAU_GAUCHE 2 // Orientation du bateau vers la gauche
#define BATEAU_DROITE 3 // Orientation du bateau vers la droite

/*
 * Element du BATEAU
 */
#define BATEAU_AVANT   1 // Identifiant de l'avant du bateau
#define BATEAU_MILIEU  2 // Identifiant du milieu du bateau
#define BATEAU_ARRIERE 3 // Identifiant de l'arriere du bateau

/*
 * Type d'ordres
 */
#define ORDRE_PRINCIPAL  0 // Identifiant de l'ordre principal
#define COMPLEMENT_ORDRE 1 // Identifiant du complement d'ordre

/*
 * Ordres
 */
#define AVANCER 1 // Identifiant de l'ordre avancer
#define TIRER   2 // Identifiant de l'ordre tirer
#define TOURNER 3 // Identifiant de l'ordre tourner

/*
 * Direction du retournement du bateau
 */
#define TOURNER_GAUCHE 1 // Tourner vers la gauche
#define TOURNER_DROITE 2 // Tourner vers la droite

/*
 * Indentifiants des IAs
 */
#define BATEAU_JOUEURS 0  // Identifiant des joueurs
#define BATEAU_PIRATES 32 // Identifiant des pirates

/*
 * Masques de filtrage et codes de recuperation
 *
 * ID d'un element de bateau(bits à bits):
 *  * * * * * * * * * * * * * * * * * * * * * * * * |       * *        |   *    |  * * * * *
 *                      Autre                       |  Element Bateau  |  Type  |     ID
 */
#define FILTRAGE_BATEAU_ID 0b11000000 // Masque de filtrage pour recuperer l'id de l'element du bateau
#define FILTRAGE_JOUEUR_ID 0b00111111 // Masque de filtrage pour recuperer l'id de l'IA
#define CODE_BATEAU        0b01000000 // Code de recuperation du bateau

/*
 * Index des images
 */
#define IMG_MAP_VIDE                    0  // Index d'un element vide
#define IMG_MAP_ILE_0C                  1  // Index d'une ile avec 0 ile a cote
#define IMG_MAP_ILE_1C                  2  // Index d'une ile avec 1 ile a cote
#define IMG_MAP_ILE_2C_LIGNE            3  // Index d'une ile avec 2 iles a cote en ligne
#define IMG_MAP_ILE_2C_0_DIAG           4  // Index d'une ile avec 2 iles a cote avec aucune ile sur la diagonale
#define IMG_MAP_ILE_2C_1_DIAG           5  // Index d'une ile avec 2 iles a cote avec 1 ile sur la diagonale
#define IMG_MAP_ILE_3C_0_DIAG           6  // Index d'une ile avec 3 iles a cote avec aucune ile sur la diagonale
#define IMG_MAP_ILE_3C_2_DIAG           7  // Index d'une ile avec 3 iles a cote avec 2 iles sur les diagonales
#define IMG_MAP_ILE_3C_1_DIAG_TOP_LEFT  8  // Index d'une ile avec 3 iles a cote avec 1 ile sur le haut a gauche
#define IMG_MAP_ILE_3C_1_DIAG_TOP_RIGHT 9  // Index d'une ile avec 3 iles a cote avec 1 ile sur le haut a droite
#define IMG_MAP_ILE_4C_0_DIAG           10 // Index d'une ile avec 4 iles a cote avec aucune ile sur la diagonale
#define IMG_MAP_ILE_4C_1_DIAG           11 // Index d'une ile avec 4 iles a cote avec 1 ile sur la diagonale
#define IMG_MAP_ILE_4C_2_DIAG_ADJ       12 // Index d'une ile avec 4 iles a cote avec 2 iles sur les diagonales adjascentes
#define IMG_MAP_ILE_4C_2_DIAG_OPP       13 // Index d'une ile avec 4 iles a cote avec 2 iles sur les diagonales opposees
#define IMG_MAP_ILE_4C_3_DIAG           14 // Index d'une ile avec 4 iles a cote avec 3 iles sur les diagonales
#define IMG_MAP_ILE_4C_4_DIAG           15 // Index d'une ile avec 4 iles a cote avec 4 iles sur les diagonales
#define IMG_MAP_LIM_2C_LIGNE            16 // Index d'une ile de limite avec 2 iles a cote en ligne
#define IMG_MAP_LIM_2C_DIRECT           17 // Index d'une ile de limite avec 2 iles a cote adjascentes
#define IMG_MAP_LIM_COMPLET             18 // Index d'une ile de limite complete
#define IMG_MAP_DEBRIS                  19 // Index d'un debris
#define IMG_MAP_BOULET                  20 // Index d'un boulet de canon
#define IMG_MAP_EXPLOSION               21 // Index de l'explosion due a un boulet de canon arrivant sur un element different de l'eau et d'une ile
#define IMG_BATEAU_PIRATE_AVANT         22 // Index de l'avant du bateau pirate
#define IMG_BATEAU_PIRATE_MILIEU        23 // Index du milieu du bateau pirate
#define IMG_BATEAU_PIRATE_ARRIERE       24 // Index de l'arriere du bateau pirate
#define IMG_BATEAU_JOUEUR_AVANT         25 // Index de l'avant du bateau joueur
#define IMG_BATEAU_JOUEUR_MILIEU        26 // Index du milieu du bateau joueur
#define IMG_BATEAU_JOUEUR_ARRIERE       27 // Index de l'arriere du bateau joueur

/*
 * Orientation des images
 */
#define ORIENTATION_0   0 // Orientation neutre
#define ORIENTATION_90  1 // Orientation 90 selon le sens trigo
#define ORIENTATION_180 2 // Orientation 180 selon le sens trigo
#define ORIENTATION_270 3 // Orientation 270 selon le sens trigo

/*
 * Position des iles environnants
 */
#define POS_HAUT   0b0001 // Code de la position en haut
#define POS_DROITE 0b0010 // Code de la position a droite
#define POS_BAS    0b0100 // Code de la position en bas
#define POS_GAUCHE 0b1000 // Code de la position a gauche
#define POS_HAUT_G 0b0001 // Code de la position en haut a gauche
#define POS_HAUT_D 0b0010 // Code de la position en haut a droite
#define POS_BAS_G  0b0100 // Code de la position en bas a gauche
#define POS_BAS_D  0b1000 // Code de la position en bas a droite
#define POS_MAX    0b1111 // Limite maximal des codes

/*
 * Index de limite de Map
 */
#define MAP_LIMITE_HAUT   0 // Index de la case contenant la coordonee de la limite haute
#define MAP_LIMITE_BAS    1 // Index de la case contenant la coordonee de la limite basse
#define MAP_LIMITE_GAUCHE 2 // Index de la case contenant la coordonee de la limite gauche
#define MAP_LIMITE_DROITE 3 // Index de la case contenant la coordonee de la limite droite

#endif // CONST_H_INCLUDED
