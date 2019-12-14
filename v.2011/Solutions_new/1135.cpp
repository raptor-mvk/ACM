#include <iostream>

using namespace std;

const int MAX_DATA_SIZE=32000;

template <class type> class array;
template <class type> ostream &operator<<(ostream &stream,
	const array<type> &arr);

template <class type> class array {
private:
	type *data; // данные
	int allocated; // объем выделенной памяти
	int length; // текущая длина массива

	void expand(); // расширение массива на одну страницу
public:
	static const int PAGE_SIZE=1024;
	static char delimiter; // разделитель при печати

	array();
	array(const array<type> &arr);
	array(int length);
	void push(type item); // добавление элемента в конец массива
	array<type> &operator=(const array<type> &arr);
	friend ostream &operator<< <>(ostream &stream,const array<type> &arr);

	~array() {
		delete [] data;
	}

	type &operator[](int index) {
		return data[index];
	}

	type &operator[](int index) const {
		return data[index];
	}

	int getLength() {
		return this->length;
	}
};

template <class type> char array<type>::delimiter=' ';

template <class type> array<type>::array() {
	this->data=new type[PAGE_SIZE];
	this->allocated=this->PAGE_SIZE;
	this->length=0;
}

template <class type> array<type>::array(const array<type> &arr) {
	this->data=new type[arr.allocated];
	this->allocated=arr.allocated;
	this->length=arr.length;
	if(arr.length)
		memcpy(this->data,arr.data,arr.length*sizeof(type));
}

template <class type> array<type>::array(int length) {
	this->data=new type[length];
	this->allocated=length;
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

template <class type> array<type> &array<type>::operator=
	(const array<type> &arr) {
		delete [] this->data;
		this->data=new type[arr.allocated];
		this->allocated=arr.allocated;
		this->length=arr.length;
		if(arr.length)
			memcpy(this->data,arr.data,arr.length*sizeof(type));
		return *this;
}

template <class type> ostream &operator<<(ostream &stream,
	const array<type> &arr) {
	for(int i=0;i<arr.length;i++)
		stream<<arr[i]<<array<int>::delimiter;
	return stream;
}

class fstring {
public:
	static const int MAX_LENGTH=256; // максимальная длина строки
	static char delimiter; // разделитель
	static char nonSymbol; // символ, который не встречается в строках
	char *data; // содержимое строки
	int length; // длина строки
	fstring();
	fstring(char *data,int length);
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
	friend fstring operator+(const fstring &left,const fstring &right);
	fstring &operator+=(const fstring &right);
	friend fstring operator+(const fstring &left,const char &right);
	fstring &operator+=(const char &right);
	fstring reverse(); // возвращает перевернутую строку

	// возвращает строку, обработанную строку функцией processFunc
	fstring process(char(*processFunc)(char));

	// возвращает префикс-функцию подстроки [start,end], где end - конец строки
	void prefixFunc(int *pfvalues,int start); 

	// возвращает все позиции вхождений строки substr
	array<int> find(fstring substr);

	// возвращает подстроку [start,start+length-1]
	fstring substrl(int start,int length) {
		return fstring(this->data+start,length);
	}

	// возвращает подстроку [start,finish]
	fstring substrf(int start,int finish) {
		return fstring(this->data+start,finish-start+1);
	}

	// возвращает подстроку [start,end], где end - конец строки
	fstring substr(int start) {
		return fstring(this->data+start,this->length-start);
	}
	
	// уменьшает длину строки на count
	void trimEnd(int count) {
		this->length-=count;
	}

	~fstring() {
		delete [] data;
	}

	char &operator[](int index) {
		return data[index];
	}

	char operator[](int index) const {
		return data[index];
	}

	int getLength() {
		return this->length;
	}
};

char fstring::delimiter='\n';
char fstring::nonSymbol='@';

fstring::fstring() {
	this->data=new char[fstring::MAX_LENGTH];
	this->length=0;
}

fstring::fstring(char *data, int length) {
	this->data=new char[fstring::MAX_LENGTH];
	if(length)
		memcpy(this->data,data,length);
	this->length=length;
}

fstring::fstring(const fstring &str) {
	this->data=new char[fstring::MAX_LENGTH];
	this->length=str.length;
	if(str.length)
		memcpy(this->data,str.data,str.length);
}

fstring &fstring::operator=(const fstring &str) {
	this->length=str.length;
	if(str.length)
		memcpy(this->data,str.data,str.length);
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

ostream &operator<<(ostream &stream,const fstring &str) {
	if(str.length)
		stream.write(str.data,str.length);
	return stream;
}

istream &operator>>(istream &stream,fstring &str) {
	stream.getline(str.data,fstring::MAX_LENGTH,fstring::delimiter);
	if(stream.eof())
		str.length=stream.gcount();
	else
		str.length=stream.gcount()-1;
	return stream;
}

fstring fstring::reverse() {
	fstring result=*this;
	int len=this->length/2;
	char temp;
	for(int i=0;i<len;i++) {
		temp=result[i];
		result[i]=result[this->length-i-1];
		result[this->length-i-1]=temp;
	}
	return result;
}

fstring operator+(const fstring &left,const fstring &right) {
	fstring result(left);
	result.length=left.length+right.length;
	if(right.length)
		memcpy(result.data+left.length,right.data,right.length);
	return result;
}

fstring &fstring::operator+=(const fstring &right) {
	if(right.length)
		memcpy(this->data+this->length,right.data,right.length);
	this->length+=right.length;
	return *this;
}

fstring operator+(const fstring &left,const char &right) {
	fstring result(left);
	result.data[result.length++]=right;
	return result;
}

fstring &fstring::operator+=(const char &right) {
	this->data[this->length++]=right;
	return *this;
}

fstring fstring::process(char(*processFunc)(char)) {
	fstring result;
	result.length=this->length;
	for(int i=0;i<this->length;i++)
		result[i]=processFunc(this->data[i]);
	return result;
}

void fstring::prefixFunc(int *pfvalues,int start) {
	int cur;
	pfvalues[0]=0;
	for(int i=1;i<this->length-start;i++) {
		cur=pfvalues[i-1];
		while(this->data[i+start]!=this->data[cur+start]) {
			if(cur)
				cur=pfvalues[cur-1];
			else {
				cur=-1;
				break;
			}
		}
		if(cur==-1)
			pfvalues[i]=0;
		else	
			pfvalues[i]=cur+1;
	}
}

array<int> fstring::find(fstring substr) {
	fstring temp(substr);
	array<int> result;
	int *pfunc;
	temp+=fstring::nonSymbol;
	temp+=*this;
	pfunc=new int[temp.length];
	temp.prefixFunc(pfunc,0);
	for(int i=substr.length+1;i<temp.length;i++)
		if(pfunc[i]==substr.length)
			result.push(i-2*substr.length);
	return result;
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

	// игнорирование count символов в направлении dir
	void ignore(int count,char dir);

	// считывание целого числа из буфера в направлении dir (вместе со стандартными
	// разделителями, если readln = true)
	template <typename type> bool getNext(type *number,char dir,bool readln);

	// считывание слова в направлении dir(вместе с разделителями, если
	// readln = true), функция checkFunc должна возвращать true для разделителя
	bool getNext(fstring *str,bool(*checkFunc)(char symbol),char dir,bool readln);

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

template <typename type> bool reader::getNext(type *number,char dir,
	bool readln) {
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
				if(readln)
					while(((this->buffer[this->startPos]==' ')||
						(this->buffer[this->startPos]=='\t')||
						(this->buffer[this->startPos]=='\n'))&&(this->startPos<=this->endPos))
							this->startPos++;
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
				if(readln)
					while(((this->buffer[this->startPos]==' ')||
						(this->buffer[this->startPos]=='\t')||
						(this->buffer[this->startPos]=='\n'))&&(this->startPos<=this->endPos))
							this->endPos--;
				return true;
		}
}

void reader::ignore(int count,char dir) {
	switch(dir) {
		case 'f': // сдвиг начала данных
			this->startPos+=count;
			return;
		case 'b': // сдвиг конца данных
			this->endPos-=count;
			return;
	}
}

bool reader::getNext(fstring *str,bool(*checkFunc)(char symbol),char dir,
	bool readln) {
		int start,length=0;
		if(this->startPos>this->endPos)
				return false;
		switch (dir) {
			case 'f': // поиск с начала данных
				start=this->startPos;
				while(this->startPos<=this->endPos)
					if(checkFunc(this->buffer[this->startPos]))
						break;
					else {
						this->startPos++;
						length++;
					}
				if(readln)
					while(this->startPos<=this->endPos)
						if(!checkFunc(this->buffer[this->startPos]))
							break;
						else
							this->startPos++;
				*str=fstring((char*)this->buffer+start,length);
				return true;
			case 'b': // поиск с конца данных
				start=this->endPos;
				while(this->startPos<=this->endPos)
					if(checkFunc(this->buffer[this->endPos]))
						break;
					else {
						this->endPos--;
						length++;
					}
				if(readln)
					while(this->startPos<=this->endPos)
						if(!checkFunc(this->buffer[this->endPos]))
							break;
						else
							this->endPos--;
				*str=fstring((char*)this->buffer+start-length+1,length);
				return true;
		}
}

bool isSentenceEnd(char symbol) {
	return (symbol=='.')||(symbol=='?')||(symbol=='!');
}

bool isCapitalLetter(char symbol) {
	return (symbol>='A')&&(symbol<='Z');
}

char lowerCase(char symbol) {
	if((symbol>='A')&&(symbol<='Z'))
		return symbol+'a'-'A';
	else
		return symbol;
}

bool isPunctuationOrDelim(char symbol) {
	return (symbol==' ')||(symbol=='\t')||(symbol=='\n')||(symbol=='.')||
		(symbol==',')||(symbol=='-')||(symbol=='!')||(symbol=='?')||(symbol==':');
}

bool isLowercaseLetter(char symbol) {
	return (symbol>='a')&&(symbol<='z');
}

bool notLetter(char symbol) {
	return !((symbol>='a')&&(symbol<='z')||(symbol>='A')&&(symbol<='Z'));
}

bool notDigit(char symbol) {
	return !((symbol>='0')&&(symbol<='9'));
}

bool isDelim(char symbol) {
	return (symbol==' ')||(symbol=='\t')||(symbol=='\n');
}

int main() {
  int n,i=0,turns=0,left=0;
  char *data;
  fstring str;
  reader *r;
  data=new char[MAX_DATA_SIZE];
  r=new reader(cin,data,MAX_DATA_SIZE);
  r->fill();
  r->getNext<int>(&n,'f',true);
  while(r->getNext(&str,&isDelim,'f',true)) {
		for(int j=0;j<str.getLength();j++)
			if(str[j]=='<')
				turns+=i++-left++;
			else
				if(str[j]=='>')
					i++;
	}
  cout<<turns;
}
