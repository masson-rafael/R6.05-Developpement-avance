#include <iostream>
using namespace std;
#include "ABR.h"
#include <queue>

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
void parcoursLarg(ArbreBin<int>& abr);

ABR<int> buildTree();

int main(void)
{
    cout << "--- TESTS ABR ---" << endl;
    ABR<int> abrTest;
    cout << "Arbre vide ? " << (abrTest.estVide() ? "Oui" : "Non") << endl;
    
    ABR<int> abr = buildTree(); // pour tester la construction d'un arbre
    cout << "Arbre vide apres build ? " << (abr.estVide() ? "Oui" : "Non") << endl;
    
    cout << "Hauteur de l'arbre : " << abr.hauteur() << endl;

    cout << "\nPrefixe attendu : 5 2 1 4 3 8 7 6 9" << endl;
    cout << "Prefixe obtenu  : ";
    parcoursPre(abr);
    cout << endl;

    cout << "\nInfixe attendu : 1 2 3 4 5 6 7 8 9" << endl;
    cout << "Infixe obtenu  : ";
    parcoursInf(abr);
    cout << endl;

    cout << "\nPostfixe attendu : 1 3 4 2 6 7 9 8 5" << endl;
    cout << "Postfixe obtenu  : ";
    parcoursPost(abr);
    cout << endl;

    cout << "\nLargeur attendu : 5 2 8 1 4 7 9 3 6" << endl;
    cout << "Largeur obtenu  : ";
    parcoursLarg(abr);
    cout << endl;

    bool recherche6 = abr.rechercher(6);
    bool recherche42 = abr.rechercher(42);
    cout << "\nrechercher(6)  : " << (recherche6 ? "vrai" : "faux") << " (attendu: vrai)" << endl;
    cout << "rechercher(42) : " << (recherche42 ? "vrai" : "faux") << " (attendu: faux)" << endl;

        cout << "\n--- TESTS SUPPRIMER(e) ---" << endl;

        // Cas 1 : suppression dans arbre vide
        ABR<int> tVide;
        tVide.supprimer(10);
        cout << "Cas vide (supprimer 10) : estVide=" << (tVide.estVide() ? "vrai" : "faux")
            << " (attendu: vrai)" << endl;

        // Cas 2 : suppression d'une valeur absente
        ABR<int> tAbsent = buildTree();
        tAbsent.supprimer(42);
        cout << "Cas absent (supprimer 42), largeur attendu: 5 2 8 1 4 7 9 3 6" << endl;
        cout << "Largeur obtenu : ";
        parcoursLarg(tAbsent);
        cout << endl;

        // Cas 3 : suppression d'une feuille (3)
        ABR<int> tFeuille = buildTree();
        tFeuille.supprimer(3);
        cout << "Cas feuille (supprimer 3), largeur attendu: 5 2 8 1 4 7 9 6" << endl;
        cout << "Largeur obtenu : ";
        parcoursLarg(tFeuille);
        cout << endl;

        // Cas 4a : suppression d'un noeud de degré 1 (fils gauche uniquement, 7)
        ABR<int> tDeg1G = buildTree();
        tDeg1G.supprimer(7);
        cout << "Cas degre 1 gauche (supprimer 7), largeur attendu: 5 2 8 1 4 6 9 3" << endl;
        cout << "Largeur obtenu : ";
        parcoursLarg(tDeg1G);
        cout << endl;

        // Cas 4b : suppression d'un noeud de degré 1 (fils droit uniquement, racine 5)
        ABR<int> tDeg1D;
        tDeg1D.ajouter(5);
        tDeg1D.ajouter(8);
        tDeg1D.supprimer(5);
        cout << "Cas degre 1 droit (supprimer racine 5), largeur attendu: 8" << endl;
        cout << "Largeur obtenu : ";
        parcoursLarg(tDeg1D);
        cout << endl;

        // Cas 5 : suppression d'un noeud de degré 2 (racine 5)
        ABR<int> tDeg2 = buildTree();
        tDeg2.supprimer(5);
        cout << "Cas degre 2 (supprimer racine 5), largeur attendu: 6 2 8 1 4 7 9 3" << endl;
        cout << "Largeur obtenu : ";
        parcoursLarg(tDeg2);
        cout << endl;

        // Cas bonus : supprimer l'unique racine (arbre a un seul element)
        ABR<int> tUnique;
        tUnique.ajouter(11);
        tUnique.supprimer(11);
        cout << "Cas racine unique (supprimer 11) : estVide=" << (tUnique.estVide() ? "vrai" : "faux")
            << " (attendu: vrai)" << endl;

    return 0;
}

ABR<int> buildTree()
{
    ABR<int> arbre;
    arbre.ajouter(5);
    arbre.ajouter(2);
    arbre.ajouter(8);
    arbre.ajouter(1);
    arbre.ajouter(4);
    arbre.ajouter(7);
    arbre.ajouter(9);
    arbre.ajouter(3);
    arbre.ajouter(6);

    return arbre;
}

void parcoursPre(ArbreBin<int>& abr) {
    if(abr.estVide()) return;
    cout << abr.racine() << " ";
    parcoursPre(abr.fG());
    parcoursPre(abr.fD());
}

void parcoursInf(ArbreBin<int>& abr) {
    if(abr.estVide()) return;
    parcoursInf(abr.fG());
    cout << abr.racine() << " ";
    parcoursInf(abr.fD());
}

void parcoursPost(ArbreBin<int>& abr) {
    if(abr.estVide()) return;
    parcoursPost(abr.fG());
    parcoursPost(abr.fD());
    cout << abr.racine() << " ";
}

void parcoursLarg(ArbreBin<int>& abr) {
    std::queue<ArbreBin<int>*> file;
    if(!abr.estVide()) file.push(&abr);
    while(!file.empty()){
        ArbreBin<int>* tete = file.front();
        cout << tete->racine() << " ";
        file.pop();
        if(!tete->fG().estVide()){
            file.push(&tete->fG());
        }
        if(!tete->fD().estVide()){
            file.push(&tete->fD());
        }
    }
}