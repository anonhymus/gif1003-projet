/**
*  \file VehiculePromenade.h
*  \brief Interface de la classe VehiculePromenade
*  \author Antoine Bouchard
*  \version 0.1-alpha
*  \date 11/22/2016
*/

#ifndef VEHICULEPROMENADE_H
#define VEHICULEPROMENADE_H

#include "vehicule.h"

namespace vehicule {
/**
 * \class VehiculePromenade
 * \brief Classe permettant de modeliser les objets Proprietaire
 */
    class VehiculePromenade : public Vehicule {

    public:
        VehiculePromenade(const std::string &p_niv, const std::string &p_immatriculation, int p_nbPlaces);

        Vehicule *clone() const;

        double tarificationAnnuelle() const;

        void asgImmatriculation(const std::string &p_immatriculation);

        int reqNbPlaces();

        std::string reqVehiculeFormate() const;

    private:

        int m_nbPlaces;

        void verifieInvariant() const;
    };

}

#endif //VEHICULEPROMENADE_H
