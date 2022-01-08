#ifndef FAILLITE_HEADER_V2_H_INCLUDED
#define FAILLITE_HEADER_V2_H_INCLUDED

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
    char nom[25]; // Nom de la case
    int position; //position de la case sur le plateau
    int valeur; //prix d'achat
    int num_joueur; //numéro du propriétaire(NULL si ya pas)
    int nb_maison; //entre 0 et 3
    int nb_hotel; //si ya un hotel ou pas
    int val_maison; //prix d'une maison sur la case
    int val_hotel; //prix de l'hotel
    int groupe_cartes; //groupe à laquelle appartient la case
    int couleur_fond; // Couleur de fond de la case
    int couleur_texte; // Couleur de texte de la case
    bool hypoteque; // booleen qui dit si la case est hypoteque
    int val_hypotheque; // donne la valeur de l'hypotheque
    int base_loyer; // donne le loyer sans maison
    int loyer_1_maison;
    int loyer_2_maison;
    int loyer_3_maison;
    int loyer_4_maison;
    int loyer_1_hotel;

}t_case;

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
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes, char* nom, int couleur_fond, int couleur_texte, int valeur_hypotheque, int base_loyer, int loyer_1_maison, int loyer_2_maison, int loyer_3_maison, int loyer_4_maison, int loyer_1_hotel);  //permet de créer une instance de strucutre de case
t_banque creation_banque(void);

//affichage d'instance
void afficher_joueur(t_joueur);
void afficher_case(t_case);
void afficher_banque(t_banque);

//fin header struct

//debut header transactions

void transaction(t_joueur tab_joueur[],int i,int montant); //IN: un joueur et un montant(positif ou negatif), sert a faciliter les transactions

//fin transaction

//v2
void afficher_case_jeu(t_case c);

int update_propriete(t_joueur tab_joueur[],int i, t_case plateau[]);

void creation_tab_joueur(t_joueur tab_joueur[]); // Permet de créer le tableau des joueurs
void hypotheque_faillite(t_joueur tab_joueur[],int i, t_case plateau[], t_banque* banque); // Permet d'hypotéquer une propriété
void creation_plateau(t_case* plateau); // Permet de créer le plateau

void propriete_a_joueur(t_joueur tab_joueur[],int i, t_case plateau[],int j);//j=position carte, i=num joueur, permet d'ajouter une propriete dans le tab propriete d'un joueur (rajoute aussi +1 a nb_propriete)
void enlever_propriete_joueur(t_joueur tab_joueur[],int i,t_case plateau[],int j);//j=position carte, i=num joueur,permet de supprimer une propriete dans le tab propriete d'un joueur (enleve aussi -1 a nb_propriete)

void afficher_propriete_joueur(t_joueur tab_joueur[],int i, t_case plateau[]);// montre les propriete d'un joueur (je sais pas si ten as besoin c'etait surtout pour moi pour mes verification)

void en_faillite(t_joueur tab_joueur[],int i,int montant,t_banque* p_banque,int proprietaire,t_case plateau[]); //on fait appel à la fonction lors de n'importe quel paiement (à la banque ou à un joueur), si proprietaire = 0 c'est la banque

#endif // FAILLITE_HEADER_V2_H_INCLUDED
