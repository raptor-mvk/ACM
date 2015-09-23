#include "Reader.h"

Reader::Reader(istream &in, const char *buffer, int max_length):in(in) {
	this->buffer = buffer;
	this->max_length = max_length;
	this->length = 0;
	this->start_pos = 0;
	this->end_pos = 0;
}

void Reader::reinit(const char *buffer, int max_length) {
	this->buffer = buffer;
	this->max_length = max_length;
}

void Reader::fill() {
	this->in.getline((char*)this->buffer, this->max_length, 0);
	this->length = this->in.gcount();
	this->start_pos = 0;
	this->end_pos = this->length - 1;
}

void Reader::ignore(int count, char dir) {
	switch (dir) {
		case 'f':
			this->start_pos += count;
			return;
		case 'b':
			this->end_pos -= count;
			return;
	}
}

bool Reader::getNext(FString *str, bool (*check_func)(char symbol), char dir,
	bool readln) {
		int start, length = 0;
		if (this->start_pos <= this->end_pos) {
      switch (dir) {
        case 'f':
          start = this->start_pos;
          while (this->start_pos <= this->end_pos) {
            if (check_func(this->buffer[this->start_pos])) {
              break;
            }	else {
              this->start_pos++;
              length++;
            }
          }
          if (readln) {
            while (this->start_pos <= this->end_pos) {
              if (!check_func(this->buffer[this->start_pos])) {
                break;
              }	else {
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
            }	else {
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

bool isSentenceEnd(char symbol) {
	return symbol == '.' || symbol == '?' || symbol=='!';
}

bool isCapitalLetter(char symbol) {
	return symbol >= 'A' && symbol <= 'Z';
}

char lowerCase(char symbol) {
	if (symbol >= 'A' && symbol <= 'Z') {
		return symbol + 'a' - 'A';
	} else {
		return symbol;
	}
}

bool isPunctuationOrDelim(char symbol) {
	return symbol == ' ' || symbol == '\t' || symbol == '\n' || symbol == '.' ||
		symbol == ',' || symbol == '-' || symbol == '!' || symbol == '?' ||
		symbol==':';
}

bool isLowercaseLetter(char symbol) {
	return symbol >= 'a' && symbol <= 'z';
}

bool isLetter(char symbol) {
	return (symbol >= 'a' && symbol <= 'z') || (symbol>='A' && symbol<='Z');
}

bool notLetter(char symbol) {
	return !isLetter(symbol);
}

bool isDigit(char symbol) {
	return symbol >= '0' && symbol <= '9';
}

bool notDigit(char symbol) {
	return !isDigit(symbol);
}

bool isDelim(char symbol) {
	return symbol == ' ' || symbol == '\t' || symbol == '\n';
}

bool isEndl(char symbol) {
	return symbol == '\n';
}
