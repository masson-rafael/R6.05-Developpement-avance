#include <iostream>
using namespace std;
#include "Liste.h"
#include "Pile.h"

int nbElements(const Liste&);
int nbElementsRec(const Liste&);

int main(void)
{
    cout << "--- TESTS LISTE ---" << endl;
    Liste liste1;
    liste1.insererDebut(1);
    liste1.insererDebut(2);
    liste1.insererDebut(5);
    cout << liste1.toString() << to_string(nbElements(liste1)) << endl << to_string(nbElementsRec(liste1)) << endl << liste1.appartient(5) << endl;

    liste1.supprimerDebut();
    cout << liste1.toString() << to_string(nbElements(liste1)) << endl << to_string(nbElementsRec(liste1)) << endl << liste1.appartient(5) << endl << endl;

    cout << "--- TESTS PILE ---" << endl;
    Pile pile1;
    cout << "Pile vide ? " << (pile1.estVide() ? "Oui" : "Non") << endl;
    pile1.empiler(10);
    pile1.empiler(20);
    pile1.empiler(30);
    cout << "Pile apres empiler(10, 20, 30) : \n" << pile1.toString();
    cout << "Sommet de la pile : " << pile1.sommet() << endl;
    
    pile1.depiler();
    cout << "Pile apres un depiler() : \n" << pile1.toString();
    cout << "Nouveau sommet : " << pile1.sommet() << endl;

    while(true){}
}

int nbElements(const Liste& l) {
    int compteur = 0;
    const Liste* courant = &l;
    while (!courant->estVide()) {
        compteur++;
        courant = &courant->suivant();
    }
    return compteur;
}

int nbElementsRec(const Liste& l) {
    if (l.estVide()) {
        return 0;
    }
    return 1 + nbElementsRec(l.suivant());
}