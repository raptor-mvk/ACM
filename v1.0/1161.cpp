#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

template <class type> class sorter {
private:
	type *data; // сортируемые данные
	int size; // размер массива

	void sortQuickAsc(int low,int high); // "быстрая" сортировка по возрастанию
	void sortQuickDesc(int low,int high); // "быстрая" сортировка по убыванию

	// поиск в массиве, отсортированном по возрастанию	
	int searchAsc(type value,int first,int last);

	// поиск в массиве, отсортированном по убыванию	
	int searchDesc(type value,int first,int last);

	void swap(int i,int j); // обмен местами i-го и j-го элемента
	bool compare(type i,type j); // сравнение i и j
public:
	sorter(type *data,int size);

	// сортировка алгоритмом algo в направлении dir
	void sort(char algo,char dir);
	// поиск значение value в отсортированном в направлении dir массиве
	int search(type value,char dir);
};

template <class type> void sorter<type>::swap(int i,int j) {
	type t;
	t=this->data[i];
	this->data[i]=this->data[j];
	this->data[j]=t;
}

template <class type> sorter<type>::sorter(type *data,int size) {
	this->data=data;
	this->size=size;
}

template <class type> void sorter<type>::sort(char algo,char dir) {
	switch(algo) {
		case 'q': // быстрая сортировка
			switch(dir) {
				case 'a': // сортировка по возрастанию
					return this->sortQuickAsc(0,this->size-1);
				case 'd': // сортировка по убыванию
					return this->sortQuickDesc(0,this->size-1);
			}
	}
}

template <class type> int sorter<type>::search(type value,char dir) {
	switch(dir) {
		case 'a': // сортировка по возрастанию
			return this->searchAsc(value,0,this->size-1);
		case 'd': // сортировка по убыванию
			return this->searchDesc(value,0,this->size-1);
	}
}

template <class type> void sorter<type>::sortQuickAsc(int low,int high) {
	int i=low,j=high;
	type x=this->data[(i+j)/2];
	while(i<j)	{
		while(this->data[i]<x)
			i++;
		while(x<this->data[j])
			j--;
		if(i<=j)
			this->swap(i++,j--);
	}
  if(low<j)
		this->sortQuickAsc(low,j);
	if(high>i)
		this->sortQuickAsc(i,high);
}

template <class type> void sorter<type>::sortQuickDesc(int low,int high) {
	int i=low,j=high;
	type x=this->data[(i+j)/2];
	while(i<j)	{
		while(this->data[i]>x)
			i++;
		while(x>this->data[j])
			j--;
		if(i<=j)
			this->swap(i++,j--);
	}
  if(low<j)
		this->sortQuickDesc(low,j);
	if(high>i)
		this->sortQuickDesc(i,high);
}

template <class type> int sorter<type>::searchAsc(type value,int first,
	int last) {
		int i=(first+last)/2;
		if(first<last) {
			if(this->data[i]==value)
				return i;
			if(this->data[i]>value)
				return this->searchAsc(value,first,--i);
			else
				return this->searchAsc(value,++i,last);
		}
		return (this->data[first]!=value)?-1:first;
}

template <class type> int sorter<type>::searchDesc(type value,int first,
	int last) {
		int i=(first+last)/2;
		if(first<last) {
			if(this->data[i]==value)
				return i;
			if(this->data[i]<value)
				return this->searchDesc(value,first,--i);
			else
				return this->searchDesc(value,++i,last);
		}
		return (this->data[first]!=value)?-1:first;
}

int main() {
	int n;
	double *stripies,result;
	sorter<double> *s;
	cin>>n;
	stripies=new double[n];
	for(int i=0;i<n;i++)
		cin>>stripies[i];
	s=new sorter<double>(stripies,n);
	s->sort('q','d');
	result=stripies[0];
	for(int i=1;i<n;i++)
		result=2.0*sqrt(result*stripies[i]);
	cout<<fixed<<setprecision(2)<<result;
}
