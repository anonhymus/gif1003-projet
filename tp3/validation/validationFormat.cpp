/**
* \file validationFormat.h
* \brief Une brève description du contenu du fichier
* \author Antoine Bouchard
* \version 1.0
* \date 14/9/2016
*/

#include <iostream>
#include <map>
#include "validationFormat.h"
#include <pthread.h>

using namespace std;
namespace util {
    const int MID = 3;
    const int VIN_LENGTH = 17;
    const int CHECKSUM_X = 10;
    const int CHECKSUM_POSITION = 8;

/**
 * \brief simple enumeration pour definir un charactere
 */
    enum CharType {
        ALPHA, DIGIT, SPACE, NONE
    };

    enum ImmatriculationType {
        PROMENADE, CAMION, INVALIDE
    };

/**
 * \brief Exception pour VIN invalide.
 */
    struct VinException : public exception {
//        const char *what() const throw() {
//            return "I, O et Q ne sont pas permis dans un NIV.";
//        }
    };

/**
 * \brief Exception pour Immatriculation invalide
 */
    struct ImmatriculationException : public exception {
        const char *what() const throw() {
            return "Plaque d'immatriculation invalide";
        }
    };

/**
 * \brief separe une string en 2 et enleve la lettre milieu
 * \param p_source[in] string a separer
 * \param p_partieA premiere partie de la string
 * \param p_partieB seconde partie de la string
 */
    void separeString(string p_source, string &p_partieA, string &p_partieB) {
        for (int i = 0; i < MID; i++) {
            p_partieA += p_source[i];
            p_partieB += p_source[i + MID + 1];
        }
    }

/**
 * \brief supprime le charactere a la position specifiee
 * \param p_cible chaine de charactere a modifiee
 * \param p_index la position du charactere
 * \return la nouvelle chaine de charactere
 */
    string supprimeCharPos(string p_cible, unsigned long p_index) {
        return p_cible.erase(p_index, 1);
    }

/**
 * \brief verifie dans quel cas on se trouve pour cette lettre
 * @param p_cible la lettre qui defini le cas
 * @return CharType
 */
    CharType verifieCas(char &p_cible) {
        if (isalpha(p_cible)) {
            return ALPHA;
        } else if (isdigit(p_cible)) {
            return DIGIT;
        } else if ((int) p_cible == 32) {
            return SPACE;
        } else {
            return NONE;
        }
    }

/**
 * \brief trouver la valeur entiere de cette lettre
 * \param p_valeur lettre que l'on veut sa valeur entiere
 * \return l'entier representant la lettre
 */
    int reqValeurLettre(char p_valeur) {
        map<char, int> keys;
        if ((p_valeur == 'I') | (p_valeur == 'O') | (p_valeur == 'Q')) throw VinException();
        else {
            keys['A'] = keys['J'] = 1;
            keys['B'] = keys['K'] = keys['S'] = 2;
            keys['C'] = keys['L'] = keys['T'] = 3;
            keys['D'] = keys['M'] = keys['U'] = 4;
            keys['E'] = keys['N'] = keys['V'] = 5;
            keys['F'] = keys['W'] = 6;
            keys['G'] = keys['P'] = keys['X'] = 7;
            keys['H'] = keys['Y'] = 8;
            keys['R'] = keys['Z'] = 9;
            return keys[p_valeur];
        }
    };

/**
 * \brief traduire chaque lettre du VIN en entier
 * \param[in] p_vin VIN a traduire
 * \param[out] p_vinArray la representation en entier du VIN
 */
    void traduireLettre(const string &p_vin, int p_vinArray[]) {
        for (unsigned i = 0; i < p_vin.length(); i++) {
            if (isupper(p_vin[i])) {
                p_vinArray[i] = reqValeurLettre(p_vin[i]);
            } else if (isdigit(p_vin[i])) {
                p_vinArray[i] = p_vin[i] % 48;
            } else {
                throw VinException();
            }
        }
    }

/**
 * \brief fonction ajoute le poids a chaque position du VIN
 * \param p_vin la chaine d'entier representant la VIN
 */
    void ajoutPoids(int p_vin[]) {
        int weights[] = {8, 7, 6, 5, 4, 3, 2, 10, 0, 9, 8, 7, 6, 5, 4, 3, 2};
        for (int i = 0; i < VIN_LENGTH; i++) {
            p_vin[i] *= weights[i];
        }
    }

/**
 * \brief calcul la somme de controle du VIN
 * \param p_vin la chaine d'entier representant la VIN
 * \return la somme de controle
 */
    int checksum(const int p_vin[]) {
        int tmp = 0;
        for (int i = 0; i < VIN_LENGTH; i++) {
            tmp += p_vin[i];
        }
        return tmp % 11;
    }

/**
 * \brief Fonction de validation d'un numero de plaque d'immatriculation
 * \param p_immatriculation le numero de la plaque a valider
 * \return si la plaque est valide ou non
 */
    ImmatriculationType validerImmatriculation(const string &p_immatriculation) {
        try {
            if (p_immatriculation.length() == 7) {
                ImmatriculationType typeImmatriculation = INVALIDE;
                char charMilieu = p_immatriculation[3];
                string immatMod = supprimeCharPos(p_immatriculation, MID);
                map<CharType, string> typeMap;
                typeMap[ALPHA] = "0";
                typeMap[DIGIT] = "1";
                typeMap[SPACE] = "2";
                typeMap[NONE] = "3";

                switch (verifieCas(charMilieu)) {
                    case ALPHA:
                        typeImmatriculation = PROMENADE;
                        for (int i = 0; i < (int) immatMod.length(); i++) {
                            if (!isdigit(immatMod[i])) {
                                throw ImmatriculationException();
                            }
                        }
                        break;
                    case DIGIT:
                        typeImmatriculation = CAMION;
                        if (immatMod[0] != 'L') {
                            throw ImmatriculationException();
                        } else {
                            for (int i = 1; i < (int) immatMod.length(); i++) {
                                if (!isdigit(immatMod[i]))
                                    throw ImmatriculationException();
                            }
                        }
                        break;
                    case SPACE: {
                        //TODO a refactorer
                        typeImmatriculation = PROMENADE;
                        string part1;
                        string part2;
                        string tmp;
                        separeString(p_immatriculation, part1, part2);
                        for (int i = 0; i < (int) part1.length(); i++) {
                            tmp += typeMap[verifieCas(part1[i])];
                        }
                        if (tmp == "111" || tmp == "011") {
                            for (int i = 0; i < (int) part2.length(); i++) {
                                if (isdigit(part2[i]))
                                    throw ImmatriculationException();
                            }
                        } else if (tmp == "000") {
                            for (int i = 0; i < (int) part2.length(); i++) {
                                if (!isdigit(part2[i]))
                                    throw ImmatriculationException();
                            }
                        } else
                            throw ImmatriculationException();
                        break;
                    }
                    case NONE:
                        throw ImmatriculationException();
                    default:
                        typeImmatriculation = INVALIDE;
                        break;
                }
                return typeImmatriculation;
            } else {
                throw ImmatriculationException();
            }
        } catch (ImmatriculationException &e) {
            return INVALIDE;
        }
    }


/**
 * \brief fonction pour valider le NIV
 * @param p_niv le NIV a valider
 * @return si le NIV est valide ou non
 */
    bool validerNiv(const string &p_niv) {
        bool isValid = false;
        try {
            if (p_niv.length() != VIN_LENGTH) {
                throw VinException();
            }
            if (p_niv[9] != 'Z' && p_niv[9] != 'U') {
                int formattedVin[VIN_LENGTH];
                traduireLettre(p_niv, formattedVin);
                ajoutPoids(formattedVin);
                int cs = checksum(formattedVin);
                if (cs == CHECKSUM_X) {
                    isValid = 'X' == p_niv[CHECKSUM_POSITION];
                } else {
                    isValid = cs == p_niv[CHECKSUM_POSITION] % 48;
                }
            }

        } catch (VinException &e) {
            isValid = false;
        }
        return isValid;
    }

    bool validationImmatriculationPromenade(const std::string &immatriculation) {
        return PROMENADE == validerImmatriculation(immatriculation);
    }

    bool validationImmatriculationCamion(const std::string &immatriculation) {
        return CAMION == validerImmatriculation(immatriculation);
    }
}
