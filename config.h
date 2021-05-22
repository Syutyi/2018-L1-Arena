#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "Link.h"

/*
 * Gains de POINTS
 */
#define PTS_ACTION_DEPLACEMENT 10 // Nombre de points a ajouter en cas de deplacement
#define PTS_ACTION_COLLISION   20 // Nombre de points a ajouter en cas de collision d'un bateau
#define PTS_ACTION_TIR_REUSSI  50 // Nombre de points a ajouter en cas de tir reussi
#define PTS_ACTION_TIR_MILIEU  80 // Nombre de points a ajouter en cas de tir reussi sur le milieu

/*
 * Informations des limites
 */
#define TIR_PORTEE      6 // Portee d'un tir de boulet
#define LIMITE_CAPACITE 3 // limites de la capacite

/*
 * Duree des limites
 */
#define TPS_RECHARGEMENT   2 // Temps de rechargement du canon
#define TPS_RECONSTRUCTION 3 // Temps de reconstruction du canon et de la propulsion
#define TPS_CAPACITE       5 // Temps de rechargement de la capacite
#define TPS_RETRECISSEMENT 5 // Temps entre deux retrecissement de Map

/*
 * Perte de VIES
 */
#define VIE_FINAL_ATTAQUE_MILIEU   -1 // Vie finale lors d'une attaque sur le milieu
#define VIE_FINAL_COLLISION_ILE    0  // Vie perdue lors d'une collision avec une ile
#define VIE_FINAL_COLLISION_BATEAU 0  // Vie perdue lors d'une collision avec un bateau
#define VIE_ATTAQUE_AV_AR          50 // Vie perdue lors d'une attaque sur l'avant ou l'arriere
#define VIE_COLLISION_DEBRIS       25 // Vie perdue lors d'une collision avec un debris

/*
 * Informations graphiques
 */
#define ECRAN_LARGEUR 1366 // Largeur de l'ecran
#define ECRAN_HAUTEUR 600  // Hauteur de l'ecran
#define NBR_IMAGES    28   // Nombre d'images differentes
#define TAILLE_IMAGES 12   // Taille des images

#endif // CONFIG_H_INCLUDED
