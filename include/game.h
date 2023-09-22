#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} Coordonnees;

typedef struct {
    int taille;
    Coordonnees premiere_case;
    int sens;  // 0 : haut, 1 : droite, 2 : bas, 3 : gauche
} Navire;

void initialisation_plateau(int **plateau, int taille_plateau);
Navire creer_navire(int taille, int taille_plateau);
int est_valide(int **plateau, int taille_plateau, Navire *navire);
void placer_navire(int **plateau, Navire *navire);
void initialiser_propositions(int **prop, int taille_plateau);
void initialiser_nb_touche_nav(int *nb_touche_nav);
void proposition_joueur(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau);
int compter_taille_navire(int **plateau, int x, int y, int taille_plateau);
void afficher_navire(Navire *navire);
int a_gagne(int *nb_touche_nav);
void afficher_propositions(int **prop, int taille_plateau);
void afficher_resultat(int a_gagne, int nb_joue);
int nb_aleatoire(int max);
void afficher_navires_non_touches(int **plateau, int **propositions, int taille_plateau);
int tous_navires_coules(int **plateau, int taille_plateau);
int aucun_navire_non_touche(int **plateau, int **propositions, int taille_plateau);
#endif
