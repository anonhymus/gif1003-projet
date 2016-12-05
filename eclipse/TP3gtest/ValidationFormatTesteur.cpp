/**
*  \file camionTest.cpp
*  \brief Test pour la classe Camion
*  \author Antoine Bouchard
*  \version 0.1-alpha
*  \date 11/23/2016
*/

#include<gtest/gtest.h>
#include "validation/validationFormat.h"
#include <iostream>

using namespace std;

//TODO plus de test pour plaque et nivValide

class ValidationFormatTest : public ::testing::Test {
public:
    vector<string> nivValide;
    vector<string> nivInvalide;
    vector<string> immatPromenade;
    vector<string> immatCamion;
    vector<string> immatPromenadeInvalide;
    vector<string> immatCamionInvalide;

    virtual void SetUp() {
        // Ajout de NIV valide dans le vecteur
        nivValide.push_back("S26F84ED0DM538541");
        nivValide.push_back("UNVT7V2H2N1325677");

        //Ajout des NIV non valide
        nivInvalide.push_back("S26184ED0DM52Q541");
        nivInvalide.push_back("S26F84ED0DM528541");

        // Plaque vehicule promenade valide
        immatPromenade.push_back("AAA 123");
        immatPromenade.push_back("000H456");
        immatPromenade.push_back("000A789");
        immatPromenade.push_back("000 ABC");
        immatPromenade.push_back("A00 XYZ");
        immatPromenade.push_back("E12 VEA");

        // Plaque vehicule promenade valide
        immatPromenadeInvalide.push_back("L000000");
        immatPromenadeInvalide.push_back("1234567");
        immatPromenadeInvalide.push_back("ABCD123");

        // Plaque camion valide
        immatCamion.push_back("L000000");
        immatCamion.push_back("L123456");

        // Plaque camion non valide
        immatCamionInvalide.push_back("A00 XYZ");
        immatCamionInvalide.push_back("E12 VEA");
    }
};

TEST_F(ValidationFormatTest, validerNivEstValide) {
    ASSERT_TRUE(util::validerNiv(nivValide.at(0)));
    ASSERT_TRUE(util::validerNiv(nivValide.at(1)));
}

TEST_F(ValidationFormatTest, validerNivEstInvalide) {
    ASSERT_FALSE(util::validerNiv(nivInvalide.at(0))) << "Le NIV n'est pas valide";
    ASSERT_FALSE(util::validerNiv(nivInvalide.at(1))) << "Le NIV n'est pas valide";
}

TEST_F(ValidationFormatTest, validationImmatriculationCamionEstValide) {
    for (int i = 0; i < immatCamion.size(); i++) {
        ASSERT_TRUE(util::validationImmatriculationCamion(immatCamion.at(i)));
    }
}

TEST_F(ValidationFormatTest, validationImmatriculationPromenadeEstValide) {
    for (int i = 0; i < immatPromenade.size(); i++) {
        ASSERT_TRUE(util::validationImmatriculationPromenade(immatPromenade.at(i)));
    }
}

TEST_F(ValidationFormatTest, validationImmatriculationCamionEstInvalide) {
    for (int i = 0; i < immatCamionInvalide.size(); i++) {
        ASSERT_FALSE(util::validationImmatriculationCamion(immatCamionInvalide.at(i)))
                                    << "Format de plaque pour camion invalide";
    }
}

TEST_F(ValidationFormatTest, validationImmatriculationPromenadeEstInvalide) {
    for (int i = 0; i < immatPromenadeInvalide.size(); i++) {
        ASSERT_FALSE(util::validationImmatriculationPromenade(immatPromenadeInvalide.at(i)))
                                    << "Format de plaque pour vehicule de promenade invalide";
    }
}