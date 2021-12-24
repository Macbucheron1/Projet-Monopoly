#include "NATHAN_H.h"
#include <time.h>

void deplacement(int* liste_de, t_joueur* joueur)
{
    /*La procédure incrémente la position du joueur
      Prend en paramètre la liste de dé et un pointeur sur le joueur qui se deplace
      Ne renvoie rien
    */
    (*joueur).position += liste_de[0] + liste_de[1];

    //salaire(joueur);
}

void aller_a(int indice_case, t_joueur* joueur)
{
    /* La procédure actualise la position du joueur pour le mettre à la case voulu
       Prend en paramètre l’indice de la case et le joueur qui se déplace,
       Ne renvoie rien
    */

    (*joueur).position = indice_case;
}

void entrer_prison(t_joueur* joueur)
{
    /*La procédure envoie le joueur en prison. Elle change l’etat prison du joueur et appelle la fonction aller à pour l’envoyer en prison
      Prend en paramètre le joueur
      Ne renvoie rien
    */
    (*joueur).prison = 1;

}

void sortie_prison(int* liste_de, t_joueur* joueur)
{
    (*joueur).tour_prison += 1;
    printf("%d", (*joueur).tour_prison);
    // Tant que le joueur n'a pas passé 3 tour en prison
    while((*joueur).tour_prison < 3)
    {
        // Si le joueur fait un double
        /*
        if (double_de(liste_de))
        {
            printf("Vous sortez de prison\n");
            (*joueur).prison = 1;
            break;

        }
        */
        // Si le joueur a assez d'argent poour l'amende
        if ((*joueur).argent >= 50)
        {
            printf("Voulez vous payer 50 pour sortir ?\n");
            printf("0 pour non, 1 pour oui :\n");
            int choix = 2;
            do
            {
                scanf("%d", &choix);
                printf("|%d|", choix);
                if (choix == 0);
                {
                    printf("Ca marche");
                }
            } while ((choix == 0) || (choix == 1));
            // Si le joueur veut payer l'amende
            if (choix == 1);
            {
                printf("Vous sortez de prison en payant\n");
                (*joueur).prison = 1;
                break;
            }
        }
        // Si le joueur a une carte sortie de prison
        if ((*joueur).carte_sortie_prison > 0)
        {
            printf("Voulez vous utiliser une carte sortie de prison ?\n");
            printf("0 pour non, 1 pour oui :\n");
            int choix = 2;
            do
            {
                scanf("%d", &choix);
            } while((choix == 0) || (choix == 1));
            // Si le joueur veut utiliser sa carte sortie de prison
            if (choix == 1);
            {
                printf("Vous sortez de prison \n");
                (*joueur).prison = 1;
                break;
            }
        }
    }
}










int main()
{
    t_joueur j1;
    j1.argent = 1500;
    j1.capital = 1500;
    j1.carte_sortie_prison = 0;
    //j1.nom = "Nathan";
    j1.position = 0;
    j1.prison = false;
    //j1.proprietes;
    j1.tour_prison = 0;
    int de[2];
    de[0] = 2;
    de[1] = 3;
    t_joueur* p_j1 = &j1;
    sortie_prison(de, p_j1);
    return 0;
}
