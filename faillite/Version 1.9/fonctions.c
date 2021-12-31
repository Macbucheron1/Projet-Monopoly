#include "Header.h"

// Fonction de deplacement de joueur
void deplacement(int* liste_de, t_joueur tab_joueur[], int i)
{
    /*La procédure incrémente la position du joueur
      Prend en paramètre la liste de dé et un pointeur sur le joueur qui se deplace
      Ne renvoie rien
    */
    tab_joueur[i].position += liste_de[0] + liste_de[1];
}

// Fonction de deplacement de joueur
void aller_a(int indice_case, t_joueur tab_joueur[], int i)
{
    /* La procédure actualise la position du joueur pour le mettre à la case voulu
       Prend en paramètre l’indice de la case et le joueur qui se déplace,
       Ne renvoie rien
    */

    tab_joueur[i].position = indice_case;
}

// fonction pour prison
void entrer_prison(t_joueur tab_joueur[], int i)
{
    /*La procédure envoie le joueur en prison. Elle change l’etat prison du joueur et appelle la fonction aller à pour l’envoyer en prison
      Prend en paramètre le joueur
      Ne renvoie rien
    */
    tab_joueur[i].en_prison = 1;

}

// fonction pour prison
bool sortie_prison(int* liste_de, t_joueur tab_joueur[], int i)
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
    }
    if (tab_joueur[i].tour_prison >= 3) // Le joueur a passé 3 tours en prison
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
void creation_plateau(t_case* plateau)
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
    plateau[0] = depart;

    t_case sport_equestre;
    sport_equestre=creation_case(1, 60, 50, 60,1, "Sport Equestre");
    plateau[1] = sport_equestre;

    t_case waterpolo;
    waterpolo=creation_case(2, 60, 50, 60,1, "Waterpolo");
    plateau[2] = waterpolo;

    t_case breaking;
    breaking=creation_case(3, 200, 0, 0,9, "Breaking");
    plateau[3] = breaking;

    t_case aviron;
    aviron=creation_case(4, 60, 50, 60,2, "Aviron");
    plateau[4] = aviron;

    t_case corruption1;
    corruption1 = creation_case(5, 0, 0, 0, 11, "Corruption");
    plateau[5] = corruption1;

    t_case canoe;
    canoe=creation_case(6, 60, 50, 60, 2, "Canoe");
    plateau[6] = canoe;

    t_case voile;
    voile=creation_case(7, 60, 50, 60, 2, "Voile");
    plateau[7] = voile;

    t_case suspension;
    suspension = creation_case(8, 0, 0, 0, 12, "Suspension");
    plateau[8] = suspension;

    t_case tennis;
    tennis=creation_case(9, 140, 100, 110,3, "Tennis");
    plateau[9] = tennis;

    t_case golf;
    golf=creation_case(10, 140, 100, 110,3, "Golf");
    plateau[10] = golf;

    t_case skate;
    skate=creation_case(11, 200, 0, 0,9, "Skate");
    plateau[11] = skate;

    t_case tir_a_l_arc;
    tir_a_l_arc=creation_case(12, 160, 100, 110,3, "Tir a l'arc");
    plateau[12] = tir_a_l_arc;

    t_case lutte;
    lutte=creation_case(13, 180, 100, 110, 4, "Lutte");
    plateau[13] = lutte;

    t_case comite_olympique1;
    comite_olympique1 = creation_case(14, 0, 0, 0, 10, "Comite olympique");
    plateau[14] = comite_olympique1;

    t_case halterophilie;
    halterophilie=creation_case(15, 200, 100, 110, 4, "Halterophilie");
    plateau[15] = halterophilie;

    t_case village_olympique;
    village_olympique = creation_case(16, 0, 0, 0, 13, "Village olympique");
    plateau[16] = village_olympique;

    t_case Volley;
    Volley=creation_case(17, 220, 150, 165, 5, "Volley");
    plateau[17] = Volley;

    t_case handball;
    handball=creation_case(18, 220, 150, 165, 5, "Handball");
    plateau[18] = handball;

    t_case escalade;
    escalade=creation_case(19, 200, 0, 0,9, "Escalade");
    plateau[19] = escalade;

    t_case amende;
    amende = creation_case(20, 0, 0, 0, 14, "Amende");
    plateau[20] = amende;

    t_case corruption2;
    corruption2 = creation_case(5, 0, 0, 0, 11, "Corruption");
    plateau[21] = corruption2;

    t_case judo;
    judo=creation_case(22, 260, 150, 165,6, "Judo");
    plateau[22] = judo;

    t_case boxe;
    boxe=creation_case(23, 280, 150, 165,6, "Boxe");
    plateau[23] = boxe;

    t_case controle_dopage;
    controle_dopage = creation_case(24, 0, 0, 0, 15, "Controle anti dopage");
    plateau[24] = controle_dopage;

    t_case basket;
    basket=creation_case(25, 300, 200, 220, 7, "Basket");
    plateau[25] = sport_equestre;

    t_case foot;
    foot=creation_case(26, 300, 200, 220, 7, "Foot");
    plateau[26] = foot;

    t_case surf;
    surf=creation_case(27, 200, 0, 0,9, "Surf");
    plateau[27] = surf;

    t_case rugby;
    rugby=creation_case(28, 320, 200, 220, 7, "Rugby");
    plateau[28] = rugby;

    t_case athletisme;
    athletisme=creation_case(29, 350, 200, 220, 8, "Athletisme");
    plateau[29] = athletisme;

    t_case comite_olympique2;
    comite_olympique2 = creation_case(5, 0, 0, 0, 10, "Comite olympique");
    plateau[30] = comite_olympique2;

    t_case natation;
    natation=creation_case(31, 400, 200, 220, 8, "Natation");
    plateau[31] = natation;
}

// fonction creation tableau joueur
void creation_tab_joueur(t_joueur tab_joueur[])
{
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
    de[0] = (rand()%6)+1;
    de[1] = (rand()%6)+1;

}

// fonction pour les dés
bool double_de(int* de)
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
void en_faillite(t_joueur tab_joueur[], int i) // En cours par LUC
{
    /* La procédure erifie si le joueur est en faillite
       Si oui le met en faillite
       Prend en paramètre un pointeur sur le joueur
    */
    int choix = 2;
    if (tab_joueur[i].capital<=0) //le joueur ne peut plus rien faire
        {
            tab_joueur[i].en_faillite=true;
            printf("Vous etes en faillite");
            //On doit supprimer ses propriétés
        }


    else if (tab_joueur[i].argent<=0) //le joueur n'a plus d'argent mais encore du capital
        {
            printf("voulez vous abandonner ?: oui[1], non[2]\n");
            scanf("%d",&choix);
            if (choix==1) // Il veut abandonner
                {
                    tab_joueur[i].en_faillite=true;
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
void loyer(t_joueur tab_joueur[], int i, t_case cases) // En cours par Nathan
{
    if ((cases.num_joueur != tab_joueur[i].numero) && (cases.num_joueur != 0) && (cases.groupe_cartes <= 9))
    {
        // le joueur doit payer
        printf("Paye\n");
    }
    else
    {
        printf("Vous n'etes pas sur la case de quelqu'un d'autre, vous ne payez pas\n");
    }
}

void tour(t_joueur tab_joueur[], t_case plateau[], t_banque* p_banque) // en cours par Nathan
{
    for (int i = 0; i < 4; i++)
    {
        en_faillite(tab_joueur, i);
        if (tab_joueur[i].en_faillite)
        {
            // Le joueur ne joue pas

        }
        else
        {
            printf("\n\nC'est le tour de %s\n", tab_joueur[i].nom);
            int de[2];
            int valeurlancerde=lance_de(de);
            salaire(t_joueur tab_joueur[i],valeurlancerde)
            printf("Vous avez fait %d et %d\n", de[0], de[1]);
            if (sortie_prison(de, tab_joueur, i)) // Le joueur sors de prison donc ne joue pas plus pendant ce tour
            {

            }
            else // Le joueur n'est pas en prison                       // continue ici
            {
                // Le joueur joue une fois
                deplacement(de, tab_joueur, i);
                printf("Vous etes a la case %s\n", plateau[tab_joueur[i].position].nom);
                loyer(tab_joueur, i, plateau[tab_joueur[i].position]);
                // acheter_propriete(p_joueur, plateau[p_joueur->position]);
                acheter_maison_hotel(tab_joueur, i, plateau, p_banque);
                if (double_de(de)) // Le joueur a fait un double
                {
                    // Le joueur joue une 2eme fois
                    lance_de(de);
                    printf("Vous avez fait %d et %d\n", de[0], de[1]);
                    deplacement(de, tab_joueur, i);
                    printf("Vous etes a la case %s\n", plateau[tab_joueur[i].position].nom);
                    loyer(tab_joueur, i, plateau[tab_joueur[i].position]);
                    // acheter_propriete(p_joueur, plateau[p_joueur->position]);
                    acheter_maison_hotel(tab_joueur, i, plateau, p_banque);
                    if (double_de(de)) // Le joueur a fait 2 doubles
                    {
                        // Le joueur joue une 3eme fois
                        lance_de(de);
                        printf("Vous avez fait %d et %d\n", de[0], de[1]);
                        deplacement(de, tab_joueur, i);
                        printf("Vous etes a la case %s\n", plateau[tab_joueur[i].position].nom);
                        loyer(tab_joueur, i, plateau[tab_joueur[i].position]);
                        // acheter_propriete(p_joueur, plateau[p_joueur->position]);
                        acheter_maison_hotel(tab_joueur, i, plateau, p_banque);
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

bool acheter_maison_hotel(t_joueur tab_joueur[], int i, t_case plateau[], t_banque* banque) // faire le blindage
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
                            printf("vous pouvez acheter une maison. voulez-vous en acheter une? oui[1]  non[0]\n");//propose d'acheter une maison
                            fflush(stdin);
                            gets(choix);
                        } while ((choix[0] != 48) && (choix[0] != 49) || (strlen(choix) > 1)); // 48 = 0 en code ascii
                        if(choix == 1)
                        {
                            plateau[tab_joueur[i].position].nb_maison+=1;//ajoute une maison
                            tab_joueur[i].argent-=plateau[tab_joueur[i].position].val_maison;//enleve l'argent au joueur
                            banque->nb_maison_restante-=1;//enleve une maison de la banque
                            printf("vous avez achete une maison.\n");
                            printf("Il y a %d maisons sur la case\n", plateau[tab_joueur[i].position].nb_maison);
                            return true;
                        }
                        else if(choix == 0)
                        {
                            printf("vous n'avez pas achete de maison.\n");
                            return false;
                        }
                    }
                    else//il n'a pas assez d'argent
                    {
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
                        if(choix == 1)
                        {
                            plateau[tab_joueur[i].position].nb_hotel+=1;//ajoute l'hotel
                            plateau[tab_joueur[i].position].nb_maison = 0;//on retire les maison
                            tab_joueur[i].argent-=plateau[tab_joueur[i].position].val_hotel;//on enleve l'argent au joueur
                            banque->nb_hotel_restant-=1;//eneleve un hotel de la banque
                            banque->nb_maison_restante+=4;//rajoute les 4 maison a la banque
                            printf("vous avez achete un hotel.\n");
                            return true;
                        }
                        else if(choix == 0)
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

bool achat(t_joueur tab_joueur[i],t_case plateau[i])
{
        if(t_case plateau[i].groupe_cartes >= 9)
       {
           if(t_case plateau[i].num_joueur==0)
          {
               int choix=0
               printf("Voulez-vous acheter cette case ?");
               printf("           si oui : 1           ");
               printf("           si non : 0           ");
               do
              {
                scanf(%d,&choix);
                if(choix!=0||choix!=1)
                   {
                      printf("Erreur : Veuillez saisir 1 pour oui et 0 pour non")
                   {
              {while(choix!=0||choix!=1)
               if(choix==1);
                {
                    if(tab_joueur[i].argent < plateau[tab_joueur[i].position].val_hotel)

                    printf("Fonds insuffisants !");
                    return false;
                  }
                    else if(tab_joueur[i].argent >= plateau[tab_joueur[i].position].valeur)
                  {
                    tab_joueur[i].argent-=plateau[tab_joueur[i].position].valeur;
                    tab_joueur[i].capital+=plateau[tab_joueur[i].position].valeur;
                    tab_joueur[i].capital-=plateau[tab_joueur[i].position].valeur;
                    plateau[tab_joueur[i].position].num_joueur=i;
                    return true;
                  }
                   if(choix==0)
                  {
                      return false;
                  }
              }
          }
            else if(plateau[i].num_joueur!=0)
          {
            printf("Vous ne pouvez pas acheter cette case !");
            return false;
          }
       }
         else if(plateau[i].num_joueur!=0)
       {
         printf("Vous ne pouvez pas acheter cette case !");
         return false;
       }
}

void salaire(t_joueur tab_joueur[i],valeurlancerde)
   {
    int addposition=tab_joueur[i].position+valeurlancerde;
        if (addposition>32)
       {
            tab_joueur[i].position=addposition%32;
            tab_joueur[i].argent+=200;
            tab_joueur[i].capital+=200;
       }
   }
