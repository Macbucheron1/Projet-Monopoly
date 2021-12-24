#include "Header.h"

// Fonction de deplacement de joueur
void deplacement(int* liste_de, t_joueur* joueur)
{
    /*La proc�dure incr�mente la position du joueur
      Prend en param�tre la liste de d� et un pointeur sur le joueur qui se deplace
      Ne renvoie rien
    */
    (*joueur).position += liste_de[0] + liste_de[1];
}

// Fonction de deplacement de joueur
void aller_a(int indice_case, t_joueur* joueur)
{
    /* La proc�dure actualise la position du joueur pour le mettre � la case voulu
       Prend en param�tre l�indice de la case et le joueur qui se d�place,
       Ne renvoie rien
    */

    (*joueur).position = indice_case;
}

// fonction pour prison
void entrer_prison(t_joueur* joueur)
{
    /*La proc�dure envoie le joueur en prison. Elle change l�etat prison du joueur et appelle la fonction aller � pour l�envoyer en prison
      Prend en param�tre le joueur
      Ne renvoie rien
    */
    (*joueur).en_prison = 1;

}

// fonction pour prison
void sortie_prison(int* liste_de, t_joueur* joueur) // En cours par NATHAN
{

}

// fonction creation d'instance
t_joueur creation_joueur(void)
{
    /* Permet la creation d'un joueur
       Ne prend pas de param�tre
       Renvoie une instance de la classe joueur au debut de partie
    */
    t_joueur j;
    fflush(stdin);

    printf("Veuillez entrer le nom du joueur :\n");
    gets(j.nom);
    j.position=0;
    j.argent=1500;
    j.capital=1500;
    j.en_prison=false;
    j.tour_prison=0;
    j.carte_sortie_prison=0;

    return j;
}

// fonction creation d'instance
t_banque creation_banque(void)
{
    /* Permet la creation de la banque
       Ne prend pas de param�tre
       Renvoie une instance de la classe banque au debut de partie
    */
    t_banque b;
    fflush(stdin);

    b.nb_maison_restante=32;
    b.nb_hotel_restant=12;

    return b;
}

// fonction affichage d'instance
void afficher_joueur(t_joueur j)
{
    /* Proc�dure qui affiche une instance de joueur
       Prend en param�tre un joueur
       Ne renvoie rien
    */
    printf("Voici le JOUEUR:\n");
    printf("nom:%s\nnumero:%d\nposition:%d\nargent:%d\ncapital:%d\npropriete:%d\netes-vous en prison?:%d\ncombien de tour en prison:%d\nnb de cartes sorites de prison:%d\nfaillite: %d\n",j.nom,j.numero,j.position,j.argent,j.capital,j.proprietes,j.en_prison,j.tour_prison,j.carte_sortie_prison, j.en_faillite);
    printf("\n"); //pour de la lisibilit�
}

// fonction affichage d'instance
void afficher_case(t_case c)
{
    /* Proc�dure qui affiche une instance de case
       Prend en param�tre une case
       Ne renvoie rien
    */
    printf("Voici la CASE:\n");
    printf("position:%d\nprix d'achat:%d\nnum joueur la possedant:%s\nnombre de maison:%d\nya til un hotel:%d\nprix dachat d'une maison:%d\nprix d'achat d'un hotel:%d\nquel groupe de carte:%d\n",c.position,c.valeur,c.num_joueur,c.nb_maison,c.nb_hotel,c.val_maison,c.val_hotel,c.groupe_cartes);
    printf("\n"); //pour de la lisibilit�
}

// fonction affichage d'instance
void afficher_banque(t_banque b)
{
    /* Proc�dure qui affiche une instance de banque
       Prend en param�tre la banque
       Ne renvoie rien
    */
    printf("Voici la BANQUE:\n");
    printf("maisons restantes:%d\nhotels restant:%d\n",b.nb_maison_restante,b.nb_hotel_restant);
    printf("\n"); //pour de la lisibilit�
}

// fonction pour les d�s
void lance_de(int* de)
{
    /* Proc�dure qui prend en param�tre une liste de 2 d� et qui les lance
       Prend en param�tre la liste de d�
       Ne renvoie rien
    */
    de[0] = (rand()%6)+1;
    de[1] = (rand()%6)+1;

}

// fonction pour les d�s
int double_de(int* de)
{
    /* La fonction verifie si le joueur a fait un double
       Prend en param�tre une liste de d�
       Renvoie un bool�en, True si double, False si non
    */
    if(de[0] == de[1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

// fonction pour faillite
void en_faillite(t_joueur *j) // En cours par LUC
{
    /* La proc�dure erifie si le joueur est en faillite
       Si oui le met en faillite
       Prend en param�tre un pointeur sur le joueur
    */
    int choix = 2;
    if (j->capital<=0) //le joueur ne peut plus rien faire
        {
            j->en_faillite=true;
            printf("Vous etes en faillite");
            //On doit supprimer ses propri�t�s
        }


    else if (j->argent<=0) //le joueur n'a plus d'argent mais encore du capital
        {
            printf("voulez vous abandonner ?: oui[1], non[2]\n");
            scanf("%d",&choix);
            if (choix==1) // Il veut abandonner
                {
                    j->en_faillite=true;
                    printf("Vous etes en faillite\n\n");
                    // On doit supprimer toute ses propri�t�s
                }
            else // Il veut continuer
                {
                    printf("ok, vous allez devoir hyppotequer\n\n");
                    // lance la fonction hypot�que
                }
        }

}
