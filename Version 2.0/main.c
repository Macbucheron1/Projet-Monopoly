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
    tab_joueur[0].argent = 0
    tour(tab_joueur, plateau, p_banque);
}
