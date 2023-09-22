#include "../include/game.h"
#include <stdio.h>
#include <stdlib.h>

void initialisation_plateau(int **plateau, int taille_plateau) {
    int i, j;
    for (i = 0; i < taille_plateau; i++) {
        for (j = 0; j < taille_plateau; j++) {
            plateau[i][j] = 0;
        }
    }

    // Création des navires
    Navire navires[5];
    navires[0] = creer_navire(5, taille_plateau); // Porte-avions
    navires[1] = creer_navire(4, taille_plateau); // Croiseur
    navires[2] = creer_navire(3, taille_plateau); // Contre-torpilleur 1
    navires[3] = creer_navire(3, taille_plateau); // Contre-torpilleur 2
    navires[4] = creer_navire(2, taille_plateau); // Torpilleur

    // Placement des navires sur le plateau
    for (i = 0; i < 5; i++) {
        while (!est_valide(plateau, taille_plateau, &navires[i])) {
            navires[i] = creer_navire(navires[i].taille, taille_plateau);
        }
        placer_navire(plateau, &navires[i]);
        afficher_navire(&navires[i]); // Affichage des coordonnées du navire créé
    }
}

Navire creer_navire(int taille, int taille_plateau) {
    Navire navire;
    navire.taille = taille;
    navire.sens = nb_aleatoire(4);
    navire.premiere_case.x = nb_aleatoire(taille_plateau);
    navire.premiere_case.y = nb_aleatoire(taille_plateau);
    return navire;
}

int est_valide(int **plateau, int taille_plateau, Navire *navire) {
    if (navire->premiere_case.x < 0 || navire->premiere_case.x >= taille_plateau ||
        navire->premiere_case.y < 0 || navire->premiere_case.y >= taille_plateau) {
        return 0;
    }

    switch (navire->sens) {
        case 0:  // Haut
            if (navire->premiere_case.x - navire->taille + 1 < 0) {
                return 0;
            }
            break;
        case 1:  // Droite
            if (navire->premiere_case.y + navire->taille - 1 >= taille_plateau) {
                return 0;
            }
            break;
        case 2:  // Bas
            if (navire->premiere_case.x + navire->taille - 1 >= taille_plateau) {
                return 0;
            }
            break;
        case 3:  // Gauche
            if (navire->premiere_case.y - navire->taille + 1 < 0) {
                return 0;
            }
            break;
    }

    int i;
    for (i = 0; i < navire->taille; i++) {
        switch (navire->sens) {
            case 0:  // Haut
                if (plateau[navire->premiere_case.x - i][navire->premiere_case.y] != 0) {
                    return 0;
                }
                break;
            case 1:  // Droite
                if (plateau[navire->premiere_case.x][navire->premiere_case.y + i] != 0) {
                    return 0;
                }
                break;
            case 2:  // Bas
                if (plateau[navire->premiere_case.x + i][navire->premiere_case.y] != 0) {
                    return 0;
                }
                break;
            case 3:  // Gauche
                if (plateau[navire->premiere_case.x][navire->premiere_case.y - i] != 0) {
                    return 0;
                }
                break;
        }
    }

    return 1;
}

void placer_navire(int **plateau, Navire *navire) {
    int i;
    switch (navire->sens) {
        case 0:  // Haut
            for (i = 0; i < navire->taille; i++) {
                plateau[navire->premiere_case.x - i][navire->premiere_case.y] = navire->taille;
            }
            break;
        case 1:  // Droite
            for (i = 0; i < navire->taille; i++) {
                plateau[navire->premiere_case.x][navire->premiere_case.y + i] = navire->taille;
            }
            break;
        case 2:  // Bas
            for (i = 0; i < navire->taille; i++) {
                plateau[navire->premiere_case.x + i][navire->premiere_case.y] = navire->taille;
            }
            break;
        case 3:  // Gauche
            for (i = 0; i < navire->taille; i++) {
                plateau[navire->premiere_case.x][navire->premiere_case.y - i] = navire->taille;
            }
            break;
    }
}

void initialiser_propositions(int **prop, int taille_plateau) {
    int i, j;
    for (i = 0; i < taille_plateau; i++) {
        for (j = 0; j < taille_plateau; j++) {
            prop[i][j] = 0;
        }
    }
}

void initialiser_nb_touche_nav(int *nb_touche_nav) {
    int i;
    for (i = 0; i < 5; i++) {
        nb_touche_nav[i] = 0;
    }
}

void proposition_joueur(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau) {
    int x, y;
    printf("Entrez les coordonnées de votre proposition (x y) : ");
    scanf("%d %d", &x, &y);

    if (x < 0 || x >= taille_plateau || y < 0 || y >= taille_plateau) {
        printf("Coordonnées invalides.\n");
        return;
    }

    if (prop[x][y] != 0) {
        printf("Cette case a déjà été proposée.\n");
        return;
    }

    (*nb_joue)++;
    prop[x][y] = 1;

    if (plateau[x][y] != 0) {
        int taille_navire = compter_taille_navire(plateau, x, y, taille_plateau);
        nb_touche_nav[taille_navire - 2]++;
        if (nb_touche_nav[taille_navire - 2] == taille_navire) {
            printf("Vous avez coulé un navire de taille %d\n", taille_navire);
        } else {
            printf("Vous avez touché un navire !\n");
        }
        (*nb_touche)++;

        if (a_gagne(nb_touche_nav)) {
            afficher_resultat(1, *nb_joue);
            exit(0);
        }
    } else {
        printf("Dans l'eau...\n");
    }

    if (a_gagne(nb_touche_nav)) {
        afficher_resultat(1, *nb_joue);
        exit(0);
    }

    afficher_navires_non_touches(plateau, prop, taille_plateau);

    if (aucun_navire_non_touche(plateau, prop, taille_plateau)) {
        afficher_resultat(1, *nb_joue);
        exit(0);
    }
}

int aucun_navire_non_touche(int **plateau, int **propositions, int taille_plateau) {
    for (int i = 0; i < taille_plateau; i++) {
        for (int j = 0; j < taille_plateau; j++) {
            if (plateau[i][j] > 0 && propositions[i][j] == 0) {
                return 0; // Il reste au moins un navire non touché
            }
        }
    }
    return 1; // Tous les navires ont été touchés
}


void afficher_navires_non_touches(int **plateau, int **propositions, int taille_plateau) {
    printf("Coordonnées des navires non touchés :\n");
    for (int i = 0; i < taille_plateau; i++) {
        for (int j = 0; j < taille_plateau; j++) {
            if (plateau[i][j] > 0 && propositions[i][j] == 0) {
                printf("Case : (%d, %d)\n", i, j);
            }
        }
    }
    printf("\n");
}

int tous_navires_coules(int **plateau, int taille_plateau) {
    int i, j;
    for (i = 0; i < taille_plateau; i++) {
        for (j = 0; j < taille_plateau; j++) {
            if (plateau[i][j] > 1 && plateau[i][j] <= 6) {
                return 0;
            }
        }
    }
    return 1;
}

int compter_taille_navire(int **plateau, int x, int y, int taille_plateau) {
    int taille = 0;
    int i, j;

    // Compte la taille du navire vers le haut
    for (i = x; i >= 0; i--) {
        if (plateau[i][y] == 0) {
            break;
        }
        taille++;
    }

    // Compte la taille du navire vers le bas
    for (i = x + 1; i < taille_plateau; i++) {
        if (plateau[i][y] == 0) {
            break;
        }
        taille++;
    }

    // Compte la taille du navire vers la gauche
    for (j = y - 1; j >= 0; j--) {
        if (plateau[x][j] == 0) {
            break;
        }
        taille++;
    }

    // Compte la taille du navire vers la droite
    for (j = y + 1; j < taille_plateau; j++) {
        if (plateau[x][j] == 0) {
            break;
        }
        taille++;
    }

    return taille;
}

int a_gagne(int *nb_touche_nav) {
    int i;
    for (i = 0; i < 5; i++) {
        if (nb_touche_nav[i] != i + 2) {
            return 0;
        }
    }
    return 1;
}

void afficher_propositions(int **prop, int taille_plateau) {
    int i, j;
    printf("\nTableau des propositions :\n");
    printf("-------------------------\n");
    for (i = 0; i < taille_plateau; i++) {
        for (j = 0; j < taille_plateau; j++) {
            if (prop[i][j] == 0) {
                printf(". ");
            } else if (prop[i][j] == 1) {
                printf("x ");
            } else {
                printf("o ");
            }
        }
        printf("\n");
    }
    printf("-------------------------\n");
}

void afficher_resultat(int a_gagne, int nb_joue) {
    if (a_gagne) {
        printf("Bravo !! Vous avez gagné en %d coups.\n", nb_joue);
    } else {
        printf("Dommage, vous avez perdu.\n");
    }
}

int nb_aleatoire(int max) {
    return rand() % max;
}

void afficher_navire(Navire *navire) {
    printf("Coordonnées du navire (taille %d):\n", navire->taille);
    printf("Première case: (%d, %d)\n", navire->premiere_case.x, navire->premiere_case.y);
    printf("Sens: ");
    switch (navire->sens) {
        case 0:
            printf("haut\n");
            break;
        case 1:
            printf("droite\n");
            break;
        case 2:
            printf("bas\n");
            break;
        case 3:
            printf("gauche\n");
            break;
        default:
            printf("inconnu\n");
            break;
    }
    printf("\n");
}
