
//
// Created by antoi on 11/22/2016.
//

#ifndef CAMION_H
#define CAMION_H

#include "vehicule.h"

namespace vehicule {
    /**
     * \class Camion
     */
    class Camion : public Vehicule {

    public:
        Camion(const std::string &p_niv, const std::string &p_immatriculation, int p_poids, int p_nbEssieux);

        Vehicule *clone() const;

        int reqPoids() const;

        int reqNombreEssieux() const;

        void asgImmatriculation(const std::string &p_immatriculation);

        double tarificationAnnuelle() const;

        std::string reqVehiculeFormate() const;




    private:
        int m_poids;
        int m_nbEssieux;

        double computeRate() const;

        void verifieInvariant() const;
    };
}

#endif //CAMION_H
