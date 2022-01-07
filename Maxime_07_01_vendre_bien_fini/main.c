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
    plateau[3].num_joueur = 1;
    plateau[6].num_joueur = 1;
    plateau[6].nb_hotel = 1;
    printf("%d", tab_joueur[0].nb_propriete);
    printf("le joueur 1 a: %d et le joueur 2 a %d\n", tab_joueur[0].argent, tab_joueur[1].argent);
    tour(tab_joueur, plateau, p_banque);
    printf("le joueur 1 a: %d et le joueur 2 a %d\n", tab_joueur[0].argent, tab_joueur[1].argent);
    tour(tab_joueur, plateau, p_banque);
    printf("le joueur 1 a: %d et le joueur 2 a %d\n", tab_joueur[0].argent, tab_joueur[1].argent);
    tour(tab_joueur, plateau, p_banque);
    printf("le joueur 1 a: %d et le joueur 2 a %d\n", tab_joueur[0].argent, tab_joueur[1].argent);
    tour(tab_joueur, plateau, p_banque);
    printf("le joueur 1 a: %d et le joueur 2 a %d\n", tab_joueur[0].argent, tab_joueur[1].argent);
}
