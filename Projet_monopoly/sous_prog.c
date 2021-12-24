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
t_case creation_case(int position)
{
    t_case c;
    fflush(stdin);
    //position[20] = [1,2,4,6,7,9,10,12,13,15,17,18,22,23,25,26,28,29,31];
    int valeur[20];// = [60,60,100,100,120,140,140,160,180,200,220,220,260,280,300,300,320,350,400];
    valeur[0] = 60;
    for(int i = 1;i<19;i++)
    {
        valeur[i]=valeur[i-1]+10;
        //printf("%d\n", valeur[i]);
    }
    int val_maison[20];// = [50,50,50,50,50,100,100,100,100,100,150,150,150,150,200,200,200,200,200];
    for(int i =0; i<19; i++)
    {
        val_maison[i] = 50;
        if(i >4 && i<10)
        {
            val_maison[i] = 100;
        }
        else if(i> 9 && i<14)
        {
            val_maison[i] = 150;
        }
        else if(i > 13)
        {
           val_maison[i] = 200;
        }
        //printf("%d\n", val_maison[i]);
    }
    int val_hotel[20];// = [60,60,60,60,60,110,110,110,110,110,165,165,165,165,220,220,220,220,220];
    for(int i =0; i<19; i++)
    {
        val_hotel[i] = 60;
        if(i >4 && i<10)
        {
            val_hotel[i] = 110;
        }
        else if(i> 9 && i<14)
        {
            val_hotel[i] = 165;
        }
        else if(i > 13)
        {
           val_hotel[i] = 220;
        }
        //printf("%d\n", val_hotel[i]);
    }
    int groupe_cartes[20];// = [1,1,2,2,2,3,3,3,4,4,5,5,6,6,7,7,7,8,8]


    c.position=position;
    c.valeur=valeur[position-1];
    c.val_maison=val_maison[position-1];
    c.val_hotel=val_hotel[position-1];
    c.groupe_cartes=groupe_cartes[position-1];


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

lance_de1()
{
    int de1;
    de1 = (rand()%6)+1;
    printf("de1 = %d\n",de1);
    return(de1);
}

lance_de2()
{
    int de2;
    de2 = (rand()%6)+1;
    printf("de2 = %d\n",de2);
    return(de2);
}

double_de(de1, de2)
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
