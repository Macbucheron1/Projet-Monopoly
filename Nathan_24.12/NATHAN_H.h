#ifndef NATHAN_H_H_INCLUDED
#define NATHAN_H_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



#define TAILLE_NOM 50
#define TAILLE_PLATEAU 32

typedef struct //case(ou cartes) du plateau
{
    int position; //position de la case sur le plateau
    int valeur; //prix d'achat
    char nom_joueur[TAILLE_NOM]; //nom du propri�taire(NONE si ya pas)
    int nb_maison; //entre 0 et 3
    int nb_hotel; //si ya un hotel ou pas
    int val_maison; //prix d'une maison sur la case
    int val_hotel; //prix de l'hotel
    int groupe_cartes; //groupe � laquelle appartient la case
}t_case;

typedef struct //joueur du plateau (max 4)
{
    char nom[TAILLE_NOM];
    int position; //initialis� � 0, la case d�part (modulo 32)
    int argent; //� initialiser avec le montant de base (argent sur le compte, c'est � dire argent utilisable)
    int capital; //c'est l'argent que le joueur a sur son compte plus la valeur des propriete, des maisons,etc (sert dns les parties rapides)
    t_case proprietes[TAILLE_PLATEAU]; //propri�t�s d�tenue par le joueur (tableau de case)
    bool prison; //bool�en v�rifiant si le joueur est en prison ou non (0 pas en prison, totu autre chiffre = en prison)
    int tour_prison; //nombre de tour en prison(max: 3)
    int carte_sortie_prison; //nombre de carte permettant au joueur de sortir de prison
}t_joueur;

typedef struct
{
    int nb_maison_restante; //32 maisons max
    int nb_hotel_restante; //12 hotel max
}t_banque;

int lancer_des(int tab_de[]);
void deplacement(int* liste_de, t_joueur* joueur);
void aller_a(int indice_case, t_joueur* joueur);
void entrer_prison(t_joueur* joueur);
void sortie_prison(int* liste_de, t_joueur* joueur);



#endif // NATHAN_H_H_INCLUDED
