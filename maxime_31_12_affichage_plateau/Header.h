#ifndef NATHAN_H_H_INCLUDED
#define NATHAN_H_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include<windows.h>

#define TAILLE_NOM 50
#define TAILLE_PLATEAU 32

typedef struct //case(ou cartes) du plateau
{
    char nom[25]; // Nom de la case
    int position; //position de la case sur le plateau
    int valeur; //prix d'achat
    int num_joueur; //num�ro du propri�taire(NULL si ya pas)
    int nb_maison; //entre 0 et 3
    int nb_hotel; //si ya un hotel ou pas
    int val_maison; //prix d'une maison sur la case
    int val_hotel; //prix de l'hotel
    int groupe_cartes; //groupe � laquelle appartient la case
    int couleur_fond; // Couleur de fond de la case
    int couleur_texte; // Couleur de texte de la case
}t_case;

typedef struct //joueur du plateau (max 4)
{
    char nom[TAILLE_NOM];
    int numero; //Num�ro du joueur
    int position; //initialis� � 0, la case d�part (modulo 32)
    int argent; //� initialiser avec le montant de base (argent sur le compte, c'est � dire argent utilisable)
    int capital; //c'est l'argent que le joueur a sur son compte plus la valeur des propriete, des maisons,etc (sert dns les parties rapides)
    t_case proprietes[TAILLE_PLATEAU]; //propri�t�s d�tenue par le joueur (tableau de case)
    bool en_prison; //bool�en v�rifiant si le joueur est en prison ou non (0 pas en prison, totu autre chiffre = en prison)
    int tour_prison; //nombre de tour en prison(max: 3)
    int carte_sortie_prison; //nombre de carte permettant au joueur de sortir de prison
    bool en_faillite; //nous dit si le joueur est en faillite ou pas (s'il l'est ne pas afficher son tour sur le menu et son pion sur le plateau)
}t_joueur;

typedef struct // Structure de la banque
{
    int nb_maison_restante; //32 maisons max
    int nb_hotel_restant; //12 hotel max
}t_banque;

// Fonction de d�
void lance_de(int* de); // Lance les deux d�s
bool double_de(int* de); // V�rifie si le joueur a fait un double

//Fonction de deplacement de joueur
void deplacement(int* liste_de, t_joueur tab_joueur[], int i); // Permet de faire avancer le joueur
void aller_a(int indice_case, t_joueur tab_joueur[],int i); // Permet de changer le joueur de case

// Fonction pour prison
void entrer_prison(t_joueur tab_joueur[], int i); // Permet de faire entrer le joueur en prison
bool sortie_prison(int* liste_de, t_joueur tab_joueur[], int i); // Permet de faire sortir le joueur de prison

//instanciation
t_joueur creation_joueur(int numero); // permet de cr�er une instance de structure joueur
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes, char* nom, int couleur_fond, int couleur_texte);  //permet de cr�er une instance de strucutre de case
t_banque creation_banque(void); // Permet de cr�er une instance de banque
void creation_plateau(t_case* plateau); // Permet de cr�er le plateau
void creation_tab_joueur(t_joueur tab_joueur[]); // Permet de cr�er le tableau des joueurs

//affichage d'instance
void afficher_joueur(t_joueur); // Permet d'afficher une instance de joueur
void afficher_case(t_case); // Permet d'afficher une instance de case
void afficher_banque(t_banque); // Permet d'afficher une instance de banque

//Fonction pour faillite
void en_faillite(t_joueur tab_joueur[], int i); // Met le joueur en faillite si necessaire

// Fonction pour faire un tour
void tour(t_joueur tab_joueur[], t_case plateau[], t_banque* p_banque); // Fais faire un tour � un joueur
bool acheter_maison_hotel(t_joueur tab_joueur[], int i, t_case plateau[], t_banque* banque); // Achat de maison et d'hotel
void loyer(t_joueur tab_joueur[], int i, t_case cases); // Permet de faire payer le loyer

void gotoligcol( int lig, int col );
void creation_sous_case(t_case plateau[], t_joueur tab_joueur[], int k_petit, int k_grand);
void creation_sous_case1(t_case plateau[], t_joueur tab_joueur[], int i);
void creation_sous_case2(t_case plateau[], t_joueur tab_joueur[], int i);
void creation_sous_case3(t_case plateau[], t_joueur tab_joueur[], int i);

// Fonction d'affichage
void afficher_plateau(t_case plateau[], t_joueur tab_joueur[]); //affiche le plateau

#endif // NATHAN_H_H_INCLUDED
