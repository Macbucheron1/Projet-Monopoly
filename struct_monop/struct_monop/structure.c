#include "struct_monop_header.h"


//instanciation
t_joueur creation_joueur(void)
{
    t_joueur j;
    fflush(stdin);

    printf("Veuillez entrer le nom du joueur :\n");
    gets(j.nom);
    j.position=0;
    j.argent=1500;
    j.capital=1500;
    j.en_prison=false;
    j.tour_prison=0;
    j.carte_sortie_prison=0;

    return j;
}
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes)
{
    t_case c;
    fflush(stdin);

    c.position=position;
    c.valeur=valeur;
    c.val_maison=val_maison;
    c.val_hotel=val_hotel;
    c.groupe_cartes=groupe_cartes;

    c.nom_joueur[TAILLE_NOM]= "NONE";
    c.nb_maison = 0;
    c.nb_hotel = 0;

    return c;
}


t_banque creation_banque(void)
{
    t_banque b;
    fflush(stdin);

    b.nb_maison_restante=32;
    b.nb_hotel_restant=12;

    return b;
}

//affichage d'instance
void afficher_joueur(t_joueur j)
{
    printf("Voici le JOUEUR:\n");
    printf("nom:%s\nposition:%d\nargent:%d\ncapital:%d\npropriete:%d\netes-vous en prison?:%d\ncombien de tour en prison:%d\nnb de cartes sorites de prison:%d\n",j.nom,j.position,j.argent,j.capital,j.proprietes,j.en_prison,j.tour_prison,j.carte_sortie_prison);
    printf("\n"); //pour de la lisibilité
}

void afficher_case(t_case c)
{
    printf("Voici la CASE:\n");
    printf("position:%d\nprix d'achat:%d\nnom joueur la possedant:%s\nnombre de maison:%d\nya til un hotel:%d\nprix dachat d'une maison:%d\nprix d'achat d'un hotel:%d\nquel groupe de carte:%d\n",c.position,c.valeur,c.nom_joueur,c.nb_maison,c.nb_hotel,c.val_maison,c.val_hotel,c.groupe_cartes);
    printf("\n"); //pour de la lisibilité
}

void afficher_banque(t_banque b)
{
    printf("Voici la BANQUE:\n");
    printf("maisons restantes:%d\nhotels restant:%d\n",b.nb_maison_restante,b.nb_hotel_restant);
    printf("\n"); //pour de la lisibilité
}
