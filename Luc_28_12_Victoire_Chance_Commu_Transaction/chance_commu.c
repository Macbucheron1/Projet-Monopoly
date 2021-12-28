#include "chance_commu_header.h"

//struct

//instanciation
t_joueur creation_joueur(int numero)
{
    t_joueur j;
    fflush(stdin);

    printf("Veuillez entrer le nom du joueur :\n");
    gets(j.nom);
    j.num_joueur=numero;
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
    printf("numero:%d\nnom:%s\nposition:%d\nargent:%d\ncapital:%d\npropriete:%d\netes-vous en prison?:%d\ncombien de tour en prison:%d\nnb de cartes sorites de prison:%d\nest-il en faillite ?:%d\n",j.num_joueur,j.nom,j.position,j.argent,j.capital,j.proprietes,j.en_prison,j.tour_prison,j.carte_sortie_prison,j.en_faillite);
    printf("\n"); //pour de la lisibilité
}

//chance commu transac

void transaction(t_joueur *j, int montant)
{
    j->argent+=montant;
    j->capital+=montant;
    printf("Joueur %d:",j->num_joueur);
    if(montant>0)
    {
        printf("Vous avez ete credite de %d euros\n",montant);
    }
    if(montant<0)
    {
        printf("Vous avez ete debite de %d euros\n",montant);
    }
}


void tirer_corruption(t_joueur *j, char* liste_corruption)
{
    srand( time( NULL ) );
    int carteCorTire = rand() % 16;

    printf("%d",carteCorTire);

    switch(carteCorTire)
    {
    case 0:
        printf("%s\n",liste_corruption[0]);
        j->carte_sortie_prison+=1;
        break;
    case 1:
        printf("%s\n",liste_corruption[1]);
        int deplacement_case=12; //la case ou l'on veut se deplacer
        int position_joueur=j->position; //position du joueur lors de lappel de la fonction
        if (position_joueur>deplacement_case)  //si on est deja apres la case ou se deplacer ca vut dire quon passe par la case depart
        {
            transaction(j,200);
        }
        j->position=deplacement_case; //definir la postion qu'on veut
        break;
    case 2:
        printf("%s\n",liste_corruption[2]);
        j->position=32; //derniere case du plateau
        break;
    case 3:
        printf("%s\n",liste_corruption[3]); // pas faite encore (payer en fonction de maisons et hotel)
        break;
    case 4:
        printf("%s\n",liste_corruption[4]);
        transaction(j,100);
        break;
    case 5:
        printf("%s\n",liste_corruption[5]);
        transaction(j,150);
        break;
    case 6:
        printf("%s\n",liste_corruption[6]);
        int deplacement_case2=26; //la case ou l'on veut se deplacer
        if (j->position>deplacement_case2) //si on est deja apres la case ou se deplacer ca vut dire quon passe par la case depart
        {
            transaction(j,200);
        }
        j->position=deplacement_case2; //definir la postion qu'on veut
        break;
    case 7:
        printf("%s\n",liste_corruption[7]);
        int deplacement_case3=20; //la case ou l'on veut se deplacer
        if (j->position>deplacement_case3) //si on est deja apres la case ou se deplacer ca vut dire quon passe par la case depart
        {
            transaction(j,200);
        }
        j->position=deplacement_case3; //definir la postion qu'on veut
        break;
    case 8:
        printf("%s\n",liste_corruption[8]); //pas faite encore (payer en fonction de maisons et hotel)
        break;
    case 9:
        printf("%s\n",liste_corruption[9]);
        transaction(j,50);
        break;
    case 10:
        printf("%s\n",liste_corruption[10]);
        int deplacement_depart=0; //la case depart
        transaction(j,200);
        j->position=deplacement_depart; //definir la postion qu'on veut
        break;
    case 11:
        printf("%s\n",liste_corruption[11]);
        transaction(j,-150);
        break;
    case 12:
        printf("%s\n",liste_corruption[12]);
        j->position=j->position-3;
        break;
    case 13:
        printf("%s\n",liste_corruption[13]);
        transaction(j,-15);
        break;
    case 14:
        printf("%s\n",liste_corruption[14]); // pas totalement finie (besoin de la fonction mettre en prison)
        j->en_prison=true;
        break;
    case 15:
        printf("%s\n",liste_corruption[15]);
        transaction(j,-20);
        break;
    }
}

void tirer_comite(t_joueur *j,t_joueur *jB,t_joueur *jC,t_joueur *jD,char* liste_commite,char* liste_corruption)
{
    srand( time( NULL ) );
    int carteComTire = rand() % 16;

    printf("%d",carteComTire);

    switch(carteComTire)
    {
    case 0:
        printf("%s\n",liste_commite[0]);
        j->carte_sortie_prison+=1;
        break;
    case 1:
        printf("%s\n",liste_commite[1]);
        int choix=0;
        do
        {
            scanf("%d",&choix);
            if (choix==1)
            {
                transaction(j,-10);
            }
            else if (choix ==2)
            {
                tirer_corruption(j,liste_corruption);
            }
        }
        while(choix<1 || choix>2);
        break;
    case 2:
        printf("%s\n",liste_commite[2]);
        transaction(j,50);
        break;
    case 3:
        printf("%s\n",liste_commite[3]); //on verifie que les joueur ne sont pas en faillite (quils jouent jtrs)
        if(jB->en_faillite==false)
        {
            transaction(jB,-10);
            transaction(j,10);
        }
        if(jC->en_faillite==false)
        {
            transaction(jC,-10);
            transaction(j,10);
        }
        if(jD->en_faillite==false)
        {
            transaction(jD,-10);
            transaction(j,10);
        }
        break;
    case 4:
        printf("%s\n",liste_commite[4]);
        transaction(j,200);
        break;
    case 5:
        printf("%s\n",liste_commite[5]);
        transaction(j,-100);
        break;
    case 6:
        printf("%s\n",liste_commite[6]);
        transaction(j,20);
        break;
    case 7:
        printf("%s\n",liste_commite[7]);
        transaction(j,100);
        break;
    case 8:
        printf("%s\n",liste_commite[8]);
        int deplacement_case1=1; // retour a la 1ere case
        j->position=deplacement_case1; //definir la postion qu'on veut
        break;
    case 9:
        printf("%s\n",liste_commite[9]);
        transaction(j,25);
        break;
    case 10:
        printf("%s\n",liste_commite[10]);
        int deplacement_depart=0; //la case depart
        transaction(j,200);
        j->position=deplacement_depart; //definir la postion qu'on veut
        break;
    case 11:
        printf("%s\n",liste_commite[11]);
        transaction(j,-50);
        break;
    case 12:
        printf("%s\n",liste_commite[12]);
        transaction(j,10);
        break;
    case 13:
        printf("%s\n",liste_commite[13]);
        transaction(j,-50);
        break;
    case 14:
        printf("%s\n",liste_commite[14]); //pas totalement finie (besoin de la fonction mettre en prison)
        j->en_prison=true;
        break;
    case 15:
        printf("%s\n",liste_commite[15]);
        transaction(j,100);
        break;
    }
}

bool victoire(t_joueur *j1, t_joueur *j2, t_joueur *j3, t_joueur *j4)
{
    if(j1->en_faillite==true && j2->en_faillite==true && j3->en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",j4->num_joueur);
        return true;
    }
    else if(j2->en_faillite==true && j3->en_faillite==true && j4->en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",j1->num_joueur);
        return true;
    }
    else if(j3->en_faillite==true && j4->en_faillite==true && j1->en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",j2->num_joueur);
        return true;
    }
    else if(j4->en_faillite==true && j1->en_faillite==true && j2->en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",j3->num_joueur);
        return true;
    }
    else
    {
        return false;
    }
}
