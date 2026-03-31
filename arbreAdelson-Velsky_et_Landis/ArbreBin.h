#ifndef ARBREBIN_H
#define ARBREBIN_H

#include <algorithm>

template <class Element>
class ArbreBin
{
protected:
    Element m_e;
    ArbreBin<Element> *m_fG;
    ArbreBin<Element> *m_fD;

public:
    ArbreBin(const ArbreBin<Element> &);
    ArbreBin<Element> &operator=(const ArbreBin<Element> &);
    ArbreBin();
    ~ArbreBin();
    ArbreBin<Element> &fG() const;
    ArbreBin<Element> &fD() const;
    bool estVide() const;
    bool estFeuille() const;
    bool estDegreDeux() const;
    Element racine() const;
    void setRacine(Element);
    void detruire();
    int hauteur() const;
};

/* ================================================================== */

template <class Element>
ArbreBin<Element>::ArbreBin() : m_e(), m_fG(nullptr), m_fD(nullptr) {}

template <class Element>
ArbreBin<Element>::~ArbreBin() {
    // this->detruire(); // delete est en cascade donc pas obligatoire
    delete m_fG; m_fG = nullptr;
    delete m_fD; m_fD = nullptr;
}

template <class Element>
ArbreBin<Element>& ArbreBin<Element>::fG() const {
    return *(this->m_fG);
}

template <class Element>
ArbreBin<Element>& ArbreBin<Element>::fD() const {
    return *(this->m_fD);
}

template <class Element>
bool ArbreBin<Element>::estVide() const
{
    return this->m_fG == nullptr; // verifie que le fils gauche car un arbre vide est (null,nullptr,nullptr)
}

template <class Element>
bool ArbreBin<Element>::estFeuille() const {
    return this->m_fG->estVide() && this->m_fD->estVide();
}

template <class Element>
bool ArbreBin<Element>::estDegreDeux() const {
    return !this->m_fG->estVide() && !this->m_fD->estVide();
}

template <class Element>
Element ArbreBin<Element>::racine() const {
    return this->m_e;
}

template <class Element>
void ArbreBin<Element>::setRacine(Element elt)
{
    if (this->estVide())
    {
        this->m_fG = new ArbreBin<Element>();
        this->m_fD = new ArbreBin<Element>();
    }
    this->m_e = elt;
}

template <class Element>
void ArbreBin<Element>::detruire()
// détruit tout le sous arbre et "retourne" un arbre vide
{
    if (!this->estVide())
    {
        this->fG().detruire();
        this->fD().detruire();
        delete this->m_fG;
        this->m_fG = nullptr;
        delete this->m_fD;
        this->m_fD = nullptr;
    }
}

template <class Element>
int ArbreBin<Element>::hauteur() const
{
    if (this->estVide()) {return 0;}
    return 1 + std::max(this->fG().hauteur(), this->fD().hauteur());
}

#endif