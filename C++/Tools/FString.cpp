#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class FString
{
  private:
    char* data;
    int length; // current string length

  public:
    static int maxLength; // maximal string length
    static char delimiter; // strings' delimiter
    static char non_symbol; // symbol, that wouldn't appear in strings

    static void setMaxLength(int maxLength)
    {
      FString::maxLength = maxLength;
    }

    // sets delimiter
    static void setDelimiter(char delimiter)
    {
      FString::delimiter = delimiter;
    }

    // sets symbol, that wouldn't appear in strings
    static void setNonSymbol(char non_symbol)
    {
      FString::non_symbol = non_symbol;
    }

    friend bool operator<(const FString& left, const FString& right);
    friend bool operator<=(const FString& left, const FString& right);
    friend bool operator>(const FString& left, const FString& right);
    friend bool operator>=(const FString& left, const FString& right);
    friend bool operator==(const FString& left, const FString& right);
    friend bool operator!=(const FString& left, const FString& right);
    friend ostream& operator<<(ostream& stream, const FString& str);
    friend istream& operator>>(istream& stream, FString& str);
    friend FString operator+(const FString& left, const FString& right);
    friend FString operator+(const FString& left, const char& right);

    // returns reversed string
    FString reverse()
    {
      FString result = *this;
      int len = this->length / 2;
      char temp;
      for (int i = 0; i < len; i++) {
        temp = result[i];
        result[i] = result[this->length - i - 1];
        result[this->length - i - 1] = temp;
      }
      return result;
    }


    // returns substring [start,start+length-1]
    FString substrl(int start, int length)
    {
      return FString(this->data[start], length);
    }

    // returns substring [start,finish]
    FString substrf(int start, int finish)
    {
      return FString(this->data[start], finish - start + 1);
    }

    // returns substring [start,end of string]
    FString substr(int start)
    {
      return FString(this->data[start], this->length - start);
    }

    // reduces the length of string by count characters
    void trimEnd(int count)
    {
      this->length -= count;
    }

    FString()
    {
      this->data = new char[FString::maxLength];
      this->length = 0;
    }

    FString(char* data, int length)
    {
      this->data = new char[FString::maxLength];
      if (length) {
        memcpy(this->data, data, length);
      }
      this->length = length;
    }

    FString(char symbol, int length)
    {
      this->data = new char[FString::maxLength];
      if (length) {
        memset(this->data, symbol, length);
      }
      this->length = length;
    }

    FString(const FString& str)
    {
      this->data = new char[FString::maxLength];
      this->length = str.length;
      if (str.length) {
        memcpy(this->data, str.data, str.length);
      }
    }

    ~FString()
    {
      delete[] data;
    }

    FString& operator+=(const FString& right)
    {
      if (right.length) {
        memcpy(this->data + this->length, right.data, right.length);
      }
      this->length += right.length;
      return *this;
    }


    FString& operator=(const FString& str)
    {
      this->length = str.length;
      if (str.length) {
        memcpy(this->data, str.data, str.length);
      }
      return *this;
    }

    FString& operator+=(const char& right)
    {
      this->data[this->length++] = right;
      return *this;
    }

    char& operator[](int index)
    {
      return data[index];
    }

    char operator[](int index) const
    {
      return data[index];
    }

    int getLength()
    {
      return this->length;
    }

    // returns string, processed by process_func
    FString process(char (*process_func)(char))
    {
      FString result;
      result.length = this->length;
      for (int i = 0; i < this->length; i++) {
        result[i] = process_func(this->data[i]);
      }
      return result;
    }

    // returns prefix function of substring [start,end of string]
    void prefixFunc(int* pfvalues, int start)
    {
      int cur;
      pfvalues[0] = 0;
      for (int i = 1; i < this->length - start; i++) {
        cur = pfvalues[i - 1];
        while (this->data[i + start] != this->data[cur + start]) {
          if (cur) {
            cur = pfvalues[cur - 1];
          } else {
            cur = -1;
            break;
          }
        }
        if (cur == -1) {
          pfvalues[i] = 0;
        } else {
          pfvalues[i] = cur + 1;
        }
      }
    }

    // returns positions of all occurrences of substr into string
    void find(FString substr, vector<int>* result)
    {
      FString temp(substr);
      int* pfunc;
      temp += FString::non_symbol;
      temp += *this;
      pfunc = new int[temp.length];
      temp.prefixFunc(pfunc, 0);
      for (int i = substr.length + 1; i < temp.length; i++) {
        if (pfunc[i] == substr.length) {
          result->push_back(i - 2 * substr.length);
        }
      }
    }
};

int FString::maxLength = 201; // maximal string length
char FString::delimiter = '\n'; // strings' delimiter
char FString::non_symbol = '@'; // symbol, that wouldn't appear in strings

bool operator<(const FString& left, const FString& right)
{
  int len = (left.length > right.length) ? right.length : left.length;
  for (int i = 0; i < len; i++) {
    if (left[i] < right[i]) {
      return true;
    } else if (left[i] > right[i]) {
      return false;
    }
  }
  if (right.length <= left.length) {
    return false;
  } else {
    return true;
  }
}

bool operator<=(const FString& left, const FString& right)
{
  int len = (left.length > right.length) ? right.length : left.length;
  for (int i = 0; i < len; i++) {
    if (left[i] < right[i]) {
      return true;
    } else if (left[i] > right[i]) {
      return false;
    }
  }
  if (right.length < left.length) {
    return false;
  } else {
    return true;
  }
}

bool operator>(const FString& left, const FString& right)
{
  return right < left;
}

bool operator>=(const FString& left, const FString& right)
{
  return right <= left;
}

bool operator==(const FString& left, const FString& right)
{
  if (right.length != left.length) {
    return false;
  }
  for (int i = 0; i < left.length; i++) {
    if (left[i] != right[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const FString& left, const FString& right)
{
  return !(right == left);
}

ostream& operator<<(ostream& stream, const FString& str)
{
  if (str.length) {
    stream.write(str.data, str.length);
  }
  return stream;
}

istream& operator>>(istream& stream, FString& str)
{
  stream.getline(str.data, FString::maxLength, FString::delimiter);
  if (stream.eof()) {
    str.length = stream.gcount();
  } else {
    str.length = stream.gcount() - 1;
  }
  return stream;
}

FString operator+(const FString& left, const FString& right)
{
  FString result(left);
  result.length = left.length + right.length;
  if (right.length) {
    memcpy(result.data + left.length, right.data, right.length);
  }
  return result;
}

FString operator+(const FString& left, const char& right)
{
  FString result(left);
  result.data[result.length++] = right;
  return result;
}
