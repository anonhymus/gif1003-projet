/**
*  \file Camion.cpp
*  \brief Implementation de la class Camion
*  \author Antoine Bouchard
*  \version 0.1-alpha
*  \date 11/22/2016
*/

#include <sstream>
#include <iomanip>
#include "contrat/ContratException.h"
#include "validation/validationFormat.h"
#include "Camion.h"

using namespace vehicule;
using namespace std;

Camion::Camion(const std::string &p_niv, const std::string &p_immatriculation, int p_poids, int p_nbEssieux)
        : Vehicule(p_niv, p_immatriculation), m_poids(p_poids), m_nbEssieux(p_nbEssieux) {
    PRECONDITION(util::validationImmatriculationCamion(p_immatriculation))
    PRECONDITION(p_poids > 3000);
    PRECONDITION(p_nbEssieux >= 2);
    POSTCONDITION(this->m_nbEssieux == p_nbEssieux);
    POSTCONDITION(this->m_poids == p_poids);
    INVARIANTS();
}
/**
 * \brief methode pour faire une copie de l'objet Camion
 * @return le nouvel objet Camion
 */
vehicule::Vehicule *vehicule::Camion::clone() const {
    return new Camion(*this);
}

/**
 * \brief Accesseur poids du camion
 * @return le poids du camion
 */
int Camion::reqPoids() const{
    return this->m_poids;
}

/**
 * \brief Accesseur nombre d'essieux du camion
 * @return le nombre d'essieux du camion
 */
int Camion::reqNombreEssieux() const{
    return this->m_nbEssieux;
}

/**
 * \brief Assigner un nouveau numero d'immatriculation
 * @param p_immatriculation la nouvelle immatriculation
 */
void Camion::asgImmatriculation(const std::string &p_immatriculation) {
    PRECONDITION(util::validationImmatriculationCamion(p_immatriculation))
    Vehicule::asgImmatriculation(p_immatriculation);
    POSTCONDITION(this->reqImmatriculation() == p_immatriculation);
}

/**
 * \brief calcule du tarif d'immatriculation annuelle
 * @return le cout d'immatriculation
 */
double Camion::tarificationAnnuelle() const {
    PRECONDITION(m_poids > 3000);
    PRECONDITION(m_nbEssieux >= 2);
    double tarif = computeRate();
    POSTCONDITION(tarif > 0);
    return tarif;
}

/**
 * \brief Affiche les informations du camion
 * @return string contenant les informations du camion
 */
std::string Camion::reqVehiculeFormate() const {
    ostringstream os;
    os << Vehicule::reqVehiculeFormate();
    os.width(26);
    os << left << "Nombre d'essieux " << ": " << this->m_nbEssieux << endl;
    os.width(26);
    os << left << "Poids " << ": " << this->m_poids << endl;
    os.width(26);
    os << left << "Tarif " << ": " << this->tarificationAnnuelle() << "$" << endl;
    return os.str();
}

/**
 * \brief methode pour calculer le prix d'immatriculation en fonction du nombre d'essieux et le poids du camion
 * @return le prix d'immatriculation
 */
double Camion::computeRate() const {
    double tarif = 0.0;
    if (this->m_nbEssieux > 6) {
        tarif = 3577.06;
    } else {
        switch (this->m_nbEssieux) {
            case 2:
                if (this->m_poids > 3000 and this->m_poids <= 4000) {
                    tarif = 556.50;
                } else if (this->m_poids >= 4001) {
                    tarif = 881.50;
                }
                break;
            case 3:
                tarif = 1512.94;
                break;
            case 4:
                tarif = 2132.94;
                break;
            case 5:
                tarif = 2698.06;
                break;
            case 6:
                tarif = 3577.06;
                break;
            default:
                break;
        }
    }
    POSTCONDITION(tarif > 0)
    return tarif;
}

void Camion::verifieInvariant() const {
    INVARIANT(this->m_nbEssieux >= 2);
    INVARIANT(this->m_poids > 3000);
}
