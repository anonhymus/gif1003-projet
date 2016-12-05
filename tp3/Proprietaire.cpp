//
// Created by antoi on 11/23/2016.
//
#include <iostream>
#include <sstream>
#include <iomanip>
#include "contrat/ContratException.h"
#include "Proprietaire.h"


using namespace std;
using namespace vehicule;
using namespace tp;

Proprietaire::Proprietaire(const string &p_nom, const string &p_prenom)
        : m_nom(p_nom), m_prenom(p_prenom) {

    PRECONDITION(!p_nom.empty() and !p_prenom.empty());

    POSTCONDITION(this->m_nom == p_nom and this->m_prenom == p_prenom);

}

const string &Proprietaire::reqNom() const {
    return m_nom;
}

void Proprietaire::asgNom(const string &p_nom) {
    PRECONDITION(!p_nom.empty());
    this->m_nom = p_nom;
    POSTCONDITION(this->m_nom == p_nom);
    INVARIANTS();
}

const string &Proprietaire::reqPrenom() const {
    return m_prenom;
}

void Proprietaire::asgPrenom(const string &p_prenom) {
    PRECONDITION(!p_prenom.empty())
    this->m_prenom = p_prenom;
    INVARIANTS();
}

/**
 * \brief Ajouter un vehicule au a la liste de vehicule du proprietaire (vector)
 * \param p_nouveauVehicule pointeur du vehicule a ajouter
 */
void Proprietaire::ajouterVehicule(const vehicule::Vehicule &p_nouveauVehicule) {
    m_vVehicules.push_back(p_nouveauVehicule.clone());
}
/**
 * \brief Affiche les informations du proprietaire
 * @return
 */
string Proprietaire::reqProprietaireFormate() {
    string separator = "-------------------";
    ostringstream os;
    os << separator << endl;
    os.width(10);
    os << "Nom " << ": " << this->m_nom << endl;
    os.width(10);
    os << "Prenom " << ": " << this->m_prenom << endl;
    for (int i = 0; i < m_vVehicules.size(); ++i) {
        os << separator << endl;
        os << m_vVehicules[i]->reqVehiculeFormate();
    }
    return os.str();
}

/**
 * \brief destructeur pour Proprietaire, on s'assure que l'on detruit aussi les vehicules la liste.
 */
Proprietaire::~Proprietaire() {
    for (vector<Vehicule *>::iterator it = m_vVehicules.begin(); it != m_vVehicules.end(); ++it) {
        delete *it;
    }
    m_vVehicules.clear();
}


void Proprietaire::verifieInvariant() const {
    INVARIANT(!this->m_nom.empty() and
              !this->m_prenom.empty())
}
