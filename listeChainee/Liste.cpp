#include "Liste.h"
#include <string>

// CONSTRUCTEURS
Liste::Liste() : m_valeur(0), m_suivant(nullptr) {}

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

int Liste::nbElements(const Liste& l) const {
    int compteur = 0;
    const Liste* courant = l.m_suivant;
    while (courant != nullptr) {
        compteur++;
        courant = courant->m_suivant;
    }
    return compteur;
}

int Liste::nbElementsRec(const Liste& l) const {
    if (l.m_suivant == nullptr) {
        return 0;
    }
    return 1 + nbElementsRec(*l.m_suivant);
}

bool Liste::appartient(int valeur) const {
    const Liste* courant = this->m_suivant;
    while (courant != nullptr) {
        if (courant->m_valeur == valeur) {
            return true;
        }
        courant = courant->m_suivant;
    }
    return false;
}

string Liste::toString() const {
    string chaine;
    const Liste* courant = this->m_suivant;
    while (courant != nullptr) {
        chaine += "[";
        chaine += to_string(courant->m_valeur);
        chaine += "] -> ";
        courant = courant->m_suivant;
    }
    chaine += "x\n";
    return chaine;
}
