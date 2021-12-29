#include "Header.h"

int main()
{
    t_joueur j1 = creation_joueur(1);
    t_joueur* p_j1 = &j1;
    t_banque banque = creation_banque();
    t_banque* p_banque = &banque;
    t_case plateau[TAILLE_PLATEAU];
    creation_plateau(plateau);
    tour(p_j1, plateau, p_banque);
}
