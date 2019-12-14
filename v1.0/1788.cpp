#include <iostream>

using namespace std;

template <class type> class sorter {
private:
	type *data; // сортируемые данные
	int size; // размер массива
	bool(*compareFunc)(type,type);
	void sortQuick(int low,int high,type *data);
	static bool ascCompare(type i,type j) {
		return i<j;
	}
	static bool descCompare(type i,type j) {
		return i>j;
	}
	void swap(type i,type j) {
		type t;
		t=this->data[i];
		this->data[i]=this->data[j];
		this->data[j]=t;
	}
public:
	sorter(type *data,int size);
	void reinit(type *data,int size);
	void sort(char algo,char dir);
};

template <class type> sorter<type>::sorter(type *data,int size) {
	this->data=data;
	this->size=size;
}

template <class type> void sorter<type>::reinit(type *data,int size) {
	this->data=data;
	this->size=size;
}

template <class type> void sorter<type>::sort(char algo,char dir) {
	switch(algo) {
		case 'q': // быстрая сортировка
			switch(dir) {
				case 'a': // по возрастанию
					this->compareFunc=&this->ascCompare;
					break;
				case 'd': // по убыванию
					this->compareFunc=&this->descCompare;
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
			swap(i++,j--);
	}
  if(low<j)
		this->sortQuick(low,j,data);
	if(high>i)
		this->sortQuick(i,high,data);
}

int main() {
	int n,m,min,*girls,*boys;
	sorter<int> *s;
	cin>>n>>m;
	girls=new int[n+1];
	boys=new int[m+1];
	for(int i=0;i<n;i++)
		cin>>girls[i];
	girls[n]=0;
	for(int i=0;i<m;i++)
		cin>>boys[i];
	boys[m]=0;
	s=new sorter<int>(boys,m);
	s->sort('q','d');
	s->reinit(girls,n);
	s->sort('q','d');
	for(int i=m;i>0;i--)
		boys[i-1]+=boys[i];
	for(int i=n;i>0;i--)
		girls[i-1]+=girls[i];
	min=girls[0];
	for(int i=1;(i<=m)&&(i<=n);i++)
		if(boys[i]*i+girls[i]<min)
			min=boys[i]*i+girls[i];
	cout<<min;
}
