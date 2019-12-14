#include <iostream>

using namespace std;

template <class type> class sorter {
private:
	type *data; // сортируемые данные
	int size; // размер массива
	bool(*compareFunc)(type,type);
	void sortQuick(int low,int high,type *data);
	void swap(int i,int j);
public:
	sorter(type *data,int size);
	void sort(char algo,char dir);
};

template <typename type> bool ascCompare(type i,type j) {
	return i<j;
}

template <typename type> bool descCompare(type i,type j) {
	return i>j;
}

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
				case 'a': // по возрастанию
					this->compareFunc=&ascCompare;
					break;
				case 'd': // по убыванию
					this->compareFunc=&descCompare;
					break;
			}
			return this->sortQuick(0,this->size-1,this->data);
	}
}

template <class type> void sorter<type>::sortQuick(int low,int high,type *data)
{
	int i=low,j=high;
	type x=data[(i+j)/2];
	while(i<j)	{
		while(this->compareFunc(data[i],x))
			i++;
		while(this->compareFunc(x,data[j]))
			j--;
		if(i<=j)
			this->swap(i++,j--);
	}
  if(low<j)
		this->sortQuick(low,j,data);
	if(high>i)
		this->sortQuick(i,high,data);
}

int main() {
  int n,*numbers;
  sorter<int> *s;
  cin>>n;
  numbers=new int[n];
  for(int i=0;i<n;i++)
  	cin>>numbers[i];
  s=new sorter<int>(numbers,n);
  s->sort('q','a');
  for(int i=n-1;i>=0;i--)
  	cout<<numbers[i]<<'\n';
}
