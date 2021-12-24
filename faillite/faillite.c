#include "faillite_header.h"

//struct

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

    j.en_faillite=false;

    return j;
}

void afficher_joueur(t_joueur j)
{
    printf("Voici le JOUEUR:\n");
    printf("nom:%s\nposition:%d\nargent:%d\ncapital:%d\npropriete:%d\netes-vous en prison?:%d\ncombien de tour en prison:%d\nnb de cartes sorites de prison:%d\nest-il en faillite ?:%d\n",j.nom,j.position,j.argent,j.capital,j.proprietes,j.en_prison,j.tour_prison,j.carte_sortie_prison,j.en_faillite);
    printf("\n"); //pour de la lisibilité
}

//faillite

void en_faillite(t_joueur *j) //est ce quon demande au joueur sil veut abandonner qnd son argent = 0 ?
{
    int choix = 2;
    if (j->capital<=0) //le joueur ne peut plus rien faire
        {
            j->en_faillite=true;
            printf("Vous etes en faillite");
        }


    else if (j->argent<=0) //le joueur a plus dargent mais encore du capital
        {
            printf("voulez vous abandonner ?: oui[1], non[2]\n");
            scanf("%d",&choix);
            if (choix==1) //s'il fait se choix il faut rendre disponible toutes ses propriétés
                {
                    j->en_faillite=true;
                    printf("Vous etes en faillite\n\n");
                }
            else //il faut alors appeler la fonction hypoteque
                {
                    printf("ok, vous allez devoir hyppotequer\n\n");
                }
        }

}
