#include <iostream>
using namespace std;
#include "ArbreBin.h"
#include <queue>

ArbreBin<int> buildTree();
ArbreBin<int> buildDegenerateTree();
ArbreBin<int> buildLocalCompletTree();
ArbreBin<int> buildPartielOrdTree();
ArbreBin<int> buildCompletNonParfaitTree();
ArbreBin<int> buildParfaitTree();
ArbreBin<int> buildTasTree();

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

/* est réduit à une branche */
bool estDegenere(ArbreBin<int>& abr);

/* tout noeud interne est de degré deux */
bool estLocalComplet(ArbreBin<int>& abr);

/* Tout noeud possède une étiquette
supérieure à celles des noeuds de son sous arbre */
bool estPartielOrd(ArbreBin<int>& abr);

/* Tout nœud possède une étiquette
supérieure à celles des noeuds de son sous arbre*/
bool estComplet(ArbreBin<int>& abr);

/* tous les niveaux sont remplis sauf
éventuellement le dernier qui a ses feuilles à gauche*/
bool estParfait(ArbreBin<int>& abr);

/* parfait et tout noeud possède une étiquette supérieure à
celles de ses fils*/
bool estTas(ArbreBin<int>& abr);

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
    parcoursLarg(abr);
    cout << endl;

    cout << "\n--- ARBRES DE TESTS ET RESULTATS ---" << endl;
    auto myBoolAlpha = [](bool val) { return val ? "VRAI" : "FAUX"; };
    
    ArbreBin<int> abrDeg = buildDegenerateTree();
    ArbreBin<int> abrLoc = buildLocalCompletTree();
    ArbreBin<int> abrPOrd = buildPartielOrdTree();
    ArbreBin<int> abrComp = buildParfaitTree();
    ArbreBin<int> abrParf = buildCompletNonParfaitTree();
    ArbreBin<int> abrTas = buildTasTree();

    cout << "1. Degenere (chaine)" << endl;
    cout << "   Prefixe : "; parcoursPre(abrDeg); cout << "\n   Largeur : "; parcoursLarg(abrDeg); cout << endl;
    cout << "   -> estDegenere: " << myBoolAlpha(estDegenere(abrDeg)) << " (attendu: VRAI)" << endl;
    cout << "   -> test sur abrLoc: " << myBoolAlpha(estDegenere(abrLoc)) << " (attendu: FAUX)" << endl << endl;

    cout << "2. Localement complet (tout noeud interne a 2 fils)" << endl;
    cout << "   Prefixe : "; parcoursPre(abrLoc); cout << "\n   Largeur : "; parcoursLarg(abrLoc); cout << endl;
    cout << "   -> estLocalComplet: " << myBoolAlpha(estLocalComplet(abrLoc)) << " (attendu: VRAI)" << endl;
    cout << "   -> test sur abrDeg: " << myBoolAlpha(estLocalComplet(abrDeg)) << " (attendu: FAUX)" << endl << endl;

    cout << "3. Partiellement Ordonne (chaque noeud > a ses fils, mais forme quelconque)" << endl;
    cout << "   Prefixe : "; parcoursPre(abrPOrd); cout << "\n   Largeur : "; parcoursLarg(abrPOrd); cout << endl;
    cout << "   -> estPartielOrd: " << myBoolAlpha(estPartielOrd(abrPOrd)) << " (attendu: VRAI)" << endl;
    cout << "   -> test sur abrLoc: " << myBoolAlpha(estPartielOrd(abrLoc)) << " (attendu: FAUX)" << endl << endl;

    // Rappel cours: "Complet" = localement complet + toutes les feuilles meme profondeur
    cout << "4. Complet (localement complet + feuilles a la meme profondeur)" << endl;
    cout << "   Prefixe : "; parcoursPre(abrComp); cout << "\n   Largeur : "; parcoursLarg(abrComp); cout << endl;
    cout << "   -> estComplet: " << myBoolAlpha(estComplet(abrComp)) << " (attendu: VRAI)" << endl;
    cout << "   -> test sur abrParf: " << myBoolAlpha(estComplet(abrParf)) << " (attendu: FAUX)" << endl << endl;

    // Rappel cours: "Parfait" = tous les niveaux remplis sauf le dernier aligne a gauche
    cout << "5. Parfait (niveaux remplis sauf dernier a gauche)" << endl;
    cout << "   Prefixe : "; parcoursPre(abrParf); cout << "\n   Largeur : "; parcoursLarg(abrParf); cout << endl;
    cout << "   -> estParfait: " << myBoolAlpha(estParfait(abrParf)) << " (attendu: VRAI)" << endl;
    cout << "   -> test sur abrComp: " << myBoolAlpha(estParfait(abrComp)) << " (attendu: VRAI - tout complet est parfait)" << endl;
    cout << "   -> test sur abrPOrd: " << myBoolAlpha(estParfait(abrPOrd)) << " (attendu: FAUX)" << endl << endl;

    cout << "6. Tas (Parfait + partiellement ordonne)" << endl;
    cout << "   Prefixe : "; parcoursPre(abrTas); cout << "\n   Largeur : "; parcoursLarg(abrTas); cout << endl;
    cout << "   -> estTas: " << myBoolAlpha(estTas(abrTas)) << " (attendu: VRAI)" << endl;
    cout << "   -> test sur abrParf: " << myBoolAlpha(estTas(abrParf)) << " (attendu: FAUX)" << endl;
    cout << "   -> test sur abrPOrd: " << myBoolAlpha(estTas(abrPOrd)) << " (attendu: FAUX)" << endl;

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

ArbreBin<int> buildDegenerateTree()
{
    ArbreBin<int> arbre;
    arbre.setRacine(10);
    arbre.fG().setRacine(9);
    arbre.fG().fG().setRacine(8);
    arbre.fG().fG().fG().setRacine(7);
    return arbre;
}

ArbreBin<int> buildLocalCompletTree()
{
    ArbreBin<int> arbre;
    arbre.setRacine(8);
    arbre.fG().setRacine(4);
    arbre.fD().setRacine(12);
    arbre.fG().fG().setRacine(2);
    arbre.fG().fD().setRacine(6);
    arbre.fD().fG().setRacine(10);
    arbre.fD().fD().setRacine(14);
    return arbre;
}

ArbreBin<int> buildPartielOrdTree()
{
    // Arbre partiellement ordonné : chaque noeud > à ses enfants
    // Mais on le fait exprès ni complet ni parfait (dégénéré par endroits)
    ArbreBin<int> arbre;
    arbre.setRacine(100);
    arbre.fG().setRacine(50);
    arbre.fG().fG().setRacine(20);
    arbre.fD().setRacine(80);
    arbre.fD().fG().setRacine(60);
    // 80 n'a pas de fils droit, donc pas localement complet
    return arbre;
}

ArbreBin<int> buildCompletNonParfaitTree()
{
    ArbreBin<int> arbre;
    arbre.setRacine(8);
    arbre.fG().setRacine(4);
    arbre.fD().setRacine(12);
    arbre.fG().fG().setRacine(2);
    arbre.fG().fD().setRacine(6);
    arbre.fD().fG().setRacine(10);
    return arbre;
}

ArbreBin<int> buildParfaitTree()
{
    ArbreBin<int> arbre;
    arbre.setRacine(7);
    arbre.fG().setRacine(3);
    arbre.fD().setRacine(11);
    arbre.fG().fG().setRacine(1);
    arbre.fG().fD().setRacine(5);
    arbre.fD().fG().setRacine(9);
    arbre.fD().fD().setRacine(13);
    return arbre;
}

ArbreBin<int> buildTasTree()
{
    ArbreBin<int> arbre;
    arbre.setRacine(50);
    arbre.fG().setRacine(30);
    arbre.fD().setRacine(40);
    arbre.fG().fG().setRacine(10);
    arbre.fG().fD().setRacine(20);
    arbre.fD().fG().setRacine(15);
    arbre.fD().fD().setRacine(25);
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

bool estDegenere(ArbreBin<int>& abr) {
    if(abr.estVide()) return true;
    if(abr.estDegreDeux()) return false;
    
    return estDegenere(abr.fG()) && estDegenere(abr.fD());
}

bool estLocalComplet(ArbreBin<int>& abr) {
    if(abr.estVide() || abr.estFeuille()) return true;

    return abr.estDegreDeux() && estLocalComplet(abr.fG()) && estLocalComplet(abr.fD());
}

bool estPartielOrd(ArbreBin<int>& abr) {
    (void)abr; // TODO: a completer
    return false;
}

bool estComplet(ArbreBin<int>& abr) {
    (void)abr; // TODO: a completer
    return false;
}

bool estParfait(ArbreBin<int>& abr) {
    (void)abr; // TODO: a completer
    return false;
}

bool estTas(ArbreBin<int>& abr) {
    (void)abr; // TODO: a completer
    return false;
}