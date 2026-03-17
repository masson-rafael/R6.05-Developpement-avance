#include "Liste.h"
#include <string>

// CONSTRUCTEURS
Liste::Liste() : m_valeur(0), m_suivant(nullptr) {}

Liste::Liste(const Liste& autre) : m_valeur(autre.m_valeur), m_suivant(nullptr) {
    if (autre.m_suivant != nullptr) {
        this->m_suivant = new Liste(*autre.m_suivant);
    }
}

// DESTRUCTEURS
Liste::~Liste() {}

// GETTERS
int Liste::getValeur() const {
    return this->m_valeur;
}

// METHODES
bool Liste::estVide() const {
    return this->m_suivant == nullptr;
}

Liste& Liste::suivant() const {
    return *this->m_suivant;
}

void Liste::insererDebut(int valeur) {
    Liste* nouvelleCellule = new Liste();
    nouvelleCellule->m_valeur = valeur;
    nouvelleCellule->m_suivant = this->m_suivant;
    this->m_suivant = nouvelleCellule;
}

void Liste::supprimerDebut() {
    if (this->m_suivant != nullptr) {
        Liste* celluleASupprimer = this->m_suivant;
        this->m_suivant = this->m_suivant->m_suivant;
        delete celluleASupprimer;
    }
}

string Liste::toString() const {
    string chaine;
    const Liste* courant = this->m_suivant;
    while (courant != nullptr) {
        chaine += "| ";
        chaine += to_string(courant->m_valeur);
        chaine += " / - | -> ";
        courant = courant->m_suivant;
    }
    chaine += "|   / x | \n";
    return chaine;
}
