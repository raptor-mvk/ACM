#include <iostream>
#include <cstring>

using namespace std;

#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

template <class type> class array;
template <class type> ostream &operator<<(ostream &stream,
	const array<type> &arr);

template <class type> class array {
private:
	type *data;
	int allocated; // size of allocated memory
	int length; // current array length

	void expand(); // one page expand
public:
	static const int PAGE_SIZE=1024; //size of one page
	static char delimiter; // delimiter for printing

	array();
	array(const array<type> &arr);
	array(int length);
	void push(type item); // adds element to the end
	array<type> &operator=(const array<type> &arr);
	friend ostream &operator<< <>(ostream &stream,const array<type> &arr);

	~array() {
		delete [] data;
	}

	type &operator[](int index) {
		return data[index];
	}

	type &operator[](int index) const {
		return data[index];
	}

	int getLength() {
		return this->length;
	}
};

template <class type> array<type>::array() {
	this->data=new type[PAGE_SIZE];
	this->allocated=this->PAGE_SIZE;
	this->length=0;
}

template <class type> array<type>::array(const array<type> &arr) {
	this->data=new type[arr.allocated];
	this->allocated=arr.allocated;
	this->length=arr.length;
	if(arr.length)
		memcpy(this->data,arr.data,arr.length*sizeof(type));
}

template <class type> array<type>::array(int length) {
	this->data=new type[length];
	this->allocated=length;
	this->length=0;
}

template <class type> void array<type>::expand() {
	type *temp;
	temp=new type[this->allocated+this->PAGE_SIZE];
	memcpy(temp,this->data,this->allocated*sizeof(type));
	delete [] this->data;
	this->data=temp;
	this->allocated+=this->PAGE_SIZE;
}

template <class type> void array<type>::push(type item) {
	if(this->length==this->allocated)
		this->expand();
	data[this->length++]=item;
}

template <class type> array<type> &array<type>::operator=
	(const array<type> &arr) {
		delete [] this->data;
		this->data=new type[arr.allocated];
		this->allocated=arr.allocated;
		this->length=arr.length;
		if(arr.length)
			memcpy(this->data,arr.data,arr.length*sizeof(type));
		return *this;
}

template <class type> ostream &operator<<(ostream &stream,
	const array<type> &arr) {
	for(int i=0;i<arr.length;i++)
		stream<<arr[i]<<array<int>::delimiter;
	return stream;
}

class fstring {
public:
	static const int MAX_LENGTH=201; // maximal string length
	static char delimiter; // strings' delimiter
	static char nonSymbol; // symbol, that wouldn't appear in strings
	char *data;
	int length; // current string length
	fstring();
	fstring(char *data,int length);
	fstring(char symbol,int length);
	fstring(const fstring &str);
	fstring &operator=(const fstring &str);
	friend bool operator<(const fstring &left,const fstring &right);
	friend bool operator<=(const fstring &left,const fstring &right);
	friend bool operator>(const fstring &left,const fstring &right);
	friend bool operator>=(const fstring &left,const fstring &right);
	friend bool operator==(const fstring &left,const fstring &right);
	friend bool operator!=(const fstring &left,const fstring &right);
	friend ostream &operator<<(ostream &stream, const fstring &str);
	friend istream &operator>>(istream &stream, fstring &str);
	friend fstring operator+(const fstring &left,const fstring &right);
	fstring &operator+=(const fstring &right);
	friend fstring operator+(const fstring &left,const char &right);
	fstring &operator+=(const char &right);
	fstring reverse(); // returns reversed string
	fstring process(char(*processFunc)(char)); // returns string, processed by processFunc
	void prefixFunc(int *pfvalues,int start); // returns prefix function of substring [start,end of string]
	array<int> find(fstring substr); // returns positions of all occurrences of substr into string

	// returns substring [start,start+length-1]
	fstring substrl(int start,int length) {
		return fstring(this->data+start,length);
	}

	// returns substring [start,finish]
	fstring substrf(int start,int finish) {
		return fstring(this->data+start,finish-start+1);
	}

	// returns substring [start,end of string]
	fstring substr(int start) {
		return fstring(this->data+start,this->length-start);
	}

	// reduces the length of string by count characters
	void trimEnd(int count) {
		this->length-=count;
	}

	~fstring() {
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

class reader {
private:
	const char *buffer; // reading buffer
	int maxLength; // maximal size of buffer
	int length; // current size of buffer
	int startPos; // current position from beginning of the buffer
	int endPos; // current position from end of the buffer
	istream &in; // input stream
public:
	reader(istream &in,const char* buffer,int maxLength);
	void reinit(const char* buffer, int maxLength); // reinitialization of buffer
	void fill(); // fill buffer with data

	// ignores count characters in dir direction,
	// dir could be 'f' as forward and 'b' as backward
	void ignore(int count,char dir);

	// reads a number from buffer in dir direction (with delimiters, if readln = true)
	template <typename type> bool getNext(type *number,char dir,bool readln);

	// reads a word in dir direction (wtih delimiter, if readln = true)
	// checkFunc should return true for delimiter character
	bool getNext(fstring *str,bool(*checkFunc)(char symbol),char dir,bool readln);

	int getLength() {
		return this->length;
	}

};

template <typename type> bool reader::getNext(type *number,char dir,
	bool readln) {
		type temp;
		switch(dir) {
			case 'f':
				if(this->startPos>this->endPos)
					return false;
				while(((this->buffer[this->startPos]==' ')||
					(this->buffer[this->startPos]=='\t')||
					(this->buffer[this->startPos]=='\n'))&&(this->startPos<=this->endPos))
						this->startPos++;
				if(this->startPos>this->endPos)
					return false;
				*number=0;
				while((this->buffer[this->startPos]>='0')&&
					(this->buffer[this->startPos]<='9')&&(this->startPos<=this->endPos)) {
						(*number)*=10;
						(*number)+=this->buffer[this->startPos]-'0';
						this->startPos++;
				}
				if(readln)
					while(((this->buffer[this->startPos]==' ')||
						(this->buffer[this->startPos]=='\t')||
						(this->buffer[this->startPos]=='\n'))&&(this->startPos<=this->endPos))
							this->startPos++;
				return true;
			case 'b':
				if(this->startPos>this->endPos)
					return false;
				while(((this->buffer[this->endPos]==' ')||
					(this->buffer[this->endPos]=='\t')||
					(this->buffer[this->endPos]=='\n'))&&(this->startPos<=this->endPos))
						this->endPos--;
				if(this->startPos>this->endPos)
					return false;
				*number=0;
				temp=1;
				while((this->buffer[this->endPos]>='0')&&
					(this->buffer[this->endPos]<='9')&&(this->startPos<=this->endPos)) {
						(*number)+=(this->buffer[this->endPos]-'0')*temp;
						temp*=10;
						this->endPos--;
				}
				if(readln)
					while(((this->buffer[this->startPos]==' ')||
						(this->buffer[this->startPos]=='\t')||
						(this->buffer[this->startPos]=='\n'))&&(this->startPos<=this->endPos))
							this->endPos--;
				return true;
		}
}

#endif // READER_H_INCLUDED
