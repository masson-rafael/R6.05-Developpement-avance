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
        Liste& operator=(const Liste&);
        bool estVide() const;
        int getValeur() const;
        Liste& suivant() const;
        void insererDebut(int);
        void supprimerDebut();
        int nbElements(const Liste&) const;
        int nbElementsRec(const Liste&) const;
        bool appartient(int) const;
        string toString() const;
};

#endif