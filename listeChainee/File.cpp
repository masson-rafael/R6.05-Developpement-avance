#include "File.h"
#include <string>

// CONSTRUCTEURS
File::File() : m_liste() {
    m_queue = &m_liste; // m_queue pointe le debut
}

// DESTRUCTEURS
File::~File() {}

// GETTERS
int File::premier() const {
    if (!estVide()) {
        return this->m_liste.suivant().getValeur();
    }
    return 0; // ou autre valeur par defaut si vide
}

// METHODES
bool File::estVide() const {
    return this->m_liste.estVide();
}

void File::enfiler(int valeur) {
    this->m_queue->insererDebut(valeur);
    this->m_queue = &(m_queue->suivant());
}

void File::defiler() {
    // On defile par la "tete de liste" (le debut)
    if (!this->m_liste.estVide()) {
        this->m_liste.supprimerDebut();
    }
}

string File::toString() const {
    if (!this->m_liste.estVide()) {
        return this->m_liste.toString();
    }
    return "x\n";
}
