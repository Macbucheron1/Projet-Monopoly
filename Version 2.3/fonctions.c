#include "Header.h"

// Fonction de deplacement de joueur
void deplacement(int* liste_de, t_joueur tab_joueur[], int i) // NATHAN fait
{
    /*La procédure incrémente la position du joueur
      Prend en paramètre la liste de dé et un pointeur sur le joueur qui se deplace
      Ne renvoie rien
    */
    if (salaire(tab_joueur, liste_de, i))
    {

    }
    else
    {
        tab_joueur[i].position += liste_de[0] + liste_de[1];
    }

}

// Fonction de deplacement de joueur
void aller_a(int indice_case, t_joueur tab_joueur[], int i) // NATHAN fait
{
    /* La procédure actualise la position du joueur pour le mettre à la case voulu
       Prend en paramètre l’indice de la case et le joueur qui se déplace,
       Ne renvoie rien
    */

    tab_joueur[i].position = indice_case;
}

// fonction pour prison
void entrer_prison(t_joueur tab_joueur[], int i) // NATHAN fait
{
    /*La procédure envoie le joueur en prison. Elle change l’etat prison du joueur et appelle la fonction aller à pour l’envoyer en prison
      Prend en paramètre le joueur
      Ne renvoie rien
    */
    tab_joueur[i].en_prison = 1;
    aller_a(8, tab_joueur, i);

}

// fonction pour prison
bool sortie_prison(int* liste_de, t_joueur tab_joueur[], int i, t_case plateau[], t_banque* p_banque) // NATHAN fait
{
    /* Fonction qui permets à un joueur de sortir de prison
       Prend en paramètre la liste de dé et un pointeur sur le joueur
       Renvoie true si le joueur est sortie de prison, false sinon
    */
    if (tab_joueur[i].en_prison == false) // Si le joueur n'est pas en prison on ne va pas plus loin
    {
        return false;
    }
    else // Sinon le joueur passe un tour de plus en prison
    {
        tab_joueur[i].tour_prison += 1;
        printf("C'est votre %d tour en prison\n", tab_joueur[i].tour_prison);
        hypotheque(tab_joueur, i, plateau, p_banque);
        Vendre_bien(tab_joueur, plateau, p_banque, i);
    }
    if (tab_joueur[i].tour_prison >= 3) // Le joueur a passé 3 tours en prison
    {
        printf("Vous avez passez 3 tours en prison, vous payez 50 et sortez\n");
        tab_joueur[i].argent -= 50;
        tab_joueur[i].en_prison = false;
        tab_joueur[i].tour_prison = 0;
        return true;
    }
    if (double_de(liste_de)) // Sortie avec un double
    {
        printf("Vous sortez de prison\n");
        tab_joueur[i].en_prison = false;
        tab_joueur[i].tour_prison = 0;
        return true;
    }
    else if (tab_joueur[i].carte_sortie_prison > 0) // sortie  avec une carte sortie de prison
    {
        printf("Vous avez une carte sortie de prison\n");
        char choix[10];
        do
        {
            printf("Voulez vous l'utilisez ?\nOUI : 1       NON : 0\n");
            fflush(stdin);
            gets(choix);
        } while (((choix[0] != 48) && (choix[0] != 49)) || (strlen(choix) > 1)); // 48 = 0 en code ascii
        if (choix[0] == 49) // 49 = 1 en code ascii
        {
            printf("Vous sortez de prison\n");
            tab_joueur[i].en_prison = false;
            tab_joueur[i].tour_prison = 0;
            tab_joueur[i].carte_sortie_prison -= 1;
            return true;
        }
    }
    char choix[10];
    do
    {
        printf("Voulez vous payez 50 pour sortir tout de suite ?\nOUI : 1       NON : 0\n");
        fflush(stdin);
        gets(choix);
    } while (((choix[0] != 48) && (choix[0] != 49)) || (strlen(choix) > 1)); // 48 = 0 en code ascii
    if (choix[0] == 49) // 49 = 1 en code ascii
    {
        printf("Vous sortez de prison\n");
        tab_joueur[i].en_prison = false;
        tab_joueur[i].tour_prison = 0;
        tab_joueur[i].argent -= 50;
        return true;
    }
    return false;
}

// fonction creation d'instance
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes, char* nom, int couleur_fond, int couleur_texte, int valeur_hypotheque, int base_loyer, int loyer_1_maison, int loyer_2_maison, int loyer_3_maison, int loyer_4_maison, int loyer_1_hotel) // LUC NATHAN MAXIME fait
{
    /* Fonction qui créée une case
       Prend en paramètre toutes ses caractéristique
       Renvoie la case
    */
    t_case c;
    fflush(stdin);
    strcpy(c.nom, nom);
    c.num_joueur = 0;
    c.position=position;
    c.valeur=valeur;
    c.val_maison=val_maison;
    c.val_hotel=val_hotel;
    c.groupe_cartes=groupe_cartes;
    c.nb_maison = 0;
    c.nb_hotel = 0;
    c.couleur_fond = couleur_fond;
    c.couleur_texte = couleur_texte;
    c.hypoteque = false;
    c.val_hypotheque = valeur_hypotheque;
    c.base_loyer = base_loyer;
    c.loyer_1_maison = loyer_1_maison;
    c.loyer_2_maison = loyer_2_maison;
    c.loyer_3_maison = loyer_3_maison;
    c.loyer_4_maison = loyer_4_maison;
    c.loyer_1_hotel = loyer_1_hotel;

    return c;
}

// fonction creation d'instance
t_joueur creation_joueur(int numero) // LUC fait
{
    /* Permet la creation d'un joueur
       Prend en paramètre le numéro du joueur
       Renvoie une instance de la classe joueur au debut de partie
    */
    t_joueur j;
    fflush(stdin);


    do
    {
        printf("Veuillez entrer le nom du joueur %d : ", numero);
        fflush(stdin);
        gets(j.nom);
    }while(strlen(j.nom) == 0);
    j.numero = numero;
    j.position=0;
    j.argent=1500;
    j.en_prison=false;
    j.tour_prison=0;
    j.carte_sortie_prison=0;
    j.en_faillite = false;

    return j;
}

// fonction creation d'instance
t_banque creation_banque(void) // LUC fait
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
void creation_plateau(t_case* plateau) // MAXIME NATHAN Fait
{
    /* Procédure de creation du plateau
       Prend en paramètre un tableau qui sera le plateau
       Ne renvoie rien
    */

    // Groupe 1 = Propriétés , 2 cases , vert caca d'oie , blanc
    // Groupe 2 = Propriétés , 3 cases , turquoise , blanc
    // Groupe 3 = Propriétés , 3 cases , violet , blanc
    // Groupe 4 = Propriétés , 2 cases , gris foncé , blanc
    // Groupe 5 = Propriétés , 2 cases , rouge , blanc
    // Groupe 6 = Propriétés , 2 cases , jaune , noir
    // Groupe 7 = Propriétés , 3 cases , vert , blanc
    // Groupe 8 = Propriétés , 2 cases , bleu , blanc
    // Groupe 9 = Gares, 4 cases , blanc , noir
    // Groupe 10 = carte communauté,
    // Groupe 11 = carte chance
    // Groupe 12 = prison
    // Groupe 13 = parc gratuit
    // Groupe 14 = Impot
    // Groupe 15 = Aller en prison
    // Groupe 16 = Depart

    t_case depart;
    depart=creation_case(0,0,0,0,16,"depart",7,0, 0, 0, 0, 0, 0, 0, 0);
    plateau[0]= depart;

    t_case sport_equestre;
    sport_equestre=creation_case(1, 60, 50, 60,1, "Sport Equestre", 6 , 15, 60, 2, 10, 30, 90, 160, 250);
    plateau[1] = sport_equestre;

    t_case waterpolo;
    waterpolo=creation_case(2, 60, 50, 60,1, "Waterpolo", 6, 15, 30, 4, 20, 60, 180, 320, 450);
    plateau[2] = waterpolo;

    t_case breaking;
    breaking=creation_case(3, 200, 0, 0,9, "Breaking",15, 0, 100, 25, 0, 0, 0, 0, 0);
    plateau[3] = breaking;

    t_case aviron;
    aviron=creation_case(4, 60, 50, 60,2, "Aviron",3, 15, 50, 6, 30, 90, 270, 400, 550);
    plateau[4] = aviron;

    t_case corruption1;
    corruption1 = creation_case(5, 0, 0, 0, 11, "Corruption",13 , 15, 0, 0, 0, 0, 0, 0, 0);
    plateau[5] = corruption1;

    t_case canoe;
    canoe=creation_case(6, 60, 50, 60, 2, "Canoe",3, 15, 50, 6, 30, 90, 270, 400, 550);
    plateau[6] = canoe;

    t_case voile;
    voile=creation_case(7, 60, 50, 60, 2, "Voile",3 , 15, 60, 8, 40, 100, 300, 450, 600);
    plateau[7] = voile;

    t_case suspension;
    suspension = creation_case(8, 0, 0, 0, 12, "Suspension", 7 , 0, 0, 0, 0, 0, 0, 0, 0);
    plateau[8] = suspension;

    t_case tennis;
    tennis=creation_case(9, 140, 100, 110,3, "Tennis",5 , 15, 70, 10, 50, 150, 450, 625, 750);
    plateau[9] = tennis;

    t_case golf;
    golf=creation_case(10, 140, 100, 110,3, "Golf", 5 , 15, 70, 10, 50, 150, 450, 625, 750);
    plateau[10] = golf;

    t_case skate;
    skate=creation_case(11, 200, 0, 0,9, "Skate", 15 , 0, 100, 25, 0, 0, 0, 0, 0);
    plateau[11] = skate;

    t_case tir_a_l_arc;
    tir_a_l_arc=creation_case(12, 160, 100, 110,3, "Tir a l'arc",5 , 15, 80, 12, 60, 180, 500, 700, 900);
    plateau[12] = tir_a_l_arc;

    t_case lutte;
    lutte=creation_case(13, 180, 100, 110, 4, "Lutte",8 , 15, 90, 14, 70, 200, 550, 700, 950);
    plateau[13] = lutte;

    t_case comite_olympique1;
    comite_olympique1 = creation_case(14, 0, 0, 0, 10, "Comite olympique",9 , 15, 0, 0, 0, 0, 0, 0, 0);
    plateau[14] = comite_olympique1;

    t_case halterophilie;
    halterophilie=creation_case(15, 200, 100, 110, 4, "Halterophilie", 8, 15, 100, 16, 80, 220, 600, 800, 1000);
    plateau[15] = halterophilie;

    t_case village_olympique;
    village_olympique = creation_case(16, 0, 0, 0, 13, "Village olympique",7, 0, 0, 0, 0, 0, 0, 0, 0);
    plateau[16] = village_olympique;

    t_case Volley;
    Volley=creation_case(17, 220, 150, 165, 5, "Volley",4 , 15, 110, 18, 90, 250, 700, 875, 1050);
    plateau[17] = Volley;

    t_case handball;
    handball=creation_case(18, 220, 150, 165, 5, "Handball",4, 15, 120, 18, 90, 250, 700, 875, 1050);
    plateau[18] = handball;

    t_case escalade;
    escalade=creation_case(19, 200, 0, 0,9, "Escalade", 15, 0, 100, 25, 0, 0, 0, 0, 0);
    plateau[19] = escalade;

    t_case amende;
    amende = creation_case(20, 0, 0, 0, 14, "Amende", 12, 15, 0, 0, 0, 0, 0, 0, 0);
    plateau[20] = amende;

    t_case corruption2;
    corruption2 = creation_case(5, 0, 0, 0, 11, "Corruption",13, 15, 0, 0, 0, 0, 0, 0, 0);
    plateau[21] = corruption2;

    t_case judo;
    judo=creation_case(22, 260, 150, 165,6, "Judo", 14, 0, 130, 22, 110, 330, 800, 975, 1150);
    plateau[22] = judo;

    t_case boxe;
    boxe=creation_case(23, 280, 150, 165,6, "Boxe", 14, 0, 140, 24, 120, 360, 850, 1025, 1200);
    plateau[23] = boxe;

    t_case controle_dopage;
    controle_dopage = creation_case(24, 0, 0, 0, 15, "Controle dopage",7,0, 0, 0, 0, 0, 0, 0, 0);
    plateau[24] = controle_dopage;

    t_case basket;
    basket=creation_case(25, 300, 200, 220, 7, "Basket" ,2, 15, 150, 26, 130, 390, 900, 1100, 1275);
    plateau[25] = basket;

    t_case foot;
    foot=creation_case(26, 300, 200, 220, 7, "Foot", 2, 15, 150, 26, 130, 390, 900, 1100, 1275);
    plateau[26] = foot;

    t_case surf;
    surf=creation_case(27, 200, 0, 0,9, "Surf",15, 0, 100, 25, 0, 0, 0, 0, 0);
    plateau[27] = surf;

    t_case rugby;
    rugby=creation_case(28, 320, 200, 220, 7, "Rugby", 2, 15, 160, 28, 150, 450, 1000, 1200, 1400);
    plateau[28] = rugby;

    t_case athletisme;
    athletisme=creation_case(29, 350, 200, 220, 8, "Athletisme",1,15, 175, 35, 175, 500, 1100, 1300, 1500);
    plateau[29] = athletisme;

    t_case comite_olympique2;
    comite_olympique2 = creation_case(5, 0, 0, 0, 10, "Comite olympique",9,15, 0, 0, 0, 0, 0, 0 , 0);
    plateau[30] = comite_olympique2;

    t_case natation;
    natation=creation_case(31, 400, 200, 220, 8, "Natation",1,15, 200, 50, 200, 600, 1400, 1700, 2000);
    plateau[31] = natation;
}

// fonction creation tableau joueur
void creation_tab_joueur(t_joueur tab_joueur[]) // NATHAN fait
{
    /* Créée le tableau de joueurs, permet de choisir le nombre de joueur
       Prend en paramètre la tableau des joueurs
       Ne renvoie rien
    */
    char choix[10];
    do
    {
        printf("Combien de joueurs vont jouer ?\nIl doit y avoir minimum 2 joueurs et maximum 4 joueurs : ");
        fflush(stdin);
        gets(choix);
    } while (((choix[0] != 50) && (choix[0] != 51) && (choix[0] != 52)) || (strlen(choix) > 1)); // 48 = 0 en code ascii
    if (choix[0] == 50) // 2 joueurs
    {
        tab_joueur[0] = creation_joueur(1);
        tab_joueur[1] = creation_joueur(2);

        t_joueur j3;
        strcpy(j3.nom, "j3");
        j3.numero = 3;
        j3.position=0;
        j3.argent=1500;
        j3.en_prison=false;
        j3.tour_prison=0;
        j3.carte_sortie_prison=0;
        j3.en_faillite = true;
        tab_joueur[2] = j3;

        t_joueur j4;
        strcpy(j4.nom, "j4");
        j4.numero = 3;
        j4.position=0;
        j4.argent=1500;
        j4.en_prison=false;
        j4.tour_prison=0;
        j4.carte_sortie_prison=0;
        j4.en_faillite = true;
        tab_joueur[3] = j4;



    }
    if (choix[0] == 51) // 3 joueurs
    {
        tab_joueur[0] = creation_joueur(1);
        tab_joueur[1] = creation_joueur(2);
        tab_joueur[2] = creation_joueur(3);

        t_joueur j4;
        strcpy(j4.nom, "j4");
        j4.numero = 3;
        j4.position=0;
        j4.argent=1500;
        j4.en_prison=false;
        j4.tour_prison=0;
        j4.carte_sortie_prison=0;
        j4.en_faillite = true;
        tab_joueur[3] = j4;

    }
    if (choix[0] == 52) // 4 joueurs
    {
        tab_joueur[0] = creation_joueur(1);
        tab_joueur[1] = creation_joueur(2);
        tab_joueur[2] = creation_joueur(3);
        tab_joueur[3] = creation_joueur(4);
    }

}

// fonction affichage d'instance
void afficher_joueur(t_joueur j) // LUC fait
{
    /* Procédure qui affiche une instance de joueur
       Prend en paramètre un joueur
       Ne renvoie rien
    */
    printf("Voici le JOUEUR:\n");
    printf("nom:%s\nnumero:%d\nposition:%d\nargent:%d\netes-vous en prison?:%d\ncombien de tour en prison:%d\nnb de cartes sorites de prison:%d\nfaillite: %d\n",j.nom,j.numero,j.position,j.argent,j.en_prison,j.tour_prison,j.carte_sortie_prison, j.en_faillite);
    printf("\n"); //pour de la lisibilité
}

// fonction affichage d'instance
void afficher_case(t_case c) // LUC fait
{
    /* Procédure qui affiche une instance de case
       Prend en paramètre une case
       Ne renvoie rien
    */
    printf("Voici la CASE:\n");
    printf("nom: %s\nposition:%d\nprix d'achat:%d\nnum joueur la possedant:%d\nnombre de maison:%d\nya til un hotel:%d\nprix dachat d'une maison:%d\nprix d'achat d'un hotel:%d\nquel groupe de carte:%d\nvaleur de l'hypotheque:%d\nHypotheque:%d",c.nom,c.position,c.valeur,c.num_joueur,c.nb_maison,c.nb_hotel,c.val_maison,c.val_hotel,c.groupe_cartes, c.val_hypotheque, c.hypoteque);
    printf("Loyer avec 1 maison:%d\nLoyer avec 2 maison:%d\nLoyer avec 3 maison:%d\nLoyer avec 4 maison:%d\nLoyer avec 1 hotel:%d\n", c.loyer_1_maison, c.loyer_2_maison, c.loyer_3_maison, c.loyer_4_maison, c.loyer_1_hotel);
    printf("\n"); //pour de la lisibilité
}

// fonction affichage dans le jeu
void afficher_case_jeu(t_case c) // LUC fait
{
    /* Procédure qui affiche une instance de case
       Prend en paramètre une case
       Ne renvoie rien
    */
    printf("Nom : %s \nPrix d'achat : %d\nNombre de maison : %d\nNombre d'Hotel : %d\nPrix d'achat maison : %d\nPrix d'achat hotel : %d\nQuel groupe de carte : %d\nLoyer sans maison : %d\n",c.nom,c.valeur,c.nb_maison,c.nb_hotel,c.val_maison,c.val_hotel,c.groupe_cartes, c.base_loyer);
    printf("Loyer avec 1 maison : %d\nLoyer avec 2 maison : %d\nLoyer avec 3 maison : %d\nLoyer avec 4 maison : %d\nLoyer avec 1 hotel : %d\n", c.loyer_1_maison, c.loyer_2_maison, c.loyer_3_maison, c.loyer_4_maison, c.loyer_1_hotel);

    if (c.hypoteque == true)
    {
        printf("Cette propriete a ete hypotheque\n");
    }
    printf("\n"); //pour de la lisibilité
}

// fonction affichage d'instance
void afficher_banque(t_banque banque) // LUC fait
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
void lance_de(int* de) // NATHAN fait
{
    /* Procédure qui prend en paramètre une liste de 2 dé et qui les lance
       Prend en paramètre la liste de dé
       Ne renvoie rien
    */
    de[0] = (rand()%6)+1;
    de[1] = (rand()%6)+1;

}

// fonction pour les dés
bool double_de(int* de) // NATHAN
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

// fonction pour loyer
bool loyer(t_joueur tab_joueur[], int i, t_case plateau[], t_banque* p_banque) // Maxime il faut rajouter faillite
{
    /* Permet de faire payer un joueur si il est sur la case d'un autre joueur
       Prend en paramèètre le tableau de joueur, l'indice du joueur qui joue et le plateau
       revoie un booleen
    */
    int option;
    if ((plateau[tab_joueur[i].position].num_joueur != tab_joueur[i].numero) && (plateau[tab_joueur[i].position].num_joueur != 0) && (plateau[tab_joueur[i].position].groupe_cartes <= 8))//regarde si la case appartient a quelqu'un d'autre que le joueur et si c'est une propriete
    {
        //regarde combien il y a de maison et d'hotels sur la case
        if(plateau[tab_joueur[i].position].nb_maison == 0 && plateau[tab_joueur[i].position].nb_hotel == 0)
        {
           option = 0;
        }
        else if(plateau[tab_joueur[i].position].nb_maison == 1 && plateau[tab_joueur[i].position].nb_hotel == 0)
        {
            option = 1;
        }
        else if(plateau[tab_joueur[i].position].nb_maison == 2 && plateau[tab_joueur[i].position].nb_hotel == 0)
        {
            option = 2;
        }
        else if(plateau[tab_joueur[i].position].nb_maison == 3 && plateau[tab_joueur[i].position].nb_hotel == 0)
        {
            option = 3;
        }
        else if(plateau[tab_joueur[i].position].nb_maison == 4 && plateau[tab_joueur[i].position].nb_hotel == 0)
        {
            option = 4;
        }
        else if(plateau[tab_joueur[i].position].nb_maison == 0 && plateau[tab_joueur[i].position].nb_hotel == 1)
        {
            option = 5;
        }
        switch(option)
        {
            case 0: // 0 maison 0 hotel
            {
                if(tab_joueur[i].argent >= plateau[tab_joueur[i].position].base_loyer)
                {
                    tab_joueur[i].argent -= plateau[tab_joueur[i].position].base_loyer;
                    tab_joueur[plateau[tab_joueur[i].position].num_joueur-1].argent += plateau[tab_joueur[i].position].base_loyer;
                }/*
                else
                {
                    en_faillite(tab_joueur, i, cases.base_loyer, banque, cases.num_joueur);
                }*/
                break;
            }
            case 1: // 1 maison
            {
                if(tab_joueur[i].argent >= plateau[tab_joueur[i].position].loyer_1_maison)
                {
                    tab_joueur[i].argent -= plateau[tab_joueur[i].position].loyer_1_maison;
                    tab_joueur[plateau[tab_joueur[i].position].num_joueur-1].argent += plateau[tab_joueur[i].position].loyer_1_maison;
                }/*
                else
                {
                    //en_faillite(tab_joueur, i, cases.loyer_1_maison, banque, cases.num_joueur);
                    continue;
                }*/
                break;
            }
            case 2: // 2 maisons
            {
                if(tab_joueur[i].argent >= plateau[tab_joueur[i].position].loyer_2_maison)
                {
                    tab_joueur[i].argent -= plateau[tab_joueur[i].position].loyer_2_maison;
                    tab_joueur[plateau[tab_joueur[i].position].num_joueur].argent += plateau[tab_joueur[i].position].loyer_2_maison;
                }/*
                else
                {
                    //en_faillite(tab_joueur, i, plateau[tab_joueur[i].position].loyer_2_maison, banque, plateau[tab_joueur[i].position].num_joueur);
                    continue;
                }*/
                break;
            }
            case 3: // 3 maisons
            {
                if(tab_joueur[i].argent >= plateau[tab_joueur[i].position].loyer_3_maison)
                {
                    tab_joueur[i].argent -= plateau[tab_joueur[i].position].loyer_3_maison;
                    tab_joueur[plateau[tab_joueur[i].position].num_joueur-1].argent += plateau[tab_joueur[i].position].loyer_3_maison;
                }/*
                else
                {
                    //en_faillite(tab_joueur, i, cases.loyer_3_maison, banque, cases.num_joueur);
                    continue;
                }*/
                break;
            }
            case 4: // 4 maisons
            {
                if(tab_joueur[i].argent >= plateau[tab_joueur[i].position].loyer_4_maison)
                {
                    tab_joueur[i].argent -= plateau[tab_joueur[i].position].loyer_4_maison;
                    tab_joueur[plateau[tab_joueur[i].position].num_joueur-1].argent += plateau[tab_joueur[i].position].loyer_4_maison;
                }/*
                else
                {
                    //en_faillite(tab_joueur, i, cases.loyer_4_maison, banque, cases.num_joueur);
                    continue;
                }*/
                break;
            }
            case 5: // 0 maisons 1 hotel
            {
                if(tab_joueur[i].argent >= plateau[tab_joueur[i].position].loyer_1_hotel)
                {
                    tab_joueur[i].argent -= plateau[tab_joueur[i].position].loyer_1_hotel;
                    tab_joueur[plateau[tab_joueur[i].position].num_joueur-1].argent += plateau[tab_joueur[i].position].loyer_1_hotel;
                }/*
                else
                {
                    //en_faillite(tab_joueur, i, cases.loyer_1_hotel, banque, cases.num_joueur);
                    continue;
                }*/
                break;
            }
        }
        return true;
    }
    // Si c'est une gare
    else if((plateau[tab_joueur[i].position].num_joueur != tab_joueur[i].numero) && (plateau[tab_joueur[i].position].num_joueur != 0) && (plateau[tab_joueur[i].position].groupe_cartes == 9))//regarde si la case appartient a quelqu'un d'autre et si cest une gare
    {
        int nb_gare = nb_gare_joueur(plateau, plateau[tab_joueur[i].position].num_joueur);
        if(nb_gare == 1) // Si 1 gare
        {
            if(tab_joueur[i].argent >= 25)
            {
                tab_joueur[i].argent -= 25;
                tab_joueur[plateau[tab_joueur[i].position].num_joueur-1].argent += 25;
            }/*
            else
            {
                //en_faillite(tab_joueur, i, 25, banque, cases.num_joueur);
                continue;
            }*/
        }
        else if(nb_gare == 2) // Si 2 gares
        {
            if(tab_joueur[i].argent >= 50)
            {
                tab_joueur[i].argent -= 50;
                tab_joueur[plateau[tab_joueur[i].position].num_joueur-1].argent += 50;
            }/*
            else
            {
                //en_faillite(tab_joueur, i, 50, banque, cases.num_joueur);
                continue;
            }*/
        }
        else if(nb_gare ==3) // Si 3 gardes
        {
            if(tab_joueur[i].argent >= 100)
            {
                tab_joueur[i].argent -= 100;
                tab_joueur[plateau[tab_joueur[i].position].num_joueur-1].argent += 100;
            }/*
            else
            {
                //en_faillite(tab_joueur,i,100, banque, cases.num_joueur);
                continue;
            }*/
        }
        else if(nb_gare ==4) // Si 4 gares
        {
            if(tab_joueur[i].argent >= 200)
            {
                tab_joueur[i].argent -= 200;
                tab_joueur[plateau[tab_joueur[i].position].num_joueur-1].argent += 200;
            }/*
            else
            {
                //en_faillite(tab_joueur, i, 200, banque, cases.num_joueur);
                continue;
            }*/
        }
        return true;
    }
    else // Si pas sur la propriété d'un autre joueur
    {
        //printf("Vous n'etes pas sur la case de quelqu'un d'autre, vous ne payez pas\n");
        return false;
    }
}

// Fonction de tour
void tour(t_joueur tab_joueur[], t_case plateau[], t_banque* p_banque, char* liste_corruption[], char* liste_comite[]) // NATHAN a refaire voir feuille dans pochette
{
    /* Procédure qui fait un tour à tout les joueurs
       Prend en paramèètre le tableau des joueurs, le plateau et la banque
       Ne renvoie rien
    */
    for (int i = 0; i < 4; i++)
    {


        if (tab_joueur[i].en_faillite)
        {
            // Le joueur ne joue pas

        }
        else
        {
            // Le joueur joue*
            system("cls");
            printf("\n\n\n\n\n\n\n                                                                           C'est le tour de %s\n\n", tab_joueur[i].nom);
            sleep(3);
            int de[2];
            lance_de(de);
            afficher_plateau(plateau, tab_joueur);
            sleep(2);
            if (sortie_prison(de, tab_joueur, i, plateau, p_banque)) // Le joueur sors de prison donc ne joue pas plus pendant ce tour
            {
                afficher_plateau(plateau, tab_joueur);
            }
            else // Le joueur n'est pas en prison                       // continue ici
            {
                // Le joueur joue une fois
                system("cls");
                deplacement(de, tab_joueur, i);
                afficher_plateau(plateau, tab_joueur);
                afficher_milieu_plateau(plateau, tab_joueur, i, de);
                gotoligcol(54, 0);
                achat(tab_joueur, plateau, i);
                afficher_milieu_plateau(plateau, tab_joueur, i, de);
                acheter_maison_hotel(tab_joueur, i, plateau, p_banque);
                afficher_milieu_plateau(plateau, tab_joueur, i, de);
                gotoligcol(54, 0);
                //hypotheque(tab_joueur, i, plateau, p_banque);
                sleep(4);
                if (double_de(de)) // Le joueur a fait un double
                {
                    system("cls");
                    // Le joueur joue une 2eme fois

                    if (double_de(de)) // Le joueur a fait 2 doubles
                    {
                        // Le joueur joue une 3eme fois

                        if (double_de(de))
                        {
                            printf("Vous allez en prison");
                            entrer_prison(tab_joueur, i);
                        }
                    }
                }
            }
        }
    }
}

// fonction pour les tours
bool acheter_maison_hotel(t_joueur tab_joueur[], int i, t_case plateau[], t_banque* banque) // MAXIME fait
{
//La fonction permet au joueur d’acheter une maison ou un hôtel (elle lui demande)
//Prend en paramètre un pointeur sur le joueur, le plateau, un pointeur sur la banque)
//renvoie un booleen(true si il a achete false sinon)
    if(plateau[tab_joueur[i].position].groupe_cartes <=8)//regarde si c'est bien des propriete
    {
        if (plateau[tab_joueur[i].position].num_joueur == tab_joueur[i].numero)//la case appartient au joueur
        {
            if((plateau[tab_joueur[i].position].nb_maison <= 3) && (plateau[tab_joueur[i].position].nb_hotel ==0))//regarde si il y a 3 maison ou moins et pas d'hotel
            {
                if(banque->nb_maison_restante!= 0)//regarde si il reste des maisons dans la banque
                {
                    if(tab_joueur[i].argent >= plateau[tab_joueur[i].position].val_maison)// regarde si le joueur a assez d'argent
                    {
                        char choix[10];
                        do
                        {
                            printf("vous pouvez acheter une medaille. voulez-vous en acheter une? oui[1]  non[0]\n");//propose d'acheter une maison
                            fflush(stdin);
                            gets(choix);
                        } while (((choix[0] != 48) && (choix[0] != 49)) || (strlen(choix) > 1)); // 48 = 0 en code ascii
                        if(choix[0] == 49) // Le joueur veut acheter une maison
                        {
                            plateau[tab_joueur[i].position].nb_maison+=1;//ajoute une maison
                            tab_joueur[i].argent-=plateau[tab_joueur[i].position].val_maison;//enleve l'argent au joueur
                            banque->nb_maison_restante-=1;//enleve une maison de la banque
                            printf("vous avez achete une medaille.\n");
                            printf("Il y a %d medaille sur la case\n", plateau[tab_joueur[i].position].nb_maison);
                            return true;
                        }
                        else if(choix[0] == 48) // Si le joueur ne veut pas acheter une maison
                        {
                            printf("vous n'avez pas achete de medaille.\n");
                            return false;
                        }
                    }
                    else//il n'a pas assez d'argent
                    {
                        printf("argent joueur : %d\ncout medaille : %d\n",tab_joueur[i].argent, plateau[tab_joueur[i].position].val_maison);
                        printf("vous n'avez pas assez d'argent\n");
                        return false;
                    }
                }
                else if(banque->nb_maison_restante == 0)//il n'y a plus de maison
                {
                    printf("il n'y a plus de medaille disponible\n");
                    return false;
                }
            }
            else if((plateau[tab_joueur[i].position].nb_maison == 4) && (plateau[tab_joueur[i].position].nb_hotel == 0))//regarde si il y a 4 maison et aucun hotel
            {
                if(banque->nb_hotel_restant != 0)//regarde si il reste des hotels dans la banque
                {
                    if(tab_joueur[i].argent >= plateau[tab_joueur[i].position].val_hotel)//regarde si le joueur a assez d'argent
                    {
                        char choix[10];
                        do
                        {
                            printf("vous pouvez acheter une double medaille d'or. voulez-vous acheter une double medaille d'or ? oui[1]  non[0]\n");
                            fflush(stdin);
                            gets(choix);
                        } while (((choix[0] != 48) && (choix[0] != 49)) || (strlen(choix) > 1)); // 48 = 0 en code ascii
                        if(choix[0] == 49) // Le joueur veut acheter un hotel
                        {
                            plateau[tab_joueur[i].position].nb_hotel+=1;//ajoute l'hotel
                            plateau[tab_joueur[i].position].nb_maison = 0;//on retire les maison
                            tab_joueur[i].argent-=plateau[tab_joueur[i].position].val_hotel;//on enleve l'argent au joueur
                            banque->nb_hotel_restant-=1;//eneleve un hotel de la banque
                            banque->nb_maison_restante+=4;//rajoute les 4 maison a la banque
                            printf("vous avez achete une double medaille d'or.\n");
                            return true;
                        }
                        else if(choix[0] == 48) // Si le joueur ne veut pas acheter d'hotel
                        {
                            printf("vous n'avez pas achete une double medaille d'or.\n");
                            return false;
                        }
                    }
                    else //le joueur n'a pas assez d'argent pour acheter un hotels
                    {
                        printf("vous n'avez pas assez d'argent\n");
                        return false;
                    }
                }
                else if(banque->nb_hotel_restant == 0)//il n'y a plus d'hotels dans la banque
                {
                    printf("il n'y a plus de double medaille d'or dans la banque\n");
                    return false;
                }
            }
            else if(plateau[tab_joueur[i].position].nb_hotel == 1)//le joueur possede 1 hotels
            {
                printf("vous ne pouvez rien faire de plus. vous avez deja un hotels\n");
                return false;
            }
        }
        else if(plateau[tab_joueur[i].position].num_joueur != tab_joueur[i].numero) // La case appartient à un autre joueur ou à personne
        {
            return false;
        }
    }
    else // Ce n'est pas une propriete
    {
        return false;
    }
    return false;
}

// Fonction affichage
void gotoligcol( int lig, int col ) // MAXIME fait
{
    /* Va a l'emplacement
       Prend en parametre la ligne et la colonne
       Ne renvoie rien
    */
    COORD mycoord;

    mycoord.X = col;

    mycoord.Y = lig;

    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );

}

// Fonction d'affichage
void Color(int couleurDuTexte,int couleurDeFond) // MAXIME fait
{
    /* Change la couleur du fond
       Prend en paramètre la couleur du texte et du fond
       Ne renvoie rien
    */
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

// Fonction d'affichage
int Longueur(int Valeur) // MAXIME fait
{
    /* calcul le nombre de caractère d'un nombre
       Prend en paramètre le nombre
       Renvoie le nombre de charactère du nombre
    */
	int Retour = 0;
	if(Valeur == 0)
    {
        Retour = 1;
    }
	while(Valeur !=0)
	{
		Retour++;
		Valeur = Valeur / 10;
	}

	return Retour;
}

// Fonction d'affichage
void afficher_valeur_case(int indice, t_case plateau[]) // MAXIME fait
{
    /* Affiche la valeur de la case
       Prend en paramètre l'indice de la case et le plateau
       Ne renvoie rien
    */
    Color(plateau[indice].couleur_texte,plateau[indice].couleur_fond);
    printf("%d",plateau[indice].valeur);
    for(int z = Longueur(plateau[indice].valeur); z<18;z++)
    {
        printf(" ");
    }
    Color(15,0);//re-met en noir et blanc
    printf("|");
}

// Fonction d'affichage
void afficher_nom_proprietaire(int indice, t_case plateau[], t_joueur tab_joueur[], int num_joueur) // MAXIME fait
{
    /* Permet d'afficher le nom du propriétaire de la case
       Prend en paramètre l'indice du joueur, le plateau, le tableau de joueur et le numero du joueur
       Ne renvoie rien
    */
    Color(plateau[indice].couleur_texte, plateau[indice].couleur_fond);
    printf("%s",tab_joueur[num_joueur].nom);
    if(plateau[indice].nb_maison == 1) // medaille choco
    {
        printf("(4)");
    }
    else if(plateau[indice].nb_maison == 2) // medaille bronze
    {
        printf("(4)");
        printf("(3)");
    }
    else if(plateau[indice].nb_maison == 3) // medaille argent
    {
        printf("(4)");
        printf("(3)");
        printf("(2)");
    }
    else if(plateau[indice].nb_maison == 4) // Medaille or
    {
        printf("(4)");
        printf("(3)");
        printf("(2)");
        printf("(1)");
    }
    else if(plateau[indice].nb_hotel == 1) // double medaille d'or
    {
        printf("(1)(1)");
    }
    for(int z = strlen(tab_joueur[num_joueur].nom)+(plateau[indice].nb_maison*3)+(plateau[indice].nb_hotel*6); z<18;z++)
    {
        printf(" ");
    }
    Color(15,0);
    printf("|");
}

//fonction d'affichage
void creation_sous_case1(t_case plateau[], t_joueur tab_joueur[], int i) // MAXIME fait
{
//permet d'afficher la premiere ligne du plateau
//prends en parametre le plateau, le tableau des joueur et l'indice i
//ne renvoie rien
    Color(plateau[i].couleur_texte,plateau[i].couleur_fond);//permet de prendre les couleur attribue a chaque case
    printf("%s", plateau[i].nom);//affiche le nom de chaque case
    for(int j = strlen(plateau[i].nom); j<18; j++)//permet de faire que chaque case ai la meme longueur
    {
        printf(" ");
    }
    Color(15,0);//re-met en noir et blanc
    printf("|");
    if(i == 8)
    {
        for (int l = 0; l<4; l++)//affiche les 4 ligne sous le nom de la case
        {
            printf("|");
            for(int k = 0;k<9;k++)//permet de parcourir l'indice des cases pour pouvoir recuperer les couleur attribue a chaque case
            {
                Color(plateau[k].couleur_texte,plateau[k].couleur_fond);
                if ((tab_joueur[l].position == k) && (tab_joueur[l].en_faillite == false))//regarde si le joueur a fait faillite
                {
                    printf("%s", tab_joueur[l].nom);
                    for(int j = strlen(tab_joueur[l].nom); j<18; j++)//permet de faire que chaque case ai la meme longueur
                    {
                        printf(" ");
                    }
                }
                else
                {
                    printf("                  ");
                }


                Color(15,0);//re-met en noir et blanc
                printf("|");
            }
        }
        //permet d'afficher la 5e ligne sous les cases
        printf("|");
        for(int k =0;k<9;k++)
        {
            if (plateau[k].groupe_cartes <= 9)
            {
                 if(plateau[k].num_joueur == 0)// || plateau[k].num_joueur != 1 || plateau[k].num_joueur != 2 || plateau[k].num_joueur != 3)
                {
                    afficher_valeur_case(k,plateau);
                }
                else
                {
                    afficher_nom_proprietaire(k,plateau, tab_joueur, plateau[k].num_joueur-1);
                }
            }
            else
            {
                Color(plateau[k].couleur_texte,plateau[k].couleur_fond);
                printf("                  ");
                Color(15,0);//re-met en noir et blanc
                printf("|");

            }
        }
    }
}

//fonction d'affichage
void creation_sous_case2(t_case plateau[], t_joueur tab_joueur[], int i) // MAXIME fait
{
//permet d'afficher les 2 colonnes sur les cote du plateau
//prends en parametre le plateau, le tableau des joueur et l'indice i
//ne renvoie rien
    Color(plateau[40-i].couleur_texte,plateau[40-i].couleur_fond);//permet de prendre les couleur attribue a chaque case
    printf("%s", plateau[40-i].nom);//affiche le nom de chaque case
    for(int j = strlen(plateau[40-i].nom); j<18; j++)//permet de faire que chaque case ai la meme longueur
    {
        printf(" ");
    }
    Color(15,0);//re-met en noir et blanc
    printf("|");
    for(int z = 0; z<=131;z++)//permet de faire l'espace entre les 2 colonnes
        {
            printf(" ");
        }
    printf("|");
    Color(plateau[i].couleur_texte,plateau[i].couleur_fond);//permet de prendre les couleur attribue a chaque case
    printf("%s", plateau[i].nom);//affiche le nom de chaque case
    for(int j = strlen(plateau[i].nom); j<18; j++)//permet de faire que chaque case ai la meme longueur
    {
        printf(" ");
    }
    Color(15,0);//re-met en noir et blanc
    printf("|");
    for (int l = 0; l<4; l++)//permet de faire les 4 lignes sous le nom des cases
    {
        printf("|");
        Color(plateau[40-i].couleur_texte,plateau[40-i].couleur_fond);//permet de prendre  les couleur attribue a chaque case
        if ((tab_joueur[l].position == 40-i) && (tab_joueur[l].en_faillite == false))//regarde si le joueur a fait faillite
        {
            printf("%s", tab_joueur[l].nom);
            for(int j = strlen(tab_joueur[l].nom); j<18; j++)//permet de faire que chaque case ai la meme longueur
            {
                printf(" ");
            }
       }
        else
        {
            printf("                  ");
        }
        Color(15,0);//re-met en noir et blanc
        printf("|");
        for(int z = 0; z<=131;z++)//permet de faire l'espace entre les 2 colonnes
        {
            printf(" ");
        }
        printf("|");
        Color(plateau[i].couleur_texte,plateau[i].couleur_fond);//permet de prendre les couleur attribue a chaque case
        if ((tab_joueur[l].position == i) && (tab_joueur[l].en_faillite == false))//regarde si le joueur a fait faillite
        {
            printf("%s", tab_joueur[l].nom);
            for(int j = strlen(tab_joueur[l].nom); j<18; j++)//permet de faire que chaque case ai la meme longueur
            {
                printf(" ");
            }
       }
        else
        {
            printf("                  ");
        }
        Color(15,0);//re-met en noir et blanc
        printf("|");
    }
    //permet de creer la 5e ligne sous les cases
    printf("|");
    if (plateau[40-i].groupe_cartes <= 9)
    {
         if(plateau[40-i].num_joueur == 0)
        {
            afficher_valeur_case(40-i,plateau);
        }
        else
        {
            afficher_nom_proprietaire(40-i,plateau, tab_joueur, plateau[40-i].num_joueur-1);
        }
    }
    else
    {
        Color(plateau[40-i].couleur_texte,plateau[40-i].couleur_fond);
        printf("                  ");
        Color(15,0);//re-met en noir et blanc
        printf("|");
    }
    for(int z = 0; z<=131;z++)
    {
        printf(" ");
    }
    printf("|");
    if (plateau[i].groupe_cartes <= 9)
    {
         if(plateau[i].num_joueur == 0)
        {
            afficher_valeur_case(i,plateau);
        }
        else
        {
            afficher_nom_proprietaire(i,plateau, tab_joueur, plateau[i].num_joueur-1);
        }
    }
    else
    {
        Color(plateau[i].couleur_texte,plateau[i].couleur_fond);
        printf("                  ");
        Color(15,0);//re-met en noir et blanc
        printf("|");
    }
}

//fonction d'affichage
void creation_sous_case3(t_case plateau[], t_joueur tab_joueur[], int i) // MAXIME fait
{
//permet d'afficher la derniere ligne du plateau
//prends en parametre le plateau, le tableau des joueur et l'indice i
//ne renvoie rien
    i = i-16;//pour mettre i =0 puis i=1 etc jusqu'a i=8
    if(i == 0)//permet d'afficher la premiere barre de la ligne
    {
        printf("|");
    }
    Color(plateau[24-(i*1)].couleur_texte,plateau[24-(i*1)].couleur_fond);//permet de prendre les couleur attribue a chaque case
    printf("%s", plateau[24-(i*1)].nom);//affiche le nom de chaque case
    for(int j = strlen(plateau[24-(i*1)].nom); j<18; j++)//permet de faire que chaque case ai la meme longueur
    {
        printf(" ");
    }
    Color(15,0);//re-met en noir et blanc
    printf("|");
    if(i == 8)//quand on arrive a la derniere case de la ligne
    {
        for (int l = 0; l<4; l++)//permet d'afficher les 4 ligne sous le nom de la case
        {
            printf("|");
            for(int k = 16;k<25;k++)
            {
                Color(plateau[40-k].couleur_texte,plateau[40-k].couleur_fond);//permet de prendre la couleur de la case
                if ((tab_joueur[l].position == 40-k) && (tab_joueur[l].en_faillite == false))//regarde si le joueur a fait faillite ou pas
                {
                    printf("%s", tab_joueur[l].nom);
                    for(int j = strlen(tab_joueur[l].nom); j<18; j++)//permet de faire que chaque case ai la meme longueur
                    {
                        printf(" ");
                    }
                }
                else
                {
                    printf("                  ");
                }
                Color(15,0);//re-met en noir et blanc
                printf("|");
            }
        }
        printf("|");
        for(int k = 16;k<25;k++)
        {
            if (plateau[40-k].groupe_cartes <= 9)
            {
                if(plateau[40-k].num_joueur == 0)
                {
                    afficher_valeur_case(40-k,plateau);
                }
                else
                {
                    afficher_nom_proprietaire(40-k,plateau, tab_joueur, plateau[40-k].num_joueur-1);
                }
            }
            else
            {
                Color(plateau[40-k].couleur_texte,plateau[40-k].couleur_fond);
                printf("                  ");
                Color(15,0);//re-met en noir et blanc
                printf("|");
            }
        }
    }
}

// Fonction d'affichage
void afficher_plateau(t_case plateau[], t_joueur tab_joueur[]) // MAXIME fait
{
//la fonction permet d'afficher le plateau
//prend en parametre le plateau et le tableau des joueurs
//ne renvoie rien
    printf("|");//fait la premiere barre(en haut a gauche)
    for(int i=0;i<25 ; i++)
    {
        if(i <= 8)//permet de creer la premiere ligne
        {
            creation_sous_case1(plateau,tab_joueur,i);
        }
        else if(i >=9 && i <= 15)//permet de creer les 2 colonnes sur les coté
        {
            printf("|");
            creation_sous_case2(plateau, tab_joueur, i);
        }
        else if(i>= 16 && i<= 24)//permet de creer la derniere ligne
        {
            creation_sous_case3(plateau,tab_joueur,i);
        }
    }
}

// fonction d'affichage
void afficher_milieu_plateau(t_case plateau[], t_joueur tab_joueur[],int i, int de[]) // NATHAN en cours
{
    /* Permet d'afficher des choses au milieu du plateau
       Prend en paramètre le plateau et le tableau de joueur
       Ne renvoie rien
    */

    gotoligcol(16, 80);
    printf("%s", tab_joueur[i].nom);
    gotoligcol(18, 75);
    printf("Vous avez fait %d et %d", de[0], de[1]);
    gotoligcol(20, 75);
    printf("Vous etes a la case %s", plateau[tab_joueur[i].position].nom);
    gotoligcol(22, 75);
    printf("Vous avez %de", tab_joueur[i].argent);
    gotoligcol(7, 21);
    printf("Legende medaille : ");
    gotoligcol(8, 21);

    printf("(4) : Medaille en chocolat");
    gotoligcol(9, 21);
    Color(4, 0);
    printf("(3) : Medaille en bronze");
    gotoligcol(10, 21);
    Color(7, 0);
    printf("(2) : Medaille en argent");
    gotoligcol(11, 21);
    printf("(1) : Medaille en or");
    gotoligcol(12, 21);
    printf("(1)(1) : Double medailles en or");

}

// fonction de jeu
bool hypotheque(t_joueur tab_joueur[],int i, t_case plateau[], t_banque* p_banque) // NATHAN fait
{
    /* fonction qui permet d'hypotéquer une propriétée
       Prend en paramètre le tableau de joueur, le numero du joueur qui joue, le plateau, un pointeur sur la banque
       Renvoie un bool, True si il a hypotéqué, false sinon
    */
    char choix[10];
    do
    {
        printf("\nVoulez vous hypotequez une propriete oui[1]  non[0]\n");//propose d'hypotéquer
        fflush(stdin);
        gets(choix);
    } while (((choix[0] != 48) && (choix[0] != 49)) || (strlen(choix) > 1)); // 48 = 0 en code ascii
    if (choix[0] == 48) // Ne veut pas hypothéquer
    {
        return false;
    }
    int long_prop = update_propriete(tab_joueur, i, plateau);
    if (long_prop == 0) // Si pas de propriete renvoie false
    {
        printf("Vous n'avez pas de propriete a hypothequer\n");
        return false;
    }
    printf("Vous avez %d proprietes, laquelle voulez vous hypotequer ?\n\n", long_prop);
    for (int j = 0; j < long_prop; j++) // affiche toutes les proprietes du joueur
    {
        printf("\nLa propriete numero %d : \n", j+1);
        afficher_case_jeu(tab_joueur[i].proprietes[j]);
    }

    do
    {
        printf("\nDonnez le numero de la propriete que vous souhaitez hypotheque : ");//propose d'hypotéquer
        printf("Si vous souhaitez quitter[0]\n");
        fflush(stdin);
        gets(choix);
        if (tab_joueur[i].proprietes[choix[0]-49].hypoteque == 1) // Si la propriete est hypothéqué
        {
            printf("Cette propriete est deja hypotheque \n");
        }
        if (choix[0] == 48) // Si le joueur ne veut pas hypothéqué
        {
            printf("Vous n'avez pas hypotheque \n");
            return false;
        }
    } while ((choix[0] < '0') || (choix[0] > '0'+long_prop) || (strlen(choix) > 1) || (tab_joueur[i].proprietes[choix[0]-49].hypoteque == 1)); // 48 = 0 en code ascii
    for (int j = 0; j < long_prop; j++)
    {
        if ((tab_joueur[i].proprietes[choix[0]-49].groupe_cartes == tab_joueur[i].proprietes[j].groupe_cartes) && (tab_joueur[i].proprietes[choix[0]-49].position != tab_joueur[i].proprietes[j].position))
        {
            // Le joueur a une carte du même groupede couleur
            if ((tab_joueur[i].proprietes[choix[0]-49].nb_maison > 0) || (tab_joueur[i].proprietes[choix[0]-49].nb_hotel > 0))
            {
                // La propriete que le joueur hypoteque a une maison ou un hotel
                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix[0]-49].nb_maison * tab_joueur[i].proprietes[choix[0]-49].val_maison)/2 + (tab_joueur[i].proprietes[choix[0]-49].nb_hotel * tab_joueur[i].proprietes[choix[0]-49].val_hotel)/2;
                p_banque->nb_maison_restante += tab_joueur[i].proprietes[choix[0]-49].nb_maison;
                p_banque->nb_hotel_restant += tab_joueur[i].proprietes[choix[0]-49].nb_hotel;
                plateau[tab_joueur[i].proprietes[choix[0]-49].position].nb_maison = 0;
                plateau[tab_joueur[i].proprietes[choix[0]-49].position].nb_hotel = 0;
                afficher_case(plateau[tab_joueur[i].proprietes[choix[0]-49].position]);
                printf("Vos maisons et hotel sur la case %s, ont ete vendu a moitie prix\n\n", tab_joueur[i].proprietes[choix[0]-49].nom);
            }
            if ((tab_joueur[i].proprietes[j].nb_maison > 0) || (tab_joueur[i].proprietes[j].nb_hotel > 0))
            {
                // La propriete teste a une maison ou un hotel
                tab_joueur[i].argent += (tab_joueur[i].proprietes[j].nb_maison * tab_joueur[i].proprietes[j].val_maison)/2 + (tab_joueur[i].proprietes[j].nb_hotel * tab_joueur[i].proprietes[j].val_hotel)/2;
                p_banque->nb_maison_restante += tab_joueur[i].proprietes[j].nb_maison;
                p_banque->nb_hotel_restant += tab_joueur[i].proprietes[j].nb_hotel;
                plateau[tab_joueur[i].proprietes[j].position].nb_maison = 0;
                plateau[tab_joueur[i].proprietes[j].position].nb_hotel = 0;
                afficher_case(plateau[tab_joueur[i].proprietes[j].position]);
                printf("Vos maisons et hotel sur la case %s, ont ete vendu a moitie prix\n\n", tab_joueur[i].proprietes[j].nom);
            }
        }
    }
    // On donne au joueurs l'argent de l'hypothéque
    tab_joueur[i].argent += tab_joueur[i].proprietes[choix[0]-49].val_hypotheque;
    // On met la propriété en hypothéque
    plateau[tab_joueur[i].proprietes[choix[0]-49].position].hypoteque = true;
    hypotheque(tab_joueur, i, plateau, p_banque);
    return false;
}

// fonction d'instance
int update_propriete(t_joueur tab_joueur[],int i, t_case plateau[]) // NATHAN fait
{
    /* Update les propriétés dees joueurs
       Prend en paramètre le tableau de joueur, l'indice du joueur, le plateau
       Renvoie le nombre de propriétés du joueur
    */
    int nb = 0; // Nombre de propriété que le joueur a
    for (int j = 0; j < 32; j++) // Compte le nombre de propriété du joueur
    {
        if (plateau[j].num_joueur == tab_joueur[i].numero)
        {
            nb+=1;
        }
    }
    int compteur = 0;
    int total = 0;
     for (int j = 0; j < 32; j++) // Remplit le tableau de propriété du joueur
    {
        if (plateau[j].num_joueur == tab_joueur[i].numero)
        {
            tab_joueur[i].proprietes[compteur] = plateau[j];
            compteur+=1;
        }
        else // on remplit le reste du tableau avec des cases vides
        {
            tab_joueur[i].proprietes[total] = creation_case(50, 0, 0, 0, 50, "Rien", 50, 50, 0, 0,0, 0, 0, 0, 0);
        }
        total+=1;
    }
    return nb;
}

// fonction affichage
void afficher_liste(char* liste[],int i) // LUC fait
{
    /* Permet d'afficher la "carte" commité ou corruption tirée, à partir de son indice et de quelle liste elle est tirée
       Prend en paramètre une liste de chaine de caractère et l'indice de la chaine que l'on veut afficher
       Ne renvoie rien
    */
    int iterateur=0;
    while(liste[i][iterateur] != '\0')   //\0 correspond à la fin de chaine
    {
        printf("%c",liste[i][iterateur]);
        iterateur++;
    }
}

// fonction de jeu
void tirer_corruption(t_joueur tab_joueur[],int i, char* liste_corruption) // LUC fait
{
    /* Permet de tirer une carte corruption
       Prend en paramètre le tableau de joueur, l'indice du joueur qui joue et la liste de corruption
       Ne renvoie rien
    */
    int carteCorTire = rand() % 16;

    printf("Vous tirez une carte corruption:\n");

    switch(carteCorTire)
    {
    case 0:
        afficher_liste(liste_corruption,0);
        tab_joueur[i].carte_sortie_prison+=1;
        break;
    case 1:
        afficher_liste(liste_corruption,1);
        int deplacement_case=18; //la case ou l'on veut se deplacer (handball)
        int position_joueur=tab_joueur[i].position; //position du joueur lors de lappel de la fonction
        if (position_joueur>deplacement_case)  //si on est deja apres la case ou se deplacer ca vut dire quon passe par la case depart
        {
            tab_joueur[i].argent += 200;
        }
        aller_a(deplacement_case,tab_joueur, i);
        break;
    case 2:
        afficher_liste(liste_corruption,2);
        aller_a(31,tab_joueur, i); //derniere case du plateau donc pas 200e
        break;
    case 3:
        afficher_liste(liste_corruption,3); // pas faite encore (payer en fonction de maisons et hotel)
        int nombre_maisons=nb_maisons_joueur(tab_joueur,i);
        int nombre_hotels=nb_hotels_joueur(tab_joueur,i);
        int total_prix_maison=25*nombre_maisons;
        int total_prix_hotel=100*nombre_hotels;
        int total_prix=total_prix_hotel+total_prix_maison;
        if (total_prix==0)
        {
            printf("Vous ne payer rien car vous n'avez aucune medaille ni aucun titre\n");
        }
        else
            {
                printf("Vous devez donc payer en tout %d euros, dont %d euros pour vos %d medaille(s) et %d euros pour vos %d titre(s)\n",total_prix,total_prix_maison,nombre_maisons,total_prix_hotel,nombre_hotels);
            }

        break;
    case 4:
        afficher_liste(liste_corruption,4);
        tab_joueur[i].argent += 100;
        break;
    case 5:
        afficher_liste(liste_corruption,5);
        tab_joueur[i].argent += 150;
        break;
    case 6:
        afficher_liste(liste_corruption,6);
        int deplacement_case2=9; //la case ou l'on veut se deplacer(tennis)
        if (tab_joueur[i].position>deplacement_case2) //si on est deja apres la case ou se deplacer ca vut dire quon passe par la case depart
        {
            tab_joueur[i].argent += 200;
        }
        aller_a(deplacement_case2,tab_joueur, i); //definir la postion qu'on veut
        break;
    case 7:
        afficher_liste(liste_corruption,7);
        int deplacement_case3=11; //la case ou l'on veut se deplacer (skate)
        if (tab_joueur[i].position>deplacement_case3) //si on est deja apres la case ou se deplacer ca vut dire quon passe par la case depart
        {
            tab_joueur[i].argent += 200;
        }
        aller_a(deplacement_case3,tab_joueur, i); //definir la postion qu'on veut
        break;
    case 8:
        afficher_liste(liste_corruption,8); //pas faite encore (payer en fonction de maisons et hotel)
        int nombre_maisons2=nb_maisons_joueur(tab_joueur,i);
        int nombre_hotels2=nb_hotels_joueur(tab_joueur,i);
        int total_prix_maison2=40*nombre_maisons2;
        int total_prix_hotel2=115*nombre_hotels2;
        int total_prix2=total_prix_hotel2+total_prix_maison2;
        if (total_prix2==0)
        {
            printf("Vous ne payer rien car vous n'avez aucune medailles ni aucun titre\n");
        }
        else
            {
                printf("Vous devez donc payer en tout %d euros, dont %d euros pour vos %d medaille(s) et %d euros pour vos %d titre(s)\n",total_prix2,total_prix_maison2,nombre_maisons2,total_prix_hotel2,nombre_hotels2);
            }
        break;
    case 9:
        afficher_liste(liste_corruption,9);
        tab_joueur[i].argent += 50;
        break;
    case 10:
        afficher_liste(liste_corruption,10);
        tab_joueur[i].argent += 200;
        aller_a(0,tab_joueur, i); //definir la postion qu'on veut (depart ici)
        break;
    case 11:
        afficher_liste(liste_corruption,11);
        tab_joueur[i].argent -= 150;
        break;
    case 12:
        afficher_liste(liste_corruption,12);
        int position = tab_joueur[i].position;
        aller_a(position-3,tab_joueur, i); //ne pas sen faire des positions negatives car corruption tjrs >3
        break;
    case 13:
        afficher_liste(liste_corruption,13);
        tab_joueur[i].argent -= 15;
        break;
    case 14:
        afficher_liste(liste_corruption,14);
        entrer_prison(tab_joueur,i);
        break;
    case 15:
        afficher_liste(liste_corruption,15);
        tab_joueur[i].argent -= 20;
        break;
    }
}

void tirer_comite(t_joueur tab_joueur[],int i,char* liste_commite,char* liste_comite) // LUC fait
{
    /* Permet de tirer une carte comite olympique
       Prend en paramètre le tableau de joueur, l'indice du joueur qui joue et la liste de comite olympique
       Ne renvoie rien
    */
    int carteComTire = rand() % 16;

    printf("Vous tirez une carte commite olympique:\n");

    char choix[10]; //on l'utilisera dans le case 1

    //numero des autres joueurs
    int B;
    int C;
    int D;

    if (i==0)
    {
        B=1;
        C=2;
        D=3;
    }
    else if (i==1)
    {
        B=2;
        C=3;
        D=0;
    }
    else if (i==2)
    {
        B=3;
        C=0;
        D=1;
    }
    else
    {
        B=0;
        C=1;
        D=3;
    }

    switch(carteComTire)
    {
    case 0:
        afficher_liste(liste_commite,0);
        tab_joueur[i].carte_sortie_prison+=1;
        break;
    case 1:
        do
        {
            afficher_liste(liste_commite,1);
            gets(choix);
            if (choix[0] == 49)
            {
                tab_joueur[i].argent -= 10;
            }
            else if (choix[0] == 50)
            {
                tirer_corruption(tab_joueur,i,liste_comite);
            }
        }
        while (((choix[0] != 49) && (choix[0] != 50)) || (strlen(choix) > 1)); // 49 = 1 en code ascii
        break;
    case 2:
        afficher_liste(liste_commite,2);
        tab_joueur[i].argent += 50;
        break;
    case 3:
        afficher_liste(liste_commite,3); //on verifie que les autres joueur ne sont pas en faillite (quils jouent trs)
        if(tab_joueur[B].en_faillite==false)
        {
            tab_joueur[B].argent -= 10;
            tab_joueur[i].argent += 10;
        }
        if(tab_joueur[C].en_faillite==false)
        {
            tab_joueur[C].argent -= 10;
            tab_joueur[i].argent += 10;
        }
        if(tab_joueur[D].en_faillite==false)
        {
            tab_joueur[D].argent -= 10;
            tab_joueur[i].argent += 10;
        }
        break;
    case 4:
        afficher_liste(liste_commite,4);
        tab_joueur[i].argent += 200;
        break;
    case 5:
        afficher_liste(liste_commite,5);
        tab_joueur[i].argent -= 100;
        break;
    case 6:
        afficher_liste(liste_commite,6);
        tab_joueur[i].argent += 20;
        break;
    case 7:
        afficher_liste(liste_commite,7);
        tab_joueur[i].argent += 100;
        break;
    case 8:
        afficher_liste(liste_commite,8);
        aller_a(1,tab_joueur, i); //definir la postion qu'on veut (ici premiere case)
        break;
    case 9:
        afficher_liste(liste_commite,9);
        tab_joueur[i].argent += 25;
        break;
    case 10:
        afficher_liste(liste_commite,10);
        tab_joueur[i].argent += 200;
        aller_a(0,tab_joueur, i); //definir la postion qu'on veut (depart ici)
        break;
    case 11:
        afficher_liste(liste_commite,11);
        tab_joueur[i].argent -= 50;
        break;
    case 12:
        afficher_liste(liste_commite,12);
        tab_joueur[i].argent += 10;
        break;
    case 13:
        afficher_liste(liste_commite,13);
        tab_joueur[i].argent -= 50;
        break;
    case 14:
        afficher_liste(liste_commite,14);
        entrer_prison(tab_joueur,i);
        break;
    case 15:
        afficher_liste(liste_commite,15);
        tab_joueur[i].argent += 100;
        break;
    }
}

int victoire(t_joueur tab_joueur[]) // LUC fait
{
    /* Fonction qui verifie si un joueur de gagner
       Prend en paramètre le tableau de joueur
       Renvoie le numero du joueur qui a gagné
    */

    if(tab_joueur[0].en_faillite==true && tab_joueur[1].en_faillite==true && tab_joueur[2].en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",tab_joueur[3].numero);
        return 4;
    }
    else if(tab_joueur[1].en_faillite==true && tab_joueur[2].en_faillite==true && tab_joueur[3].en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",tab_joueur[0].numero);
        return 1;
    }
    else if(tab_joueur[2].en_faillite==true && tab_joueur[3].en_faillite==true && tab_joueur[0].en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",tab_joueur[1].numero);
        return 2;
    }
    else if(tab_joueur[3].en_faillite==true && tab_joueur[0].en_faillite==true && tab_joueur[1].en_faillite==true)
    {
        printf("Le joueur %d a gagner la partie. Felicitation !!!!!\n",tab_joueur[2].numero);
        return 3;
    }
    else
    {
        return 0;
    }
}


// fonction utilitaire
int nb_maisons_joueur(t_joueur tab_joueur[],int i) // LUC fait
{
    /* Compte le nombre de maison du joueur
       Prend en paramètre le tableau de joueur et l'indice du joueur
       Renvoie le nombre de maison du joueur
    */
    int nb_maisons=0;
    for (int j=0; j<TAILLE_PLATEAU; j++)
    {
        nb_maisons=tab_joueur[i].proprietes[j].nb_maison;
    }
    if (nb_maisons>32)//c'est que le joueur n'a aucune maison
    {
        nb_maisons=0;
    }
    return nb_maisons;
}

// fonction utilitaire
int nb_hotels_joueur(t_joueur tab_joueur[],int i) // LUC fait
{
    /* Compte le nombre d'hotel du joueur
       Prend en paramètre le tableau de joueur et l'indice du joueur
       Renvoie le nombre d'hotel du joueur
    */
    int nb_hotels=0;
    for (int j=0; j<TAILLE_PLATEAU; j++)
    {
        nb_hotels+=tab_joueur[i].proprietes[j].nb_hotel;
    }
    if (nb_hotels>12)//c'est que le joueur n'a aucun hotel
    {
        nb_hotels=0;
    }
    return nb_hotels;
}

// fonction de jeu
bool achat(t_joueur tab_joueur[],t_case plateau[],int i) // KEIS fait
{
    /* Permet d'acheter une propriete
       Prend en paramètre le tableau de joueur, le plateau et l'indice du joueur qui joue
       Renvoie true si le joueur a acheté une propriété sinon false
    */
        if(plateau[tab_joueur[i].position].groupe_cartes <= 9)//on verifie si la case est une propriété
       {
           if(plateau[tab_joueur[i].position].num_joueur==0)//on verifie si la case n'appartient a personne
          {
               char choix[10];
               afficher_case_jeu(plateau[tab_joueur[i].position]);
               do
               {
                   printf("\nVoulez vous achetez %s ? oui[1]  non[0]\n", plateau[tab_joueur[i].position].nom);//propose d'hypotéquer
                   fflush(stdin);
                   gets(choix);
               } while (((choix[0] != 48) && (choix[0] != 49)) || (strlen(choix) > 1)); // 48 = 0 en code ascii
               if(choix[0] == 49) // Le joueur veut acheter
                {
                    if(tab_joueur[i].argent < plateau[tab_joueur[i].position].valeur)//on verfie si le joueur n'a pas les fonds nécessaires
                    {
                        printf("Fonds insuffisants !\n");
                        return false;
                    }
                    else if(tab_joueur[i].argent >= plateau[tab_joueur[i].position].valeur)//on verfie si le joueur a les fonds nécessaires
                    {
                        tab_joueur[i].argent-=plateau[tab_joueur[i].position].valeur;//on décrémente l'argent du joueur
                        plateau[tab_joueur[i].position].num_joueur=tab_joueur[i].numero;//on actualise le propriétaire de la case
                        return true;
                    }
                }
               if(choix[0] == 48) // Le joueur ne veut pas acheter
                {
                      return false;
                }
          }
      }
  printf("Vous ne pouvez pas achete cette case\n");
  return false;
}

// Fonction de jeu
void impot(t_joueur tab_joueur[],t_case plateau[],int i) // KEIS fait
   {
    /* Permet d'imposer le joueur
       Prend en paramètre le tableau de joueur, le plateau et l'indice du joueur qui joue
       Ne renvoie rien
    */

       if(plateau[tab_joueur[i].position].groupe_cartes == 14)//on vérifie si le joueur est sur la case impôt
       {
          printf("        Impôt sur le revenu        \n");
          printf("    Vous devez 200€ à la banque!    \n ");
          tab_joueur[i].argent-=200;//on décrémente son argent du montant de l'impôt
       }
    }

// fonction de jeu
bool salaire(t_joueur tab_joueur[],int de[2],int i) // KEIS fait
{
    /* Permet de donner le salaire au joueur si celui ci passe par la case depart
       Prend en paramètre le tableau de joueur, la liste de de du joueur et l'indice du joueur qui joue
       Renvoie True si le joueur a recu un salaire, false sinon
    */
    int addposition=tab_joueur[i].position+de[0]+de[1];//on additionne la valeur des dés avec la position du joueur
    if (addposition>32)//on vérifie si le joueur passe par la case départ
  {
      tab_joueur[i].position=addposition%32;//on actualise sa position
      tab_joueur[i].argent+=200;//on incrémente l'argent du joueur
      return true;
  }
  return false;
}

// Fonction d'affichage
void menu(t_joueur tab_joueur[], t_case plateau[], t_banque* p_banque, char* liste_corruption[], char* liste_comite[]) // NATHAN rajouter charger partie
{
    /* Affiche le menu d'avant jeu
       Prend en parametre la liste des joueur, le plateau, le pointeur de banque, la liste des cartes corruptions et la liste des cartes comités
       Ne renvoie rien
    */
    system("cls");
    Color(12, 0);
    printf("\n\n\n                                                                         MONOPOLY JEUX OLYMPIQUES\n\n\n");
    Color(15, 0);
    printf("                                                                        [1]  -  Nouvelle partie\n\n");
    printf("                                                                        [2]  -  Charger partie\n\n");
    printf("                                                                        [3]  -  Afficher les regles\n\n");
    printf("                                                                        [4]  -  Credit\n\n");
    printf("                                                                        [5]  -  Quitter\n\n");
    char choix[10];
    do
    {
        printf("\n                                                                        Que voulez vous faire : ");//propose d'hypotéquer
        fflush(stdin);
        gets(choix);
    } while ((choix[0] < '1') || (choix[0] > '5') || (strlen(choix) > 1) || (strlen(choix) != 1)); // 48 = 0 en code ascii
    if (choix[0] == '1')
    {
        system("cls");
        creation_tab_joueur(tab_joueur);
        tour(tab_joueur, plateau, p_banque, liste_corruption, liste_comite);
    }
    else if (choix[0] == '2')
    {

    }
    else if (choix[0] == '3')
    {
        system("cls");
        Color(12, 0);
        printf("\n\n\n                                                                                     REGLE");
        Color(15, 0);
        printf("\n\n\n                                            Le Monopoly est un jeu de societe ou chaque joueur dispose d'une meme somme d'argent initiale,\n");
        printf("                                      et va tenter de monopoliser le marche immobilier d'une ville, en ruinant progressivement ses adversaires.\n");
        sleep(5);
        menu(tab_joueur, plateau, p_banque, liste_corruption, liste_comite);
    }
    else if (choix[0] == '4')
    {
        system("cls");
        Color(12, 0);
        printf("\n\n\n\n                                                                                      CREDIT");
        Color(15, 0);
        printf("\n\n\n\n                                                       CHEF SANS QUI RIEN N'AURAIT ETE POSSIBLE : NATHAN DEPRAT TD12 PROMO 2026\n");
        printf("\n                                                                  SUBALTERNE 1 : MAXIME MAEDER TD12 PROMO 2026\n");
        printf("\n                                                                   SUBALTERNE 2 : LUC RENAUD TD12 PROMO 2026\n");
        printf("\n                                                                  SUBALTERNE 3 : KEIS AISSAOUI TD12 PROMO 2026\n");
        sleep(5);
        menu(tab_joueur, plateau, p_banque, liste_corruption, liste_comite);
    }
    else if (choix[0] == '5')
    {

    }

}

// Fonction utilitaire
int nb_gare_joueur(t_case plateau[], int i) // MAXIME fait
{
    /*
    permet de calculer le nombre de gare du joueur
    prend en parametre le plateau et l'indice i du joueur a qui appartient la gare
    renvoie le nombre de gare
    */
    int nb_gare = 0;
    if(plateau[3].num_joueur == i)
    {
        nb_gare+=1;
    }
    if(plateau[11].num_joueur == i)
    {
        nb_gare+=1;
    }
    if(plateau[19].num_joueur== i)
    {
        nb_gare +=1;
    }
    if(plateau[27].num_joueur == i)
    {
        nb_gare +=1;
    }
    return nb_gare;
}

// Fonction de jeu
void en_faillite(t_joueur tab_joueur[],int i,int montant,t_banque* p_banque,int proprietaire,t_case plateau[]) // LUC faiy
{
    /* Met en failite un joueur
       Prend en paramètre le tableau de joueur, l'indice du joueur, le montant à payer, la personne a qui le joueur doit de l'argent (0 pour la banque) et le plateau de jeu
       Ne renvoie rien

    */
    int nb_hypoteque=0;//nb de propriete hypotequé
    int nb_prop_j=tab_joueur[i].nb_propriete;
    int iterateur=0;
    if (tab_joueur[i].argent>=montant)
    {
        tab_joueur[i].en_faillite=false;
    }
    else
    {
        if (tab_joueur[i].nb_propriete==0)
        {
            printf("Vous ne pouvez pas hypotequer et vous n'avez plus d'argent pour payer.\nVous faites faillites\n");
            tab_joueur[i].en_faillite=true;
        }
        else
        {
            do
            {
                //sert a verifier qu'il reste d) es propriété a hypothequer
                printf("Vous n'avez pas assez d'argent pour payer, vous allez devoir hypotequer\n");
                hypotheque_faillite(tab_joueur,i,plateau,p_banque);//appel de la fonction d'hypotheque pour la faillite

                if (tab_joueur[i].argent<montant)
                {
                    int reste_a_payer=montant-tab_joueur[i].argent;
                    printf("Voici votre argent apres l'hypoteque %d euros, il vous reste %d euros a payer\n",tab_joueur[i].argent,reste_a_payer);
                }


                iterateur+=1;//nombre de proprieté hypothequé
            }
            while (iterateur == nb_prop_j ^ tab_joueur[i].argent<montant);//verifier qu'on a plus rien a hypoteque ou que les hypoteque on rembourser le montant

            if (tab_joueur[i].argent<montant)
            {
                printf("Malgre vos hypoteques vous ne pouvez toujours pas payer.\nVous faites faillite\n");
                tab_joueur[i].en_faillite=true;
                if (proprietaire==0)//veut dire que le joueur doit de largent à la banque
                {
                    //rendre les propiétés a la banque (les rendres libres et plus hypothequer)
                    for (int k=0; k<=nb_prop_j; k++)
                    {
                        int position_prop_a_supp=tab_joueur[i].proprietes[0].position;//indice 0 car on enleve les propriete du tableau a chaque fois
                        plateau[position_prop_a_supp].hypoteque=false;//enleve l'hypoteque de la propriete
                        enlever_propriete_joueur(tab_joueur,i,plateau,position_prop_a_supp);
                    }
                }
                else //joueur doit payer a un autre joueur
                {
                    for (int k=0; k<nb_prop_j; k++)
                    {
                        int position_prop_a_echanger=tab_joueur[i].proprietes[0].position; //indice 0 car on enleve les propriete du tableau a chaque fois
                        enlever_propriete_joueur(tab_joueur,i,plateau,position_prop_a_echanger);
                        propriete_a_joueur(tab_joueur,proprietaire,plateau,position_prop_a_echanger);
                    }
                }
            }
            else
            {
                printf("Grace a vos hypoteques vous pouvez payer\n");
                tab_joueur[i].en_faillite=false;
            }
        }
    }
}


void propriete_a_joueur(t_joueur tab_joueur[],int i, t_case plateau[],int j) // LUC a commenter
{
    /* Ajoute une propriete dans la liste de prop d'un joueur

    */
    int nb_prop_j=tab_joueur[i].nb_propriete; // recupere la longueur de liste (la ou il faudra rajouter la propriete) en gros le nombre d'element dans la liste(pas l'indice)

    tab_joueur[i].proprietes[nb_prop_j].couleur_fond=plateau[j].couleur_fond;
    tab_joueur[i].proprietes[nb_prop_j].couleur_texte=plateau[j].couleur_texte;
    tab_joueur[i].proprietes[nb_prop_j].groupe_cartes=plateau[j].groupe_cartes;
    tab_joueur[i].proprietes[nb_prop_j].hypoteque=plateau[j].hypoteque;
    tab_joueur[i].proprietes[nb_prop_j].nb_hotel=plateau[j].nb_hotel;
    tab_joueur[i].proprietes[nb_prop_j].nb_maison=plateau[j].nb_maison;
    tab_joueur[i].proprietes[nb_prop_j].num_joueur=plateau[j].num_joueur;
    tab_joueur[i].proprietes[nb_prop_j].position=plateau[j].position;
    tab_joueur[i].proprietes[nb_prop_j].valeur=plateau[j].valeur;
    tab_joueur[i].proprietes[nb_prop_j].val_hotel=plateau[j].val_hotel;
    tab_joueur[i].proprietes[nb_prop_j].val_maison=plateau[j].val_maison;
    int iterateur=0;
    while(plateau[j].nom[iterateur] != '\0')   //\0 correspond à la fin de chaine
    {
        tab_joueur[i].proprietes[nb_prop_j].nom[iterateur]=plateau[j].nom[iterateur];
        iterateur++;
    }

    tab_joueur[i].proprietes[nb_prop_j].val_hypotheque=plateau[j].val_hypotheque;
    tab_joueur[i].proprietes[nb_prop_j].base_loyer=plateau[j].base_loyer;
    tab_joueur[i].proprietes[nb_prop_j].loyer_1_hotel=plateau[j].loyer_1_hotel;
    tab_joueur[i].proprietes[nb_prop_j].loyer_1_maison=plateau[j].loyer_1_maison;
    tab_joueur[i].proprietes[nb_prop_j].loyer_2_maison=plateau[j].loyer_2_maison;
    tab_joueur[i].proprietes[nb_prop_j].loyer_3_maison=plateau[j].loyer_3_maison;
    tab_joueur[i].proprietes[nb_prop_j].loyer_4_maison=plateau[j].loyer_4_maison;



    plateau[j].num_joueur=tab_joueur[i].numero;
    tab_joueur[i].nb_propriete+=1;
}

void enlever_propriete_joueur(t_joueur tab_joueur[],int i,t_case plateau[],int j)
{
    /* enleve la propriete choisie dns la liste de prop d'un joueur
       Prend en paramètre la liste de joueur, l'indice dun joueur qui joue, le plateau, l'indice de la case que l'on retire
       Ne renvoie rien
    */
    int nb_prop_j=tab_joueur[i].nb_propriete;
    int indice_prop_supp=0;
    for (int k=0; k<=nb_prop_j; k++)
    {
        if (tab_joueur[i].proprietes[k].position==j)//verifie l'indice du tableau a laquelle est situe la propriete a supprimer
        {
            indice_prop_supp=k;
        }
    }
    for (int l=indice_prop_supp; l<=nb_prop_j; l++) //decale le tableau afin de remplacer la case que l'on veut enlever par la case juste apres
    {
        tab_joueur[i].proprietes[l].couleur_fond=tab_joueur[i].proprietes[l+1].couleur_fond;
        tab_joueur[i].proprietes[l].couleur_texte=tab_joueur[i].proprietes[l+1].couleur_texte;
        tab_joueur[i].proprietes[l].groupe_cartes=tab_joueur[i].proprietes[l+1].groupe_cartes;
        tab_joueur[i].proprietes[l].hypoteque=tab_joueur[i].proprietes[l+1].hypoteque;
        tab_joueur[i].proprietes[l].nb_hotel=tab_joueur[i].proprietes[l+1].nb_hotel;
        tab_joueur[i].proprietes[l].nb_maison=tab_joueur[i].proprietes[l+1].nb_maison;
        tab_joueur[i].proprietes[l].num_joueur=tab_joueur[i].proprietes[l+1].num_joueur;
        tab_joueur[i].proprietes[l].position=tab_joueur[i].proprietes[l+1].position;
        tab_joueur[i].proprietes[l].valeur=tab_joueur[i].proprietes[l+1].valeur;
        tab_joueur[i].proprietes[l].val_hotel=tab_joueur[i].proprietes[l+1].val_hotel;
        tab_joueur[i].proprietes[l].val_maison=tab_joueur[i].proprietes[l+1].val_maison;
        int iterateur=0;
        while(tab_joueur[i].proprietes[l].nom[iterateur] != '\0')//remettre le nom vide
        {
            tab_joueur[i].proprietes[l].nom[iterateur]=0;
            iterateur++;
        }
        iterateur=0;
        while(tab_joueur[i].proprietes[l+1].nom[iterateur] != '\0') //changer le nom (decaler celui de l'indice l+1 en l
        {
            tab_joueur[i].proprietes[l].nom[iterateur]=tab_joueur[i].proprietes[l+1].nom[iterateur];
            iterateur++;
        }

        tab_joueur[i].proprietes[l].val_hypotheque=tab_joueur[i].proprietes[l+1].val_hypotheque;
        tab_joueur[i].proprietes[l].base_loyer=tab_joueur[i].proprietes[l+1].base_loyer;
        tab_joueur[i].proprietes[l].loyer_1_hotel=tab_joueur[i].proprietes[l+1].loyer_1_hotel;
        tab_joueur[i].proprietes[l].loyer_1_maison=tab_joueur[i].proprietes[l+1].loyer_1_maison;
        tab_joueur[i].proprietes[l].loyer_2_maison=tab_joueur[i].proprietes[l+1].loyer_2_maison;
        tab_joueur[i].proprietes[l].loyer_3_maison=tab_joueur[i].proprietes[l+1].loyer_3_maison;
        tab_joueur[i].proprietes[l].loyer_4_maison=tab_joueur[i].proprietes[l+1].loyer_4_maison;
    }
    plateau[j].num_joueur=0;
    tab_joueur[i].nb_propriete-=1;
}

// fonction de jeu
void hypotheque_faillite(t_joueur tab_joueur[],int i, t_case plateau[], t_banque* p_banque) // V2 NATHAN -> LUC fait
{
    /* fonction qui permet d'hypotéquer une propriétée dans le cadre de la fonction faillite
       Prend en paramètre le tableau de joueur, le numero du joueur qui joue, le plateau, un pointeur sur la banque
       Renvoie un bool, True si il a hypotéqué, false sinon
    */
    char choix[10];
    int long_prop = update_propriete(tab_joueur, i, plateau);
    printf("Vous avez %d proprietes, laquelle voulez vous hypotequer ?\n\n", long_prop);
    for (int j = 0; j < long_prop; j++) // affiche toutes les proprietes du joueur
    {
        printf("\nLa propriete numero %d : \n", j+1);
        afficher_case_jeu(tab_joueur[i].proprietes[j]);
    }

    do
    {
        printf("\nDonnez le numero de la propriete que vous souhaitez hypotheque : ");//propose d'hypotéquer
        fflush(stdin);
        gets(choix);
        if (tab_joueur[i].proprietes[choix[0]-49].hypoteque == 1) // Si la propriete est hypothéqué
        {
            printf("Cette propriete est deja hypotheque \n");
        }
    }
    while ((choix[0] < '1') || (choix[0] > '0'+long_prop) || (strlen(choix) > 1) || (tab_joueur[i].proprietes[choix[0]-49].hypoteque == 1));   // 48 = 0 en code ascii
    for (int j = 0; j < long_prop; j++)
    {
        if ((tab_joueur[i].proprietes[choix[0]-49].groupe_cartes == tab_joueur[i].proprietes[j].groupe_cartes) && (tab_joueur[i].proprietes[choix[0]-49].position != tab_joueur[i].proprietes[j].position))
        {
            // Le joueur a une carte du même groupede couleur
            if ((tab_joueur[i].proprietes[choix[0]-49].nb_maison > 0) || (tab_joueur[i].proprietes[choix[0]-49].nb_hotel > 0))
            {
                // La propriete que le joueur hypoteque a une maison ou un hotel
                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix[0]-49].nb_maison * tab_joueur[i].proprietes[choix[0]-49].val_maison)/2 + (tab_joueur[i].proprietes[choix[0]-49].nb_hotel * tab_joueur[i].proprietes[choix[0]-49].val_hotel)/2;
                p_banque->nb_maison_restante += tab_joueur[i].proprietes[choix[0]-49].nb_maison;
                p_banque->nb_hotel_restant += tab_joueur[i].proprietes[choix[0]-49].nb_hotel;
                plateau[tab_joueur[i].proprietes[choix[0]-49].position].nb_maison = 0;
                plateau[tab_joueur[i].proprietes[choix[0]-49].position].nb_hotel = 0;
                afficher_case(plateau[tab_joueur[i].proprietes[choix[0]-49].position]);
                printf("Vos maisons et hotel sur la case %s, ont ete vendu a moitie prix\n\n", tab_joueur[i].proprietes[choix[0]-49].nom);
            }
            if ((tab_joueur[i].proprietes[j].nb_maison > 0) || (tab_joueur[i].proprietes[j].nb_hotel > 0))
            {
                // La propriete teste a une maison ou un hotel
                tab_joueur[i].argent += (tab_joueur[i].proprietes[j].nb_maison * tab_joueur[i].proprietes[j].val_maison)/2 + (tab_joueur[i].proprietes[j].nb_hotel * tab_joueur[i].proprietes[j].val_hotel)/2;
                p_banque->nb_maison_restante += tab_joueur[i].proprietes[j].nb_maison;
                p_banque->nb_hotel_restant += tab_joueur[i].proprietes[j].nb_hotel;
                plateau[tab_joueur[i].proprietes[j].position].nb_maison = 0;
                plateau[tab_joueur[i].proprietes[j].position].nb_hotel = 0;
                afficher_case(plateau[tab_joueur[i].proprietes[j].position]);
                printf("Vos maisons et hotel sur la case %s, ont ete vendu a moitie prix\n\n", tab_joueur[i].proprietes[j].nom);
            }
        }
    }
    // On donne au joueurs l'argent de l'hypothéque
    tab_joueur[i].argent += tab_joueur[i].proprietes[choix[0]-49].val_hypotheque;
    // On met la propriété en hypothéque
    tab_joueur[i].proprietes[choix[0]-49].hypoteque=true;
    plateau[tab_joueur[i].proprietes[choix[0]-49].position].hypoteque = true;
}

bool Vendre_bien(t_joueur tab_joueur[], t_case plateau[], t_banque* banque, int i) // MAXIME fait
{
//permet de vendre les biens que possede un joueur sur une propriete
//le tableau des joueurs, le plateua, i l'indice du joueur
//renvoie un booleen
    char choix[10];
    char choix2[10];
    char option[10];
    int option_maison = 0;
    int long_prop = update_propriete(tab_joueur, i, plateau);
    int long_prop_maison = 0;

    if (long_prop == 0) // Si pas de propriete renvoie false
    {
        printf("Vous n'avez pas de propriete\n");
        return false;
    }
    else// si le joueur a des propriete
    {
        for(int j= 0; j<long_prop; j++)
        {
            if(tab_joueur[i].proprietes[j].nb_maison >= 1)// regarde si la propriete possede des maisons
            {
                long_prop_maison+=1;
            }
            else if(tab_joueur[i].proprietes[j].nb_hotel == 1)// regarde si la propriete possede un hotel
            {
                long_prop_maison+=1;
            }
        }
        if(long_prop_maison == 0)//le joueur ne possede ni de maison ni d'hotel
        {
            printf("Vous n'avez pas de bien\n");
            return false;
        }
        else // le joueur possede soit des maisons soit un hotel
        {
            do
            {
                printf("voulez-vous vendre un bien? oui[1] non[0]");
                fflush(stdin);
                gets(choix);
            } while (((choix[0] != 48) && (choix[0] != 49)) || (strlen(choix) > 1)); // 48 = 0 en code ascii
            if(choix[0] == 49)//le joueur veut vendre
            {
               for(int k=0; k<long_prop;k++)//affiche toute les propriete du joueur qui possede un bien
               {
                   if((tab_joueur[i].proprietes[k].nb_maison >= 1) || (tab_joueur[i].proprietes[k].nb_hotel == 1))
                   {
                       printf("\n la propriete numero : %d\n", k+1);
                       afficher_case_jeu(tab_joueur[i].proprietes[k]);
                   }
               }
               do
                {
                    printf("\nDonnez le numero de la propriete sur laquelle vous voulez enlever un bien : ");
                    printf("Si vous souhaitez quitter[0]\n");
                    fflush(stdin);
                    gets(choix2);
                    if (choix2[0] == 48) // Si le joueur ne veut pas
                    {
                        printf("Vous n'avez pas enleve de bien \n");
                        return false;
                    }
                } while ((choix2[0] < '0') || (choix2[0] > '0'+long_prop) || (strlen(choix2) > 1)); // 48 = 0 en code ascii
                if(tab_joueur[i].proprietes[choix2[0]-49].nb_maison > 0)//le joueur possede au moins une maison, il vend donc 1 seul maison
                {
                    plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison -=1;
                    banque->nb_maison_restante+=1;
                    tab_joueur[i].argent+= (tab_joueur[i].proprietes[choix2[0]-49].val_maison)/2;
                    return true;
                }
                else if(tab_joueur[i].proprietes[choix2[0]-49].nb_hotel == 1)//le joueur possede 1 hotel
                {
                    //on regarde combien de maison il reste dans la banque
                    if(banque->nb_maison_restante >=4)
                    {
                        option_maison = 1;
                    }
                    else if(banque->nb_maison_restante == 3)
                    {
                        option_maison = 2;
                    }
                    else if(banque->nb_maison_restante == 2)
                    {
                        option_maison = 3;
                    }
                    else if(banque->nb_maison_restante == 1)
                    {
                        option_maison = 4;
                    }
                    else if(banque->nb_maison_restante == 0)
                    {
                        option_maison = 5;
                    }
                    //en fonction du nombre de maison restante on lui fait different choix
                    switch(option_maison)
                    {
                    case 1:
                        {
                            do
                            {
                                printf("vous avez plusieurs option : \n[1] : vous enlevez l'hotel et recuperez 4 maisons \n[2] : vous enlevez l'hotel et une maison et  vous ne recuperez que 3 maisons \n[3] : pareil mais vous ne recuperez que 2 maisons \n[4] : pareil mais vous ne recuperez qu'une maison \n[5] : vous enlevez tous");
                                fflush(stdin);
                                gets(option);
                            }while(((option[0] != 49) && (option[0] != 50) && (option[0] != 51) && (option[0] != 52) && (option[0] != 53)) || strlen(option) > 1);
                            if(option[0] == 49)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel =0;
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison =4;
                                banque->nb_hotel_restant += 1;
                                banque->nb_maison_restante -=4;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2;
                            }
                            else if(option[0] == 50)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison +=3;
                                banque->nb_hotel_restant += 1;
                                banque->nb_maison_restante -=3;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + (tab_joueur[i].proprietes[choix2[0]-49].val_maison)/2;
                            }
                            else if(option[0] == 51)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison +=2;
                                banque->nb_hotel_restant += 1;
                                banque->nb_maison_restante -=2;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + (tab_joueur[i].proprietes[choix2[0]-49].val_maison);
                            }
                            else if(option[0] == 52)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison +=1;
                                banque->nb_hotel_restant += 1;
                                banque->nb_maison_restante -=1;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + 3*((tab_joueur[i].proprietes[choix2[0]-49].val_maison)/2);
                            }
                            else if(option[0] == 53)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                banque->nb_hotel_restant += 1;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + 2*(tab_joueur[i].proprietes[choix2[0]-49].val_maison);
                            }
                            break;
                        }
                    case 2:
                        {
                            do
                            {
                                printf("vous avez plusieurs option : \n[1] : vous enlevez l'hotel et vous ne recuperez que 3 maisons \n[2] : pareil mais vous ne recuperez que 2 maisons \n[3] : pareil mais vous ne recuperez qu'une maison \n[4] : vous enlevez tous");
                                fflush(stdin);
                                gets(option);
                            }while(((option[0] != 49) && (option[0] != 50) && (option[0] != 51) && (option[0] != 52)) || strlen(option) > 1);
                            if(option[0] == 49)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison +=3;
                                banque->nb_hotel_restant += 1;
                                banque->nb_maison_restante -=3;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + (tab_joueur[i].proprietes[choix2[0]-49].val_maison)/2;
                            }
                            else if(option[0] == 50)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison +=2;
                                banque->nb_hotel_restant += 1;
                                banque->nb_maison_restante -=2;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + (tab_joueur[i].proprietes[choix2[0]-49].val_maison);
                            }
                            else if(option[0] == 51)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison +=1;
                                banque->nb_hotel_restant += 1;
                                banque->nb_maison_restante -=1;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + 3*((tab_joueur[i].proprietes[choix2[0]-49].val_maison)/2);
                            }
                            else if(option[0] == 52)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                banque->nb_hotel_restant += 1;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + 2*(tab_joueur[i].proprietes[choix2[0]-49].val_maison);
                            }
                            break;
                        }
                    case 3:
                        {
                            do
                            {
                                printf("vous avez plusieurs option : \n[1] : vous enlevez l'hotel et vous ne recuperez que 2 maisons \n[2] : pareil mais vous ne recuperez qu'une maison \n[3] : vous enlevez tous");
                                fflush(stdin);
                                gets(option);
                            }while(((option[0] != 49) && (option[0] != 50) && (option[0] != 51)) || strlen(option) > 1);
                            if(option[0] == 49)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison +=2;
                                banque->nb_hotel_restant += 1;
                                banque->nb_maison_restante -=2;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + (tab_joueur[i].proprietes[choix2[0]-49].val_maison);
                            }
                            else if(option[0] == 50)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison +=1;
                                banque->nb_hotel_restant += 1;
                                banque->nb_maison_restante -=1;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + 3*((tab_joueur[i].proprietes[choix2[0]-49].val_maison)/2);
                            }
                            else if(option[0] == 51)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                banque->nb_hotel_restant += 1;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + 2*(tab_joueur[i].proprietes[choix2[0]-49].val_maison);
                            }
                            break;
                        }
                    case 4:
                        {
                            do
                            {
                                printf("vous avez plusieurs option : \n[1] : vous enlevez l'hotel et vous ne recuperez qu'une maison \n[2] : vous enlevez tous");
                                fflush(stdin);
                                gets(option);
                            }while(((option[0] != 49) && (option[0] != 50)) || strlen(option) > 1);
                            if(option[0] == 49)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_maison +=1;
                                banque->nb_hotel_restant += 1;
                                banque->nb_maison_restante -=1;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + 3*((tab_joueur[i].proprietes[choix2[0]-49].val_maison)/2);
                            }
                            else if(option[0] == 50)
                            {
                                plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                                banque->nb_hotel_restant += 1;
                                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + 2*(tab_joueur[i].proprietes[choix2[0]-49].val_maison);
                            }
                            break;
                        }
                    case 5:
                        {
                            printf("vous enlevez l'hotel et les 4 maisons");
                            plateau[tab_joueur[i].proprietes[choix2[0]-49].position].nb_hotel -=1;
                            banque->nb_hotel_restant += 1;
                            tab_joueur[i].argent += (tab_joueur[i].proprietes[choix2[0]-49].val_hotel)/2 + 2*(tab_joueur[i].proprietes[choix2[0]-49].val_maison);
                        }
                        break;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}


 void clear_bas()
 {
     gotoligcol(54, 0);
     for (int i; i < 20; i++)
     {
        printf("                                                                   \n");
     }
     gotoligcol(54, 0);

 }
