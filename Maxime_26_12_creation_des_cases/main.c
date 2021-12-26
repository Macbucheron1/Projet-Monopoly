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

    //creation de toute les cases propriete du plateau
    t_case sport_equestre;
    sport_equestre=creation_case(1, 60, 50, 60,1);
    t_case waterpolo;
    waterpolo=creation_case(2, 60, 50, 60,1);
    t_case breaking;
    breaking=creation_case(3, 200, 0, 0,9);
    t_case aviron;
    aviron=creation_case(4, 60, 50, 60,2);
    t_case canoe;
    canoe=creation_case(6, 60, 50, 60,2);
    t_case voile;
    voile=creation_case(7, 60, 50, 60,2);
    t_case tennis;
    tennis=creation_case(9, 140, 100, 110,3);
    t_case golf;
    golf=creation_case(10, 140, 100, 110,3);
    t_case skate;
    skate=creation_case(11, 200, 0, 0,9);
    t_case tir_a_l_arc;
    tir_a_l_arc=creation_case(12, 160, 100, 110,3);
    t_case lutte;
    lutte=creation_case(13, 180, 100, 110, 4);
    t_case halterophilie;
    halterophilie=creation_case(15, 200, 100, 110, 4);
    t_case Volley;
    Volley=creation_case(17, 220, 150, 165, 5);
    t_case handball;
    handball=creation_case(18, 220, 150, 165, 5);
    t_case escalade;
    escalade=creation_case(19, 200, 0, 0,9);
    t_case judo;
    judo=creation_case(22, 260, 150, 165,6);
    t_case boxe;
    boxe=creation_case(23, 280, 150, 165,6);
    t_case basket;
    basket=creation_case(25, 300, 200, 220, 7);
    t_case foot;
    foot=creation_case(26, 300, 200, 220, 7);
    t_case surf;
    surf=creation_case(27, 200, 0, 0,9);
    t_case rugby;
    rugby=creation_case(28, 320, 200, 220, 7);
    t_case athle;
    athle=creation_case(29, 350, 200, 220, 8);
    t_case natation;
    natation=creation_case(31, 400, 200, 220, 8);

    t_banque banque;
    banque=creation_banque();

    de1 = lance_de1();
    de2 = lance_de2();
    sortie = double_de(de1, de2);
    joueur1.en_prison = triple(sortie,joueur1);

    printf("\n"); //pour de la lisibilité
    //afficher_banque(banque);
    afficher_case(rugby);
    //afficher_joueur(joueur1);
    return 0;
}
