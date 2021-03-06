#include <iostream>
#include <iomanip>

using namespace std;

template <class type> class array;
template <class type> ostream &operator<<(ostream &stream,
	const array<type> &arr);

template <class type> class array {
private:
	type *data; // ������
	int allocated; // ����� ���������� ������
	int length; // ������� ����� �������

	void expand(); // ���������� ������� �� ���� ��������
public:
	static const int PAGE_SIZE=1024;
	static char delimiter; // ����������� ��� ������

	array();
	array(const array<type> &arr);
	array(int length);
	void push(type item); // ���������� �������� � ����� �������
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
	static const int MAX_LENGTH=2002; // ������������ ����� ������
	static char delimiter; // �����������
	static char nonSymbol; // ������, ������� �� ����������� � �������
	char *data; // ���������� ������
	int length; // ����� ������
	fstring();
	fstring(char *data,int length);
	fstring(char symbol,int length);
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
	fstring reverse(); // ���������� ������������ ������
	fstring trimEnd(int count); // ��������� ����� ������ �� count

	// ���������� ������, ������������ ������ �������� processFunc
	fstring process(char(*processFunc)(char));

	// ���������� �������-������� ��������� [start,end], ��� end - ����� ������
	void prefixFunc(int *pfvalues,int start); 

	// ���������� ��� ������� ��������� ������ substr
	array<int> find(fstring substr);

	// ���������� ��������� [start,start+length-1]
	fstring substrl(int start,int length) {
		return fstring(this->data+start,length);
	}

	// ���������� ��������� [start,finish]
	fstring substrf(int start,int finish) {
		return fstring(this->data+start,finish-start+1);
	}

	// ���������� ��������� [start,end], ��� end - ����� ������
	fstring substr(int start) {
		return fstring(this->data+start,this->length-start);
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

fstring fstring::trimEnd(int count)	{
	this->length-=count;
	return *this;
}

class huge {
	friend class fstring;
	
private:
	int *number; // �����
	int length; // ������� ����� �����

	void shift(int count); // ����� �� count �������� �����

	// ��������� �� "�����" � ����� �� shift �������� �����
	void mul(int number,int shift); 

	int &operator[](int index) {
		return this->number[index];
	}	
public:
	static const int FOUNDATION=10000;
	static const int MAX_LENGTH=500;
	static const int WIDTH=4;
	static const int DIGITS=10;

	huge(int number);
	huge(const huge &number);
	huge(const fstring &str);
	huge();
	huge &operator=(const huge &number);
	huge &operator=(const int &number);
	huge &operator+=(const int &right);
	huge &operator+=(const huge &right);
	huge &operator*=(const int &right);
	huge &operator*=(const huge &right);
	operator fstring() const;
	operator fstring();
	friend ostream &operator<<(ostream &stream, huge const &number);
	friend huge operator+(const huge &left, const int &right);
	friend huge operator+(const huge &left, const huge &right);
	friend huge operator*(const huge &left, const int &right);
	friend huge operator*(const huge &left, const huge &right);
	friend bool operator<(const huge &left,const huge &right);
	friend bool operator<=(const huge &left,const huge &right);
	friend bool operator>(const huge &left,const huge &right);
	friend bool operator>=(const huge &left,const huge &right);
	friend bool operator==(const huge &left,const huge &right);
	friend bool operator!=(const huge &left,const huge &right);

	~huge() {
		delete [] this->number;
	}

	int operator[](int index) const {
		return this->number[index];
	}
	
	int getLength() const {
		return this->length;
	}
};

huge::huge() {
	this->length=1;
	this->number=new int[huge::MAX_LENGTH];
	memset(this->number,0,huge::MAX_LENGTH*sizeof(int));
}

huge::huge(int number) {
	this->length=0;
	this->number=new int[huge::MAX_LENGTH];
	memset(this->number,0,huge::MAX_LENGTH*sizeof(int));
	while(number) {
		this->number[this->length++]=number%huge::FOUNDATION;
		number/=huge::FOUNDATION;
	}
}

huge::huge(const huge &number) {
	this->length=number.length;
	this->number=new int[huge::MAX_LENGTH];
	memset(this->number,0,huge::MAX_LENGTH*sizeof(int));
	memcpy(this->number,number.number,number.length*sizeof(int));
}

huge::huge(const fstring &str) {
	int tmp=0,mul=1;
	this->number=new int[huge::MAX_LENGTH];
	if(!str.length)
		this->length=1;
	else
		this->length=0;
	for(int i=str.length-1;i>=0;i--) {
		tmp+=(str[i]-'0')*mul;
		mul*=this->DIGITS;
		if(mul==this->FOUNDATION) {
			this->number[this->length++]=tmp;
			mul=1;
			tmp=0;
		}
	}
	if(tmp||!this->length)
		this->number[this->length++]=tmp;
}

void huge::shift(int count) {
	if(count) {
		memmove(this->number+count,this->number,this->length*sizeof(int));
		memset(this->number,0,count*sizeof(int));
		this->length+=count;
	}
}

void huge::mul(int number,int shift) {
	int carry=0;
	for(int i=0;i<this->length;i++) {
		carry+=this->number[i]*number;
		this->number[i]=carry%huge::FOUNDATION;
		carry/=huge::FOUNDATION;
	}
	if(carry)
		this->number[this->length++]=carry;
	this->shift(shift);
}

huge::operator fstring() const {
	fstring res;
	int tmp,mul;
	bool started=false;
	tmp=this->number[this->length-1];
	mul=this->FOUNDATION/this->DIGITS;
	while(mul) {
		if(tmp/mul)
			started=true;
		if(started)
			res[res.length++]=tmp/mul+'0';
		tmp=tmp%mul;
		mul/=this->DIGITS;
	}
	for(int i=this->length-2;i>=0;i--) {
		tmp=this->number[i];
		mul=this->FOUNDATION/this->DIGITS;
		for(int j=0;j<this->WIDTH;j++) {
			res[res.length++]=tmp/mul+'0';
			tmp=tmp%mul;
			mul/=this->DIGITS;
		}
	}
	return res;
}

huge::operator fstring() {
	fstring res;
	int tmp,mul;
	bool started=false;
	tmp=this->number[this->length-1];
	mul=this->FOUNDATION/this->DIGITS;
	while(mul) {
		if(tmp/mul)
			started=true;
		if(started)
			res[res.length++]=tmp/mul+'0';
		tmp=tmp%mul;
		mul/=this->DIGITS;
	}
	for(int i=this->length-2;i>=0;i--) {
		tmp=this->number[i];
		mul=this->FOUNDATION/this->DIGITS;
		for(int j=0;j<this->WIDTH;j++) {
			res[res.length++]=tmp/mul+'0';
			tmp=tmp%mul;
			mul/=this->DIGITS;
		}
	}
	return res;
}

huge &huge::operator=(const huge &number) {
	delete [] this->number;
	this->length=number.getLength();
	this->number=new int[huge::MAX_LENGTH];
	memcpy(this->number,number.number,number.getLength()*sizeof(int));
	return *this;
}

huge &huge::operator=(const int &number) {
	int temp=number;
	delete [] this->number;
	this->length=0;
	this->number=new int[huge::MAX_LENGTH];
	while(temp) {
		this->number[this->length++]=temp%huge::FOUNDATION;
		temp/=huge::FOUNDATION;
	}
	return *this;
}

ostream &operator<<(ostream &stream, huge const &number) {
	stream<<number[number.length-1];
	for(int i=number.length-2;i>=0;i--)
		stream<<setw(huge::WIDTH)<<setfill('0')<<number[i];
	return stream;
}

huge operator+(const huge &left, const int &right) {
	huge result(left);
	int temp=right,carry=0,length=0;
	while(temp) {
		carry+=result[length]+(temp%huge::FOUNDATION);
		result[length++]=carry%huge::FOUNDATION;
		carry/=huge::FOUNDATION;
		temp/=huge::FOUNDATION;
	}
	while(carry) {
		carry+=result[length];
		result[length++]=carry%huge::FOUNDATION;
		carry/=huge::FOUNDATION;
	}
	if(length>result.length)
		result.length=length;
	return result;
}

huge operator+(const huge &left, const huge &right) {
	huge result(left);
	int carry=0,length=right.length;
	for(int i=0;i<right.length;i++) {
		carry+=result[i]+right[i];
		result[i]=carry%huge::FOUNDATION;
		carry/=huge::FOUNDATION;
	}
	while(carry) {
		carry+=result[length];
		result[length++]=carry%huge::FOUNDATION;
		carry/=huge::FOUNDATION;
	}
	if(length>result.length)
		result.length=length;
	return result;
}

huge operator*(const huge &left, const int &right) {
	huge result,temp;
	int temp2=right,shift=0;
	while(temp2) {
		temp=left;
		temp.mul(temp2%huge::FOUNDATION,shift++);
		result+=temp;
		temp2/=huge::FOUNDATION;
	}
	return result;
}

huge operator*(const huge &left, const huge &right) {
	huge result,temp;
	int shift=0;
	for(int i=0;i<right.length;i++) {
		temp=left;
		temp.mul(right[i],i);
		result+=temp;
	}
	return result;
}

huge &huge::operator+=(const int &right) {
	int temp=right,carry=0,length=0;
	while(temp) {
		carry+=this->number[length]+(temp%huge::FOUNDATION);
		this->number[length++]=carry%huge::FOUNDATION;
		carry/=huge::FOUNDATION;
		temp/=huge::FOUNDATION;
	}
	while(carry) {
		carry+=this->number[length];
		this->number[length++]=carry%huge::FOUNDATION;
		carry/=huge::FOUNDATION;
	}
	if(length>this->length)
		this->length=length;
	return *this;
}

huge &huge::operator+=(const huge &right) {
	int carry=0,length=right.length;
	for(int i=0;i<right.length;i++) {
		carry+=this->number[i]+right[i];
		this->number[i]=carry%huge::FOUNDATION;
		carry/=huge::FOUNDATION;
	}
	while(carry) {
		carry+=this->number[length];
		this->number[length++]=carry%huge::FOUNDATION;
		carry/=huge::FOUNDATION;
	}
	if(length>this->length)
		this->length=length;
	return *this;
}

huge &huge::operator*=(const int &right) {
	huge result,temp;
	int temp2=right,shift=0;
	while(temp2) {
		temp=*this;
		temp.mul(temp2%huge::FOUNDATION,shift++);
		result+=temp;
		temp2/=huge::FOUNDATION;
	}
	*this=result;
	return *this;
}

huge &huge::operator*=(const huge &right) {
	huge result,temp;
	int shift=0;
	for(int i=0;i<right.length;i++) {
		temp=*this;
		temp.mul(right[i],i);
		result+=temp;
	}
	*this=result;
	return *this;
}

bool operator<(const huge &left,const huge &right) {
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

bool operator<=(const huge &left,const huge &right) {
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

bool operator>(const huge &left,const huge &right) {
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

bool operator>=(const huge &left,const huge &right) {
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

bool operator==(const huge &left,const huge &right) {
	if(right.length!=left.length)
		return false;
	for(int i=0;i<left.length;i++)
		if(left[i]!=right[i])
			return false;
	return true;
}

bool operator!=(const huge &left,const huge &right) {
	if(right.length!=left.length)
		return true;
	for(int i=0;i<left.length;i++)
		if(left[i]!=right[i])
			return true;
	return false;
}
