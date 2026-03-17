#include <iostream>
using namespace std;
#include "Liste.h"

int nbElements(const Liste&);
int nbElementsRec(const Liste&);

int main(void)
{
    Liste liste1;

    liste1.insererDebut(1);
    liste1.insererDebut(2);
    liste1.insererDebut(5);

    cout << liste1.toString() << endl << to_string(nbElements(liste1)) << endl << to_string(nbElementsRec(liste1)) << endl << liste1.appartient(5) << endl << endl;

    liste1.supprimerDebut();

    cout << liste1.toString() << endl << to_string(nbElements(liste1)) << endl << to_string(nbElementsRec(liste1)) << endl << liste1.appartient(5) << endl << endl;

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