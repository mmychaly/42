#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class bigint {
private:
    std::vector<int> digits; // chiffres stockés en ordre inverse (123 = {3,2,1})

public:
    // Constructeurs
    bigint();
    bigint(unsigned long long n);
    bigint(const std::string& s);
    bigint(const bigint& other);

    // Destructeur
    ~bigint();

    // Affectation
    bigint& operator=(const bigint& other);

    // Comparaisons
    bool operator==(const bigint& other) const;
    bool operator<(const bigint& other) const;
    bool operator!=(const bigint& other) const;
    bool operator>(const bigint& other) const;
    bool operator<=(const bigint& other) const;
    bool operator>=(const bigint& other) const;

    // Opérations arithmétiques
    bigint operator+(const bigint& other) const;
    bigint& operator+=(const bigint& other);
    bigint operator-(const bigint& other) const;

    // Décalage de chiffres
    bigint operator<<(size_t n) const;
    bigint operator>>(size_t n) const;
    bigint& operator<<=(size_t n);
    bigint& operator>>=(size_t n);

    // Incrément
    bigint& operator++();   // prefixe
    bigint operator++(int); // postfixe

    // Utile pour normaliser
    void removeLeadingZeros();

    // ✅ Getter pour lire le vecteur de chiffres
    std::vector<int> get_digits() const;
};

// ✅ Déclaration externe de l’opérateur d’affichage
std::ostream& operator<<(std::ostream& os, const bigint& num);

#endif



/*#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class bigint 
{


    public:
        // Constructeurs
        bigint();                        // 0
        bigint(unsigned long long n);    // à partir d’un entier
        bigint(const std::string& s);    // à partir d’une string
        bigint(const bigint& other);     // constructeur par copie

        // Destructeur
        ~bigint();

        // Affectation
        bigint& operator=(const bigint& other);

        // Comparaisons
        bool operator==(const bigint& other) const;
        bool operator<(const bigint& other) const;
        bool operator!=(const bigint& other) const;
        bool operator>(const bigint& other) const;
        bool operator<=(const bigint& other) const;
        bool operator>=(const bigint& other) const;

        // Opérations arithmétiques
        bigint operator+(const bigint& other) const;
        bigint& operator+=(const bigint& other);
        bigint operator-(const bigint& other) const;

        // Décalage de chiffres
        bigint operator<<(size_t n) const;
        bigint operator>>(size_t n) const;
        bigint& operator<<=(size_t n);
        bigint& operator>>=(size_t n);

        // Incrément
        bigint& operator++();   // prefixe
        bigint operator++(int); // postfixe

        // Affichage

        // Utile pour normaliser
        void removeLeadingZeros();
        std::vector<int> get_conteneur() const;
    private:
        std::vector<int> digits; // chiffres stockés en ordre inverse (123 = {3,2,1})
};

    std::ostream& operator<<(std::ostream& os, const bigint& num);
#endif
*/