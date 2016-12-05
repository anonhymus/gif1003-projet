//
// Created by antoi on 11/23/2016.
//

#ifndef GIF1003_PROJETSESSION_PROPRIETAIRE_H
#define GIF1003_PROJETSESSION_PROPRIETAIRE_H


#include <string>
#include <vector>
#include "vehicule.h"

namespace tp {
/**
 * \class Proprietaire
 * \brief Classe Proprietaire permettant de modeliser les objets Proprietaire
 */
    class Proprietaire {
    public:
        Proprietaire(const std::string &p_nom, const std::string &p_prenom);

        const std::string &reqNom() const;

        void asgNom(const std::string &p_nom);

        const std::string &reqPrenom() const;

        void asgPrenom(const std::string &p_prenom);

        void ajouterVehicule(const vehicule::Vehicule &p_nouveauVehicule);

        std::string reqProprietaireFormate();

        ~Proprietaire();

    public:

    private:
        std::string m_nom;
        std::string m_prenom;
        std::vector<vehicule::Vehicule *> m_vVehicules;

        void verifieInvariant() const;
    };

}
#endif //GIF1003_PROJETSESSION_PROPRIETAIRE_H
