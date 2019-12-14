#include <iostream>

template <class type> class array {
private:
	static const int PAGE_SIZE=1000;
	static const int MAX_PAGES=4000;
	
	type **pages; // ссылки на страницы памяти
	int allocated; // текущее количество выделенных страниц

public:
	array();
	~array();
	type &operator[](int index);
};

template <class type> array<type>::array()
{
	this->pages=new type*[array::MAX_PAGES];
	this->allocated=0;
}

template <class type> array<type>::~array()
{
	for(int i=0;i<allocated;i++)
		delete [] pages[i];
	delete [] pages;
}

template <class type> type &array<type>::operator[](int index) {
	while(allocated*PAGE_SIZE<=index) {
		pages[allocated]=new type[PAGE_SIZE];
		memset(pages[allocated++],0,PAGE_SIZE*sizeof(type));
	}
	return pages[index/PAGE_SIZE][index%PAGE_SIZE];
}

using namespace std;

int main() {
	array<long long> stones;
	long long x1,x2,x3,cur,tmp;
	int len=3,count;
	cin>>x1>>x2>>x3;
	if((x1==x2)||(x1==x3)||(x2==x3))
		cout<<1;
	else {
		if(x1>x2)	{
			if(x1>x3)	{
				if(x2>x3) {
					stones[0]=x1;
					stones[1]=x2;
					stones[2]=x3;
				}
				else {
					stones[0]=x1;
					stones[1]=x3;
					stones[2]=x2;
				}
			}
			else {
				stones[0]=x3;
				stones[1]=x1;
				stones[2]=x2;
			}
		}
		else {
			if(x3>x1) {
				if(x2>x3) {
					stones[0]=x2;
					stones[1]=x3;
					stones[2]=x1;
				}
				else {
					stones[0]=x3;
					stones[1]=x2;
					stones[2]=x1;
				}
			}
			else {
				stones[0]=x2;
				stones[1]=x1;
				stones[2]=x3;
			}
		}
		if(stones[0]-stones[1]>stones[1]-stones[2])
			cur=stones[1]-stones[2];
		else
			cur=stones[0]-stones[1];
		count=1;
		while(cur) {
			stones[len++]=cur;
			for(int i=len-1;i>1;i--)
				if(stones[i]>stones[i-1])	{
					tmp=stones[i];
					stones[i]=stones[i-1];
					stones[i-1]=tmp;
				}				
				else {
					if(i==len-1) {
						if(stones[i-1]-stones[i]<cur)
							cur=stones[i-1]-stones[i];
					}
					else {
						if(stones[i-1]-stones[i]<cur)
							cur=stones[i-1]-stones[i];
						if(stones[i]-stones[i+1]<cur)
							cur=stones[i]-stones[i+1];
					}
					break;
				}
			count++;
		}
		cout<<count;
	}
}
