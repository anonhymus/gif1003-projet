/**
* \file Vehicule.cpp
* \brief Implementation de la classe Vehicule
* \author Antoine Bouchard
* \version 0.3-alpha
* \date 10/14/2016
*/
#include <iostream>
#include <iomanip>
#include <sstream>
#include "contrat/ContratException.h"
#include "validation/validationFormat.h"
#include "vehicule.h"

using namespace std;
namespace vehicule {

    /**
     * \brief Constructeur vehicule
     * \exception VehiculeException parametre invalide.
     * \param[in] p_niv est une chaine de caractere representant le numero d'identification du vehicule
     * \param[in] p_immatriculation est une chaine de character representant le numero de plaque d'immatriculation
     */
    Vehicule::Vehicule(const string &p_niv, const string &p_immatriculation) : m_niv(p_niv),
                                                                               m_immatriculation(p_immatriculation) {
        PRECONDITION(util::validerNiv(p_niv))
        POSTCONDITION(this->m_niv == p_niv);
        POSTCONDITION(this->m_immatriculation == p_immatriculation);
        INVARIANTS();
    }

    /**
     * \brief retourne le numero d'identification du vehicule
     * \return le numero d'identification du vehicule
     */
    string Vehicule::reqNiv() const {
        return this->m_niv;
    }

    /**
     * \brief retourne le numero de plaque d'immatriculation
     * \return le numero de plaque d'immatriculation
     */
    string Vehicule::reqImmatriculation() const {
        return this->m_immatriculation;
    }

    /**
     * \brief assigne un numero de plaque d'immatriculation a l'objet courant
     * \param[in] p_immatriculation chaine de caractere representant le numero de plaque d'immatriculation
     */
    void Vehicule::asgImmatriculation(const string &p_immatriculation) {
        PRECONDITION(p_immatriculation.size() == 7);
        this->m_immatriculation = p_immatriculation;
        POSTCONDITION(this->m_immatriculation == p_immatriculation);
        INVARIANTS();
    }

    /**
     * \brief retourne la date de creation du vehicule
     * \return la date de creation
     */
    util::Date &Vehicule::reqDateEnregistrement() {
        return m_dateEnregistrement;
    }

    /**
     * \brief retourne la chaine de caractere representant les informations du vehicule.
     * \return la chaine de caractere.
     */
    string Vehicule::reqVehiculeFormate() const {
        ostringstream os;
        os.width(26);
        os << left << "Numero de serie" << ": " << this->m_niv << endl;
        os.width(26);
        os << left << "Numero d'immatriculation" << ": " << this->m_immatriculation << endl;
        os.width(26);
        os << left << "Date d'enregistrement" << ": "
           << this->m_dateEnregistrement.reqDateFormatee() << endl;
        return os.str();
    }

    double Vehicule::tarificationAnnuelle() const {
        return 0;
    }

    void Vehicule::verifieInvariant() const {
        INVARIANT(!this->m_niv.empty());
        INVARIANT(!this->m_immatriculation.empty())
    }

    /**
     * \brief operateur d'egalite entre 2 vehicule
     * @param b vehicule avec lequel on compare
     * @return les vehicules sont egal ou non
     */
    bool operator==(Vehicule &L, Vehicule &R) {
        bool estEgal = (L.m_niv == R.reqNiv()) and
                       (L.m_immatriculation == R.reqImmatriculation());
        cout << estEgal << endl;
        return estEgal;
    }

}
