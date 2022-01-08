#ifndef NATHAN_H_H_INCLUDED
#define NATHAN_H_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include<windows.h>

#define TAILLE_NOM 16
#define TAILLE_PLATEAU 32
#define TAILLE_LISTE 16

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
    char nom[TAILLE_NOM];
    int numero; //Numéro du joueur
    int position; //initialisé à 0, la case départ (modulo 32)
    int argent; //à initialiser avec le montant de base (argent sur le compte, c'est à dire argent utilisable)
    t_case proprietes[TAILLE_PLATEAU]; //propriétés détenue par le joueur (tableau de case)
    bool en_prison; //booléen vérifiant si le joueur est en prison ou non (0 pas en prison, totu autre chiffre = en prison)
    int tour_prison; //nombre de tour en prison(max: 3)
    int carte_sortie_prison; //nombre de carte permettant au joueur de sortir de prison
    bool en_faillite; //nous dit si le joueur est en faillite ou pas (s'il l'est ne pas afficher son tour sur le menu et son pion sur le plateau)
    int nb_propriete; //Nombre de propriété
}t_joueur;

typedef struct // Structure de la banque
{
    int nb_maison_restante; //32 maisons max
    int nb_hotel_restant; //12 hotel max
}t_banque;

// Fonction de dé
void lance_de(int* de); // Lance les deux dés
bool double_de(int* de); // Vérifie si le joueur a fait un double

//Fonction de deplacement de joueur
void deplacement(int* liste_de, t_joueur tab_joueur[], int i); // Permet de faire avancer le joueur
void aller_a(int indice_case, t_joueur tab_joueur[],int i); // Permet de changer le joueur de case

// Fonction pour prison
void entrer_prison(t_joueur tab_joueur[], int i); // Permet de faire entrer le joueur en prison
bool sortie_prison(int* liste_de, t_joueur tab_joueur[], int i, t_case plateau[], t_banque* p_banque); // Permet de faire sortir le joueur de prison

//instanciation
t_joueur creation_joueur(int numero); // permet de créer une instance de structure joueur
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes, char* nom, int couleur_fond, int couleur_texte, int valeur_hypotheque, int base_loyer, int loyer_1_maison, int loyer_2_maison, int loyer_3_maison, int loyer_4_maison, int loyer_1_hotel)
;  //permet de créer une instance de strucutre de case
t_banque creation_banque(void); // Permet de créer une instance de banque
void creation_plateau(t_case* plateau); // Permet de créer le plateau
void creation_tab_joueur(t_joueur tab_joueur[]); // Permet de créer le tableau des joueurs

//affichage d'instance
void afficher_joueur(t_joueur); // Permet d'afficher une instance de joueur
void afficher_case(t_case); // Permet d'afficher une instance de case
void afficher_banque(t_banque); // Permet d'afficher une instance de banque

//Fonction pour faillite
void en_faillite(t_joueur tab_joueur[],int i,int montant,t_banque* p_banque,int proprietaire,t_case plateau[]); // Met le joueur en faillite si necessaire
void hypotheque_faillite(t_joueur tab_joueur[],int i, t_case plateau[], t_banque* p_banque); // Permet de mettre une propriete en faillite dans le cadre de la fonction faillite
void enlever_propriete_joueur(t_joueur tab_joueur[],int i,t_case plateau[],int j); //
void propriete_a_joueur(t_joueur tab_joueur[],int i, t_case plateau[],int j);
void propriete_a_joueur(t_joueur tab_joueur[],int i, t_case plateau[],int j);

// Fonction pour faire un tour
void tour(t_joueur tab_joueur[], t_case plateau[], t_banque* p_banque, char* liste_corruption[], char* liste_comite[]); // Fais faire un tour à un joueur
bool acheter_maison_hotel(t_joueur tab_joueur[], int i, t_case plateau[], t_banque* banque); // Achat de maison et d'hotel
bool loyer(t_joueur tab_joueur[], int i, t_case plateau[], t_banque* p_banque); // Permet de faire payer le loyer
bool hypotheque(t_joueur tab_joueur[],int i, t_case plateau[], t_banque* banque); // Permet d'hypotéquer une propriété
void tirer_corruption(t_joueur tab_joueur[],int i, char* liste_corruption); // Permet de tirer une carte corruption
bool achat(t_joueur tab_joueur[],t_case plateau[],int i); // Permet d'acheter une propriété
void impot(t_joueur tab_joueur[],t_case plateau[],int i); // Impose le joueur si il est sur la case impot
bool salaire(t_joueur tab_joueur[],int de[2],int i); // Fait avancer le joueur et lui donne 200 dollars si il passe sur la case depart
int victoire(t_joueur tab_joueur[]); // Permet de verifier si un joueur à gagner
void tirer_comite(t_joueur tab_joueur[],int i,char* liste_commite,char* liste_corruption); // Permet de tirer une carte comite olympique
void tirer_corruption(t_joueur tab_joueur[],int i, char* liste_corruption); // Permet de tirer une carte corruption
bool Vendre_bien(t_joueur tab_joueur[], t_case plateau[], t_banque* banque, int i);


//fonction d'affichage
void afficher_plateau(t_case plateau[], t_joueur tab_joueur[]); //affiche le plateau
void gotoligcol( int lig, int col ); // permet de se deplacer sur la console
void afficher_valeur_case(int indice, t_case plateau[]);
void afficher_nom_proprietaire(int indice, t_case plateau[], t_joueur tab_joueur[], int num_joueur);
void creation_sous_case1(t_case plateau[], t_joueur tab_joueur[], int i);
void creation_sous_case2(t_case plateau[], t_joueur tab_joueur[], int i);
void creation_sous_case3(t_case plateau[], t_joueur tab_joueur[], int i);
void menu(t_joueur tab_joueur[], t_case plateau[], t_banque* p_banque, char* liste_corruption[], char* liste_comite[]);
void afficher_milieu_plateau(t_case plateau[], t_joueur tab_joueur[],int i, int de[]);

// fonction d'affichage dans le jeu
void afficher_liste(char* liste[],int i);
void afficher_case_jeu(t_case cases);
void clear_bas();

// fonction utilitaire
int nb_hotels_joueur(t_joueur tab_joueur[],int i);
int nb_maisons_joueur(t_joueur tab_joueur[],int i);
int Longueur(int Valeur);
int update_propriete(t_joueur tab_joueur[],int i, t_case plateau[]);
int nb_gare_joueur(t_case plateau[], int i); // Calcul le nombre de gare d'un joueur


#endif // NATHAN_H_H_INCLUDED
