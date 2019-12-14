#include <iostream>

using namespace std;

template <class type> class array;
template <class type> ostream &operator<<(ostream &stream,
	const array<type> &arr);

template <class type> class array {
private:
	type *data; // данные
	int allocated; // объем выделенной памяти
	int length; // текущая длина массива

	void expand(); // расширение массива на одну страницу
public:
	static const int PAGE_SIZE=1024;
	static char delimiter; // разделитель при печати

	array();
	array(const array<type> &arr);
	array(int length);
	void push(type item); // добавление элемента в конец массива
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

template <class type> char array<type>::delimiter=' ';

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
