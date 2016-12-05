/**
*  \file proprietaire_unittest.cpp
*  \brief Unit test pour Proprietaire
*  \author Antoine Bouchard
*  \version 0.1-alpha
*  \date 11/30/2016
*/
#include <gtest/gtest.h>
#include "Proprietaire.h"
#include "contrat/ContratException.h"
#include "vehiculePromenade.h"
#include "Camion.h"

using namespace std;
using namespace vehicule;
using namespace tp;

/*
 * \brief Simple test de pour valider le bon fonctionnement des preconditions du constructeur
 */
TEST(Proprietaire, constructeurEstInvalideContratExeption) {
    const string nom = "";
    string prenom = "";
    ASSERT_THROW(Proprietaire proprietaire(nom, prenom);, ContratException);
}
/*
 * \brief Simple test de pour valider le bon fonctionnement du constructeur avec des parametre valide
 */
TEST(Proprietaire, constructeurEstValide) {
    const string prenom = "John";
    const string nom = "Doe";
    ASSERT_NO_THROW(Proprietaire proprietaire(nom, prenom););
}

class ProprietaireTest : public ::testing::Test {
public:
    Proprietaire *t_proprietaire;
    VehiculePromenade *t_vehiculePromenade;
    Camion *t_camion;
    const string t_nom = "Doe";
    const string t_prenom = "John";
    virtual void SetUp() {
        t_proprietaire = new Proprietaire(t_nom, t_prenom);
        string niv = "S26F84ED0DM538541";
        string immat = "AAA 000";

        t_vehiculePromenade = new VehiculePromenade(niv, immat, 2);
        t_camion = new Camion(niv, "L000000", 3004, 4);
    }
};

/**
 * \brief test que le constructeur initialise bien le nom et prenom
 */
TEST_F(ProprietaireTest, constructeur) {
    ASSERT_EQ(t_proprietaire->reqNom(), "Doe");
    ASSERT_EQ(t_proprietaire->reqPrenom(), "John");
}

TEST_F(ProprietaireTest, asgNomTest) {
    t_proprietaire->asgNom("Wonka");
    ASSERT_EQ(t_proprietaire->reqNom(), "Wonka");
}

TEST_F(ProprietaireTest, asgPrenomTest) {
    t_proprietaire->asgPrenom("Wonka");
    ASSERT_EQ(t_proprietaire->reqPrenom(), "Wonka");
}

TEST_F(ProprietaireTest, asgNomTest_ContratException) {
    ASSERT_THROW(t_proprietaire->asgNom("");, ContratException);
}

TEST_F(ProprietaireTest, asgPrenomTest_ContratException) {
    ASSERT_THROW(t_proprietaire->asgPrenom("");, ContratException);
}

TEST_F(ProprietaireTest, ajouterVehiculeTest) {
    t_proprietaire->ajouterVehicule(*t_vehiculePromenade);

}
/**
 * \brief test du formattage des donnees de Proprietaire
 */
TEST_F(ProprietaireTest, reqProprietaireFormatTest_avecVehicule) {
    ostringstream os;
    string camionFormat = t_camion->reqVehiculeFormate();
    string vehiculePromenadeFormat = t_vehiculePromenade->reqVehiculeFormate();
    string separator = "-------------------";

    t_proprietaire->ajouterVehicule(*t_vehiculePromenade);
    t_proprietaire->ajouterVehicule(*t_camion);

    os << separator << endl;
    os.width(10);
    os << "Nom " << ": " << this->t_nom << endl;
    os.width(10);
    os << "Prenom " << ": " << this->t_prenom << endl;
    os << separator << endl;
    os << vehiculePromenadeFormat;
    os << separator << endl;
    os<< camionFormat;
    ASSERT_EQ(t_proprietaire->reqProprietaireFormate(), os.str());
}


TEST_F(ProprietaireTest, reqProprietaireFormatTest_sansVehicule) {
    ostringstream os;
    string separator = "-------------------";
    os << separator << endl;
    os.width(10);
    os << "Nom " << ": " << this->t_nom << endl;
    os.width(10);
    os << "Prenom " << ": " << this->t_prenom << endl;
    ASSERT_EQ(t_proprietaire->reqProprietaireFormate(), os.str());
}
