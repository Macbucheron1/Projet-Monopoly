#include "chance_commu_header.h"

int main()
{
    char* corruption[TAILLE_LISTE] =   //cartes chances
    {
        "Vous etes libere de prison\n\nCette carte peut etre conservee jusqu'a ce qu'elle soit utilisee ou vendu\n",
        "Rendez-vous à Avenue Havre-Caumartin\nSi vous passez par la case Village Olympique recevez 200e\n",
        "Rendez-vous Rue de la paix\n", //derniere case du plateau donc pas 200e
        "Faites des reparation dans toutes vos maisons\nVersez 25e pour chaque maisons\nVersez 100e pour chaque hotel\n",
        "Vous avez gagner le prix de mots coisés recevez 100e\n",
        "Votre immeuble et votre pret rapportent\nVous devez toucher 150e\n",
        "Avancer au Boulevard de la Vilette\nSi vous passez par la case Village Olympique recevez 200e\n",
        "Allez à gare de lyon\nSi vous passez par la case Village Olympique recevez 200e\n",
        "Vous etes impose pour les reparations de voirie a raisons de\n40e par maisons\n115e par hotel\n",
        "La Banque vous verse 50e de dividendes\n",
        "Avancez jusqu'a la case depart\n <--------|\n",
        "Payer pour frais de Scolarité 150e\n",
        "Reculez de 3 cases\n",
        "Amende pour exces de vitesse 15e\n",
        "Allez en prison\nAvancez tout droit en prison\nNe passez pas par la case Village Olympique\nNe recevez pas 200e\n",
        "Amende pour ivresse 20e\n"
    };

        char* comite_olympique[TAILLE_LISTE] =   //cartes caisse de communautée
    {
        "Vous etes libere de prison\n\nCette carte peut etre conservee jusqu'a ce qu'elle soit utilisee ou vendu\n",
        "Payez une amende de 10e[1] ou bien tirez une carte chance[2]:\n",
        "La vente de votre stock vous rapporte 50e\n",
        "C'est votre anniversaire\nChaque joueur doit vous donner 10e\n",
        "Erreur de la Banque en votre faveur\nRecevez 200e\n",
        "Payer l'hopital 100e\n",
        "Les contributions vous remboursent la somme de 20e\n",
        "Vous heritez 100e\n",
        "Retournez à Belleville\n",
        "Recevez votre interet sur l'emprunt à 7% 25e\n",
        "Avancez jusqu'a la case depart\n <--------|\n",
        "Payez la note du medecin 50e\n",
        "Vous avez gagner le deuxieme prix de beaute\nRecevez 10e\n",
        "Payer votre police d'assurance s'elevant à 50e\n",
        "Allez en prison\nAvancez tout droit en prison\nNe passez pas par la case Village Olympique\nNe recevez pas 200e\n",
        "Recevez votre revenu annuel 100e\n"
    };


    t_joueur joueur1;
    joueur1=creation_joueur(1);

    t_joueur joueur2;
    joueur2=creation_joueur(2);

    t_joueur joueur3;
    joueur3=creation_joueur(3);

    t_joueur joueur4;
    joueur4=creation_joueur(4);

    afficher_joueur(joueur1);

    t_joueur *p_joueur1=&joueur1;
    t_joueur *p_joueur2=&joueur2;
    t_joueur *p_joueur3=&joueur3;
    t_joueur *p_joueur4=&joueur4;

    transaction(p_joueur1,-200);
    afficher_joueur(joueur1);

    tirer_corruption(p_joueur1,corruption);
    afficher_joueur(joueur1);

    tirer_comite(p_joueur1,p_joueur2,p_joueur3,p_joueur4,comite_olympique,corruption);
    afficher_joueur(joueur1);

    p_joueur2->en_faillite=true;
    p_joueur3->en_faillite=true;
    p_joueur4->en_faillite=true;
    victoire(p_joueur1,p_joueur2,p_joueur3,p_joueur4);

    return 0;
}
