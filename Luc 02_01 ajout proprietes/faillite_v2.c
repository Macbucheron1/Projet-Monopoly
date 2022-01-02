#include "faillite_header_v2.h"

//struct

//instanciation
t_joueur creation_joueur(int numero)
{
    t_joueur j;
    fflush(stdin);

    printf("Veuillez entrer le nom du joueur :\n");
    gets(j.nom);
    j.numero=numero;
    j.position=0;
    j.argent=1500;
    j.capital=1500;
    j.en_prison=false;
    j.tour_prison=0;
    j.carte_sortie_prison=0;
    j.nb_propriete=0;

    j.en_faillite=false;

    return j;
}

// fonction creation d'instance
t_case creation_case(int position,int valeur, int val_maison, int val_hotel, int groupe_cartes, char* nom, int couleur_fond, int couleur_texte)
{
    /* Fonction qui créée une case
       Prend en paramètre toutes ses caractéristique
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

    return c;
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
    while ((choix[0] != 50) && (choix[0] != 51) && (choix[0] != 52) || (strlen(choix) > 1));   // 48 = 0 en code ascii
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
        j4.numero = 4;
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
        j4.numero = 4;
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
            printf("Nom case:");
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

// fonction creation plateau
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
    depart=creation_case(0,0,0,0,16,"depart",7,0);
    plateau[0]= depart;

    t_case sport_equestre;
    sport_equestre=creation_case(1, 60, 50, 60,1, "Sport Equestre", 6, 15);
    plateau[1] = sport_equestre;

    t_case waterpolo;
    waterpolo=creation_case(2, 60, 50, 60,1, "Waterpolo", 6, 15);
    plateau[2] = waterpolo;

    t_case breaking;
    breaking=creation_case(3, 200, 0, 0,9, "Breaking",15, 0);
    plateau[3] = breaking;

    t_case aviron;
    aviron=creation_case(4, 60, 50, 60,2, "Aviron",3, 15);
    plateau[4] = aviron;

    t_case corruption1;
    corruption1 = creation_case(5, 0, 0, 0, 11, "Corruption",13, 15);
    plateau[5] = corruption1;

    t_case canoe;
    canoe=creation_case(6, 60, 50, 60, 2, "Canoe",3, 15);
    plateau[6] = canoe;

    t_case voile;
    voile=creation_case(7, 60, 50, 60, 2, "Voile",3, 15);
    plateau[7] = voile;

    t_case suspension;
    suspension = creation_case(8, 0, 0, 0, 12, "Suspension", 7, 0);
    plateau[8] = suspension;

    t_case tennis;
    tennis=creation_case(9, 140, 100, 110,3, "Tennis",5, 15);
    plateau[9] = tennis;

    t_case golf;
    golf=creation_case(10, 140, 100, 110,3, "Golf", 5, 15);
    plateau[10] = golf;

    t_case skate;
    skate=creation_case(11, 200, 0, 0,9, "Skate", 15, 0);
    plateau[11] = skate;

    t_case tir_a_l_arc;
    tir_a_l_arc=creation_case(12, 160, 100, 110,3, "Tir a l'arc",5, 15);
    plateau[12] = tir_a_l_arc;

    t_case lutte;
    lutte=creation_case(13, 180, 100, 110, 4, "Lutte",8, 15);
    plateau[13] = lutte;

    t_case comite_olympique1;
    comite_olympique1 = creation_case(14, 0, 0, 0, 10, "Comite olympique",9, 15);
    plateau[14] = comite_olympique1;

    t_case halterophilie;
    halterophilie=creation_case(15, 200, 100, 110, 4, "Halterophilie", 8, 15);
    plateau[15] = halterophilie;

    t_case village_olympique;
    village_olympique = creation_case(16, 0, 0, 0, 13, "Village olympique",7, 0);
    plateau[16] = village_olympique;

    t_case Volley;
    Volley=creation_case(17, 220, 150, 165, 5, "Volley",4, 15);
    plateau[17] = Volley;

    t_case handball;
    handball=creation_case(18, 220, 150, 165, 5, "Handball",4, 15);
    plateau[18] = handball;

    t_case escalade;
    escalade=creation_case(19, 200, 0, 0,9, "Escalade", 15, 0);
    plateau[19] = escalade;

    t_case amende;
    amende = creation_case(20, 0, 0, 0, 14, "Amende", 12, 15);
    plateau[20] = amende;

    t_case corruption2;
    corruption2 = creation_case(5, 0, 0, 0, 11, "Corruption",13, 15);
    plateau[21] = corruption2;

    t_case judo;
    judo=creation_case(22, 260, 150, 165,6, "Judo", 14, 0);
    plateau[22] = judo;

    t_case boxe;
    boxe=creation_case(23, 280, 150, 165,6, "Boxe", 14, 0);
    plateau[23] = boxe;

    t_case controle_dopage;
    controle_dopage = creation_case(24, 0, 0, 0, 15, "Controle dopage",7,0);
    plateau[24] = controle_dopage;

    t_case basket;
    basket=creation_case(25, 300, 200, 220, 7, "Basket",2, 15);
    plateau[25] = basket;

    t_case foot;
    foot=creation_case(26, 300, 200, 220, 7, "Foot", 2, 15);
    plateau[26] = foot;

    t_case surf;
    surf=creation_case(27, 200, 0, 0,9, "Surf",15, 0);
    plateau[27] = surf;

    t_case rugby;
    rugby=creation_case(28, 320, 200, 220, 7, "Rugby", 2, 15);
    plateau[28] = rugby;

    t_case athletisme;
    athletisme=creation_case(29, 350, 200, 220, 8, "Athletisme",1,15);
    plateau[29] = athletisme;

    t_case comite_olympique2;
    comite_olympique2 = creation_case(5, 0, 0, 0, 10, "Comite olympique",9,15);
    plateau[30] = comite_olympique2;

    t_case natation;
    natation=creation_case(31, 400, 200, 220, 8, "Natation",1,15);
    plateau[31] = natation;
}

void propriete_a_joueur(t_joueur tab_joueur[],int i, t_case plateau[],int j)
{
    int nb_prop_j=tab_joueur[i].nb_propriete;
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

    plateau[j].num_joueur=tab_joueur[i].numero;
    tab_joueur[i].nb_propriete+=1;
}

//faillite

bool en_faillite(t_joueur tab_joueur[],int i,int montant,t_banque* b,int proprietaire)//pas fait encore
{

}
