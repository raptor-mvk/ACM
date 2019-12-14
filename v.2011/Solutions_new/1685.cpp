#include <iostream>

using namespace std;


class fstring {
private:
	static const int MAX_LENGTH=20001; // максимальная длина строки
	
public:
	static char delimiter; // разделитель
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
	bool isPalindrom(); // true, если строка является палиндромом

	// возвращает подстроку [start,start+length-1]
	fstring substrl(int start,int length);

	// возвращает подстроку [start,finish]
	fstring substrf(int start,int finish);

	// возвращает подстроку [start,end], где end - конец строки
	fstring substr(int start);

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

fstring::fstring() {
	this->data=new char[fstring::MAX_LENGTH];
	this->length=0;
}

fstring::fstring(char *data, int length) {
	this->data=new char[fstring::MAX_LENGTH];
	memcpy(this->data,data,length);
	this->length=length;
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

bool fstring::isPalindrom() {
	int len=this->length/2;
	for(int i=0;i<len;i++)
		if(this->data[i]!=this->data[this->length-i-1])
			return false;
	return true;
}

fstring fstring::substrl(int start,int length) {
	if(start+length<this->length)
		return fstring(this->data+start,length);
	else
		return this->substr(start);
}

fstring fstring::substrf(int start,int finish) {
	if(finish<this->length)
		return fstring(this->data+start,finish-start+1);
	else
		return this->substr(start);
}

fstring fstring::substr(int start) {
	if(start<this->length)
		return fstring(this->data+start,this->length-start);
	else
		return fstring();
}

fstring operator+(const fstring &left,const fstring &right) {
	fstring result(left);
	result.length=left.length+right.length;
	memcpy(result.data+left.length,right.data,right.length);
	return result;
}

fstring &fstring::operator+=(const fstring &right) {
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

void restore(fstring str,fstring *result) {
	int len=str.length;
	if(len!=0)
		if(len==1)
			(*result)+=str[0];
		else {
			restore(str.substrl(1,(len+1)/2-1),result);
			(*result)+=str[0];
			restore(str.substr((len+1)/2),result);
		}
}

int main() {
	fstring str,result;
	cin>>str;
	restore(str,&result);
	cout<<result;
}
