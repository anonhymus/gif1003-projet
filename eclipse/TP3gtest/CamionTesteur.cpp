#include<gtest/gtest.h>
#include <sstream>
#include "contrat/ContratException.h"
#include "Camion.h"
#include "date/Date.h"

using namespace std;
using namespace vehicule;

TEST(Camion, ConstructeurNivNonValide) {
    ASSERT_THROW(Camion camion("", "", 3002, 4);, PreconditionException);
    ASSERT_THROW(Camion camion("S26F84ED0DM538541", "L000000", 0, 4);, PreconditionException);
    ASSERT_THROW(Camion camion("S26F84ED0DM538541", "L000000", 3001, 0);, PreconditionException);
}


class CamionTest : public ::testing::Test {
public:
    Camion *camion1;
    Camion *camion2;
    string niv = "S26F84ED0DM538541";
    string immat = "L000012";
    int poids = 3004;
    int nbEssieux = 2;
    double tarif2Essieux = 556.50;
    util::Date dateEnr;

    virtual void SetUp() {
        this->camion1 = new Camion(niv, immat, poids, nbEssieux);
        this->camion2 = new Camion(niv, immat, poids, nbEssieux);
    }
};

TEST_F(CamionTest, constructeurValide) {
    ASSERT_EQ(niv, camion1->reqNiv());
    ASSERT_EQ(immat, camion1->reqImmatriculation());
    ASSERT_EQ(poids, camion1->reqPoids());
    ASSERT_EQ(nbEssieux, camion1->reqNombreEssieux());
}

TEST_F(CamionTest, modifierImmatriculationCamionValide) {
    camion1->asgImmatriculation("L123456");
    ASSERT_EQ("L123456", camion1->reqImmatriculation());
}

TEST_F(CamionTest, modifierImmatriculationCamionNonValide) {
    ASSERT_THROW(camion1->asgImmatriculation("AAA 000"), PreconditionException);
}

TEST_F(CamionTest, formattageCamion_test) {
    ostringstream os;
    os.width(26);
    os << left << "Numero de serie" << ": " << niv << endl;
    os.width(26);
    os << left << "Numero d'immatriculation" << ": " << immat << endl;
    os.width(26);
    os << left << "Date d'enregistrement" << ": "
       << dateEnr.reqDateFormatee() << endl;
    os.width(26);
    os << left << "Nombre d'essieux " << ": " << this->nbEssieux << endl;
    os.width(26);
    os << left << "Poids " << ": " << this->poids << endl;
    os.width(26);
    os << left << "Tarif " << ": " << this->tarif2Essieux << "$" << endl;

    ASSERT_EQ(os.str(), camion1->reqVehiculeFormate());
}


TEST_F(CamionTest, reqPoids_test) {
    ASSERT_EQ(3004, camion1->reqPoids());
}

TEST(Camion, operateurEgaliteTestEstValide) {
    Camion camion1("S26F84ED0DM538541", "L000000", 3002, 2);
    Camion camion2("S26F84ED0DM538541", "L000000", 3002, 2);

    ASSERT_TRUE(camion1 == camion2);
}

TEST(Camion, tarrificationAnnuelle_test) {
    Camion camion1("S26F84ED0DM538541", "L000000", 3002, 2);
    Camion camion2("S26F84ED0DM538541", "L000000", 4003, 2);
    Camion camion3("S26F84ED0DM538541", "L000000", 4003, 3);
    Camion camion4("S26F84ED0DM538541", "L000000", 4003, 4);
    Camion camion5("S26F84ED0DM538541", "L000000", 4003, 5);
    Camion camion6("S26F84ED0DM538541", "L000000", 4003, 6);
    Camion camion7("S26F84ED0DM538541", "L000000", 4003, 7);

    // 2 essieux
    ASSERT_EQ(556.50, camion1.tarificationAnnuelle());
    ASSERT_EQ(881.50, camion2.tarificationAnnuelle());
    // 3 essieux
    ASSERT_EQ(1512.94, camion3.tarificationAnnuelle());
    // 4 essieux
    ASSERT_EQ(2132.94, camion4.tarificationAnnuelle());
    // 5 essieux
    ASSERT_EQ(2698.06, camion5.tarificationAnnuelle());
    // 6 essieux
    ASSERT_EQ(3577.06, camion6.tarificationAnnuelle());
    // 7 essieux
    ASSERT_EQ(3577.06, camion7.tarificationAnnuelle());
}
