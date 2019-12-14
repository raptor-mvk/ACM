#include <iostream>

using namespace std;

template <class type> class array {
private:
	static const int PAGE_SIZE=100;
	
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

int main() {
	array<int> *children,queue;
	int n,cur,*parents,start=0;
	cin>>n;
	children=new array<int>[n];
	parents=new int[n];
	memset(parents,0,n*sizeof(int));
	for(int i=0;i<n;i++) {
		cin>>cur;
		while(cur--) {
			children[i].push(cur);
			parents[cur]++;
			cin>>cur;
		}
	}
	for(int i=0;i<n;i++)
		if(!parents[i])
			queue.push(i);
	while(start<queue.getLength()) {
		cout<<(queue[start]+1)<<' ';
		for(int i=0;i<children[queue[start]].getLength();i++)
			if(!(--parents[children[queue[start]][i]]))
				queue.push(children[queue[start]][i]);
		start++;
	}
}