#include <iostream>

using namespace std;

class reader {
private:
	const char *buffer; // ����� ��� ������ ������
	int maxLength; // ������ ������
	int length; // ������� ������ ������ � ������
	int startPos; // ������� ������� � ������ ������
	int endPos; // ������� ������� � ����� ������
	istream &in; // ������� ����� ��� ������ ������
public:
	reader(istream &in,const char* buffer,int maxLength);
	void reinit(const char* buffer, int maxLength); // ������� ������ ������
	void fill(); // ���������� ������ �������
	// ���������� ���������� ������ � ������ ������
	template <typename type> void readln(type *data);
	// ���������� ������ ����� �� ������ � ����������� dir
	template <typename type> bool bufread(type *number,char dir);
	
	int getLength() {
		return this->length;
	}
};

reader::reader(istream &in,const char *buffer,int maxLength):in(in) {
	this->buffer=buffer;
	this->maxLength=maxLength;
	this->length=0;
	this->startPos=0;
	this->endPos=0;
}

void reader::reinit(const char *buffer,int maxLength) {
	this->buffer=buffer;
	this->maxLength=maxLength;
}

void reader::fill() {
	this->in.getline((char*)this->buffer,this->maxLength,0);
	this->length=this->in.gcount();
	this->startPos=0;
	this->endPos=this->length-1;
}

template <typename type> void reader::readln(type *data) {
	this->in>>(*data);
	this->in.ignore(1,'\n');
}

template <typename type> bool reader::bufread(type *number,char dir) {
	type temp;
	switch(dir) {
		case 'f': // ��������� � ������ ������
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
			return true;
		case 'b': // ��������� � ����� ������
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
			return true;
	}
}

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
				return searchAsc(value,first,--i);
			else
				return searchAsc(value,++i,last);
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
				return searchDesc(value,first,--i);
			else
				return searchDesc(value,++i,last);
		}
		return (this->data[first]!=value)?-1:first;
}

int main() {
	int n,m,*teacher,cur,count=0;
	char *data;
	reader *r;
	sorter<int> *s;
	r=new reader(cin,0,0);
	r->readln<int>(&n);
	teacher=new int[n];
	for(int i=0;i<n;i++)
		r->readln<int>(teacher+i);
	s=new sorter<int>(teacher,n);
	r->readln<int>(&m);
	data=new char[m*11];
	r->reinit(data,m*11);
	r->fill();
	for(int i=0;i<m;i++) {
		r->bufread<int>(&cur,'f');
		if(s->search(cur,'a')!=-1)
			count++;
	}
	cout<<count;
}