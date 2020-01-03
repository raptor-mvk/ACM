// Topic: graph
// Subtopic: Lee algorithm
// Idea: vertices of graph are digits in phone number, edges are words of
//       dictionary

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

class Reader
{
  private:
    const char* buffer;
    int max_length; // maximal size of buffer
    int length; // current size of buffer
    int start_pos; // current position from beginning of the buffer
    int end_pos; // current position from end of the buffer
    istream& in; // input stream

  public:
    Reader(istream& in, const char* buffer, int max_length) :in(in)
    {
      this->buffer = buffer;
      this->max_length = max_length;
      this->length = 0;
      this->start_pos = 0;
      this->end_pos = 0;
    }

    // reinitialization of buffer
    void reinit(const char* buffer, int max_length)
    {
      this->buffer = buffer;
      this->max_length = max_length;
    }

    // fill buffer with data
    void fill()
    {
      this->in.getline((char*)this->buffer, this->max_length, 0);
      this->length = this->in.gcount();
      this->start_pos = 0;
      this->end_pos = this->length - 1;
    }

    // reads a word in dir direction (with delimiter, if readln = true)
    // check_func should return true for delimiter character
    bool getNext(FString* str, bool (*check_func)(char symbol), char dir, bool readln)
    {
      int start, length = 0;
      if (this->start_pos <= this->end_pos) {
        switch (dir) {
        case 'f':
          start = this->start_pos;
          while (this->start_pos <= this->end_pos) {
            if (check_func(this->buffer[this->start_pos])) {
              break;
            } else {
              this->start_pos++;
              length++;
            }
          }
          if (readln) {
            while (this->start_pos <= this->end_pos) {
              if (!check_func(this->buffer[this->start_pos])) {
                break;
              } else {
                this->start_pos++;
              }
            }
          }
          *str = FString((char*)this->buffer + start, length);
          return true;
        case 'b':
          start = this->end_pos;
          while (this->start_pos <= this->end_pos) {
            if (check_func(this->buffer[this->end_pos])) {
              break;
            } else {
              this->end_pos--;
              length++;
            }
          }
          if (readln) {
            while (this->start_pos <= this->end_pos) {
              if (!check_func(this->buffer[this->end_pos])) {
                break;
              } else {
                this->end_pos--;
              }
            }
          }
          *str = FString((char*)this->buffer + start - length + 1, length);
          return true;
        }
      }
      return false;
    }
    
    template <class T> bool getNext(T* number, char dir, bool readln)
    {
      T temp;
      switch (dir) {
      case 'f':
        if (this->start_pos > this->end_pos) {
          return false;
        }
        while (this->start_pos <= this->end_pos &&
          (this->buffer[this->start_pos] == ' ' ||
          this->buffer[this->start_pos] == '\t' ||
          this->buffer[this->start_pos] == '\n')) {
            this->start_pos++;
        }
        if (this->start_pos > this->end_pos) {
          return false;
        }
        *number = 0;
        while (this->buffer[this->start_pos] >= '0' &&
          this->buffer[this->start_pos] <= '9' &&
          this->start_pos <= this->end_pos) {
            (*number) *= 10;
            (*number) += this->buffer[this->start_pos] - '0';
            this->start_pos++;
        }
        if (readln) {
          while (this->start_pos <= this->end_pos &&
            (this->buffer[this->start_pos] == ' ' ||
            this->buffer[this->start_pos] == '\t' ||
            this->buffer[this->start_pos] == '\n')) {
              this->start_pos++;
          }
        }
        return true;
      case 'b':
        if (this->start_pos > this->end_pos) {
          return false;
        }
        while (this->start_pos <= this->end_pos &&
          (this->buffer[this->end_pos] == ' ' ||
          this->buffer[this->end_pos] == '\t' ||
          this->buffer[this->end_pos] == '\n')) {
            this->end_pos--;
        }
        if (this->start_pos > this->end_pos) {
          return false;
        }
        *number = 0;
        temp = 1;
        while (this->buffer[this->end_pos] >= '0' &&
          this->buffer[this->end_pos] <= '9' &&
          this->start_pos <= this->end_pos) {
            (*number) += (this->buffer[this->end_pos] - '0') * temp;
            temp *= 10;
            this->end_pos--;
        }
        if (readln) {
          while (this->start_pos <= this->end_pos &&
            (this->buffer[this->start_pos] == ' ' ||
            this->buffer[this->start_pos] == '\t' ||
            this->buffer[this->start_pos] == '\n')) {
              this->end_pos--;
          }
        }
        return true;
      }
      return false;
    }

    // ignores count characters in dir direction,
    // dir could be 'f' as forward and 'b' as backward
    void ignore(int count, char dir)
    {
      switch (dir) {
      case 'f':
        this->start_pos += count;
        return;
      case 'b':
        this->end_pos -= count;
        return;
      }
    }

    // reads a number from buffer in dir direction (with delimiters,
    // if readln = true)

    int getLength()
    {
      return this->length;
    }
};

// returns true, if symbol is '.', '!' or '?'
bool isSentenceEnd(char symbol)
{
  return symbol == '.' || symbol == '?' || symbol == '!';
}

// returns true, if symbol is a latin capital letter
bool isCapitalLetter(char symbol)
{
  return symbol >= 'A' && symbol <= 'Z';
}

// returns lowercased latin capital letters
// (or symbol itself for other symbols)
char lowerCase(char symbol)
{
  if (symbol >= 'A' && symbol <= 'Z') {
    return symbol + 'a' - 'A';
  } else {
    return symbol;
  }
}

// returns true, if symbol is a space, '\t', '\n', '.', ','
// '-', '!', '?', ':' or ';'
bool isPunctuationOrDelim(char symbol)
{
  return symbol == ' ' || symbol == '\t' || symbol == '\n' || symbol == '.' ||
    symbol == ',' || symbol == '-' || symbol == '!' || symbol == '?' ||
    symbol == ':' || symbol == ';';
}

// returns true, if symbol is a latin lowercase letter
bool isLowercaseLetter(char symbol)
{
  return symbol >= 'a' && symbol <= 'z';
}

// returns true, if symbol is a latin letter
bool isLetter(char symbol)
{
  return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z');
}

// returns true, if symbol is not a latin letter
bool notLetter(char symbol)
{
  return !isLetter(symbol);
}

// returns true, if symbol is a digit
bool isDigit(char symbol)
{
  return symbol >= '0' && symbol <= '9';
}

// returns true, if symbol is not a digit
bool notDigit(char symbol)
{
  return !isDigit(symbol);
}

// returns true, if symbol is a space, '\t' or '\n'
bool isDelim(char symbol)
{
  return symbol == ' ' || symbol == '\t' || symbol == '\n';
}

// returns true, if symbol is '\n'
bool isEndl(char symbol)
{
  return symbol == '\n';
}

template <class T> class vector2
{
  private:
    vector<T>* data;
    int dim[2]; // dimensions of array

  public:
    ~vector2()
    {
      delete[]data;
    }

    vector2()
    {
      dim[0] = 0;
      dim[1] = 0;
      data = 0;
    }

    vector2(int n, int m, T value)
    {
      dim[0] = n;
      dim[1] = m;
      data = new vector<T>[n];
      for (int i = 0; i < n; i++) {
        data[i].assign(m, value);
      }
    }

    vector2(const vector2<T>& a)
    {
      dim[0] = a.dim[0];
      dim[1] = a.dim[1];
      data = new vector<T>[dim[0]];
      for (int i = 0; i < dim[0]; i++) {
        data[i] = a.data[i];
      }
    }

    vector2<T>& operator=(const vector2<T>& a)
    {
      delete[] data;
      dim[0] = a.dim[0];
      dim[1] = a.dim[1];
      data = new vector<T>[dim[0]];
      for (int i = 0; i < dim[0]; i++) {
        data[i] = a.data[i];
      }
    }

    vector<T>& operator[](int i) const
    {
      return data[i];
    }

    vector<T>& operator[](int i)
    {
      return data[i];
    }

    int size()
    {
      return dim[0] * dim[1];
    }

    void assign(int n, int m, T value)
    {
      delete[] data;
      dim[0] = n;
      dim[1] = m;
      data = new vector<T>[n];
      for (int i = 0; i < n; i++) {
        data[i].assign(m, value);
      }
    }
};

class Graph
{
  private:
    static const int NO_EDGE = -1;

    vector2<int> adj; // adjacency matrix
    bool isOriented;
    int verticesCount;
  public:
    Graph(int n, bool isOriented)
    {
      adj.assign(n, n, NO_EDGE);
      verticesCount = n;
      this->isOriented = isOriented;
    }

    // read k edges from stream
    void readEdgeList(istream& stream, int k, bool weighed = false)
    {
      int start, finish, weight;
      for (int i = 0; i < k; i++) {
        stream >> start >> finish;
        if (weighed) {
          stream >> weight;
        } else {
          weight = 1;
        }
        addEdge(start - 1, finish - 1, weight);
      }
    }

    // add edge from i to j
    void addEdge(int i, int j, int weight = 1)
    {
      adj[i][j] = weight;
      if (!isOriented) {
        adj[j][i] = weight;
      }
    }

    // way search between 'first' and 'last' using lee algorithm
    void findWayLee(int first, int last, vector<int>* way)
    {
      vector<int> queue;
      int* was;
      unsigned int start = 0;
      was = new int[verticesCount];
      memset(was, 0, verticesCount * sizeof(int));
      queue.push_back(first);
      was[first] = 1;
      while (start < queue.size()) {
        for (int i = 0; i < verticesCount; i++) {
          if (adj[queue[start]][i] != NO_EDGE && (!was[i] || was[i] >
            was[queue[start]] + 1)) {
              was[i] = was[queue[start]] + 1;
              if (i == last) {
                break;
              }
              queue.push_back(i);
          }
        }
        start++;
      }
      if (was[last]) {
        way->push_back(last);
        for (int i = 0; i < was[last] - 1; i++) {
          for (int j = 0; j < verticesCount; j++) {
            if (adj[j][(*way)[i]] != NO_EDGE && was[j] == was[(*way)[i]] - 1) {
              way->push_back(j);
              break;
            }
          }
        }
      }
    }

    // gets all neighbors of kth vertex
    void getNeighbors(int k, vector<int>* result)
    {
      for (int i = 0; i < verticesCount; i++) {
        if (adj[k][i] != NO_EDGE) {
          result->push_back(i);
        }
      }
    }

    vector<int>& operator[](int i) const
    {
      return adj[i];
    }

    vector<int>& operator[](int i)
    {
      return adj[i];
    }
};

const int MAX_WORD_LENGTH = 152;
const int MAX_DATA_SIZE = 300 * 1024 + 1;

char processFunc(char symbol)
{
  switch (symbol) {
    case 'i': case 'j':
      return '1';
    case 'a': case 'b': case 'c':
      return '2';
    case 'd': case 'e': case 'f':
      return '3';
    case 'g': case 'h':
      return '4';
    case 'k': case 'l':
      return '5';
    case 'm': case 'n':
      return '6';
    case 'p': case 'r': case 's':
      return '7';
    case 't': case 'u': case 'v':
      return '8';
    case 'w': case 'x': case 'y':
      return '9';
    case 'o': case 'q': case 'z':
      return '0';
  }
  return 0;
}

int main()
{
  FString::setMaxLength(MAX_WORD_LENGTH);
  int n;
  char* data = new char[MAX_DATA_SIZE];
  FString phone, * dictionary, * words;
  Reader* r;
  Graph* g;
  vector<int> pos;
  r = new Reader(cin, data, MAX_DATA_SIZE);
  r->fill();
  while (true) {
    r->getNext(&phone, &isDelim, 'f', true);
    if (phone[0] == '-') {
      break;
    }
    g = new Graph(phone.getLength() + 1, true);
    r->getNext<int>(&n, 'f', true);
    dictionary = new FString[n];
    words = new FString[n];
    for (int i = 0; i < n; i++) {
      r->getNext(words + i, &isDelim, 'f', true);
      dictionary[i] = words[i].process(&processFunc);
      pos.clear();
      phone.find(dictionary[i], &pos);
      for (int j = 0, count = pos.size(); j < count; j++) {
        g->addEdge(pos[j], pos[j] + dictionary[i].getLength(), i + 1);
      }
    }
    pos.clear();
    g->findWayLee(0, phone.getLength(), &pos);
    if (pos.size()) {
      for (int i = pos.size() - 1; i > 0; i--) {
        cout << words[(*g)[pos[i]][pos[i - 1]] - 1];
        if (i > 1) {
          cout << ' ';
        } else {
          cout << '\n';
        }
      }
    } else {
      cout << "No solution.\n";
    }
    delete[] dictionary;
    delete[] words;
    delete g;
  }
}
