#include <iostream>
using namespace std;
#include "Liste.h"

int main(void)
{
    Liste liste1;

    liste1.insererDebut(1);
    liste1.insererDebut(2);
    liste1.insererDebut(5);

    cout << liste1.toString() << endl << to_string(liste1.nbElements(liste1)) << endl << to_string(liste1.nbElementsRec(liste1)) << endl << endl;

    liste1.supprimerDebut();

    cout << liste1.toString() << endl << to_string(liste1.nbElements(liste1)) << endl << to_string(liste1.nbElementsRec(liste1)) << endl << endl;

    while(true){}
    
}