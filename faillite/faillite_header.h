#ifndef FAILLITE_HEADER_H_INCLUDED
#define FAILLITE_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define bool unsigned int
#define true 1
#define false 0

#define TAILLE_NOM 50
#define TAILLE_PLATEAU 32

//debut header struct

typedef struct //case(ou cartes) du plateau
{
    int position; //position de la case sur le plateau
    int valeur; //prix d'achat
    char nom_joueur[TAILLE_NOM]; //nom du propriétaire(NONE si ya pas)
    int nb_maison; //entre 0 et 3
    int nb_hotel; //si ya un hotel ou pas
    int val_maison; //prix d'une maison sur la case
    int val_hotel; //prix de l'hotel
    int groupe_cartes; //groupe à laquelle appartient la case
}t_case;

typedef struct //joueur du plateau (max 4)
{
    char nom[TAILLE_NOM];
    int position; //initialisé à 0, la case départ (modulo 32)
    int argent; //à initialiser avec le montant de base (argent sur le compte, c'est à dire argent utilisable)
    int capital; //c'est l'argent que le joueur a sur son compte plus la valeur des propriete, des maisons,etc (sert dns les parties rapides)
    int proprietes[TAILLE_PLATEAU]; //propriétés détenue par le joueur --> position de la case (tableau de case)
    bool en_prison; //booléen vérifiant si le joueur est en prison ou non (0 pas en prison, totu autre chiffre = en prison)
    int tour_prison; //nombre de tour en prison(max: 3)
    int carte_sortie_prison; //nombre de carte permettant au joueur de sortir de prison
    bool en_faillite; //nous dit si le joueur est en faillite ou pas (s'il l'est ne pas afficher son tour sur le menu et son pion sur le plateua)
}t_joueur;

typedef struct
{
    int nb_maison_restante; //32 maisons max
    int nb_hotel_restant; //12 hotel max
}t_banque;

//instanciation
t_joueur creation_joueur(void); // permet de modifier une instance de structure joueur
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes); //permet de modifier une instance de strucutre de case
t_banque creation_banque(void);

//affichage d'instance
void afficher_joueur(t_joueur);
void afficher_case(t_case);
void afficher_banque(t_banque);

//fin header struct

//debut header faillite

void en_faillite(t_joueur *j); //permet de mettre en faillite un joueur en verifiant une condition


#endif // FAILLITE_HEADER_H_INCLUDED
