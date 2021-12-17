#ifndef STRUCT_MONOP_HEADER_H_INCLUDED
#define STRUCT_MONOP_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define TAILLE_NOM 50
#define TAILLE_PLATEAU 32

typedef struct t_case //case(ou cartes) du plateau
{
    int position; //position de la case sur le plateau
    int valeur; //prix d'achat
    char nom_joueur[TAILLE_NOM]; //nom du propriétaire(NONE si ya pas)
    int nb_maison; //entre 0 et 3
    int nb_hotel; //si ya un hotel ou pas
    int val_maison; //prix d'une maison sur la case
    int val_hotel; //prix de l'hotel
    int groupe_cartes; //groupe à laquelle appartient la case
}Case;

typedef struct t_joueur //joueur du plateau (max 4)
{
    char nom[TAILLE_NOM];
    int position; //initialisé à 0, la case départ (modulo 32)
    int argent; //à initialiser avec le montant de base (argent sur le compte, c'est à dire argent utilisable)
    int capital; //c'est l'argent que le joueur a sur son compte plus la valeur des propriete, des maisons,etc (sert dns les parties rapides)
    Case proprietes[TAILLE_PLATEAU]; //propriétés détenue par le joueur (tableau de case)
    int prison; //booléen vérifiant si le joueur est en prison ou non (0 pas en prison, totu autre chiffre = en prison)
    int tour_prison; //nombre de tour en prison(max: 3)
    int carte_sortie_prison; //nombre de carte permettant au joueur de sortir de prison
}Joueur;

typedef struct t_banque
{
    int nb_maison_restante; //32 maisons max
    int nb_hotel_restante; //12 hotel max
}Banque;

#endif // STRUCT_MONOP_HEADER_H_INCLUDED
