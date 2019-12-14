#include <iostream>

using namespace std;

class reader {
private:
	const char *buffer; // буфер для чтения данных
	int maxLength; // размер буфера
	int length; // текущий размер данных в буфере
	int startPos; // текущая позиция с начала буфера
	int endPos; // текущая позиция с конца буфера
	istream &in; // входной поток для чтения данных
public:
	reader(istream &in,const char* buffer,int maxLength);
	void reinit(const char* buffer, int maxLength); // задание нового буфера
	void fill(); // заполнение буфера данными
	// считывание переменной вместе с концом строки
	template <typename type> void readln(type *data);
	// считывание целого числа из буфера в направлении dir
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
		case 'f': // считывать с начала буфера
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
		case 'b': // считывать с конца буфера
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
	int n,k,cur=-1,count=0;
	char *data;
	reader *r;
	r=new reader(cin,0,0);
	r->readln(&n);
	data=new char[n*11];
	r->reinit(data,n*11);
	r->fill();
	for(int i=0;i<n;i++) {
		r->bufread<int>(&k,'f');
		if(count) {
			if(k==cur)
				count++;
			else
				count--;
		}
		else {
			cur=k;
			count=1;
		}
	}
	cout<<cur;
}