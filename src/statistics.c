#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/statistics.h"

// Initialise les statistiques du jeu
Stats *init_stats() {
    Stats *stats = malloc(sizeof(Stats));
    if (stats == NULL) {
        perror("Erreur d'allocation de mémoire pour les statistiques");
        exit(EXIT_FAILURE);
    }
    stats->nb_total_coups = 0;
    stats->nb_coups_a_leau = 0;
    stats->nb_coups_deja_joue = 0;
    stats->nb_coups_touche = 0;
    memset(stats->nom_dernier_navire_coule, 0, sizeof(stats->nom_dernier_navire_coule));
    return stats;
}

// Met à jour les statistiques du jeu
void update_stats(Stats *stats, int resultat_coup, const char *nom_navire_coule) {
    stats->nb_total_coups++;
    switch (resultat_coup) {
        case A_LEAU:
            stats->nb_coups_a_leau++;
            break;
        case DEJA_JOUE:
            stats->nb_coups_deja_joue++;
            break;
        case TOUCHE:
            stats->nb_coups_touche++;
            break;
        default:
            fprintf(stderr, "Résultat de coup inconnu : %d\n", resultat_coup);
            break;
    }
    if (nom_navire_coule != NULL) {
        strncpy(stats->nom_dernier_navire_coule, nom_navire_coule, sizeof(stats->nom_dernier_navire_coule) - 1);
    }
}

// Enregistre les statistiques du jeu dans un fichier
void save_stats(Stats *stats, const char *filename) {
    printf("Enregistrement des statistiques dans le fichier %s\n", filename);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier de statistiques");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Nombre total de coups : %d\n", stats->nb_total_coups);
    fprintf(file, "Nombre de coups à l'eau : %d\n", stats->nb_coups_a_leau);
    fprintf(file, "Nombre de coups déjà joués : %d\n", stats->nb_coups_deja_joue);
    fprintf(file, "Nombre de coups touchés : %d\n", stats->nb_coups_touche);
    fprintf(file, "Nom du dernier navire coulé : %s\n", stats->nom_dernier_navire_coule);
    fclose(file);
}

// Libère les ressources associées aux statistiques du jeu
void free_stats(Stats *stats) {
    free(stats);
}
