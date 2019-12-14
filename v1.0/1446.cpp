#include <iostream>

using namespace std;

const int FACULTY_COUNT=4;
const int SLYTHERIN=0;
const int HUFFLEPUFF=1;
const int GRYFFINDOR=2;
const int RAVENCLAW=3;

template <class type> class array {
private:
	static const int PAGE_SIZE=1024;
	
	type *data; // данные
	int allocated; // объем выделенной памяти
	int length; // текущая длина массива

	void expand(); // расширение массива на одну страницу
public:
	array();
	void push(type item); // добавление элемента в конец массива

	~array() {
		delete [] data;
	}

	type &operator[](int index) {
		return data[index];
	}

	int getLength() {
		return this->length;
	}
};

template <class type> array<type>::array() {
	this->data=new type[PAGE_SIZE];
	this->allocated=this->PAGE_SIZE;
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

class fstring {
private:
	static const int MAX_LENGTH=201; // максимальная длина строки
	static char delimiter; // разделитель
	
public:
	char *data; // содержимое строки
	int length; // длина строки
	fstring();
	fstring(const fstring &str);
	fstring &operator=(const fstring &str);
	friend bool operator<(const fstring &left,const fstring &right);
	friend bool operator<=(const fstring &left,const fstring &right);
	friend bool operator>(const fstring &left,const fstring &right);
	friend bool operator>=(const fstring &left,const fstring &right);
	friend bool operator==(const fstring &left,const fstring &right);
	friend bool operator!=(const fstring &left,const fstring &right);
	friend ostream &operator<<(ostream &stream, const fstring &str);
	friend istream &operator>>(istream &stream, fstring &str);

	~fstring() {
		delete [] data;
	}

	static void setDelimiter(char delimiter) {
		fstring::delimiter=delimiter;
	}

	char &operator[](int index) {
		return data[index];
	}

	char &operator[](int index) const {
		return data[index];
	}

	int getLength() {
		return this->length;
	}
};

char fstring::delimiter;

fstring::fstring() {
	fstring::delimiter='\n';
	this->data=new char[fstring::MAX_LENGTH];
	this->length=0;
}

fstring::fstring(const fstring &str) {
	this->data=new char[fstring::MAX_LENGTH];
	this->length=str.length;
	memcpy(this->data,str.data,fstring::MAX_LENGTH);
}

fstring &fstring::operator=(const fstring &str) {
	this->length=str.length;
	memcpy(this->data,str.data,fstring::MAX_LENGTH);
	return *this;
}

bool operator<(const fstring &left,const fstring &right) {
	int len=(left.length>right.length)?right.length:left.length;
	for(int i=0;i<len;i++)
		if(left[i]<right[i])
			return true;
		else
			if(left[i]>right[i])
				return false;
	if(right.length<=left.length)
		return false;
	else
		return true;
}

bool operator<=(const fstring &left,const fstring &right) {
	int len=(left.length>right.length)?right.length:left.length;
	for(int i=0;i<len;i++)
		if(left[i]<right[i])
			return true;
		else
			if(left[i]>right[i])
				return false;
	if(right.length<left.length)
		return false;
	else
		return true;
}

bool operator>(const fstring &left,const fstring &right) {
	int len=(left.length>right.length)?right.length:left.length;
	for(int i=0;i<len;i++)
		if(left[i]<right[i])
			return false;
		else
			if(left[i]>right[i])
				return true;
	if(right.length<left.length)
		return true;
	else
		return false;
}

bool operator>=(const fstring &left,const fstring &right) {
	int len=(left.length>right.length)?right.length:left.length;
	for(int i=0;i<len;i++)
		if(left[i]<right[i])
			return false;
		else
			if(left[i]>right[i])
				return true;
	if(right.length<=left.length)
		return true;
	else
		return false;
}

bool operator==(const fstring &left,const fstring &right) {
	if(right.length!=left.length)
		return false;
	for(int i=0;i<left.length;i++)
		if(left[i]!=right[i])
			return false;
	return true;
}

bool operator!=(const fstring &left,const fstring &right) {
	if(right.length!=left.length)
		return true;
	for(int i=0;i<left.length;i++)
		if(left[i]!=right[i])
			return true;
	return false;
}

ostream &operator<<(ostream &stream, const fstring &str) {
	stream.write(str.data,str.length);
	return stream;
}

istream &operator>>(istream &stream, fstring &str) {
	stream.getline(str.data,fstring::MAX_LENGTH,fstring::delimiter);
	if(stream.eof())
		str.length=stream.gcount();
	else
		str.length=stream.gcount()-1;
	return stream;
}

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
	int n;
	array<fstring> faculties[FACULTY_COUNT];
	char used[FACULTY_COUNT];
	fstring faculty,name;
	reader r(cin,0,0);
	r.readln<int>(&n);
	memset(used,0,FACULTY_COUNT);
	for(int i=0;i<n;i++) {
		cin>>name;
		cin>>faculty;
		switch(faculty[0]) {
		case 'H':
			if(!used[HUFFLEPUFF]) {
				faculties[HUFFLEPUFF].push(faculty);			
				used[HUFFLEPUFF]=1;
			}
			faculties[HUFFLEPUFF].push(name);			
			break;
		case 'S':
			if(!used[SLYTHERIN]) {
				faculties[SLYTHERIN].push(faculty);			
				used[SLYTHERIN]=1;
			}
			faculties[SLYTHERIN].push(name);
			break;
		case 'G':
			if(!used[GRYFFINDOR]) {
				faculties[GRYFFINDOR].push(faculty);			
				used[GRYFFINDOR]=1;
			}
			faculties[GRYFFINDOR].push(name);
			break;
		case 'R':
			if(!used[RAVENCLAW]) {
				faculties[RAVENCLAW].push(faculty);			
				used[RAVENCLAW]=1;
			}
			faculties[RAVENCLAW].push(name);;
			break;
		}
	}
	for(int i=0;i<FACULTY_COUNT;i++) {
		cout<<faculties[i][0]<<":\n";
		for(int j=1;j<faculties[i].getLength();j++)
			cout<<faculties[i][j]<<"\n";
		cout<<"\n";
	}
}
