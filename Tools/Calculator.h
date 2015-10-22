#include <vector>
#include <cmath>

#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

using namespace std;

class Calculator {
  private:
    // array of pre-calculated prime numbers
    vector<int> primes;
    // last calculated prime number
    int lastPrime;

    // adds next prime number to primes
    int getNextPrime();

    // calculate all prime numbers, which are less than n
    void calcPrimes(int n);
  public:
    Calculator();

    // fast modular exponentiation
    static int fastExpMod(int x, int n, int m);

    // calculate number of partial permutations of k elements from n
    static int partPermutCount(int n, int k);

    // calculate number of ordered distributions of n elements to k groups
    static int ordDistribCount(int n, int k);

    // calculate number of ordered groupings of n elements
    static int ordGroupCount(int n);

    // get all prime numbers, which are less than n
    vector<int> *getPrimes(int n);

    // fills result with all prime dividers of n
    void getPrimeDividers(int n, vector<int> *result);

    // fills result with powers of prime dividers of n,
    // indices corresponds to primes vector
    void getPrimeDividersPowers(int n, vector<int> *result);
};

#endif // CALCULATOR_H_INCLUDED
