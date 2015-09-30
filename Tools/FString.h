#include <iostream>
#include <cstring>
#include <vector>

#ifndef FSTRING_H_INCLUDED
#define FSTRING_H_INCLUDED

using namespace std;

class FString {
  public:
    static const int MAX_LENGTH = 201; // maximal string length
    static char delimiter; // strings' delimiter
    static char non_symbol; // symbol, that wouldn't appear in strings

    // sets delimiter
    static void setDelimiter(char delimiter) {
      FString::delimiter = delimiter;
    }

    // sets symbol, that wouldn't appear in strings
    static void setNonSymbol(char non_symbol) {
      FString::non_symbol = non_symbol;
    }

    char *data;
    int length; // current string length
    FString();
    FString(char *data, int length);
    FString(char symbol, int length);
    FString(const FString &str);
    FString &operator=(const FString &str);
    friend bool operator<(const FString &left, const FString &right);
    friend bool operator<=(const FString &left, const FString &right);
    friend bool operator>(const FString &left, const FString &right);
    friend bool operator>=(const FString &left, const FString &right);
    friend bool operator==(const FString &left, const FString &right);
    friend bool operator!=(const FString &left, const FString &right);
    friend ostream &operator<<(ostream &stream, const FString &str);
    friend istream &operator>>(istream &stream, FString &str);
    friend FString operator+(const FString &left, const FString &right);
    FString &operator+=(const FString &right);
    friend FString operator+(const FString &left, const char &right);
    FString &operator+=(const char &right);
    FString reverse(); // returns reversed string

    // returns string, processed by process_func
    FString process(char (*process_func)(char));

    // returns prefix function of substring [start,end of string]
    void prefixFunc(int *pfvalues, int start);

    // returns positions of all occurrences of substr into string
    vector<int> find(FString substr);

    // returns substring [start,start+length-1]
    FString substrl(int start, int length) {
      return FString(this->data[start], length);
    }

    // returns substring [start,finish]
    FString substrf(int start, int finish) {
      return FString(this->data[start], finish - start + 1);
    }

    // returns substring [start,end of string]
    FString substr(int start) {
      return FString(this->data[start], this->length - start);
    }

    // reduces the length of string by count characters
    void trimEnd(int count) {
      this->length -= count;
    }

    ~FString() {
      delete [] data;
    }

    char &operator[](int index) {
      return data[index];
    }

    char operator[](int index) const {
      return data[index];
    }

    int getLength() {
      return this->length;
    }
};

#endif // FSTRING_H_INCLUDED
