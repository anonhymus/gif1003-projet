/**
* \file Vehicule.h
* \brief Fichier qui contient l'insterface de la classe Vehicule
* \author Antoine Bouchard
* \version 0.1-alpha
* \date 10/14/2016
*/
#include <iostream>
#include "date/Date.h"

#ifndef VEHICULE_H
#define VEHICULE_H

namespace vehicule {

    /**
     * \class Vehicule
     * \brief Class contenant les informations d'un vehicule
     */
    class Vehicule {
    public:
        Vehicule(const std::string &p_niv, const std::string &p_immatriculation);

        virtual ~Vehicule() {};

        virtual Vehicule *clone() const = 0;

        virtual double tarificationAnnuelle() const;

        std::string reqNiv() const;

        std::string reqImmatriculation() const ;

        virtual void asgImmatriculation(const std::string &p_immatriculation);

        util::Date &reqDateEnregistrement();

        virtual std::string reqVehiculeFormate() const;
        friend bool operator==(Vehicule &L, Vehicule &R);

    private:
        std::string m_niv;
        std::string m_immatriculation;
        util::Date m_dateEnregistrement;

        void verifieInvariant() const;
    };
}
#endif //_VEHICULE_H
