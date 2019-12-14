#include <iostream>
#include <iomanip>

using namespace std;

class huge {
private:
	static const int FOUNDATION=10000;
	static const int MAX_LENGTH=50;

	int *number;
	int length;

	void shift(int count);
	void mul(int number,int shift);

	int &operator[](int index) {
		return this->number[index];
	}	
public:
	static const int WIDTH=4;

	huge(int number);
	huge(const huge &number);
	huge();
	~huge();
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

	int operator[](int index) const {
		return this->number[index];
	}
	
	int getLength() const {
		return this->length;
	}
};

huge::~huge() {
	delete [] this->number;
}

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
	this->length=number.getLength();
	this->number=new int[huge::MAX_LENGTH];
	memset(this->number,0,huge::MAX_LENGTH*sizeof(int));
	memcpy(this->number,number.number,number.getLength()*sizeof(int));
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

int main() {
	int n,k;
	huge prev,cur,next;
	cin>>n>>k;
	prev=1;
	cur=k-1;
	for(int i=2;i<=n;i++) {
		next=(prev+cur)*(k-1);
		prev=cur;
		cur=next;
	}	
	cout<<next;
}
