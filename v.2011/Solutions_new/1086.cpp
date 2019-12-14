#include <iostream>

using namespace std;

class intArray {
private:
	static const int PAGE_SIZE=1000;
	static const int MAX_PAGES=4000;
	
	int **pages; // ссылки на страницы памяти
	int allocated; // текущее количество выделенных страниц

public:
	intArray();
	~intArray();
	int &operator[](int index);
};

intArray::intArray() {
	this->pages=new int*[intArray::MAX_PAGES];
	this->allocated=0;
}

intArray::~intArray() {
	for(int i=0;i<allocated;i++)
		delete [] pages[i];
	delete [] pages;
}

int &intArray::operator[](int index) {
	while(allocated*PAGE_SIZE<=index) {
		pages[allocated]=new int[PAGE_SIZE];
		memset(pages[allocated++],0,PAGE_SIZE*sizeof(int));
	}
	return pages[index/PAGE_SIZE][index%PAGE_SIZE];
}

class calculator {
private:
	intArray primes; // массив с простыми числами
	int primesCount; // количество вычисленных простых чисел
	
public:
	calculator();
	int getPrime(int n);
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
			this->primes[this->primesCount++]=cur;
		cur+=2;
	}
	return this->primes[n];
}

int main() {
	int k,n;
	calculator c;
	cin>>k;
	for(int i=0;i<k;i++) {
		cin>>n;
		cout<<c.getPrime(n-1)<<'\n';
	}
}
