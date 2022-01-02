#include "faillite_header_v2.h"

int main()
{
    t_joueur tab_joueur[4];
    creation_tab_joueur(tab_joueur);
    printf("\n");

    //pour les test

    t_joueur *p_joueur1=&tab_joueur[0];
    t_joueur *p_joueur2=&tab_joueur[1];
    t_joueur *p_joueur3=&tab_joueur[2];
    t_joueur *p_joueur4=&tab_joueur[3];

    t_case plateau[TAILLE_PLATEAU];
    creation_plateau(plateau);

    propriete_a_joueur(tab_joueur,0,plateau,2);
    propriete_a_joueur(tab_joueur,0,plateau,12);
    afficher_propriete_joueur(tab_joueur,0,plateau);

    return 0;
}
