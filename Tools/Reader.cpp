#include "Reader.h"

using namespace std;

template <class type> char array<type>::delimiter=' ';

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

fstring::fstring(char symbol, int length) {
	this->data=new char[fstring::MAX_LENGTH];
	if(length)
		memset(this->data,symbol,length);
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

void reader::ignore(int count,char dir) {
	switch(dir) {
		case 'f':
			this->startPos+=count;
			return;
		case 'b':
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
			case 'f':
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
			case 'b':
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

bool isEndl(char symbol) {
	return symbol=='\n';
}
