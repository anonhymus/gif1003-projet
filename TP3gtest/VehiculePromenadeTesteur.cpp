/**
*  \file vehiculePromenade_test.cpp
*  \brief Test pour vehiculePromenade
*  \author Antoine Bouchard
*  \version 0.1-alpha
*  \date 11/29/2016
*/

#include <gtest/gtest.h>
#include "vehicule.h"
#include "contrat/ContratException.h"
#include "vehiculePromenade.h"

using namespace std;
using namespace vehicule;

TEST(VehiculePromenade, constructeurEstValide) {
    ASSERT_NO_THROW(VehiculePromenade vehiculePromenade("S26F84ED0DM538541", "AAA 000", 2));
}

/**
 * \brief test cas invalide constructeur
 */
TEST(VehiculePromenade, constructeurEstInvalide) {
    ASSERT_THROW(VehiculePromenade vehiculePromenade("", "AAA 000", 2), ContratException);
    ASSERT_THROW(VehiculePromenade vehiculePromenade("S26F84ED0DM538541", "", 2), ContratException);
    ASSERT_THROW(VehiculePromenade vehiculePromenade("S26F84ED0DM538541", "AAA 000", 0), ContratException);
    ASSERT_THROW(VehiculePromenade vehiculePromenade("S26F84ED0DM538541", "L000000", 2), ContratException);
}

class VehiculePromenadeTest : public ::testing::Test {
public:
    VehiculePromenade *t_vehiculePromenade;
    string t_niv = "S26F84ED0DM538541";
    string t_immat = "AAA 000";
    int t_nbPlaces = 2;
    util::Date t_dateEnr;
    virtual void SetUp() {
        t_vehiculePromenade = new VehiculePromenade(t_niv, t_immat, t_nbPlaces);
    }
};

TEST_F(VehiculePromenadeTest, reqNbPlacesTest) {
    ASSERT_TRUE(t_nbPlaces == t_vehiculePromenade->reqNbPlaces());
}

TEST_F(VehiculePromenadeTest, asgImmatriculationTest){
    t_vehiculePromenade->asgImmatriculation("123H456");
    ASSERT_EQ("123H456", t_vehiculePromenade->reqImmatriculation());
}

TEST_F(VehiculePromenadeTest, asgImmatriculationTest_ContratException){
    ASSERT_THROW(t_vehiculePromenade->asgImmatriculation("L000000"), ContratException);
}

TEST_F(VehiculePromenadeTest, reqVehiculeFormateTest){
    ostringstream os;
    os.width(26);
    os << left << "Numero de serie" << ": " << t_niv << endl;
    os.width(26);
    os << left << "Numero d'immatriculation" << ": " << t_immat << endl;
    os.width(26);
    os << left << "Date d'enregistrement" << ": "
       << t_dateEnr.reqDateFormatee() << endl;
    os.width(26);
    os << left << "Nombre de places " << ": " << t_nbPlaces << endl;
    os.width(26);
    os << left << "Tarif " << ": " << t_vehiculePromenade->tarificationAnnuelle() << "$" << endl;
    ASSERT_EQ(os.str(), t_vehiculePromenade->reqVehiculeFormate());
}



