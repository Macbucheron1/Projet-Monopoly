#include "faillite_header.h"

int main()
{
    t_joueur joueur1;
    joueur1=creation_joueur();

    t_joueur *p_joueur1=&joueur1;
    en_faillite(p_joueur1);

    afficher_joueur(joueur1);
    return 0;
}
