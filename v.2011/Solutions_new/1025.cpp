#include <iostream>

using namespace std;

class Sorter {
private:
	void *data; // сортируемые данные
	int size; // размер массива
	void sortIntQuick(int low,int high,int *data);
public:
	Sorter(void *data,int size);
	void sortInt(char type);
};

Sorter::Sorter(void *data,int size) {
	this->data=data;
	this->size=size;
}

void Sorter::sortInt(char type) {
	switch(type) {
		case 'q': // быстрая сортировка
			return this->sortIntQuick(0,this->size-1,(int*)this->data);
	}
}

void Sorter::sortIntQuick(int low,int high,int *data)
{
	int i=low,j=high,t;
	int x=data[(i+j)/2];
	while(i<j)	{
		while(data[i]<x)
			i++;
		while(data[j]>x)
			j--;
		if(i<=j) {
			t=data[i];
			data[i++]=data[j];
			data[j--]=t;
		}
	}
  if(low<j)
		this->sortIntQuick(low,j,data);
	if(high>i)
		this->sortIntQuick(i,high,data);
}

int main() {
	int k,count=0,*data;
	Sorter *s;
	cin>>k;
	data=new int[k];
	for(int i=0;i<k;i++)
		cin>>data[i];
	s=new Sorter(data,k);
	s->sortInt('q');
	for(int i=0;i<k/2+k%2;i++)
		count+=data[i]/2+data[i]%2;
	cout<<count;
}
