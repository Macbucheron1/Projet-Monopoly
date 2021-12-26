#include "sous_prog.h"

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
t_case creation_case(int position, int valeur, int val_maison, int val_hotel, int groupe_cartes)
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

//anciennes fonction de lancé de dé fait par maxime
lance_de1()
//lance un dé entre 1 et 6
//renvoie la valeur du dé
{
    int de1;
    de1 = (rand()%6)+1;
    printf("de1 = %d\n",de1);
    return(de1);
}

lance_de2()
//lance un dé entre 1 et 6
//renvoie la valeur du dé
{
    int de2;
    de2 = (rand()%6)+1;
    printf("de2 = %d\n",de2);
    return(de2);
}

double_de(de1, de2)
//regarde si les 2 dé ont la meme valeur
//prend la valeur des 2 dé en parametre
//renvoie true ou false
{
    if(de1 == de2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

triple(bool sortie, t_joueur joueur1)
//regarde si on fait 3 double de suite
//prend la fonction double et la structure joueur en parametre
//renvoie si le joueur est en prison ou pas
{
    int incrementation = 0,de1,de2;
    while(sortie == true)
    {
        incrementation += 1;
        if (incrementation == 3)
        {
            printf("aller en prison\n");
            return joueur1.en_prison = 1;
            break;
        }
        de1 = lance_de1();
        de2 = lance_de2();
        sortie = double_de(de1,de2);
    }
    return joueur1.en_prison = 0;

}
