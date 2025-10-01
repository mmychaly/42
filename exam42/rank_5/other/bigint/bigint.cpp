#include "bigint.hpp"

// ===== Constructeurs =====
bigint::bigint() {
    digits.push_back(0);
}

bigint::bigint(unsigned long long n) {
    if (n == 0) digits.push_back(0);
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
}

bigint::bigint(const std::string& s) {
    digits.clear();
    for (int i = s.size() - 1; i >= 0; --i) {
        if (isdigit(s[i])) {
            digits.push_back(s[i] - '0');
        }
    }
    removeLeadingZeros();
}

bigint::bigint(const bigint& other) {
    digits = other.digits;
}

// ===== Destructeur =====
bigint::~bigint() {}

// ===== Affectation =====
bigint& bigint::operator=(const bigint& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

// ===== Comparaisons =====
bool bigint::operator==(const bigint& other) const {
    return digits == other.digits;
}

bool bigint::operator<(const bigint& other) const {
    if (digits.size() != other.digits.size())
        return digits.size() < other.digits.size();
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i])
            return digits[i] < other.digits[i];
    }
    return false;
}

bool bigint::operator!=(const bigint& other) const { return !(*this == other); }
bool bigint::operator>(const bigint& other) const { return other < *this; }
bool bigint::operator<=(const bigint& other) const { return !(*this > other); }
bool bigint::operator>=(const bigint& other) const { return !(*this < other); }

// ===== Addition =====
bigint bigint::operator+(const bigint& other) const {
    bigint result;
    result.digits.clear();

    int carry = 0;
    size_t n = std::max(digits.size(), other.digits.size());
    for (size_t i = 0; i < n || carry; ++i) {
        int sum = carry;
        if (i < digits.size()) sum += digits[i];
        if (i < other.digits.size()) sum += other.digits[i];
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    return result;
}

bigint& bigint::operator+=(const bigint& other) {
    *this = *this + other;
    return *this;
}

// ===== Soustraction (supposons *this >= other) =====
bigint bigint::operator-(const bigint& other) const {
    if (*this < other) {
        return bigint(0);  // Retourne 0 pour un unsigned
    }
    bigint result = *this;
    int borrow = 0;
    for (size_t i = 0; i < result.digits.size(); ++i) {
        result.digits[i] -= borrow + (i < other.digits.size() ? other.digits[i] : 0);
        if (result.digits[i] < 0) {
            result.digits[i] += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
    }
    result.removeLeadingZeros();
    return result;
}

// ===== Décalages =====
bigint bigint::operator<<(size_t n) const {
    bigint result = *this;
    result <<= n;
    return result;
}

bigint bigint::operator>>(size_t n) const {
    bigint result = *this;
    result >>= n;
    return result;
}

bigint& bigint::operator<<=(size_t n) {
    if (*this == bigint(0)) return *this;
    digits.insert(digits.begin(), n, 0);
    return *this;
}

bigint& bigint::operator>>=(size_t n) {
    if (n >= digits.size()) {
        digits.clear();
        digits.push_back(0);
    } else {
        digits.erase(digits.begin(), digits.begin() + n);
    }
    return *this;
}

// ===== Incréments =====
bigint& bigint::operator++() {
    *this += bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint tmp(*this);
    ++(*this);
    return tmp;
}

// ===== Normalisation =====
void bigint::removeLeadingZeros() {
    
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
}

// ===== Getter =====
std::vector<int> bigint::get_digits() const {
    return digits;
}

// ===== Affichage =====
std::ostream& operator<<(std::ostream& os, const bigint& num) {
    std::vector<int> d = num.get_digits();
    for (int i = d.size() - 1; i >= 0; --i) {
        os << d[i];
    }
    return os;
}


/*

#include "bigint.hpp"

// --- Constructeurs ---
bigint::bigint() {
    digits.push_back(0);
}

bigint::bigint(unsigned long long n) {
    if (n == 0) digits.push_back(0);
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
}

bigint::bigint(const std::string& s) {
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        if (isdigit(*it))
            digits.push_back(*it - '0');
    }
    removeLeadingZeros();
    if (digits.empty()) digits.push_back(0);
}

bigint::bigint(const bigint& other) {
    digits = other.digits;
}

// --- Destructeur ---
bigint::~bigint() {}

// --- Affectation ---
bigint& bigint::operator=(const bigint& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

// --- Comparaisons ---
bool bigint::operator==(const bigint& other) const {
    return digits == other.digits;
}

bool bigint::operator<(const bigint& other) const {
    if (digits.size() != other.digits.size())
        return digits.size() < other.digits.size();
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i])
            return digits[i] < other.digits[i];
    }
    return false;
}

bool bigint::operator!=(const bigint& other) const {
    return !(*this == other);
}

bool bigint::operator>(const bigint& other) const {
    return other < *this;
}

bool bigint::operator<=(const bigint& other) const {
    return !(*this > other);
}

bool bigint::operator>=(const bigint& other) const {
    return !(*this < other);
}

// --- Arithmétique ---
bigint bigint::operator+(const bigint& other) const {
    bigint result;
    result.digits.clear();
    int carry = 0;
    size_t n = std::max(digits.size(), other.digits.size());

    for (size_t i = 0; i < n || carry; ++i) {
        int sum = carry;
        if (i < digits.size()) sum += digits[i];
        if (i < other.digits.size()) sum += other.digits[i];
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    return result;
}

bigint& bigint::operator+=(const bigint& other) {
    *this = *this + other;
    return *this;
}

bigint bigint::operator-(const bigint& other) const {
    // suppose *this >= other
    bigint result;
    result.digits.clear();
    int borrow = 0;

    for (size_t i = 0; i < digits.size(); ++i) {
        int diff = digits[i] - borrow;
        if (i < other.digits.size()) diff -= other.digits[i];
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.push_back(diff);
    }
    result.removeLeadingZeros();
    return result;
}

// --- Décalage ---
bigint bigint::operator<<(size_t n) const {
    bigint result = *this;
    result.digits.insert(result.digits.begin(), n, 0);
    return result;
}

bigint bigint::operator>>(size_t n) const {
    bigint result = *this;
    if (n >= result.digits.size()) return bigint(0);
    result.digits.erase(result.digits.begin(), result.digits.begin() + n);
    return result;
}

bigint& bigint::operator<<=(size_t n) {
    digits.insert(digits.begin(), n, 0);
    return *this;
}

bigint& bigint::operator>>=(size_t n) {
    if (n >= digits.size()) {
        digits = {0};
    } else {
        digits.erase(digits.begin(), digits.begin() + n);
    }
    return *this;
}

// --- Incrément ---
bigint& bigint::operator++() {
    *this += bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint temp = *this;
    ++(*this);
    return temp;
}

std::vector<int> bigint::get_conteneur(void) const
{
    return digits;
}
// --- Affichage ---
// Ici, ton header impose que ce soit une MÉTHODE, pas un friend externe.
// Donc on l’écrit ainsi :

// --- Utils ---
void bigint::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
}

std::ostream& operator<<(std::ostream& os, const bigint& num)
{
    std::vector<int> tmp = num.get_conteneur();
    for (int i = tmp.size() - 1; i >= 0; --i) {
        os << tmp[i];
    }
    return os;
}
--------------------------------
#include <string>
#include <stdexcept>  // pour std::invalid_argument
#include <cctype>     // pour std::isdigit

bool is_all_digits(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;

bigint::bigint(const std::string& s) {
    if (!is_all_digits(s)) {
        throw std::invalid_argument("Invalid string for bigint");
    }
    // enlever les zéros devant
    size_t pos = s.find_first_not_of('0');
    if (pos == std::string::npos)
        digits = {0};
    else {
        for (auto it = s.rbegin(); it != s.rend() - pos; ++it)
            digits.push_back(*it - '0');
    }
}
}*/
