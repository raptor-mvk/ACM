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

int main() {
	int n,q,*data,k,l;
	char *str;
	reader r(cin,0,0);
	cin>>n;
	data=new int[n+1];
	data[0]=0;
	for(int i=0;i<n;i++) {
		cin>>data[i+1];
		if(i)
			data[i+1]+=data[i];
	}
	r.readln<int>(&q);
	str=new char[12*q];
	r.reinit(str,12*q);
	r.fill();
	for(int i=0;i<q;i++) {
		r.bufread<int>(&k,'f');
		r.bufread<int>(&l,'f');
		cout<<data[l]-data[k-1]<<'\n';
	}
}
