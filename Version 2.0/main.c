#include "Header.h"

int main()
{
    srand(time(0));
    t_joueur tab_joueur[4];
    creation_tab_joueur(tab_joueur);
    t_banque banque = creation_banque();
    t_banque* p_banque = &banque;
    t_case plateau[TAILLE_PLATEAU];
    creation_plateau(plateau);
    plateau[4].num_joueur = 1;
    plateau[6].num_joueur = 1;
    plateau[9].num_joueur = 1;
    tour(tab_joueur, plateau, p_banque);
    tour(tab_joueur, plateau, p_banque);
    tour(tab_joueur, plateau, p_banque);
    tour(tab_joueur, plateau, p_banque);
}
