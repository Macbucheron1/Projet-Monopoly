#include "Header.h"

int main()
{
    char* liste_corruption[TAILLE_LISTE] =   //cartes chances
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

    srand(time(0));
    t_joueur tab_joueur[4];
    t_banque banque = creation_banque();
    t_banque* p_banque = &banque;
    t_case plateau[TAILLE_PLATEAU];
    creation_plateau(plateau);
    menu(tab_joueur, plateau, p_banque, liste_corruption);

}
