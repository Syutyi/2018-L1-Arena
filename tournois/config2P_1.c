#include "config2P_1.h"

int* test1(int** carte, int largeur, int hauteur) {
    int *test = NULL;
    test = (int*)malloc(2 * sizeof(int));
    test[ORDRE_PRINCIPAL] = TIRER;
    test[COMPLEMENT_ORDRE] = 0;
    return test;
}

int* test2(int** carte, int largeur, int hauteur) {
    int *test = NULL;
    test = (int*)malloc(2 * sizeof(int));
    test[ORDRE_PRINCIPAL] = TIRER;
    test[COMPLEMENT_ORDRE] = 0;
    return test;
}

int* test3(int** carte, int largeur, int hauteur) {
    int *test = NULL;
    test = (int*)malloc(2 * sizeof(int));
    test[ORDRE_PRINCIPAL] = AVANCER;
    test[COMPLEMENT_ORDRE] = 1;
    return test;
}

int* test4(int** carte, int largeur, int hauteur) {
    int *test = NULL;
    test = (int*)malloc(2 * sizeof(int));
    test[ORDRE_PRINCIPAL] = AVANCER;
    test[COMPLEMENT_ORDRE] = LIMITE_CAPACITE;
    return test;
}

int* test5(int** carte, int largeur, int hauteur) {
    int *test = NULL;
    test = (int*)malloc(2 * sizeof(int));
    test[ORDRE_PRINCIPAL] = TOURNER;
    test[COMPLEMENT_ORDRE] = TOURNER_GAUCHE;
    return test;
}

int* test6(int** carte, int largeur, int hauteur) {
    int *test = NULL;
    test = (int*)malloc(2 * sizeof(int));
    test[ORDRE_PRINCIPAL] = TOURNER;
    test[COMPLEMENT_ORDRE] = TOURNER_DROITE;
    return test;
}
