#include "chance_commu_header_v3.h"

int main()
{
    //liste de cartes

    char* corruption[TAILLE_LISTE] =   //cartes chances
    {
        "Vous etes libere de Suspension\nCette carte peut etre conservee jusqu'a ce qu'elle soit utilisee ou vendu\n",
        "Rendez-vous au Handball\nSi vous passez par la case Depart recevez 200e\n",
        "Rendez-vous a la Natation\n",
        "Faites des dons a des associations\nVersez 25e pour chaque medailles\nVersez 100e pour chaque titres\n",//a modifier
        "Vous avez gagner le prix du meilleur emabassadeur sportif 100e\n",
        "Votre medailles et titres vous rapportent\nVous devez toucher 150e\n",
        "Avancer au tennis\nSi vous passez par la case Depart recevez 200e\n",
        "Allez au skate\nSi vous passez par la case Depart recevez 200e\n",
        "Vous payer votre tournee au bar pour vos compatriotes a raisons de\n40e par medaille\n115e par titre\n",// a modifier
        "La Banque vous verse 50e pour vos performances\n",
        "Avancez jusqu'a la case depart\n <--------|\n",
        "Payer pour des frais d'equipements 150e\n",
        "Reculez de 3 cases\n",
        "Amende pour non respect des regles 15e\n",
        "Le resultat de votre controle anti-dopage est positif\nAvancez tout droit en Suspension\nNe passez pas par la case Depart\nNe recevez pas 200e\n",
        "Amende pour pollution sonore au Village Olympique 20e\n"
    };

    char* comite_olympique[TAILLE_LISTE] =   //cartes caisse de communautée
    {
        "Vous etes libere de Suspension\nCette carte peut etre conservee jusqu'a ce qu'elle soit utilisee ou vendu\n",
        "Payez une amende de 10e[1] ou bien tirez une carte corruption[2]:\n",
        "La vente de vos produits derives vous rapporte 50e\n",
        "C'est votre anniversaire\nChaque joueur doit vous donner 10e\n",
        "Erreur de la Banque en votre faveur\nRecevez 200e\n",
        "Payer l'hopital pour votre operation 100e\n",
        "Le commite vous rembourse la somme de 20e\n",
        "Vous heritez 100e\n",
        "Retournez au Sport equestre\n",
        "Recevez votre salaire 25e\n",
        "Avancez jusqu'a la case depart\n <--------|\n",
        "Payez la note du medecin 50e\n",
        "Vous avez gagner le deuxieme prix de beaute\nRecevez 10e\n", //a modifier
        "Payer votre assurance s'elevant a 50e\n",
        "Le resultat de votre controle anti-dopage est positif\nAvancez tout droit en Suspension\nNe passez pas par la case Depart\nNe recevez pas 200e\n",
        "Vous etes nomme atlhete de l'annee\nRecevez 100e\n"
    };

    t_joueur tab_joueur[4];
    creation_tab_joueur(tab_joueur);
    printf("\n");

    //pour les test

    t_joueur *p_joueur1=&tab_joueur[0];
    t_joueur *p_joueur2=&tab_joueur[1];
    t_joueur *p_joueur3=&tab_joueur[2];
    t_joueur *p_joueur4=&tab_joueur[3];

    p_joueur1->position=30;

    /* ca marche pas mon test (pour case 3 et 8 de corruption)
    p_joueur1->proprietes[1]=creation_case(1,1,1,1,1);
    p_joueur1->proprietes[1].nb_maison=2;
    p_joueur1->proprietes[2]=creation_case(2,2,2,2,2);
    p_joueur1->proprietes[2].nb_hotel=1;*/

    tirer_corruption(tab_joueur,0,corruption);
    printf("\n");
    afficher_joueur(tab_joueur[0]);

    tirer_comite(tab_joueur,0,comite_olympique,corruption);
    printf("\n");
    afficher_joueur(tab_joueur[0]);

    //verification pour la victoire

    p_joueur2->en_faillite=true;
    p_joueur3->en_faillite=true;
    p_joueur4->en_faillite=true;
    victoire(tab_joueur);

    return 0;

}
