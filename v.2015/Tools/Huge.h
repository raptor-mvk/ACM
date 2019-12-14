#include "FString.h"
#include <cmath>

#ifndef HUGE_H_INCLUDED
#define HUGE_H_INCLUDED

class Huge {
	friend class FString;

  private:
    int *number;
    int length; // current number length

    void shift(int count); // shift by 'count' digits to the left

    // multiply by 'number' and shift by 'shift' digits to the right
    void mul(int number, int shift);

    int &operator[](int index) {
      return this->number[index];
    }

  public:
    static const int FOUNDATION = 10; // base foundation
    static int power; // number of base digits in each Huge digit
    static int huge_foundation; // Huge foundation
    static int max_length; // max length of Huge number in Huge digits

    static void setFoundationPower(int power) {
      huge_foundation = (int)floor(pow(10.0, power));
      Huge::power = power;
    }

    static void setMaxLength(int max_length) {
      Huge::max_length = max_length;
    }

    Huge(int number);
    Huge(const Huge &number);
    Huge(const FString &str);
    Huge();
    Huge &operator=(const Huge &number);
    Huge &operator=(const int &number);
    Huge &operator+=(const int &right);
    Huge &operator+=(const Huge &right);
    Huge &operator*=(const int &right);
    Huge &operator*=(const Huge &right);
    operator FString() const;
    operator FString();
    friend ostream &operator<<(ostream &stream, Huge const &number);
    friend Huge operator+(const Huge &left, const int &right);
    friend Huge operator+(const Huge &left, const Huge &right);
    friend Huge operator*(const Huge &left, const int &right);
    friend Huge operator*(const Huge &left, const Huge &right);
    friend bool operator<(const Huge &left, const Huge &right);
    friend bool operator<=(const Huge &left, const Huge &right);
    friend bool operator>(const Huge &left, const Huge &right);
    friend bool operator>=(const Huge &left, const Huge &right);
    friend bool operator==(const Huge &left, const Huge &right);
    friend bool operator!=(const Huge &left, const Huge &right);

    ~Huge() {
      delete [] this->number;
    }

    int operator[](int index) const {
      return this->number[index];
    }

    int getLength() const {
      return this->length;
    }
};

#endif // HUGE_H_INCLUDED
