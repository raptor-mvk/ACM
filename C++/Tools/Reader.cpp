// Require FString.cpp

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
