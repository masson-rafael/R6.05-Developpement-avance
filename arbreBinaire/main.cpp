#include <iostream>
using namespace std;
#include "ArbreBin.h"

int main(void)
{
    cout << "--- TESTS ARBRE BINAIRE ---" << endl;
    ArbreBin<int> abr;
    cout << "Arbre vide ? " << (abr.estVide() ? "Oui" : "Non") << endl;
    
    abr.setRacine(8);
    cout << "Arbre vide apres setRacine(8) ? " << (abr.estVide() ? "Oui" : "Non") << endl;
    cout << "Racine : " << abr.racine() << endl;

    // Ajout d'un sous-arbre
    abr.fG().setRacine(4);
    abr.fD().setRacine(12);

    cout << "Fils gauche : " << abr.fG().racine() << endl;
    cout << "Fils droit  : " << abr.fD().racine() << endl;

    // Sous sous-arbres
    abr.fG().fG().setRacine(2);
    abr.fG().fD().setRacine(6);

    cout << "Fils gauche du fils gauche : " << abr.fG().fG().racine() << endl;
    cout << "Fils droit du fils gauche  : " << abr.fG().fD().racine() << endl;

    cout << "Hauteur de l'arbre : " << abr.hauteur() << endl;

    return 0;
}