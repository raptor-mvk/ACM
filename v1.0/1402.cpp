#include <iostream>
#include <iomanip>

using namespace std;

class huge {
private:
	static const int FOUNDATION=10000;
	static const int MAX_LENGTH=500;

	int *number; // число
	int length; // текущая длина числа

	void shift(int count); // сдвиг на count разрядов влево

	// умножение на "цифру" и сдвиг на shift разрядов влево
	void mul(int number,int shift); 

	int &operator[](int index) {
		return this->number[index];
	}	
public:
	static const int WIDTH=4;

	huge(int number);
	huge(const huge &number);
	huge();
	huge &operator=(const huge &number);
	huge &operator=(const int &number);
	huge &operator+=(const int &right);
	huge &operator+=(const huge &right);
	huge &operator*=(const int &right);
	huge &operator*=(const huge &right);
	friend ostream &operator<<(ostream &stream, huge const &number);
	friend huge operator+(const huge &left, const int &right);
	friend huge operator+(const huge &left, const huge &right);
	friend huge operator*(const huge &left, const int &right);
	friend huge operator*(const huge &left, const huge &right);

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

class calculator {
private:
	array<int> primes; // массив с простыми числами
	int primesCount; // количество вычисленных простых чисел
	
public:
	calculator();
	int getPrime(int n); // получение n-го простого числа
	huge getA(int n,int k); // получение числа размещений из n по k
	huge getP(int n); // получение числа перестановок из n
};

calculator::calculator() {
	this->primes[0]=2;
	this->primes[1]=3;
	this->primesCount=2;
}

int calculator::getPrime(int n) {
	int cur;
	bool isPrime;
	if (this->primesCount>n)
		return this->primes[n];
	cur=this->primes[this->primesCount-1]+2;
	while(this->primesCount<=n) {
		isPrime=true;
		for(int i=1;i<this->primesCount;i++) {
			if (this->primes[i]*this->primes[i]>cur)
				break;
			if(!(cur%this->primes[i])) {
				isPrime=false;
				break;
			}
		}
		if(isPrime)
			this->primes.push(cur);
		cur+=2;
	}
	return this->primes[n];
}

huge calculator::getA(int n,int k) {
	huge temp(1);
	for(int i=n-k+1;i<=n;i++)
		temp*=i;
	return temp;
}

huge calculator::getP(int n) {
	huge temp(1);
	for(int i=2;i<=n;i++)
		temp*=i;
	return temp;
}

int main() {
	int n;
	huge count;
	calculator c;
	cin>>n;
	if(n==1)
		cout<<0;
	else {
		for(int i=2;i<n;i++)
			count+=c.getA(n,i);
		count+=c.getP(n);
		cout<<count;
	}
}
