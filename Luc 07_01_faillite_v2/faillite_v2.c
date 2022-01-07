#include "faillite_header_v2.h"

//struct

//instanciation
t_joueur creation_joueur(int num)
{
    t_joueur j;
    fflush(stdin);
    printf("Veuillez entrer le nom du joueur :\n");
    gets(j.nom);
    j.numero=num;
    j.position=0;
    j.argent=1500;
    j.capital=1500;
    j.en_prison=false;
    j.tour_prison=0;
    j.carte_sortie_prison=0;
    j.nb_propriete=0; //NOUVEAU

    j.en_faillite=false;

    return j;
}

// fonction creation d'instance
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes, char* nom, int couleur_fond, int couleur_texte, int valeur_hypotheque, int base_loyer, int loyer_1_maison, int loyer_2_maison, int loyer_3_maison, int loyer_4_maison, int loyer_1_hotel)
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
t_banque creation_banque(void) // LUC
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
//afichage

void afficher_joueur(t_joueur j)
{
    printf("Voici le JOUEUR:\n");
    printf("numero:%d\nnom:%s\nposition:%d\nargent:%d\ncapital:%d\npropriete:%d\netes-vous en prison?:%d\ncombien de tour en prison:%d\nnb de cartes sorites de prison:%d\nest-il en faillite ?:%d\n",j.numero,j.nom,j.position,j.argent,j.capital,j.proprietes,j.en_prison,j.tour_prison,j.carte_sortie_prison,j.en_faillite);
    printf("\n"); //pour de la lisibilité
}

// transaction

void transaction(t_joueur tab_joueur[],int i,int montant)
{
    tab_joueur[i].argent+=montant;
    tab_joueur[i].capital+=montant;
    /* optionel
    printf("Joueur %d:",tab_joueur[i].numero);
    if(montant>0)
    {
        printf("Vous avez ete credite de %d euros\n\n",montant);
    }
    if(montant<0)
    {
        printf("Vous avez ete debite de %d euros\n\n",montant);
    }*/
}

//v2

// fonction creation tableau joueur
void creation_tab_joueur(t_joueur tab_joueur[])
{
    char choix[10];
    do
    {
        printf("Combien de joueurs vont jouer ?\nIl doit y avoir minimum 2 joueurs et maximum 4 joueurs : ");
        fflush(stdin);
        gets(choix);
    }
    while (((choix[0] != 50) && (choix[0] != 51) && (choix[0] != 52)) || (strlen(choix) > 1));   // 48 = 0 en code ascii
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
        j3.nb_propriete=0; //NOUVEAU
        tab_joueur[2] = j3;

        t_joueur j4;
        strcpy(j4.nom, "j4");
        j4.numero = 4;
        j4.position=0;
        j4.argent=1500;
        j4.capital=1500;
        j4.en_prison=false;
        j4.tour_prison=0;
        j4.carte_sortie_prison=0;
        j4.en_faillite = true;
        j4.nb_propriete=0; //NOUVEAU
        tab_joueur[3] = j4;



    }
    if (choix[0] == 51)
    {
        tab_joueur[0] = creation_joueur(1);
        tab_joueur[1] = creation_joueur(2);
        tab_joueur[2] = creation_joueur(3);

        t_joueur j4;
        strcpy(j4.nom, "j4");
        j4.numero = 4;
        j4.position=0;
        j4.argent=1500;
        j4.capital=1500;
        j4.en_prison=false;
        j4.tour_prison=0;
        j4.carte_sortie_prison=0;
        j4.en_faillite = true;
        j4.nb_propriete=0; //NOUVEAU
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

void afficher_case_jeu(t_case c) // LUC
{
    /* Procédure qui affiche une instance de case
       Prend en paramètre une case
       Ne renvoie rien
    */
    printf("nom: %s\nprix d'achat:%d\nnombre de maison:%d\nNombre d'Hotel hotel:%d\nprix dachat d'une maison:%d\nprix d'achat d'un hotel:%d\nquel groupe de carte:%d\nLoyer sans maison:%d\n",c.nom,c.valeur,c.nb_maison,c.nb_hotel,c.val_maison,c.val_hotel,c.groupe_cartes, c.base_loyer);
    if (c.hypoteque == true)
    {
        printf("Cette propriete a ete hypotheque\n");
    }
    printf("\n"); //pour de la lisibilité
}


void afficher_propriete_joueur(t_joueur tab_joueur[],int i, t_case plateau[])
{
    int nb_proprietes=tab_joueur[i].nb_propriete;
    if (nb_proprietes==0)
    {
        printf("le joueur n'a pas de propriete\n");
    }
    else
    {
        for (int j=0; j<nb_proprietes; j++)
        {
            int iterateur=0;
            printf("Nom case: ");
            while(tab_joueur[i].proprietes[j].nom[iterateur] != '\0')   //\0 correspond à la fin de chaine
            {
                printf("%c",tab_joueur[i].proprietes[j].nom[iterateur]);
                iterateur++;
            }
            printf("\n");
            printf("position:%d\nvaleur:%d\nnb maison:%d\nnb hotel:%d\n\n",tab_joueur[i].proprietes[j].position,tab_joueur[i].proprietes[j].valeur,tab_joueur[i].proprietes[j].nb_maison,tab_joueur[i].proprietes[j].nb_hotel);
        }
    }
}

void creation_plateau(t_case* plateau)
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
    sport_equestre=creation_case(1, 60, 50, 60,1, "Sport Equestre", 6, 15, 60, 2, 10, 30, 90, 160, 250);
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
    corruption1 = creation_case(5, 0, 0, 0, 11, "Corruption",13, 15, 0, 0, 0, 0, 0, 0, 0);
    plateau[5] = corruption1;

    t_case canoe;
    canoe=creation_case(6, 60, 50, 60, 2, "Canoe",3, 15, 50, 6, 30, 90, 270, 400, 550);
    plateau[6] = canoe;

    t_case voile;
    voile=creation_case(7, 60, 50, 60, 2, "Voile",3, 15, 60, 8, 40, 100, 300, 450, 600);
    plateau[7] = voile;

    t_case suspension;
    suspension = creation_case(8, 0, 0, 0, 12, "Suspension", 7, 0, 0, 0, 0, 0, 0, 0, 0);
    plateau[8] = suspension;

    t_case tennis;
    tennis=creation_case(9, 140, 100, 110,3, "Tennis",5, 15, 70, 10, 50, 150, 450, 625, 750);
    plateau[9] = tennis;

    t_case golf;
    golf=creation_case(10, 140, 100, 110,3, "Golf", 5, 15, 70, 10, 50, 150, 450, 625, 750);
    plateau[10] = golf;

    t_case skate;
    skate=creation_case(11, 200, 0, 0,9, "Skate", 15, 0, 100, 25, 0, 0, 0, 0, 0);
    plateau[11] = skate;

    t_case tir_a_l_arc;
    tir_a_l_arc=creation_case(12, 160, 100, 110,3, "Tir a l'arc",5, 15, 80, 12, 60, 180, 500, 700, 900);
    plateau[12] = tir_a_l_arc;

    t_case lutte;
    lutte=creation_case(13, 180, 100, 110, 4, "Lutte",8, 15, 90, 14, 70, 200, 550, 700, 950);
    plateau[13] = lutte;

    t_case comite_olympique1;
    comite_olympique1 = creation_case(14, 0, 0, 0, 10, "Comite olympique",9, 15, 0, 0, 0, 0, 0, 0, 0);
    plateau[14] = comite_olympique1;

    t_case halterophilie;
    halterophilie=creation_case(15, 200, 100, 110, 4, "Halterophilie", 8, 15, 100, 16, 80, 220, 600, 800, 1000);
    plateau[15] = halterophilie;

    t_case village_olympique;
    village_olympique = creation_case(16, 0, 0, 0, 13, "Village olympique",7, 0, 0, 0, 0, 0, 0, 0, 0);
    plateau[16] = village_olympique;

    t_case Volley;
    Volley=creation_case(17, 220, 150, 165, 5, "Volley",4, 15, 110, 18, 90, 250, 700, 875, 1050);
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
    basket=creation_case(25, 300, 200, 220, 7, "Basket",2, 15, 150, 26, 130, 390, 900, 1100, 1275);
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
    comite_olympique2 = creation_case(5, 0, 0, 0, 10, "Comite olympique",9,15, 0, 0, 0, 0, 0, 0, 0);
    plateau[30] = comite_olympique2;

    t_case natation;
    natation=creation_case(31, 400, 200, 220, 8, "Natation",1,15, 200, 50, 200, 600, 1400, 1700, 2000);
    plateau[31] = natation;
}

void propriete_a_joueur(t_joueur tab_joueur[],int i, t_case plateau[],int j) //ajoute une propriete dans la liste de prop d'un joueur
{
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

void enlever_propriete_joueur(t_joueur tab_joueur[],int i,t_case plateau[],int j) //enleve la propriete choisie dns la liste de prop d'un joueur , m=0 banque, m=1 autre joueur
{
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
void hypotheque_faillite(t_joueur tab_joueur[],int i, t_case plateau[], t_banque* p_banque)
{
    /* fonction qui permet d'hypotéquer une propriétée
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

// fonction d'instance
int update_propriete(t_joueur tab_joueur[],int i, t_case plateau[]) // NATHAN
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

//faillite

void en_faillite(t_joueur tab_joueur[],int i,int montant,t_banque* p_banque,int proprietaire,t_case plateau[])
{
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
                //sert a verifier qu'il reste des propriété a hypothequer
                printf("Vous n'avez pas assez d'argent pour payer, vous allez devoir hypotequer\n");
                hypotheque_faillite(tab_joueur,i,plateau,p_banque);//appel de la fonction d'hypotheque pour la faillite

                if (tab_joueur[i].argent<montant)
                {
                    int reste_a_payer=montant-tab_joueur[i].argent;
                    printf("Voici votre argent apres l'hypoteque %d euros, il vous reste %d euros a payer\n",tab_joueur[i].argent,reste_a_payer);
                }


                iterateur+=1;//nombre de proprieté hypothequé
            }
            while (iterateur==nb_prop_j ^ tab_joueur[i].argent<montant);//verifier qu'on a plus rien a hypoteque ou que les hypoteque on rembourser le montant

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
