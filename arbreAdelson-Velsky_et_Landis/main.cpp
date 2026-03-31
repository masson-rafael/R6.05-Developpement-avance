#include <iostream>
using namespace std;
#include "AVL.h"
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

AVL<int> buildTree();

int main(void)
{
    cout << "--- TESTS AVL ---" << endl;

    AVL<int> avl;
    cout << "Arbre vide ? " << (avl.estVide() ? "Oui" : "Non") << endl;

    int valeurs[] = {30, 20, 10, 40, 50, 25, 5, 35, 45};
    int n = sizeof(valeurs) / sizeof(valeurs[0]);

    cout << "\nInsertions progressives (visualisation en largeur)" << endl;
    for (int i = 0; i < n; ++i) {
        avl.ajouter(valeurs[i]);
        cout << "apres ajouter(" << valeurs[i] << ") : ";
        parcoursLarg(avl);
        cout << " | hauteur=" << avl.hauteur() << endl;
    }

    cout << "\nParcours finaux" << endl;
    cout << "Prefixe : ";
    parcoursPre(avl);
    cout << endl;

    cout << "Infixe : ";
    parcoursInf(avl);
    cout << endl;

    cout << "Postfixe : ";
    parcoursPost(avl);
    cout << endl;

    cout << "Largeur : ";
    parcoursLarg(avl);
    cout << endl;

    cout << "\nTests rechercher" << endl;
    cout << "rechercher(25) : " << (avl.rechercher(25) ? "vrai" : "faux") << " (attendu: vrai)" << endl;
    cout << "rechercher(99) : " << (avl.rechercher(99) ? "vrai" : "faux") << " (attendu: faux)" << endl;

    cout << "\nTests supprimer (visualisation en largeur)" << endl;

    // 1) suppression d'une feuille
    avl.supprimer(5);
    cout << "apres supprimer(5) [feuille] : ";
    parcoursLarg(avl);
    cout << " | hauteur=" << avl.hauteur() << endl;

    // 2) suppression d'un noeud de degre 1
    avl.supprimer(50);
    cout << "apres supprimer(50) [degre 1] : ";
    parcoursLarg(avl);
    cout << " | hauteur=" << avl.hauteur() << endl;

    // 3) suppression d'un noeud de degre 2
    avl.supprimer(30);
    cout << "apres supprimer(30) [degre 2] : ";
    parcoursLarg(avl);
    cout << " | hauteur=" << avl.hauteur() << endl;

    // 4) suppression valeur absente
    avl.supprimer(1234);
    cout << "apres supprimer(1234) [absent] : ";
    parcoursLarg(avl);
    cout << " | hauteur=" << avl.hauteur() << endl;

    return 0;
}

AVL<int> buildTree()
{
    AVL<int> arbre;
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