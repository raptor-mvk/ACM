#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class huge {
private:
	int *number; // число
	int length; // текуща€ длина числа

	void shift(int count); // сдвиг на count разр€дов влево

	// умножение на "цифру" и сдвиг на shift разр€дов влево
	void mul(int number,int shift); 

	int &operator[](int index) {
		return this->number[index];
	}	
public:
	static const int FOUNDATION=10000;
	static const int MAX_LENGTH=500;
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

template <class type> class array;
template <class type> ostream &operator<<(ostream &stream,
	const array<type> &arr);

template <class type> class array {
private:
	type *data; // данные
	int allocated; // объем выделенной пам€ти
	int length; // текуща€ длина массива

	void expand(); // расширение массива на одну страницу
public:
	static const int PAGE_SIZE=1024;
	static char delimiter; // разделитель при печати

	array();
	array(const array<type> &arr);
	array(int length);
	void push(type item); // добавление элемента в конец массива
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
	this->data=new type[arr.length];
	this->allocated=arr.length;
	this->length=arr.length;
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

template <class type> ostream &operator<<(ostream &stream,
	const array<type> &arr) {
	for(int i=0;i<arr.length;i++)
		stream<<arr[i]<<array<int>::delimiter;
	return stream;
}

const double EPS=0.000000001; // точность сравнений

class calculator {
private:
	array<int> primes; // массив с простыми числами
	int primesCount; // количество вычисленных простых чисел
	
	// поиск решени€ уравнени€ func=0 на отрезке [start,finish] дихотомией
	// дл€ функций, положительных справа и отрицательных слева
	double solveAsc(double(*func)(double),double start,double finish);

	// поиск решени€ уравнени€ func=0 на отрезке [start,finish] дихотомией
	// дл€ функций, положительных слева и отрицательных справа
	double solveDesc(double(*func)(double),double start,double finish);
public:
	calculator();
	int getPrime(int n); // получение n-го простого числа
	huge getA(int n,int k); // получение числа размещений из n по k
	huge getP(int n); // получение числа перестановок из n
	int gcd(int a,int b); // вычисление Ќќƒ
	int lgm(int a,int b); // вычисление Ќќ 
	
	// быстрое возведение x в степень n по модулю m
	int fastPowerMod(int x,int n,int m);

	// поиск решени€ уравнени€ func=0 на отрезке [start,finish] дихотомией
	double solve(double(*func)(double),double start,double finish);
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

double calculator::solveAsc(double(*func)(double),double start,double finish) {
	double cur=(start+finish)/2.0;
	if(abs(start-finish)<EPS)
		return (abs(func(start))<abs(func(finish)))?start:finish;
	if(abs(func(cur))<EPS)
		return cur;
	if(func(cur)>EPS)
		return this->solveAsc(func,start,cur);
	else
		return this->solveAsc(func,cur,finish);
}

double calculator::solveDesc(double(*func)(double),double start,
	double finish) {
		double cur=(start+finish)/2.0;
		if(abs(start-finish)<EPS)
			return (abs(func(start))<abs(func(finish)))?start:finish;
		if(abs(func(cur))<EPS)
			return cur;
		if(func(cur)<-EPS)
			return this->solveDesc(func,start,cur);
		else
			return this->solveDesc(func,cur,finish);
}

double calculator::solve(double(*func)(double),double start,double finish) {
	if(abs(func(start))<EPS)
		return start;
	if(abs(func(finish))<EPS)
		return finish;
	if(func(start)>EPS)
		return this->solveDesc(func,start,finish);
	if(func(start)<-EPS)
		return this->solveAsc(func,start,finish);
}

int calculator::gcd(int a,int b) {
	int c;
	if(b>a) {
		c=a;
		a=b;
		b=c;
	}
	while(a%b) {
		c=a%b;
		a=b;
		b=c;
	}
	return b;
}

int calculator::lgm(int a,int b) {
	int c,t;
	t=a*b;
	if(b>a) {
		c=a;
		a=b;
		b=c;
	}
	while(a%b) {
		c=a%b;
		a=b;
		b=c;
	}
	return t/b;
}

int calculator::fastPowerMod(int x,int n,int m) {
  int result=1;
  while(n) {
    if(n&1) {
      result*=x;
      result=result%m;
    }
    x*=x;
    x=x%m;
    n>>=1;
  }
  return result;
}

int main() {
    int k,e,n,c,p,q;
    calculator cl;
    cin>>k;
    for(int i=0;i<k;i++) {
			cin>>e>>n>>c;
      p=3;
      while(n%p)
				p+=2;
      q=n/p;
      p=(p-1)*(q-1);
      for(q=1;e*q%p!=1;q++);
      	cout<<cl.fastPowerMod(c,q,n)<<'\n';
    }
}
