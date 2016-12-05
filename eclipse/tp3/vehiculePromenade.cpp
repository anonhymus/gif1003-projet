/**
*  \file VehiculePromenade.cpp
*  \brief Implementation de la classe VehiculePromenade
*  \author Antoine Bouchard
*  \version 0.1-alpha
*  \date 11/22/2016
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include "validation/validationFormat.h"
#include "tarification.h"
#include "contrat/ContratException.h"
#include "vehiculePromenade.h"

using namespace vehicule;
using namespace std;
/**
 * \brief Constructeur de la classe Promenade
 * \param[in] p_niv le NIV valide du vehicule
 * \param[in] p_immatriculation le numero d'immatriculation valide du vehicule
 * \param[in] p_nbPlaces nombre de place dans le vehicule
 * \pre p_nbPlaces doit etre strictement plus grand que 0
 * \pre p_immatriculation doit etre un format valide
 * \post m_nbPlaces est egale au parametre recus en entré
 */
VehiculePromenade::VehiculePromenade(const string &p_niv, const string &p_immatriculation, int p_nbPlaces)
        : Vehicule(p_niv, p_immatriculation), m_nbPlaces(p_nbPlaces) {
    PRECONDITION(p_nbPlaces > 0);
    PRECONDITION(util::validationImmatriculationPromenade(p_immatriculation));
    POSTCONDITION(m_nbPlaces == p_nbPlaces);
    INVARIANTS();
}

/**
 * \brief Creation d'un clone (copie) de l'objet
 * @return la copie de l'objet vehiculePromenade
 */
Vehicule *VehiculePromenade::clone() const {
    return new VehiculePromenade(*this);
}

/**
 * \brief calcule du tarif d'immatriculation annuelle
 * @return le cout d'immatriculation
 */
double VehiculePromenade::tarificationAnnuelle() const {
    return tarif::PROMENADE;
}

/**
 * \brief Assigner un nouveau numero d'immatriculation
 * @param p_immatriculation
 * \pre p_immatriculation[in] est dans un format valide
 * \post m_immatriculation[in] est egalde a p_immatriculation
 */
void VehiculePromenade::asgImmatriculation(const string &p_immatriculation) {
    PRECONDITION(util::validationImmatriculationPromenade(p_immatriculation));
    Vehicule::asgImmatriculation(p_immatriculation);
    POSTCONDITION(this->reqImmatriculation() == p_immatriculation);
    INVARIANTS();
}

/**
 * \brief methode pour formatter les informations d'un vehicule
 * @return string contenant les informations du vehicule
 */
string VehiculePromenade::reqVehiculeFormate() const {
    ostringstream os;
    os << Vehicule::reqVehiculeFormate();
    os.width(26);
    os << left << "Nombre de places " << ": " << this->m_nbPlaces << endl;
    os.width(26);
    os << left << "Tarif " << ": " << this->tarificationAnnuelle() << "$" << endl;
    return os.str();
}

/**
 * \brief Méthode accesseur récupérant le nombre de place
 * @return
 */
int VehiculePromenade::reqNbPlaces() {
    return this->m_nbPlaces;
}

void VehiculePromenade::verifieInvariant() const {
    Vehicule::reqVehiculeFormate();
    INVARIANT(this->m_nbPlaces > 0);
}
