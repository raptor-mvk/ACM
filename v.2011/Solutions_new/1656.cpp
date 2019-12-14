#include <iostream>

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
	int n,*soldiers,*army,cur;
	sorter<int> *s;
	cin>>n;
	soldiers=new int[n*n];
	army=new int[n*n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>soldiers[i*n+j];
	s=new sorter<int>(soldiers,n*n);
	s->sort('q','a');
	cur=0;
	for(int i=0;i<n/2;i++) {
		army[i*n+i]=soldiers[cur++];
		army[i*n+n-i-1]=soldiers[cur++];
		army[(n-i-1)*n+i]=soldiers[cur++];
		army[(n-i-1)*n+n-i-1]=soldiers[cur++];
		for(int j=1;j<n/2-i;j++) {
			army[i*n+i+j]=soldiers[cur++];
			army[(i+j)*n+i]=soldiers[cur++];
			army[i*n+n-i-j-1]=soldiers[cur++];
			army[(i+j)*n+n-i-1]=soldiers[cur++];
			army[(n-i-1)*n+i+j]=soldiers[cur++];
			army[(n-i-j-1)*n+i]=soldiers[cur++];
			army[(n-i-1)*n+n-i-j-1]=soldiers[cur++];
			army[(n-i-j-1)*n+n-i-1]=soldiers[cur++];
		}
		army[i*n+n/2]=soldiers[cur++];
		army[(n-i-1)*n+n/2]=soldiers[cur++];
		army[n/2*n+i]=soldiers[cur++];
		army[n/2*n+n-i-1]=soldiers[cur++];
	}
	army[n*n/2]=soldiers[cur];
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++)
			cout<<army[i*n+j]<<' ';
		cout<<'\n';
	}
}
