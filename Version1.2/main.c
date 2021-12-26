#include "Header.h"

int main()
{
    t_joueur j1 = creation_joueur(1);
    t_joueur* p_j1 = &j1;
    j1.carte_sortie_prison = 1;
    int de[2];
    lance_de(de);
    t_case plateau[TAILLE_PLATEAU];
    creation_plateau(plateau);
    for (int i = 0; i < TAILLE_PLATEAU; i++)
    {
        afficher_case(plateau[i]);
    }
}
