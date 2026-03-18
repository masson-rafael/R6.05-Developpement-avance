#ifndef PILE_H
#define PILE_H
#include <string>
#include "Liste.h"
using namespace std;

class Pile {
    private:
        Liste m_liste;
    public:
        Pile();
        Pile(const Pile&);
        ~Pile();
        Pile& operator=(const Pile&);
        bool estVide() const;
        int sommet() const;
        //Pile& suivant() const;
        void empiler(int);
        void depiler();
        //bool appartient(int) const;
        string toString() const;
};

#endif