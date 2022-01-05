#ifndef CHANCE_COMMU_HEADER_V3_H_INCLUDED
#define CHANCE_COMMU_HEADER_V3_H_INCLUDED

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

//instanciation
t_joueur creation_joueur(int num)
{
    t_joueur j;
    fflush(stdin);
    printf("Veuillez entrer le nom du joueur :\n");
    gets(j.nom);
    j.numero=num;
    j.position=0;
    j.argent=1500;
    j.capital=1500;
    j.en_prison=false;
    j.tour_prison=0;
    j.carte_sortie_prison=0;
    j.nb_propriete=0; //NOUVEAU

    j.en_faillite=false;

    return j;
}

typedef struct //joueur du plateau (max 4)
{
    int numero; //joueur 1 2 3 ou 4 ?
    char nom[TAILLE_NOM];
    int position; //initialisé à 0, la case départ (modulo 32)
    int argent; //à initialiser avec le montant de base (argent sur le compte, c'est à dire argent utilisable)
    int capital; //c'est l'argent que le joueur a sur son compte plus la valeur des propriete, des maisons,etc (sert dns les parties rapides)
    t_case proprietes[TAILLE_PLATEAU]; //propriétés détenue par le joueur --> position de la case (tableau de case)
    bool en_prison; //booléen vérifiant si le joueur est en prison ou non (0 pas en prison, totu autre chiffre = en prison)
    int tour_prison; //nombre de tour en prison(max: 3)
    int carte_sortie_prison; //nombre de carte permettant au joueur de sortir de prison
    bool en_faillite; //nous dit si le joueur est en faillite ou pas (s'il l'est ne pas afficher son tour sur le menu et son pion sur le plateua)

    int nb_propriete; //NOUVEAU
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
void tirer_comite(t_joueur tab_joueur[],int i,char* liste_commite,char* liste_corruption); //tirez une carte communauté (celui qui tire la carte est le j)

bool victoire(t_joueur tab_j[]);

//v2

void creation_tab_joueur(t_joueur tab_joueur[]); // Permet de créer le tableau des joueurs
void entrer_prison(t_joueur tab_joueur[], int i); // Permet de faire entrer le joueur en prison
void aller_a(int indice_case, t_joueur tab_joueur[], int i);

void afficher_liste(char* liste[],int i);

//je sais pas vrmnt si ca marche (en principe cest bon) a verifier lors de test quand on aura tout le code
int nb_maisons_joueur(t_joueur tab_joueur[],int i);
int nb_hotels_joueur(t_joueur tab_joueur[],int i);

#endif // CHANCE_COMMU_HEADER_V3_H_INCLUDED
