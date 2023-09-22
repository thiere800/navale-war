#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/game.h"
#include "../include/statistics.h"

int main(int argc, char *argv[]) {
    int taille_plateau = 10;
    char *stats_filename = NULL;
    Stats *stats = NULL;
    int opt;
    int nb_touche = 0;
    int nb_touche_nav[5] = {0, 0, 0, 0, 0};

    while ((opt = getopt(argc, argv, "S:")) != -1) {
        switch (opt) {
            case 'S':
                stats_filename = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-S stats_filename]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (stats_filename != NULL) {
        stats = init_stats();
    }

    printf("Entrez la taille du plateau (min 6, max 100): ");
    scanf("%d", &taille_plateau);

    if (taille_plateau < 6 || taille_plateau > 100) {
        fprintf(stderr, "La taille du plateau est invalide\n");
        exit(EXIT_FAILURE);
    }

    int **plateau = (int **) calloc(taille_plateau, sizeof(int *));
    for (int i = 0; i < taille_plateau; i++) {
        plateau[i] = (int *) calloc(taille_plateau, sizeof(int));
    }

    int **propositions = (int **) calloc(taille_plateau, sizeof(int *));
    for (int i = 0; i < taille_plateau; i++) {
        propositions[i] = (int *) calloc(taille_plateau, sizeof(int));
    }

    initialisation_plateau(plateau, taille_plateau);

    int nb_joue = 0;
    while (!a_gagne(nb_touche_nav)) {
        proposition_joueur(plateau, propositions, &nb_touche, &nb_joue, nb_touche_nav, taille_plateau);
        afficher_propositions(propositions, taille_plateau);
        printf("Nombre de  : %d\n", nb_touche);
        afficher_navires_non_touches(plateau, propositions, taille_plateau);
        if (tous_navires_coules(plateau, taille_plateau)) {
            printf("Vous avez coulé tous les navires ! Victoire !\n");
            break;
        }
        if (stats != NULL) {
            update_stats(stats, TOUCHE, NULL);
        }
    }

    afficher_resultat(a_gagne(nb_touche_nav), nb_joue);

    if (stats != NULL) {
        save_stats(stats, stats_filename);
        free_stats(stats);
    }

    // Libération de la mémoire
    for (int i = 0; i < taille_plateau; i++) {
        free(plateau[i]);
        free(propositions[i]);
    }
    free(plateau);
    free(propositions);

    return 0;
}
