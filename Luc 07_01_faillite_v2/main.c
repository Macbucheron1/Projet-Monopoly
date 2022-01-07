#include "faillite_header_v2.h"

int main()
{
    t_joueur tab_joueur[4];
    creation_tab_joueur(tab_joueur);
    printf("\n");
    t_banque banque = creation_banque();
    t_banque* p_banque = &banque;

    //pour les test

    t_joueur *p_joueur1=&tab_joueur[0];
/*
    t_joueur *p_joueur2=&tab_joueur[1];
    t_joueur *p_joueur3=&tab_joueur[2];
    t_joueur *p_joueur4=&tab_joueur[3];*/

    t_case plateau[TAILLE_PLATEAU];
    creation_plateau(plateau);

    propriete_a_joueur(tab_joueur,0,plateau,2);
    propriete_a_joueur(tab_joueur,0,plateau,12);
    propriete_a_joueur(tab_joueur,0,plateau,17);
    afficher_propriete_joueur(tab_joueur,0,plateau);

    printf("Suprression\n\n");

    enlever_propriete_joueur(tab_joueur,0,plateau,12);
    afficher_propriete_joueur(tab_joueur,0,plateau);

    //verification faillite banque

    p_joueur1->argent=100;
    en_faillite(tab_joueur,0,1000,p_banque,0,plateau);

    printf("hypo case 2 =%d\n",plateau[2].hypoteque);
    printf("hypo case 17 =%d\n",plateau[17].hypoteque);

    //verification faillite avec le joueur 2 en créancier (mettre en commentaire la verification de la banque)

    p_joueur1->argent=100;
    en_faillite(tab_joueur,0,1000,p_banque,1,plateau);

    printf("Propriete du joueur 2:\n\n");
    afficher_propriete_joueur(tab_joueur,1,plateau);

    return 0;
}
