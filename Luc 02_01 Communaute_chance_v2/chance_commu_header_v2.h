#ifndef CHANCE_COMMU_HEADER_V2_H_INCLUDED
#define CHANCE_COMMU_HEADER_V2_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include<windows.h>

#define bool unsigned int
#define true 1
#define false 0

#define TAILLE_NOM 50
#define TAILLE_PLATEAU 32
#define TAILLE_LISTE 16


//debut header struct

typedef struct //case(ou cartes) du plateau
{
    int position; //position de la case sur le plateau
    int valeur; //prix d'achat
    char nom_joueur[TAILLE_NOM]; //nom du propri�taire(NULL si ya pas)
    int nb_maison; //entre 0 et 3
    int nb_hotel; //si ya un hotel ou pas
    int val_maison; //prix d'une maison sur la case
    int val_hotel; //prix de l'hotel
    int groupe_cartes; //groupe � laquelle appartient la case
}t_case;

typedef struct //joueur du plateau (max 4)
{
    int numero; //joueur 1 2 3 ou 4 ?
    char nom[TAILLE_NOM];
    int position; //initialis� � 0, la case d�part (modulo 32)
    int argent; //� initialiser avec le montant de base (argent sur le compte, c'est � dire argent utilisable)
    int capital; //c'est l'argent que le joueur a sur son compte plus la valeur des propriete, des maisons,etc (sert dns les parties rapides)
    t_case proprietes[TAILLE_PLATEAU]; //propri�t�s d�tenue par le joueur --> position de la case (tableau de case)
    bool en_prison; //bool�en v�rifiant si le joueur est en prison ou non (0 pas en prison, totu autre chiffre = en prison)
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
t_joueur creation_joueur(int num); // permet de modifier une instance de structure joueur
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes); //permet de modifier une instance de strucutre de case
t_banque creation_banque(void);

//affichage d'instance
void afficher_joueur(t_joueur);
void afficher_case(t_case);
void afficher_banque(t_banque);

//fin header struct

//debut header chance commu et transactions

void transaction(t_joueur tab_joueur[],int i,int montant); //IN: un joueur e tun montant(positif ou negatif), sert a faciliter les transactions

char* corruption[TAILLE_LISTE]; //cartes chance
char* comite_olympique[TAILLE_LISTE]; //cartes commu

void tirer_corruption(t_joueur tab_joueur[],int i, char* liste_corruption); //tirez une carte chance
void tirer_comite(t_joueur tab_joueur[],int i,char* liste_commite,char* liste_corruption); //tirez une carte communaut� (celui qui tire la carte est le j)

bool victoire(t_joueur tab_j[]);

//v2

void creation_tab_joueur(t_joueur tab_joueur[]); // Permet de cr�er le tableau des joueurs
void entrer_prison(t_joueur tab_joueur[], int i); // Permet de faire entrer le joueur en prison
void aller_a(int indice_case, t_joueur tab_joueur[], int i);

void afficher_liste(char* liste[],int i);

//je sais pas vrmnt si ca marche (en principe cest bon) a verifier lors de test quand on aura tout le code
int nb_maisons_joueur(t_joueur tab_joueur[],int i);
int nb_hotels_joueur(t_joueur tab_joueur[],int i);

#endif // CHANCE_COMMU_HEADER_V2_H_INCLUDED
