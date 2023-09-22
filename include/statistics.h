#ifndef STATISTICS_H
#define STATISTICS_H

#define NOM_NAVIRE_MAX 64

typedef struct {
    int nb_total_coups;
    int nb_coups_a_leau;
    int nb_coups_deja_joue;
    int nb_coups_touche;
    char nom_dernier_navire_coule[NOM_NAVIRE_MAX];
} Stats;

enum { A_LEAU, DEJA_JOUE, TOUCHE , COULE};

// Initialise les statistiques du jeu
Stats *init_stats();

// Met à jour les statistiques du jeu
void update_stats(Stats *stats, int resultat_coup, const char *nom_navire_coule);

// Enregistre les statistiques du jeu dans un fichier
void save_stats(Stats *stats, const char *filename);

// Libère les ressources associées aux statistiques du jeu
void free_stats(Stats *stats);

int count_unique_letters(const char *str);

#endif
