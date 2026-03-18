#include "Pile.h"
#include <string>

// CONSTRUCTEURS
Pile::Pile() : m_liste() {}

// DESTRUCTEURS
Pile::~Pile() {}

// GETTERS
int Pile::sommet() const {
    if (!estVide()) {
        return this->m_liste.suivant().getValeur();
    }
    return 0; // ou lever une exception
}

// METHODES
bool Pile::estVide() const {
    return this->m_liste.estVide();
}

void Pile::empiler(int valeur) {
    this->m_liste.insererDebut(valeur);
}

void Pile::depiler() {
    this->m_liste.supprimerDebut();
}

string Pile::toString() const {
    if (!this->m_liste.estVide()) {
        return this->m_liste.toString();
    }
    return "x\n";
}
