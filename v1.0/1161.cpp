#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

template <class type> class sorter {
private:
	type *data; // ����������� ������
	int size; // ������ �������

	void sortQuickAsc(int low,int high); // "�������" ���������� �� �����������
	void sortQuickDesc(int low,int high); // "�������" ���������� �� ��������

	// ����� � �������, ��������������� �� �����������	
	int searchAsc(type value,int first,int last);

	// ����� � �������, ��������������� �� ��������	
	int searchDesc(type value,int first,int last);

	void swap(int i,int j); // ����� ������� i-�� � j-�� ��������
	bool compare(type i,type j); // ��������� i � j
public:
	sorter(type *data,int size);

	// ���������� ���������� algo � ����������� dir
	void sort(char algo,char dir);
	// ����� �������� value � ��������������� � ����������� dir �������
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
		case 'q': // ������� ����������
			switch(dir) {
				case 'a': // ���������� �� �����������
					return this->sortQuickAsc(0,this->size-1);
				case 'd': // ���������� �� ��������
					return this->sortQuickDesc(0,this->size-1);
			}
	}
}

template <class type> int sorter<type>::search(type value,char dir) {
	switch(dir) {
		case 'a': // ���������� �� �����������
			return this->searchAsc(value,0,this->size-1);
		case 'd': // ���������� �� ��������
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
