#include "Header.h"

// Fonction de deplacement de joueur
void deplacement(int* liste_de, t_joueur* joueur)
{
    /*La procédure incrémente la position du joueur
      Prend en paramètre la liste de dé et un pointeur sur le joueur qui se deplace
      Ne renvoie rien
    */
    (*joueur).position += liste_de[0] + liste_de[1];
}

// Fonction de deplacement de joueur
void aller_a(int indice_case, t_joueur* joueur)
{
    /* La procédure actualise la position du joueur pour le mettre à la case voulu
       Prend en paramètre l’indice de la case et le joueur qui se déplace,
       Ne renvoie rien
    */

    (*joueur).position = indice_case;
}

// fonction pour prison
void entrer_prison(t_joueur* joueur)
{
    /*La procédure envoie le joueur en prison. Elle change l’etat prison du joueur et appelle la fonction aller à pour l’envoyer en prison
      Prend en paramètre le joueur
      Ne renvoie rien
    */
    (*joueur).en_prison = 1;

}

// fonction pour prison
bool sortie_prison(int* liste_de, t_joueur* joueur)
{
    /* Fonction qui permets à un joueur de sortir de prison
       Prend en paramètre la liste de dé et un pointeur sur le joueur
       Renvoie true si le joueur est sortie de prison, false sinon
    */
    if (joueur->en_prison == false) // Si le joueur n'est pas en prison on ne va pas plus loin
    {
        return false;
    }
    else // Sinon le joueur passe un tour de plus en prison
    {
        joueur->tour_prison += 1;
        printf("C'est votre %d tour en prison\n", joueur->tour_prison);
    }
    if (joueur->tour_prison >= 3) // Le joueur a passé 3 tours en prison
    {
        printf("Vous avez passez 3 tours en prison, vous payez 50 et sortez\n");
        joueur->argent -= 50;
        joueur->capital -= 50;
        joueur->en_prison = false;
        joueur->tour_prison = 0;
        return true;
    }
    if (double_de(liste_de)) // Sortie avec un double
    {
        printf("Vous sortez de prison\n");
        joueur->en_prison = false;
        joueur->tour_prison = 0;
        return true;
    }
    else if (joueur->carte_sortie_prison > 0) // sortie  avec une carte sortie de prison
    {
        printf("Vous avez une carte sortie de prison\n");
        char choix[10];
        do
        {
            printf("Voulez vous l'utilisez ?\nOUI : 1       NON : 0\n");
            fflush(stdin);
            gets(choix);
        } while ((choix[0] != 48) && (choix[0] != 49) || (strlen(choix) > 1)); // 48 = 0 en code ascii
        if (choix[0] == 49) // 49 = 1 en code ascii
        {
            printf("Vous sortez de prison\n");
            joueur->en_prison = false;
            joueur->tour_prison = 0;
            joueur->carte_sortie_prison -= 1;
            return true;
        }
    }
    char choix[10];
    do
    {
        printf("Voulez vous payez 50 pour sortir tout de suite ?\nOUI : 1       NON : 0\n");
        fflush(stdin);
        gets(choix);
    } while ((choix[0] != 48) && (choix[0] != 49) || (strlen(choix) > 1)); // 48 = 0 en code ascii
    if (choix[0] == 49) // 49 = 1 en code ascii
    {
        printf("Vous sortez de prison\n");
        joueur->en_prison = false;
        joueur->tour_prison = 0;
        joueur->argent -= 50;
        joueur->capital -= 50;
        return true;
    }

}

// fonction creation d'instance
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes, char* nom)
{
    t_case c;
    fflush(stdin);
    strcpy(c.nom, nom);
    c.num_joueur = NULL;
    c.position=position;
    c.valeur=valeur;
    c.val_maison=val_maison;
    c.val_hotel=val_hotel;
    c.groupe_cartes=groupe_cartes;
    c.nb_maison = 0;
    c.nb_hotel = 0;

    return c;
}

// fonction creation d'instance
t_joueur creation_joueur(int numero)
{
    /* Permet la creation d'un joueur
       Ne prend pas de paramètre
       Renvoie une instance de la classe joueur au debut de partie
    */
    t_joueur j;
    fflush(stdin);

    printf("Veuillez entrer le nom du joueur :\n");
    gets(j.nom);
    j.numero = numero;
    j.position=0;
    j.argent=1500;
    j.capital=1500;
    j.en_prison=false;
    j.tour_prison=0;
    j.carte_sortie_prison=0;
    j.en_faillite = false;

    return j;
}

// fonction creation d'instance
t_banque creation_banque(void)
{
    /* Permet la creation de la banque
       Ne prend pas de paramètre
       Renvoie une instance de la classe banque au debut de partie
    */
    t_banque b;
    fflush(stdin);

    b.nb_maison_restante=32;
    b.nb_hotel_restant=12;

    return b;
}

// fonction creation plateau
void creation_plateau(t_case** plateau)
{
    /* Procédure de creation du plateau
       Prend en paramètre un tableau qui sera le plateau
       Ne renvoie rien
    */

    // Groupe 1 = Propriétés , 2 cases
    // Groupe 2 = Propriétés , 3 cases
    // Groupe 3 = Propriétés , 3 cases
    // Groupe 4 = Propriétés , 2 cases
    // Groupe 5 = Propriétés , 2 cases
    // Groupe 6 = Propriétés , 2 cases
    // Groupe 7 = Propriétés , 3 cases
    // Groupe 8 = Propriétés , 2 cases
    // Groupe 9 = Gares, 4 cases
    // Groupe 10 = carte communauté,
    // Groupe 11 = carte chance
    // Groupe 12 = prison
    // Groupe 13 = parc gratuit
    // Groupe 14 = Impot
    // Groupe 15 = Aller en prison
    // Groupe 16 = Depart

    t_case depart;
    depart = creation_case(0, 0, 0, 0, 16, "Depart");
    t_case* p_depart = &depart;
    plateau[0] = p_depart;

    t_case sport_equestre;
    sport_equestre=creation_case(1, 60, 50, 60,1, "Sport Equestre");
    t_case* p_sport_equestre = &sport_equestre;
    plateau[1] = p_sport_equestre;

    t_case waterpolo;
    waterpolo=creation_case(2, 60, 50, 60,1, "Waterpolo");
    t_case* p_waterpolo = &waterpolo;
    plateau[2] = p_waterpolo;

    t_case breaking;
    breaking=creation_case(3, 200, 0, 0,9, "Breaking");
    t_case* p_breaking = &breaking;
    plateau[3] = p_breaking;

    t_case aviron;
    aviron=creation_case(4, 60, 50, 60,2, "Aviron");
    t_case* p_aviron = &aviron;
    plateau[4] = p_aviron;

    t_case corruption1;
    corruption1 = creation_case(5, 0, 0, 0, 11, "Corruption");
    t_case* p_corruption1 = &corruption1;
    plateau[5] = p_corruption1;

    t_case canoe;
    canoe=creation_case(6, 60, 50, 60, 2, "Canoe");
    t_case* p_canoe = &canoe;
    plateau[6] = p_canoe;

    t_case voile;
    voile=creation_case(7, 60, 50, 60, 2, "Voile");
    t_case* p_voile = &voile;
    plateau[7] = p_voile;

    t_case suspension;
    suspension = creation_case(8, 0, 0, 0, 12, "Suspension");
    t_case* p_suspension = &suspension;
    plateau[8] = p_suspension;

    t_case tennis;
    tennis=creation_case(9, 140, 100, 110,3, "Tennis");
    t_case* p_tennis = &tennis;
    plateau[9] = p_tennis;

    t_case golf;
    golf=creation_case(10, 140, 100, 110,3, "Golf");
    t_case* p_golf = &golf;
    plateau[10] = p_golf;

    t_case skate;
    skate=creation_case(11, 200, 0, 0,9, "Skate");
    t_case* p_skate = &skate;
    plateau[11] = p_skate;

    t_case tir_a_l_arc;
    tir_a_l_arc=creation_case(12, 160, 100, 110,3, "Tir a l'arc");
    t_case* p_tir_a_l_arc = &tir_a_l_arc;
    plateau[12] = p_tir_a_l_arc;

    t_case lutte;
    lutte=creation_case(13, 180, 100, 110, 4, "Lutte");
    t_case* p_lutte = &lutte;
    plateau[13] = p_lutte;

    t_case comite_olympique1;
    comite_olympique1 = creation_case(14, 0, 0, 0, 10, "Comite olympique");
    t_case* p_comite_olympique1 = &comite_olympique1;
    plateau[14] = p_comite_olympique1;

    t_case halterophilie;
    halterophilie=creation_case(15, 200, 100, 110, 4, "Halterophilie");
    t_case* p_halterophilie = &halterophilie;
    plateau[15] = p_halterophilie;

    t_case village_olympique;
    village_olympique = creation_case(16, 0, 0, 0, 13, "Village olympique");
    t_case* p_village_olympique = &village_olympique;
    plateau[16] = p_village_olympique;

    t_case Volley;
    Volley=creation_case(17, 220, 150, 165, 5, "Volley");
    t_case* p_volley = &Volley;
    plateau[17] = p_volley;

    t_case handball;
    handball=creation_case(18, 220, 150, 165, 5, "Handball");
    t_case* p_handball = &handball;
    plateau[18] = p_handball;

    t_case escalade;
    escalade=creation_case(19, 200, 0, 0,9, "Escalade");
    t_case* p_escalade = &escalade;
    plateau[19] = p_escalade;

    t_case amende;
    amende = creation_case(20, 0, 0, 0, 14, "Amende");
    t_case* p_amende = &amende;
    plateau[20] = p_amende;

    t_case corruption2;
    corruption2 = creation_case(5, 0, 0, 0, 11, "Corruption");
    t_case* p_corruption2 = &corruption2;
    plateau[21] = p_corruption2;

    t_case judo;
    judo=creation_case(22, 260, 150, 165,6, "Judo");
    t_case* p_judo = &judo;
    plateau[22] = p_judo;

    t_case boxe;
    boxe=creation_case(23, 280, 150, 165,6, "Boxe");
    t_case* p_boxe = &boxe;
    plateau[23] = p_boxe;

    t_case controle_dopage;
    controle_dopage = creation_case(24, 0, 0, 0, 15, "Controle anti dopage");
    t_case* p_controle_dopage = &controle_dopage;
    plateau[24] = p_controle_dopage;

    t_case basket;
    basket=creation_case(25, 300, 200, 220, 7, "Basket");
    t_case* p_basket= &basket;
    plateau[25] = p_basket;

    t_case foot;
    foot=creation_case(26, 300, 200, 220, 7, "Foot");
    t_case* p_foot = &foot;
    plateau[26] = p_foot;

    t_case surf;
    surf=creation_case(27, 200, 0, 0,9, "Surf");
    t_case* p_surf = &surf;
    plateau[27] = p_surf;

    t_case rugby;
    rugby=creation_case(28, 320, 200, 220, 7, "Rugby");
    t_case* p_rugby = &rugby;
    plateau[28] = p_rugby;

    t_case athletisme;
    athletisme=creation_case(29, 350, 200, 220, 8, "Athletisme");
    t_case* p_athletisme = &athletisme;
    plateau[29] = p_athletisme;

    t_case comite_olympique2;
    comite_olympique2 = creation_case(5, 0, 0, 0, 10, "Comite olympique");
    t_case* p_comite_olympique2 = &comite_olympique2;
    plateau[30] = p_comite_olympique2;

    t_case natation;
    natation=creation_case(31, 400, 200, 220, 8, "Natation");
    t_case* p_natation = &natation;
    plateau[31] = p_natation;
}

// fonction affichage d'instance
void afficher_joueur(t_joueur j)
{
    /* Procédure qui affiche une instance de joueur
       Prend en paramètre un joueur
       Ne renvoie rien
    */
    printf("Voici le JOUEUR:\n");
    printf("nom:%s\nnumero:%d\nposition:%d\nargent:%d\ncapital:%d\npropriete:%d\netes-vous en prison?:%d\ncombien de tour en prison:%d\nnb de cartes sorites de prison:%d\nfaillite: %d\n",j.nom,j.numero,j.position,j.argent,j.capital,j.proprietes,j.en_prison,j.tour_prison,j.carte_sortie_prison, j.en_faillite);
    printf("\n"); //pour de la lisibilité
}

// fonction affichage d'instance
void afficher_case(t_case c)
{
    /* Procédure qui affiche une instance de case
       Prend en paramètre une case
       Ne renvoie rien
    */
    printf("Voici la CASE:\n");
    printf("nom: %s\nposition:%d\nprix d'achat:%d\nnum joueur la possedant:%d\nnombre de maison:%d\nya til un hotel:%d\nprix dachat d'une maison:%d\nprix d'achat d'un hotel:%d\nquel groupe de carte:%d\n",c.nom,c.position,c.valeur,c.num_joueur,c.nb_maison,c.nb_hotel,c.val_maison,c.val_hotel,c.groupe_cartes);
    printf("\n"); //pour de la lisibilité
}

// fonction affichage d'instance
void afficher_banque(t_banque banque)
{
    /* Procédure qui affiche une instance de banque
       Prend en paramètre la banque
       Ne renvoie rien
    */
    printf("Voici la BANQUE:\n");
    printf("maisons restantes:%d\nhotels restant:%d\n",banque.nb_maison_restante,banque.nb_hotel_restant);
    printf("\n"); //pour de la lisibilité
}

// fonction pour les dés
void lance_de(int* de)
{
    /* Procédure qui prend en paramètre une liste de 2 dé et qui les lance
       Prend en paramètre la liste de dé
       Ne renvoie rien
    */
    srand(time(NULL));
    de[0] = (rand()%6)+1;
    de[1] = (rand()%6)+1;

}

// fonction pour les dés
int double_de(int* de)
{
    /* La fonction verifie si le joueur a fait un double
       Prend en paramètre une liste de dé
       Renvoie un booléen, True si double, False si non
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
void en_faillite(t_joueur *joueur) // En cours par LUC
{
    /* La procédure erifie si le joueur est en faillite
       Si oui le met en faillite
       Prend en paramètre un pointeur sur le joueur
    */
    int choix = 2;
    if (joueur->capital<=0) //le joueur ne peut plus rien faire
        {
            joueur->en_faillite=true;
            printf("Vous etes en faillite");
            //On doit supprimer ses propriétés
        }


    else if (joueur->argent<=0) //le joueur n'a plus d'argent mais encore du capital
        {
            printf("voulez vous abandonner ?: oui[1], non[2]\n");
            scanf("%d",&choix);
            if (choix==1) // Il veut abandonner
                {
                    joueur->en_faillite=true;
                    printf("Vous etes en faillite\n\n");
                    // On doit supprimer toute ses propriétés
                }
            else // Il veut continuer
                {
                    printf("ok, vous allez devoir hyppotequer\n\n");
                    // lance la fonction hypotèque
                }
        }

}

// fonction pour loyer
void loyer(t_joueur* joueur, t_case* cases) // En cours par Nathan
{
    //printf("%d\n", cases->num_joueur);
    //printf("num_joueur case: %d\nnum joueur : d\ngroupe_cartes cases : d\n", cases->num_joueur);
    if /*((cases->num_joueur != joueur->numero) && */(cases->num_joueur == 0)/* && (cases->groupe_cartes <= 9))*/
    {
        // le joueur doit payer
        printf("Paye");
    }
    else
    {
        printf("Il ne se passe rien");
    }
}

void tour(t_joueur* p_joueur, t_case* plateau[], t_banque* p_banque)
{
    printf("C'est le tour de %s\n", p_joueur->nom);
    int de[2];
    lance_de(de);
    de[0] = 1;
    de[1] = 1;
    printf("Vous avez fait %d et %d\n", de[0], de[1]);
    if (p_joueur->en_faillite)
    {
        return false;
    }
    if (sortie_prison(de, p_joueur )) // Le joueur sors de prison donc ne joue pas plus pendant ce tour
    {

    }
    else // Le joueur n'est pas en prison
    {
        deplacement(de, p_joueur);
        printf("Vous etes a la case %s\n", plateau[(p_joueur->position)]->nom);
        loyer(p_joueur, plateau[p_joueur->position]);
        // acheter_propriete(p_joueur, plateau[p_joueur->position]);
        // acheter_maison_hotel();


    }

}

