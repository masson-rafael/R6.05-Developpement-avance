#ifndef AVL_H
#define AVL_H

#include "ABR.h"

template <class Element>
class AVL : public ABR<Element>

{
protected:
    int m_hauteur;
    void rotationDroite();
    void rotationGauche();
    AVL<Element>& fG() const;
    AVL<Element>& fD() const;
    void setRacine(Element);
    void remonterFilsNonVide();

public:
    AVL();
    AVL(const AVL<Element> &);
    ~AVL();
    AVL<Element> &operator=(const AVL<Element> &);
    void ajouter(Element);
    void supprimer(Element);
    // bool rechercher(Element) const;
};

/* ================================================================== */

template <class Element>
AVL<Element>::AVL() : ABR<Element>(), m_hauteur(0) {}

template <class Element>
AVL<Element>::~AVL() {
    delete this->m_fG; this->m_fG = nullptr;
    delete this->m_fD; this->m_fD = nullptr;
}

template <class Element>
AVL<Element>& AVL<Element>::fG() const {
    return static_cast<AVL<Element>&>(*(this->m_fG)); //this->ABR<Element>::fG()
}

template <class Element>
AVL<Element>& AVL<Element>::fD() const {
    return static_cast<AVL<Element>&>(*(this->m_fD)); //this->ABR<Element>::fD()
}

template <class Element>
void AVL<Element>::setRacine(Element e) {
    if (this->estVide()) {
        this->m_fG = new AVL<Element>();
        this->m_fD = new AVL<Element>();
        this->m_hauteur = 1;
    }
    this->m_e = e;
}

template <class Element>
void AVL<Element>::rotationDroite() {
    AVL<Element>* a = &this->fG().fG();
    AVL<Element>* b = &this->fG().fD();
    AVL<Element>* c = &this->fD();
    AVL<Element>* cellP = &this->fG();

    // Permutation des elements
    Element tmp = this->m_e;
    this->m_e = cellP->m_e;
    cellP->m_e = tmp;

    // Modification des accrochages
    this->m_fG = a;
    this->m_fD = cellP;
    cellP->m_fG = b;
    cellP->m_fD = c;

    // Mise à jour des hauteurs
    cellP->m_hauteur = 1 + std::max(b->m_hauteur, c->m_hauteur);
    this->m_hauteur = 1 + std::max(this->fG().m_hauteur, this->fD().m_hauteur);
}

template <class Element>
void AVL<Element>::rotationGauche() {
    AVL<Element>* a = &this->fG();
    AVL<Element>* b = &this->fD().fG();
    AVL<Element>* c = &this->fD().fD();
    AVL<Element>* cellP = &this->fD();

    // Permutation des elements
    Element tmp = this->m_e;
    this->m_e = cellP->m_e;
    cellP->m_e = tmp;

    // Modification des accrochages
    this->m_fG = cellP;
    this->m_fD = c;
    cellP->m_fG = a;
    cellP->m_fD = b;

    // Mise à jour des hauteurs
    cellP->m_hauteur = 1 + std::max(a->m_hauteur, b->m_hauteur);
    this->m_hauteur = 1 + std::max(this->fG().m_hauteur, this->fD().m_hauteur);
}

// template <class Element>
// bool ABR<Element>::rechercher(Element e) const {
//     if (this->estVide()) return false;
//     if (e == this->racine()) return true;
//     if (e < this->racine()) return this->fG().rechercher(e);
//     return this->fD().rechercher(e);
// }

template <class Element>
void AVL<Element>::ajouter(Element e){
    ABR<Element>::ajouter(e);
    this->m_hauteur = 1 + std::max(this->fG().m_hauteur, this->fD().m_hauteur);
    if (this->fG().m_hauteur - this->fD().m_hauteur >= 2) {
        if (e < this->fG().m_e) {
            this->rotationDroite();
        } else {
            this->fG().rotationGauche();
            this->rotationDroite();
        }
    } else if (this->fD().m_hauteur - this->fG().m_hauteur >= 2) {
        if (e > this->fD().m_e) {
            this->rotationGauche();
        } else {
            this->fD().rotationDroite();
            this->rotationGauche();
        }
    }
}

template <class Element>
void AVL<Element>::supprimer(Element e) {
    if (this->estVide()) return;

    if (e < this->racine()){
        this->fG().supprimer(e);
    } else if (e > this->racine()){
        this->fD().supprimer(e);
    } else {
        // e == this->racine()
        if (this->fG().estVide() && this->fD().estVide()) {
            // feuille
            this->detruire();
            this->m_hauteur = 0;
            return;
        }
        if (this->fG().estVide() || this->fD().estVide()) {
            // noeud de degré 1
            this->remonterFilsNonVide();
        } else {
            // noeud de degré 2
            Element succ = this->fD().rechercheMin();
            this->m_e = succ;
            this->fD().supprimer(succ);
        }
    }

    if (this->estVide()) {
        this->m_hauteur = 0;
        return;
    }

    this->m_hauteur = 1 + std::max(this->fG().m_hauteur, this->fD().m_hauteur);

    int equilibre = this->fG().m_hauteur - this->fD().m_hauteur;

    if (equilibre >= 2) {
        int equilibreG = this->fG().fG().m_hauteur - this->fG().fD().m_hauteur;
        if (equilibreG >= 0) {
            this->rotationDroite();
        } else {
            this->fG().rotationGauche();
            this->rotationDroite();
        }
    } else if (equilibre <= -2) {
        int equilibreD = this->fD().fG().m_hauteur - this->fD().fD().m_hauteur;
        if (equilibreD <= 0) {
            this->rotationGauche();
        } else {
            this->fD().rotationDroite();
            this->rotationGauche();
        }
    }
}

template <class Element>
void AVL<Element>::remonterFilsNonVide() {
    ABR<Element>::remonterFilsNonVide();
}

#endif