#include "Header.h"

// Fonction de deplacement de joueur
void deplacement(int* liste_de, t_joueur tab_joueur[], int i)
{
    /*La proc�dure incr�mente la position du joueur
      Prend en param�tre la liste de d� et un pointeur sur le joueur qui se deplace
      Ne renvoie rien
    */
    tab_joueur[i].position += liste_de[0] + liste_de[1];
}

// Fonction de deplacement de joueur
void aller_a(int indice_case, t_joueur tab_joueur[], int i)
{
    /* La proc�dure actualise la position du joueur pour le mettre � la case voulu
       Prend en param�tre l�indice de la case et le joueur qui se d�place,
       Ne renvoie rien
    */

    tab_joueur[i].position = indice_case;
}

// fonction pour prison
void entrer_prison(t_joueur tab_joueur[], int i)
{
    /*La proc�dure envoie le joueur en prison. Elle change l�etat prison du joueur et appelle la fonction aller � pour l�envoyer en prison
      Prend en param�tre le joueur
      Ne renvoie rien
    */
    tab_joueur[i].en_prison = 1;

}

// fonction pour prison
bool sortie_prison(int* liste_de, t_joueur tab_joueur[], int i)
{
    /* Fonction qui permets � un joueur de sortir de prison
       Prend en param�tre la liste de d� et un pointeur sur le joueur
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
    }
    if (tab_joueur[i].tour_prison >= 3) // Le joueur a pass� 3 tours en prison
    {
        printf("Vous avez passez 3 tours en prison, vous payez 50 et sortez\n");
        tab_joueur[i].argent -= 50;
        tab_joueur[i].capital -= 50;
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
        } while ((choix[0] != 48) && (choix[0] != 49) || (strlen(choix) > 1)); // 48 = 0 en code ascii
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
    } while ((choix[0] != 48) && (choix[0] != 49) || (strlen(choix) > 1)); // 48 = 0 en code ascii
    if (choix[0] == 49) // 49 = 1 en code ascii
    {
        printf("Vous sortez de prison\n");
        tab_joueur[i].en_prison = false;
        tab_joueur[i].tour_prison = 0;
        tab_joueur[i].argent -= 50;
        tab_joueur[i].capital -= 50;
        return true;
    }

}

// fonction creation d'instance
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes, char* nom, int couleur_fond, int couleur_texte, int valeur_hypotheque, int base_loyer, int loyer_1_maison, int loyer_2_maison, int loyer_3_maison, int loyer_4_maison, int loyer_1_hotel)
{
    /* Fonction qui cr��e une case
       Prend en param�tre toutes ses caract�ristique
       Renvoie la case
    */
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
t_joueur creation_joueur(int numero)
{
    /* Permet la creation d'un joueur
       Prend en param�tre le num�ro du joueur
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
       Ne prend pas de param�tre
       Renvoie une instance de la classe banque au debut de partie
    */
    t_banque b;
    fflush(stdin);

    b.nb_maison_restante=32;
    b.nb_hotel_restant=12;

    return b;
}

// fonction creation plateau
void creation_plateau(t_case* plateau)
{
    /* Proc�dure de creation du plateau
       Prend en param�tre un tableau qui sera le plateau
       Ne renvoie rien
    */

    // Groupe 1 = Propri�t�s , 2 cases , vert caca d'oie , blanc
    // Groupe 2 = Propri�t�s , 3 cases , turquoise , blanc
    // Groupe 3 = Propri�t�s , 3 cases , violet , blanc
    // Groupe 4 = Propri�t�s , 2 cases , gris fonc� , blanc
    // Groupe 5 = Propri�t�s , 2 cases , rouge , blanc
    // Groupe 6 = Propri�t�s , 2 cases , jaune , noir
    // Groupe 7 = Propri�t�s , 3 cases , vert , blanc
    // Groupe 8 = Propri�t�s , 2 cases , bleu , blanc
    // Groupe 9 = Gares, 4 cases , blanc , noir
    // Groupe 10 = carte communaut�,
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
void creation_tab_joueur(t_joueur tab_joueur[])
{
    /* Cr��e le tableau de joueurs, permet de choisir le nombre de joueur
       Prend en param�tre la tableau des joueurs
       Ne renvoie rien
    */
    char choix[10];
    do
    {
        printf("Combien de joueurs vont jouer ?\nIl doit y avoir minimum 2 joueurs et maximum 4 joueurs : ");
        fflush(stdin);
        gets(choix);
    } while ((choix[0] != 50) && (choix[0] != 51) && (choix[0] != 52) || (strlen(choix) > 1)); // 48 = 0 en code ascii
    if (choix[0] == 50)
    {
        tab_joueur[0] = creation_joueur(1);
        tab_joueur[1] = creation_joueur(2);

        t_joueur j3;
        strcpy(j3.nom, "j3");
        j3.numero = 3;
        j3.position=0;
        j3.argent=1500;
        j3.capital=1500;
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
        j4.capital=1500;
        j4.en_prison=false;
        j4.tour_prison=0;
        j4.carte_sortie_prison=0;
        j4.en_faillite = true;
        tab_joueur[3] = j4;



    }
    if (choix[0] == 51)
    {
        tab_joueur[0] = creation_joueur(1);
        tab_joueur[1] = creation_joueur(2);
        tab_joueur[2] = creation_joueur(3);

        t_joueur j4;
        strcpy(j4.nom, "j4");
        j4.numero = 3;
        j4.position=0;
        j4.argent=1500;
        j4.capital=1500;
        j4.en_prison=false;
        j4.tour_prison=0;
        j4.carte_sortie_prison=0;
        j4.en_faillite = true;
        tab_joueur[3] = j4;

    }
    if (choix[0] == 52)
    {
        tab_joueur[0] = creation_joueur(1);
        tab_joueur[1] = creation_joueur(2);
        tab_joueur[2] = creation_joueur(3);
        tab_joueur[3] = creation_joueur(4);
    }

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
    printf("nom: %s\nposition:%d\nprix d'achat:%d\nnum joueur la possedant:%d\nnombre de maison:%d\nya til un hotel:%d\nprix dachat d'une maison:%d\nprix d'achat d'un hotel:%d\nquel groupe de carte:%d\nvaleur de l'hypotheque:%d\nHypotheque:%d",c.nom,c.position,c.valeur,c.num_joueur,c.nb_maison,c.nb_hotel,c.val_maison,c.val_hotel,c.groupe_cartes, c.val_hypotheque, c.hypoteque);
    printf("\n"); //pour de la lisibilit�
}

// fonction affichage d'instance dans le jeu
void afficher_case_jeu(t_case c)
{
    /* Proc�dure qui affiche une instance de case
       Prend en param�tre une case
       Ne renvoie rien
    */
    printf("nom: %s\nprix d'achat:%d\nnombre de maison:%d\nNombre d'Hotel hotel:%d\nprix dachat d'une maison:%d\nprix d'achat d'un hotel:%d\nquel groupe de carte:%d\nLoyer sans maison:%d\n",c.nom,c.valeur,c.nb_maison,c.nb_hotel,c.val_maison,c.val_hotel,c.groupe_cartes, c.base_loyer);
    printf("\n"); //pour de la lisibilit�
}

// fonction affichage d'instance
void afficher_banque(t_banque banque)
{
    /* Proc�dure qui affiche une instance de banque
       Prend en param�tre la banque
       Ne renvoie rien
    */
    printf("Voici la BANQUE:\n");
    printf("maisons restantes:%d\nhotels restant:%d\n",banque.nb_maison_restante,banque.nb_hotel_restant);
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
bool double_de(int* de)
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
void en_faillite(t_joueur tab_joueur[], int i) // En cours par LUC
{
    /* La proc�dure erifie si le joueur est en faillite
       Si oui le met en faillite
       Prend en param�tre un pointeur sur le joueur
    */
    int choix = 2;
    if (tab_joueur[i].capital<=0) //le joueur ne peut plus rien faire
        {
            tab_joueur[i].en_faillite=true;
            printf("Vous etes en faillite");
            //On doit supprimer ses propri�t�s
        }


    else if (tab_joueur[i].argent<=0) //le joueur n'a plus d'argent mais encore du capital
        {
            printf("voulez vous abandonner ?: oui[1], non[2]\n");
            scanf("%d",&choix);
            if (choix==1) // Il veut abandonner
                {
                    tab_joueur[i].en_faillite=true;
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

// fonction calcul nb de gare du joueur
int nb_gare_joueur(t_case plateau[], int i)
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

// fonction pour loyer
bool loyer(t_joueur tab_joueur[], int i, t_case plateau[])
{
    /* Permet de faire payer un joueur si il est sur la case d'un autre joueur
       Prend en param��tre le tableau de joueur, l'indice du joueur qui joue et le plateau
       revoie un booleen
    */
    t_banque banque;
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
            case 0:
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
            case 1:
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
            case 2:
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
            case 3:
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
            case 4:
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
            case 5:
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
    else if((plateau[tab_joueur[i].position].num_joueur != tab_joueur[i].numero) && (plateau[tab_joueur[i].position].num_joueur != 0) && (plateau[tab_joueur[i].position].groupe_cartes == 9))//regarde si la case appartient a quelqu'un d'autre et si cest une gare
    {
        int nb_gare = nb_gare_joueur(plateau, plateau[tab_joueur[i].position].num_joueur);
        if(nb_gare == 1)
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
        else if(nb_gare == 2)
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
        else if(nb_gare ==3)
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
        else if(nb_gare ==4)
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
    else
    {
        printf("Vous n'etes pas sur la case de quelqu'un d'autre, vous ne payez pas\n");
        return false;
    }
}

// Fonction de tour
void tour(t_joueur tab_joueur[], t_case plateau[], t_banque* p_banque) // en cours par Nathan
{
    /* Proc�dure qui fait un tour � tout les joueurs
       Prend en param��tre le tableau des joueurs, le plateau et la banque
       Ne renvoie rien
    */
    for (int i = 0; i < 4; i++)
    {
        // En faillite
        if (tab_joueur[i].en_faillite)
        {
            // Le joueur ne joue pas

        }
        else
        {
            printf("\n\nC'est le tour de %s\n", tab_joueur[i].nom);
            int de[2];
            lance_de(de);
            de[0] = 1;
            de[1] = 2;
            printf("Vous avez fait %d et %d\n", de[0], de[1]);
            if (sortie_prison(de, tab_joueur, i)) // Le joueur sors de prison donc ne joue pas plus pendant ce tour
            {
                afficher_plateau(plateau, tab_joueur);
            }
            else // Le joueur n'est pas en prison                       // continue ici
            {
                // Le joueur joue une fois
                deplacement(de, tab_joueur, i);
                afficher_plateau(plateau, tab_joueur);
                printf("Vous etes a la case %s\n", plateau[tab_joueur[i].position].nom);
                loyer(tab_joueur, i, plateau);
                acheter_maison_hotel(tab_joueur, i, plateau, p_banque);
                hypotheque(tab_joueur, i, plateau, p_banque);
                if (double_de(de)) // Le joueur a fait un double
                {
                    // Le joueur joue une 2eme fois
                    lance_de(de);
                    printf("Vous avez fait %d et %d\n", de[0], de[1]);
                    deplacement(de, tab_joueur, i);
                    afficher_plateau(plateau, tab_joueur);
                    printf("Vous etes a la case %s\n", plateau[tab_joueur[i].position].nom);
                    loyer(tab_joueur, i, plateau);
                    // acheter_propriete(p_joueur, plateau[p_joueur->position]);
                    acheter_maison_hotel(tab_joueur, i, plateau, p_banque);
                    //hypotheque(tab_joueur, i, plateau, p_banque);
                    if (double_de(de)) // Le joueur a fait 2 doubles
                    {
                        // Le joueur joue une 3eme fois
                        lance_de(de);
                        printf("Vous avez fait %d et %d\n", de[0], de[1]);
                        afficher_plateau(plateau, tab_joueur);
                        deplacement(de, tab_joueur, i);
                        printf("Vous etes a la case %s\n", plateau[tab_joueur[i].position].nom);
                        loyer(tab_joueur, i, plateau);
                        // acheter_propriete(p_joueur, plateau[p_joueur->position]);
                        acheter_maison_hotel(tab_joueur, i, plateau, p_banque);
                        //hypotheque(tab_joueur, i, plateau, p_banque);
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
bool acheter_maison_hotel(t_joueur tab_joueur[], int i, t_case plateau[], t_banque* banque) // faire le blindage
{
    //La fonction permet au joueur d�acheter une maison ou un h�tel (elle lui demande)
    //Prend en param�tre un pointeur sur le joueur, le plateau, un pointeur sur la banque)
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
                            printf("vous pouvez acheter une maison. voulez-vous en acheter une? oui[1]  non[0]\n");//propose d'acheter une maison
                            fflush(stdin);
                            gets(choix);
                        } while ((choix[0] != 48) && (choix[0] != 49) || (strlen(choix) > 1)); // 48 = 0 en code ascii
                        if(choix[0] == 49)
                        {
                            plateau[tab_joueur[i].position].nb_maison+=1;//ajoute une maison
                            tab_joueur[i].argent-=plateau[tab_joueur[i].position].val_maison;//enleve l'argent au joueur
                            banque->nb_maison_restante-=1;//enleve une maison de la banque
                            printf("vous avez achete une maison.\n");
                            printf("Il y a %d maisons sur la case\n", plateau[tab_joueur[i].position].nb_maison);
                            return true;
                        }
                        else if(choix[0] == 48)
                        {
                            printf("vous n'avez pas achete de maison.\n");
                            return false;
                        }
                    }
                    else//il n'a pas assez d'argent
                    {
                        printf("argent joueur : %d\ncout maison : %d\n",tab_joueur[i].argent, plateau[tab_joueur[i].position].val_maison);
                        printf("vous n'avez pas assez d'argent\n");
                        return false;
                    }
                }
                else if(banque->nb_maison_restante == 0)//il n'y a plus de maison
                {
                    printf("il n'y a plus de maison disponible\n");
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
                            printf("vous pouvez acheter un hotel. voulez-vous acheter un hotel? oui[1]  non[0]\n");
                            fflush(stdin);
                            gets(choix);
                        } while ((choix[0] != 48) && (choix[0] != 49) || (strlen(choix) > 1)); // 48 = 0 en code ascii
                        if(choix[0] == 49)
                        {
                            plateau[tab_joueur[i].position].nb_hotel+=1;//ajoute l'hotel
                            plateau[tab_joueur[i].position].nb_maison = 0;//on retire les maison
                            tab_joueur[i].argent-=plateau[tab_joueur[i].position].val_hotel;//on enleve l'argent au joueur
                            banque->nb_hotel_restant-=1;//eneleve un hotel de la banque
                            banque->nb_maison_restante+=4;//rajoute les 4 maison a la banque
                            printf("vous avez achete un hotel.\n");
                            return true;
                        }
                        else if(choix[0] == 48)
                        {
                            printf("vous n'avez pas achete d'hotel.\n");
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
                    printf("il n'y a plus d'hotels dans la banque\n");
                    return false;
                }
            }
            else if(plateau[tab_joueur[i].position].nb_hotel == 1)//le joueur possede 1 hotels
            {
                printf("vous ne pouvez rien faire de plus. vous avez deja un hotels\n");
                return false;
            }
        }
        else if(plateau[tab_joueur[i].position].num_joueur != tab_joueur[i].numero)
        {
            printf("la case ne vous appartient pas. elle appartient a quelqu'un d'autres ou a personne.\n");
            return false;
        }
    }
    else
    {
        printf("vous ne pouvez pas acheter de maison ni d'hotels, vous n'etes pas sur une case propriete.\n");
        return false;
    }
}

// Fonction affichage
void gotoligcol( int lig, int col )
{

    // ressources

    COORD mycoord;

    mycoord.X = col;

    mycoord.Y = lig;

    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );

}

// Fonction d'affichage
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

// Fonction d'affichage
int Longueur(int Valeur)
{
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
void afficher_valeur_case(int indice, t_case plateau[])
{
    Color(plateau[indice].couleur_texte, plateau[indice].couleur_fond);
    printf("%d",plateau[indice].valeur);
    for(int z = Longueur(plateau[indice].valeur); z<18;z++)
    {
        printf(" ");
    }
    Color(15,0);
    printf("|");
}

// Fonction d'affichage
void afficher_nom_proprietaire(int indice, t_case plateau[], t_joueur tab_joueur[], int num_joueur)
{
    Color(plateau[indice].couleur_texte, plateau[indice].couleur_fond);
    printf("%s",tab_joueur[num_joueur].nom);
    if(plateau[indice].nb_maison == 1)
    {
        printf("(4)");
    }
    else if(plateau[indice].nb_maison == 2)
    {
        printf("(4)");
        printf("(3)");
    }
    else if(plateau[indice].nb_maison == 3)
    {
        printf("(4)");
        printf("(3)");
        printf("(2)");
    }
    else if(plateau[indice].nb_maison == 4)
    {
        printf("(4)");
        printf("(3)");
        printf("(2)");
        printf("(1)");
    }
    else if(plateau[indice].nb_hotel == 1)
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
void creation_sous_case1(t_case plateau[], t_joueur tab_joueur[], int i)
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
                Color(plateau[k].couleur_texte, plateau[k].couleur_fond);
                printf("                  ");
                Color(15,0);//re-met en noir et blanc
                printf("|");

            }
        }
    }
}

//fonction d'affichage
void creation_sous_case2(t_case plateau[], t_joueur tab_joueur[], int i)
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
        Color(plateau[40-i].couleur_texte, plateau[40-i].couleur_fond);
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
        Color(plateau[i].couleur_texte, plateau[i].couleur_fond);
        printf("                  ");
        Color(15,0);//re-met en noir et blanc
        printf("|");
    }
}

//fonction d'affichage
void creation_sous_case3(t_case plateau[], t_joueur tab_joueur[], int i)
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
                Color(plateau[40-k].couleur_texte, plateau[40-k].couleur_fond);
                printf("                  ");
                Color(15,0);//re-met en noir et blanc
                printf("|");
            }
        }
    }
}

// Fonction d'affichage
void afficher_plateau(t_case plateau[], t_joueur tab_joueur[])
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
        else if(i >=9 && i <= 15)//permet de creer les 2 colonnes sur les cot�
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
// fonction de jeu
bool hypotheque(t_joueur tab_joueur[],int i, t_case plateau[], t_banque* p_banque)
{
    /* fonction qui permet d'hypot�quer une propri�t�e
       Prend en param�tre le tableau de joueur, le numero du joueur qui joue, le plateau, un pointeur sur la banque
       Renvoie un bool, True si il a hypot�qu�, false sinon
    */
    char choix[10];
    do
    {
        printf("\nVoulez vous hypotequez une propriete oui[1]  non[0]\n");//propose d'hypot�quer
        fflush(stdin);
        gets(choix);
    } while ((choix[0] != 48) && (choix[0] != 49) || (strlen(choix) > 1)); // 48 = 0 en code ascii
    if (choix[0] == 48)
    {
        return false;
    }
    int long_prop = update_propriete(tab_joueur, i, plateau);
    if (long_prop == 0)
    {
        return false;
    }
    printf("\nVous avez %d proprietes, laquelle voulez vous hypotequer ?\n\n", long_prop);
    for (int j = 0; j < long_prop; j++)
    {
        printf("La propriete numero %d : \n", j+1);
        afficher_case_jeu(tab_joueur[i].proprietes[j]);
    }

    do
    {
        printf("\nDonnez le numero de la propriete que vous souhaitez hypotheque : ");//propose d'hypot�quer
        fflush(stdin);
        gets(choix);
    } while ((choix[0] < '1') || (choix[0] > '0'+long_prop) || (strlen(choix) > 1)); // 48 = 0 en code ascii
    for (int j = 0; j < long_prop; j++)
    {
        if ((tab_joueur[i].proprietes[choix[0]-49].groupe_cartes == tab_joueur[i].proprietes[j].groupe_cartes) && (tab_joueur[i].proprietes[choix[0]-49].position != tab_joueur[i].proprietes[j].position))
        {
            // Le joueur a une carte du m�me groupede couleur
            if ((tab_joueur[i].proprietes[choix[0]-49].nb_maison > 0) || (tab_joueur[i].proprietes[choix[0]-49].nb_hotel > 0)) // La propriete que le joueur hypoteque a une maison ou un hotel
            {
                tab_joueur[i].argent += (tab_joueur[i].proprietes[choix[0]-49].nb_maison * tab_joueur[i].proprietes[choix[0]-49].val_maison)/2 + (tab_joueur[i].proprietes[choix[0]-49].nb_hotel * tab_joueur[i].proprietes[choix[0]-49].val_hotel)/2;
                tab_joueur[i].proprietes[choix[0]-49].nb_maison = 0;
                tab_joueur[i].proprietes[choix[0]-49].nb_hotel = 0;
                printf("Vos maisons et hotel sur la case %s, ont ete vendu a moitie prix\n", tab_joueur[i].proprietes[choix[0]-49].nom);
            }
            if ((tab_joueur[i].proprietes[j].nb_maison > 0) || (tab_joueur[i].proprietes[j].nb_hotel > 0)) // La propriete teste a une maison ou un hotel
            {
                tab_joueur[i].argent += (tab_joueur[i].proprietes[j].nb_maison * tab_joueur[i].proprietes[j].val_maison)/2 + (tab_joueur[i].proprietes[j].nb_hotel * tab_joueur[i].proprietes[j].val_hotel)/2;
                tab_joueur[i].proprietes[j].nb_maison = 0;
                tab_joueur[i].proprietes[j].nb_hotel = 0;
                printf("Vos maisons et hotel sur la case %s, ont ete vendu a moitie prix\n", tab_joueur[i].proprietes[j].nom);
            }
        }
    }
    printf("que dalle\n");
}

// fonction d'instance
int update_propriete(t_joueur tab_joueur[],int i, t_case plateau[])
{
    int nb = 0; // Nombre de propri�t� que le joueur a
    for (int j = 0; j < 32; j++)
    {
        if (plateau[j].num_joueur == tab_joueur[i].numero)
        {
            nb+=1;
        }
    }
    int compteur = 0;
    int total = 0;
     for (int j = 0; j < 32; j++)
    {
        if (plateau[j].num_joueur == tab_joueur[i].numero)
        {
            tab_joueur[i].proprietes[compteur] = plateau[j];
            compteur+=1;
        }
        else
        {
            tab_joueur[i].proprietes[total] = creation_case(50, 0, 0, 0, 50, "Rien", 50, 50, 0, 0, 0, 0, 0, 0, 0); // on remplit le reste du tableau avec des cases vides
        }
        total+=1;
    }
    return nb;
}
