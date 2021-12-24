#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "sous_prog.h"

int main()
{
    int de1, de2;
    bool sortie;
    srand(time(NULL));
    // pour tester que tout marche bien
    t_joueur joueur1;
    joueur1=creation_joueur();

    t_case case1;
    case1=creation_case(6);
    t_banque banque;
    banque=creation_banque();

    de1 = lance_de1();
    de2 = lance_de2();
    sortie = double_de(de1, de2);
    joueur1.en_prison = triple(sortie,joueur1);

    printf("\n"); //pour de la lisibilité
    //afficher_banque(banque);
    afficher_case(case1);
    //afficher_joueur(joueur1);
    return 0;
}
