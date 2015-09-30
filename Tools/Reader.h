#include "FString.h"

#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

class Reader {
private:
	const char *buffer;
	int max_length; // maximal size of buffer
	int length; // current size of buffer
	int start_pos; // current position from beginning of the buffer
	int end_pos; // current position from end of the buffer
	istream &in; // input stream
public:
	Reader(istream &in, const char* buffer, int max_length);
	void reinit(const char* buffer, int max_length); // reinitialization of buffer
	void fill(); // fill buffer with data

	// ignores count characters in dir direction,
	// dir could be 'f' as forward and 'b' as backward
	void ignore(int count, char dir);

	// reads a number from buffer in dir direction (with delimiters,
  // if readln = true)
	template <typename T> bool getNext(T *number, char dir, bool readln);

	// reads a word in dir direction (with delimiter, if readln = true)
	// check_func should return true for delimiter character
	bool getNext(FString *str, bool (*check_func)(char symbol), char dir,
              bool readln);

	int getLength() {
		return this->length;
	}

};

template <typename T> bool Reader::getNext(T *number, char dir,
	bool readln) {
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
					while(this->start_pos <= this->end_pos &&
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

#endif // READER_H_INCLUDED
