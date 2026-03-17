#ifndef LISTE_H
#define LISTE_H
#include <string>
using namespace std;

class Liste {
    private:
        int m_valeur;
        Liste* m_suivant;
    public:
        Liste();
        Liste(const Liste&);
        ~Liste();
        bool estVide() const;
        int getValeur() const;
        Liste& suivant() const;
        void insererDebut(int);
        void supprimerDebut();
        int nbElements(const Liste&) const;
        int nbElementsRec(const Liste&) const;
        string toString() const;
};

#endif