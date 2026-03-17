#include <iostream>
using namespace std;
#include "Liste.h"

int main(void)
{
    Liste liste1;

    liste1.insererDebut(1);
    liste1.insererDebut(2);
    liste1.insererDebut(5);

    cout << liste1.toString() << endl;

    liste1.supprimerDebut();

    cout << liste1.toString() << endl;

    while(true){}
    
}