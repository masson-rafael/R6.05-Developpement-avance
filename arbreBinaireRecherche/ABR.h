#ifndef ABR_H
#define ABR_H

#include "ArbreBin.h"

template <class Element>
class ABR : public ArbreBin<Element>
{
protected:
    ABR<Element>& fG() const;
    ABR<Element>& fD() const;
    void setRacine(Element);

public:
    ABR();
    ABR(const ABR<Element> &);
    ~ABR();
    ABR<Element> &operator=(const ABR<Element> &);
    void ajouter(Element);
    void supprimer(Element);
    bool rechercher(Element) const;
    void remonterFilsNonVide();
    Element rechercheMin();
};

/* ================================================================== */

template <class Element>
ABR<Element>::ABR() : ArbreBin<Element>() {}

template <class Element>
ABR<Element>::~ABR() {
    delete this->m_fG; this->m_fG = nullptr;
    delete this->m_fD; this->m_fD = nullptr;
}

template <class Element>
ABR<Element>& ABR<Element>::fG() const {
    return static_cast<ABR<Element>&>(this->ArbreBin<Element>::fG());
}

template <class Element>
ABR<Element>& ABR<Element>::fD() const {
    return static_cast<ABR<Element>&>(this->ArbreBin<Element>::fD());
}

template <class Element>
void ABR<Element>::setRacine(Element e) {
    if (this->estVide()) {
        this->m_fG = new ABR<Element>();
        this->m_fD = new ABR<Element>();
    }
    this->m_e = e;
}

template <class Element>
bool ABR<Element>::rechercher(Element e) const {
    if (this->estVide()) return false;
    if (e == this->racine()) return true;
    if (e < this->racine()) return this->fG().rechercher(e);
    return this->fD().rechercher(e);
}

template <class Element>
void ABR<Element>::ajouter(Element e) {
    if (this->estVide()) {
        this->setRacine(e);
    } else if (e < this->racine()) {
        this->fG().ajouter(e);
    } else if (e > this->racine()) {
        this->fD().ajouter(e);
    }
}

template <class Element>
void ABR<Element>::supprimer(Element e) {
    if (this->estVide()) return;

    if (e < this->racine()){
        this->fG().supprimer(e);
        return;
    }

    if (e > this->racine()){
        this->fD().supprimer(e);
        return;
    }

    // e == this->racine() 
    if (this->fG().estVide() && this->fD().estVide()) {
        /* feuille */
        this->detruire();
        return;
    } 
    if (this->fG().estVide() || this->fD().estVide()) {
        /* noeud de degré 1 */
        this->remonterFilsNonVide();
        return;
    }
    /* noeud de degré 2 */
    Element succ = this->fD().rechercheMin();
    this->fD().supprimer(succ);
    this->setRacine(succ);
}

template <class Element>
void ABR<Element>::remonterFilsNonVide() {

    ABR<Element>* filsNonVide = this->fG().estVide() ? &this->fD() : &this->fG();
    ABR<Element>* filsVide = this->fG().estVide() ? &this->fG() : &this->fD();

    delete filsVide;

    this->setRacine(filsNonVide->racine());
    this->m_fG = filsNonVide->m_fG;
    this->m_fD = filsNonVide->m_fD;

    filsNonVide->m_fG = nullptr;
    filsNonVide->m_fD = nullptr;

    delete filsNonVide;
}

template <class Element>
Element ABR<Element>::rechercheMin() {
    if (this->estVide()) return Element();
    if (this->fG().estVide()) return this->racine();
    return this->fG().rechercheMin();
}

#endif