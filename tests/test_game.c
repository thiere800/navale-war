#include <CUnit/Basic.h>
#include "../include/game.h"

// Test de la fonction est_valide
void test_est_valide(void) {
    int taille_plateau = 10;
    int **plateau = malloc(taille_plateau * sizeof(int*));
    for (int i = 0; i < taille_plateau; i++) {
        plateau[i] = malloc(taille_plateau * sizeof(int));
    }

    // Test d'un navire valide
    Navire navire;
    navire.taille = 3;
    navire.sens = 0;  // Haut
    navire.premiere_case.x = 3;
    navire.premiere_case.y = 5;

    int resultat = est_valide(plateau, taille_plateau, &navire);
    CU_ASSERT_EQUAL(resultat, 1);

    // Test d'un navire non valide (hors du plateau)
    navire.premiere_case.x = 10;
    navire.premiere_case.y = 5;

    resultat = est_valide(plateau, taille_plateau, &navire);
    CU_ASSERT_EQUAL(resultat, 0);

    // Libération de la mémoire
    for (int i = 0; i < taille_plateau; i++) {
        free(plateau[i]);
    }
    free(plateau);
}

// Test de la fonction placer_navire
void test_placer_navire(void) {
    int taille_plateau = 10;
    int **plateau = malloc(taille_plateau * sizeof(int*));
    for (int i = 0; i < taille_plateau; i++) {
        plateau[i] = malloc(taille_plateau * sizeof(int));
    }

    // Création d'un navire
    Navire navire;
    navire.taille = 3;
    navire.sens = 0;  // Haut
    navire.premiere_case.x = 3;
    navire.premiere_case.y = 5;

    // Placement du navire sur le plateau
    placer_navire(plateau, &navire);

    // Vérification du placement du navire sur le plateau
    CU_ASSERT_EQUAL(plateau[3][5], 3);
    CU_ASSERT_EQUAL(plateau[2][5], 3);
    CU_ASSERT_EQUAL(plateau[1][5], 3);

    // Libération de la mémoire
    for (int i = 0; i < taille_plateau; i++) {
        free(plateau[i]);
    }
    free(plateau);
}

// Test de la fonction compter_taille_navire
void test_compter_taille_navire(void) {
    int taille_plateau = 10;
    int **plateau = malloc(taille_plateau * sizeof(int*));
    for (int i = 0; i < taille_plateau; i++) {
        plateau[i] = malloc(taille_plateau * sizeof(int));
    }

    // Placement d'un navire sur le plateau
    plateau[3][5] = 3;
    plateau[2][5] = 3;
    plateau[1][5] = 3;

    // Comptage de la taille du navire
    int taille = compter_taille_navire(plateau, 3, 5, taille_plateau);
    CU_ASSERT_EQUAL(taille, 3);

    // Libération de la mémoire
    for (int i = 0; i < taille_plateau; i++) {
        free(plateau[i]);
    }
    free(plateau);
}

// Fonction principale des tests
int main() {
    // Initialisation du framework CUnit
    CU_initialize_registry();

    // Création d'une suite de tests
    CU_pSuite suite = CU_add_suite("Suite de tests", NULL, NULL);

    // Ajout des tests à la suite de tests
    CU_add_test(suite, "Test de est_valide", test_est_valide);
    CU_add_test(suite, "Test de placer_navire", test_placer_navire);
    CU_add_test(suite, "Test de compter_taille_navire", test_compter_taille_navire);

    // Exécution des tests
    CU_basic_run_tests();

    // Nettoyage du framework CUnit
    CU_cleanup_registry();

    return 0;
}
