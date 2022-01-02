#include "chance_commu_header_v2.h"

//struct

//instanciation
t_joueur creation_joueur(int numero)
{
    t_joueur j;
    fflush(stdin);

    printf("Veuillez entrer le nom du joueur :\n");
    gets(j.nom);
    j.numero=numero;
    j.position=0;
    j.argent=1500;
    j.capital=1500;
    j.en_prison=false;
    j.tour_prison=0;
    j.carte_sortie_prison=0;

    j.en_faillite=false;

    return j;
}

//afichage

void afficher_joueur(t_joueur j)
{
    printf("Voici le JOUEUR:\n");
    printf("numero:%d\nnom:%s\nposition:%d\nargent:%d\ncapital:%d\npropriete:%d\netes-vous en prison?:%d\ncombien de tour en prison:%d\nnb de cartes sorites de prison:%d\nest-il en faillite ?:%d\n",j.numero,j.nom,j.position,j.argent,j.capital,j.proprietes,j.en_prison,j.tour_prison,j.carte_sortie_prison,j.en_faillite);
    printf("\n"); //pour de la lisibilité
}

//chance commu transac

void transaction(t_joueur tab_joueur[],int i,int montant)
{
    tab_joueur[i].argent+=montant;
    tab_joueur[i].capital+=montant;
    /* optionel
    printf("Joueur %d:",tab_joueur[i].numero);
    if(montant>0)
    {
        printf("Vous avez ete credite de %d euros\n\n",montant);
    }
    if(montant<0)
    {
        printf("Vous avez ete debite de %d euros\n\n",montant);
    }*/
}


void tirer_corruption(t_joueur tab_joueur[],int i, char* liste_corruption)
{
    srand( time( NULL ) );
    int carteCorTire = rand() % 16;

    printf("Vous tirez une carte corruption:\n");

    switch(carteCorTire)
    {
    case 0:
        afficher_liste(liste_corruption,0);
        tab_joueur[i].carte_sortie_prison+=1;
        break;
    case 1:
        afficher_liste(liste_corruption,1);
        int deplacement_case=18; //la case ou l'on veut se deplacer (handball)
        int position_joueur=tab_joueur[i].position; //position du joueur lors de lappel de la fonction
        if (position_joueur>deplacement_case)  //si on est deja apres la case ou se deplacer ca vut dire quon passe par la case depart
        {
            transaction(tab_joueur,i,200);
        }
        aller_a(deplacement_case,tab_joueur, i);
        break;
    case 2:
        afficher_liste(liste_corruption,2);
        aller_a(31,tab_joueur, i); //derniere case du plateau donc pas 200e
        break;
    case 3:
        afficher_liste(liste_corruption,3); // pas faite encore (payer en fonction de maisons et hotel)
        int nombre_maisons=nb_maisons_joueur(tab_joueur,i);
        int nombre_hotels=nb_hotels_joueur(tab_joueur,i);
        int total_prix_maison=25*nombre_maisons;
        int total_prix_hotel=100*nombre_hotels;
        int total_prix=total_prix_hotel+total_prix_maison;
        if (total_prix==0)
        {
            printf("Vous ne payer rien car vous n'avez aucune medaille ni aucun titre\n");
        }
        else
            {
                printf("Vous devez donc payer en tout %d euros, dont %d euros pour vos %d medaille(s) et %d euros pour vos %d titre(s)\n",total_prix,total_prix_maison,nombre_maisons,total_prix_hotel,nombre_hotels);
            }

        break;
    case 4:
        afficher_liste(liste_corruption,4);
        transaction(tab_joueur,i,100);
        break;
    case 5:
        afficher_liste(liste_corruption,5);
        transaction(tab_joueur,i,150);
        break;
    case 6:
        afficher_liste(liste_corruption,6);
        int deplacement_case2=9; //la case ou l'on veut se deplacer(tennis)
        if (tab_joueur[i].position>deplacement_case2) //si on est deja apres la case ou se deplacer ca vut dire quon passe par la case depart
        {
            transaction(tab_joueur,i,200);
        }
        aller_a(deplacement_case2,tab_joueur, i); //definir la postion qu'on veut
        break;
    case 7:
        afficher_liste(liste_corruption,7);
        int deplacement_case3=11; //la case ou l'on veut se deplacer (skate)
        if (tab_joueur[i].position>deplacement_case3) //si on est deja apres la case ou se deplacer ca vut dire quon passe par la case depart
        {
            transaction(tab_joueur,i,200);
        }
        aller_a(deplacement_case3,tab_joueur, i); //definir la postion qu'on veut
        break;
    case 8:
        afficher_liste(liste_corruption,8); //pas faite encore (payer en fonction de maisons et hotel)
        int nombre_maisons2=nb_maisons_joueur(tab_joueur,i);
        int nombre_hotels2=nb_hotels_joueur(tab_joueur,i);
        int total_prix_maison2=40*nombre_maisons;
        int total_prix_hotel2=115*nombre_hotels;
        int total_prix2=total_prix_hotel2+total_prix_maison2;
        if (total_prix2==0)
        {
            printf("Vous ne payer rien car vous n'avez aucune medailles ni aucun titre\n");
        }
        else
            {
                printf("Vous devez donc payer en tout %d euros, dont %d euros pour vos %d medaille(s) et %d euros pour vos %d titre(s)\n",total_prix2,total_prix_maison2,nombre_maisons2,total_prix_hotel2,nombre_hotels2);
            }
        break;
    case 9:
        afficher_liste(liste_corruption,9);
        transaction(tab_joueur,i,50);
        break;
    case 10:
        afficher_liste(liste_corruption,10);
        transaction(tab_joueur,i,200);
        aller_a(0,tab_joueur, i); //definir la postion qu'on veut (depart ici)
        break;
    case 11:
        afficher_liste(liste_corruption,11);
        transaction(tab_joueur,i,-150);
        break;
    case 12:
        afficher_liste(liste_corruption,12);
        int position = tab_joueur[i].position;
        aller_a(position-3,tab_joueur, i); //ne pas sen faire des positions negatives car corruption tjrs >3
        break;
    case 13:
        afficher_liste(liste_corruption,13);
        transaction(tab_joueur,i,-15);
        break;
    case 14:
        afficher_liste(liste_corruption,14);
        entrer_prison(tab_joueur,i);
        break;
    case 15:
        afficher_liste(liste_corruption,15);
        transaction(tab_joueur,i,-20);
        break;
    }
}

void tirer_comite(t_joueur tab_joueur[],int i,char* liste_commite,char* liste_corruption)
{
    srand( time( NULL ) );
    int carteComTire = rand() % 16;

    printf("Vous tirez une carte commite olympique:\n");
    
    char choix[10]; //on l'utilisera dans le case 1

    //numero des autres joueurs
    int B;
    int C;
    int D;

    if (i==0)
    {
        B=1;
        C=2;
        D=3;
    }
    else if (i==1)
    {
        B=2;
        C=3;
        D=0;
    }
    else if (i==2)
    {
        B=3;
        C=0;
        D=1;
    }
    else
    {
        B=0;
        C=1;
        D=3;
    }

    switch(carteComTire)
    {
    case 0:
        afficher_liste(liste_commite,0);
        tab_joueur[i].carte_sortie_prison+=1;
        break;
    case 1:
        do
        {
            afficher_liste(liste_commite,1);
            gets(choix);
            if (choix[0] == 49)
            {
                transaction(tab_joueur,i,-10);
            }
            else if (choix[0] == 50)
            {
                tirer_corruption(tab_joueur,i,liste_corruption);
            }
        }
        while ((choix[0] != 49) && (choix[0] != 50) || (strlen(choix) > 1)); // 49 = 1 en code ascii
        break;
    case 2:
        afficher_liste(liste_commite,2);
        transaction(tab_joueur,i,50);
        break;
    case 3:
        afficher_liste(liste_commite,3); //on verifie que les autres joueur ne sont pas en faillite (quils jouent trs)
        if(tab_joueur[B].en_faillite==false)
        {
            transaction(tab_joueur,B,-10);
            transaction(tab_joueur,i,10);
        }
        if(tab_joueur[C].en_faillite==false)
        {
            transaction(tab_joueur,C,-10);
            transaction(tab_joueur,i,10);
        }
        if(tab_joueur[D].en_faillite==false)
        {
            transaction(tab_joueur,D,-10);
            transaction(tab_joueur,i,10);
        }
        break;
    case 4:
        afficher_liste(liste_commite,4);
        transaction(tab_joueur,i,200);
        break;
    case 5:
        afficher_liste(liste_commite,5);
        transaction(tab_joueur,i,-100);
        break;
    case 6:
        afficher_liste(liste_commite,6);
        transaction(tab_joueur,i,20);
        break;
    case 7:
        afficher_liste(liste_commite,7);
        transaction(tab_joueur,i,100);
        break;
    case 8:
        afficher_liste(liste_commite,8);
        aller_a(1,tab_joueur, i); //definir la postion qu'on veut (ici premiere case)
        break;
    case 9:
        afficher_liste(liste_commite,9);
        transaction(tab_joueur,i,25);
        break;
    case 10:
        afficher_liste(liste_commite,10);
        transaction(tab_joueur,i,200);
        aller_a(0,tab_joueur, i); //definir la postion qu'on veut (depart ici)
        break;
    case 11:
        afficher_liste(liste_commite,11);
        transaction(tab_joueur,i,-50);
        break;
    case 12:
        afficher_liste(liste_commite,12);
        transaction(tab_joueur,i,10);
        break;
    case 13:
        afficher_liste(liste_commite,13);
        transaction(tab_joueur,i,-50);
        break;
    case 14:
        afficher_liste(liste_commite,14);
        entrer_prison(tab_joueur,i);
        break;
    case 15:
        afficher_liste(liste_commite,15);
        transaction(tab_joueur,i,100);
        break;
    }
}

bool victoire(t_joueur tab_joueur[])
{
    if(tab_joueur[0].en_faillite==true && tab_joueur[1].en_faillite==true && tab_joueur[2].en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",tab_joueur[3].numero);
        return true;
    }
    else if(tab_joueur[1].en_faillite==true && tab_joueur[2].en_faillite==true && tab_joueur[3].en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",tab_joueur[0].numero);
        return true;
    }
    else if(tab_joueur[2].en_faillite==true && tab_joueur[3].en_faillite==true && tab_joueur[0].en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",tab_joueur[1].numero);
        return true;
    }
    else if(tab_joueur[3].en_faillite==true && tab_joueur[0].en_faillite==true && tab_joueur[1].en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",tab_joueur[2].numero);
        return true;
    }
    else
    {
        return false;
    }
}

//v2

// fonction creation tableau joueur
void creation_tab_joueur(t_joueur tab_joueur[])
{
    char choix[10];
    do
    {
        printf("Combien de joueurs vont jouer ?\nIl doit y avoir minimum 2 joueurs et maximum 4 joueurs : ");
        fflush(stdin);
        gets(choix);
    }
    while ((choix[0] != 50) && (choix[0] != 51) && (choix[0] != 52) || (strlen(choix) > 1));   // 48 = 0 en code ascii
    if (choix[0] == 50)
    {
        tab_joueur[0] = creation_joueur(1);
        tab_joueur[1] = creation_joueur(2);

        t_joueur j3;
        strcpy(j3.nom, "j3");
        j3.numero = 3;
        j3.position=0;
        j3.argent=1500;
        j3.capital=1500;
        j3.en_prison=false;
        j3.tour_prison=0;
        j3.carte_sortie_prison=0;
        j3.en_faillite = true;
        tab_joueur[2] = j3;

        t_joueur j4;
        strcpy(j4.nom, "j4");
        j4.numero = 4;
        j4.position=0;
        j4.argent=1500;
        j4.capital=1500;
        j4.en_prison=false;
        j4.tour_prison=0;
        j4.carte_sortie_prison=0;
        j4.en_faillite = true;
        tab_joueur[3] = j4;



    }
    if (choix[0] == 51)
    {
        tab_joueur[0] = creation_joueur(1);
        tab_joueur[1] = creation_joueur(2);
        tab_joueur[2] = creation_joueur(3);

        t_joueur j4;
        strcpy(j4.nom, "j4");
        j4.numero = 4;
        j4.position=0;
        j4.argent=1500;
        j4.capital=1500;
        j4.en_prison=false;
        j4.tour_prison=0;
        j4.carte_sortie_prison=0;
        j4.en_faillite = true;
        tab_joueur[3] = j4;

    }
    if (choix[0] == 52)
    {
        tab_joueur[0] = creation_joueur(1);
        tab_joueur[1] = creation_joueur(2);
        tab_joueur[2] = creation_joueur(3);
        tab_joueur[3] = creation_joueur(4);
    }

}

void entrer_prison(t_joueur tab_joueur[], int i)
{
    /*La procédure envoie le joueur en prison. Elle change letat prison du joueur et appelle la fonction aller à pour lenvoyer en prison
      Prend en paramètre le joueur
      Ne renvoie rien
    */
    tab_joueur[i].en_prison = 1;
    aller_a(8,tab_joueur, i);

}

void aller_a(int indice_case, t_joueur tab_joueur[], int i)
{
    /* La procédure actualise la position du joueur pour le mettre à la case voulu
       Prend en paramètre lindice de la case et le joueur qui se déplace,
       Ne renvoie rien
    */

    tab_joueur[i].position = indice_case;
}

void afficher_liste(char* liste[],int i)
{
    int iterateur=0;
    while(liste[i][iterateur] != '\0')   //\0 correspond à la fin de chaine
    {
        printf("%c",liste[i][iterateur]);
        iterateur++;
    }
}

int nb_maisons_joueur(t_joueur tab_joueur[],int i)
{
    int nb_maisons=0;
    for (int j=0; j<TAILLE_PLATEAU; j++)
    {
        nb_maisons=tab_joueur[i].proprietes[j].nb_maison;
    }
    if (nb_maisons>32)//c'est que le joueur n'a aucune maison
    {
        nb_maisons=0;
    }
    return nb_maisons;
}

int nb_hotels_joueur(t_joueur tab_joueur[],int i)
{
    int nb_hotels=0;
    for (int j=0; j<TAILLE_PLATEAU; j++)
    {
        nb_hotels=tab_joueur[i].proprietes[j].nb_hotel;
    }
    if (nb_hotels>12)//c'est que le joueur n'a aucun hotel
    {
        nb_hotels=0;
    }
    return nb_hotels;
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

    c.nom_joueur[TAILLE_NOM]= NULL;
    c.nb_maison = 0;
    c.nb_hotel = 0;

    return c;
}
