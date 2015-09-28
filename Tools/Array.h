#include <iostream>
#include <cstring>

#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

using namespace std;

template <class type> class Array;
template <class type> ostream &operator<<(ostream &stream,
                                          const Array<type> &arr);

template <class type> class Array {
  private:
    type *data;
    int allocated; // size of allocated memory
    int length; // current array length

    void expand(); // one page expand
  public:
    static const int PAGE_SIZE = 1024; //size of one page
    static char delimiter; // delimiter for printing

    // sets delimiter
    static void setDelimiter(char delimiter) {
      Array::delimiter = delimiter;
    }

    Array();
    Array(const Array<type> &arr);
    Array(int length);
    void push(type item); // adds element to the end
    Array<type> &operator=(const Array<type> &arr);
    friend ostream &operator<< <>(ostream &stream, const Array<type> &arr);

    ~Array() {
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

template <class type> Array<type>::Array() {
	this->data = new type[PAGE_SIZE];
	this->allocated = this->PAGE_SIZE;
	this->length = 0;
}

template <class type> Array<type>::Array(const Array<type> &arr) {
	this->data = new type[arr.allocated];
	this->allocated = arr.allocated;
	this->length = arr.length;
	if (arr.length) {
		memcpy(this->data, arr.data, arr.length * sizeof(type));
	}
}

template <class type> Array<type>::Array(int length) {
	this->data = new type[length];
	this->allocated = length;
	this->length = 0;
}

template <class type> void Array<type>::expand() {
	type *temp;
	temp = new type[this->allocated + this->PAGE_SIZE];
	memcpy(temp, this->data, this->allocated * sizeof(type));
	delete [] this->data;
	this->data = temp;
	this->allocated += this->PAGE_SIZE;
}

template <class type> void Array<type>::push(type item) {
	if (this->length == this->allocated) {
		this->expand();
	}
	data[this->length++] = item;
}

template <class type> Array<type> &Array<type>::operator=
  (const Array<type> &arr) {
		delete [] this->data;
		this->data = new type[arr.allocated];
		this->allocated = arr.allocated;
		this->length = arr.length;
		if (arr.length) {
			memcpy(this->data, arr.data, arr.length * sizeof(type));
		}
		return *this;
}

template <class type> ostream &operator<<(ostream &stream,
	const Array<type> &arr) {
	for (int i = 0; i < arr.length; i++) {
		stream << arr[i] << Array<int>::delimiter;
	}
	return stream;
}

#endif // ARRAY_H_INCLUDED
