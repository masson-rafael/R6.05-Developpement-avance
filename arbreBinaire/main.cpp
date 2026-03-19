#include <iostream>
using namespace std;
#include "ArbreBin.h"

ArbreBin<int> buildTree();

/* Préfixe : on traite la racine, puis le sous arbre gauche, puis
le sous arbre droit */
void parcoursPre(ArbreBin<int>& abr);

/* Infixe : on traite le sous arbre gauche, puis la racine, puis le
sous arbre droit */
void parcoursInf(ArbreBin<int>& abr);

/* Postfixe : on traite le sous arbre gauche, puis le sous arbre
droit, puis la racine */
void parcoursPost(ArbreBin<int>& abr);

/* on parcourt tous les sommets de
profondeur p avant ceux de profondeur p+1 */
void parcoursLargeur(ArbreBin<int>& abr);

int main(void)
{
    cout << "--- TESTS ARBRE BINAIRE ---" << endl;
    ArbreBin<int> abrTest;
    cout << "Arbre vide ? " << (abrTest.estVide() ? "Oui" : "Non") << endl;
    
    ArbreBin<int> abr = buildTree(); // pour tester la construction d'un arbre
    cout << "Arbre vide apres build ? " << (abr.estVide() ? "Oui" : "Non") << endl;
    
    cout << "Hauteur de l'arbre : " << abr.hauteur() << endl;

    cout << "\nParcours Prefixe attendu :  6 4 3 2 5 9 8 7 1 \n";
    cout << "Parcours Prefixe test :     ";
    parcoursPre(abr);
    cout << endl;
    
    cout << "\nParcours Infixe attendu :  3 4 5 2 9 6 7 1 8 \n";
    cout << "Parcours Infixe test :     ";
    parcoursInf(abr);
    cout << endl;
    
    cout << "\nParcours Postfixe attendu :  3 5 9 2 4 1 7 8 6 \n";
    cout << "Parcours Postfixe test :     ";
    parcoursPost(abr);
    cout << endl;
    
    cout << "\nParcours Largeur attendu :  6 4 8 3 2 7 5 9 1 \n";
    cout << "Parcours Largeur test :     ";
    parcoursLargeur(abr);
    cout << endl;

    return 0;
}

ArbreBin<int> buildTree()
{
    ArbreBin<int> arbre;
    arbre.setRacine(6);

    // Arbre gauche (diapo 29)
    arbre.fG().setRacine(4);
    arbre.fG().fG().setRacine(3);
    arbre.fG().fD().setRacine(2);
    arbre.fG().fD().fG().setRacine(5);
    arbre.fG().fD().fD().setRacine(9);

    // Arbre Droit
    arbre.fD().setRacine(8);
    arbre.fD().fG().setRacine(7);
    arbre.fD().fG().fD().setRacine(1);

    return arbre;
}

void parcoursPre(ArbreBin<int>& abr) {
    if(abr.estVide()) { return; }
    cout << abr.racine() << " ";
    parcoursPre(abr.fG());
    parcoursPre(abr.fD());
}

void parcoursInf(ArbreBin<int>& abr) {
    if(abr.estVide()) { return; }
    parcoursInf(abr.fG());
    cout << abr.racine() << " ";
    parcoursInf(abr.fD());
}

void parcoursPost(ArbreBin<int>& abr) {
    if(abr.estVide()) { return; }
    parcoursPost(abr.fG());
    parcoursPost(abr.fD());
    cout << abr.racine() << " ";
}

void parcoursLargeur(ArbreBin<int>& abr) {
    cout << "test";
}