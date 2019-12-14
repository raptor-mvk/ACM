#include <iostream>

using namespace std;

const int PARTNERS_COUNT=3;
const int ISENBAEV_LENGTH=8;
const char ISENBAEV[ISENBAEV_LENGTH+1]="Isenbaev";

template <class type> class array {
private:
	static const int PAGE_SIZE=100;
	
	type *data; // данные
	int allocated; // объем выделенной пам€ти
	int length; // текуща€ длина массива

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

template <class keytype,class valuetype> class keypair {
public:
	keytype key; // ключ
	valuetype value; // значение
	
	keypair() {}
	keypair(keytype key,valuetype value);
	void reinit(keytype key,valuetype value); // реинициализаци€

	bool operator<(const keypair &right) {
		return this->key<right.key;
	}

	bool operator<=(const keypair &right) {
		return this->key<=right.key;
	}

	bool operator>(const keypair &right) {
		return this->key>right.key;
	}

	bool operator>=(const keypair &right) {
		return this->key>=right.key;
	}

	bool operator==(const keypair &right) {
		return this->key==right.key;
	}

	bool operator!=(const keypair &right) {
		return this->key!=right.key;
	}
};

template <class keytype,class valuetype> keypair<keytype,valuetype>::
	keypair(keytype key,valuetype value) {
		this->key=key;
		this->value=value;
}

template <class keytype,class valuetype> void keypair<keytype,valuetype>::
	reinit(keytype key,valuetype value) {
		this->key=key;
		this->value=value;
}

template <class keytype,class valuetype> class hashtable {
private:
	keypair<keytype,valuetype> *data; // данные
	char *used; // флаги использовани€ €чейки
	int(*hashFunc)(keytype); // хэш-функци€

public:
	static const int SIZE=10093;
	
	hashtable(int(*hashFunc)(keytype));
	~hashtable();
	void push(keypair<keytype,valuetype> item); // добавление элемента в таблицу
	bool get(keypair<keytype,valuetype> *item); // получение элемента из таблицы
};

template <class keytype,class valuetype> hashtable<keytype,valuetype>::
	hashtable(int(*hashFunc)(keytype)) {
		this->data=new keypair<keytype,valuetype>[SIZE];
		this->used=new char[SIZE];
		memset(used,0,SIZE);
		this->hashFunc=hashFunc;
}

template <class keytype,class valuetype> hashtable<keytype,valuetype>::
	~hashtable() {
		delete [] used;
		delete [] data;
}

template <class keytype,class valuetype> void hashtable<keytype,valuetype>::
	push(keypair<keytype,valuetype> item) {
		int index=hashFunc(item.key);
		while(used[index])
			if(index<SIZE)
				index++;
			else
				index=0;
		data[index]=item;
		used[index]=1;
}

template <class keytype,class valuetype> bool hashtable<keytype,valuetype>::
	get(keypair<keytype,valuetype> *item) {
		int index=hashFunc(item->key);
		while(used[index])
			if(data[index].key==item->key) {
				*item=data[index];
				return true;
			}
			else
				if(index<SIZE)
					index++;
				else
					index=0;
		return false;
}

class fstring {
private:
	static const int MAX_LENGTH=201; // максимальна€ длина строки
	
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

	~fstring() {
		delete [] data;
	}

	char &operator[](int index) {
		return data[index];
	}

	char &operator[](int index) const {
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

class reader {
private:
	const char *buffer; // буфер дл€ чтени€ данных
	int maxLength; // размер буфера
	int length; // текущий размер данных в буфере
	int startPos; // текуща€ позици€ с начала буфера
	int endPos; // текуща€ позици€ с конца буфера
	istream &in; // входной поток дл€ чтени€ данных
public:
	reader(istream &in,const char* buffer,int maxLength);
	void reinit(const char* buffer, int maxLength); // задание нового буфера
	void fill(); // заполнение буфера данными
	// считывание переменной вместе с концом строки
	template <typename type> void readln(type *data);
	// считывание целого числа из буфера в направлении dir
	template <typename type> bool bufread(type *number,char dir);
	
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

template <typename type> void reader::readln(type *data) {
	this->in>>(*data);
	this->in.ignore(1,'\n');
}

template <typename type> bool reader::bufread(type *number,char dir) {
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
			return true;
	}
}

template <class type> class sorter {
private:
	type *data; // сортируемые данные
	int size; // размер массива

	void sortQuickAsc(int low,int high); // "быстра€" сортировка по возрастанию
	void sortQuickDesc(int low,int high); // "быстра€" сортировка по убыванию
	void swap(int i,int j); // обмен местами i-го и j-го элемента
	bool compare(type i,type j); // сравнение i и j
public:
	sorter(type *data,int size);

	// сортировка алгоритмом algo в направлении dir
	void sort(char algo,char dir);
};

template <class type> void sorter<type>::swap(int i,int j) {
	type t;
	t=this->data[i];
	this->data[i]=this->data[j];
	this->data[j]=t;
}

template <class type> sorter<type>::sorter(type *data,int size) {
	this->data=data;
	this->size=size;
}

template <class type> void sorter<type>::sort(char algo,char dir) {
	switch(algo) {
		case 'q': // быстра€ сортировка
			switch(dir) {
				case 'a': // сортировка по возрастанию
					return this->sortQuickAsc(0,this->size-1);
				case 'd': // сортировка по убыванию
					return this->sortQuickDesc(0,this->size-1);
			}
	}
}

template <class type> void sorter<type>::sortQuickAsc(int low,int high) {
	int i=low,j=high;
	type x=this->data[(i+j)/2];
	while(i<j)	{
		while(this->data[i]<x)
			i++;
		while(x<this->data[j])
			j--;
		if(i<=j)
			this->swap(i++,j--);
	}
  if(low<j)
		this->sortQuickAsc(low,j);
	if(high>i)
		this->sortQuickAsc(i,high);
}

template <class type> void sorter<type>::sortQuickDesc(int low,int high) {
	int i=low,j=high;
	type x=this->data[(i+j)/2];
	while(i<j)	{
		while(this->data[i]>x)
			i++;
		while(x>this->data[j])
			j--;
		if(i<=j)
			this->swap(i++,j--);
	}
  if(low<j)
		this->sortQuickDesc(low,j);
	if(high>i)
		this->sortQuickDesc(i,high);
}

int hashFunc(fstring str) {
	int result=0;
	for(int i=0;i<str.getLength();i++)
		result=(result+(int)str[i])%hashtable<fstring,int>::SIZE;
	return result;
}

int main() {
	reader r(cin,0,0);
	int n,count=0,command[PARTNERS_COUNT],*numbers,start=0;
	hashtable<fstring,int> names(hashFunc);
	keypair<fstring,int> temp;
	array<int> *partners,queue;
	fstring str,*namesStr;
	sorter<fstring> *s;
	r.readln(&n);
	partners=new array<int>[PARTNERS_COUNT*n];
	namesStr=new fstring[PARTNERS_COUNT*n];
	for(int i=0;i<n;i++) {
		for(int j=0;j<PARTNERS_COUNT;j++) {
			if(j<PARTNERS_COUNT-1)
				fstring::delimiter=' ';
			else
				fstring::delimiter='\n';
			cin>>str;
			temp=keypair<fstring,int>(str,0);
			if(names.get(&temp))
				command[j]=temp.value;
			else {
				names.push(keypair<fstring,int>(str,count));
				namesStr[count]=str;
				command[j]=count++;
			}
			if(!queue.getLength()&&(str==fstring((char*)ISENBAEV,ISENBAEV_LENGTH)))
				queue.push(command[j]);
		}
		for(int j=0;j<PARTNERS_COUNT-1;j++)
			for(int k=j+1;k<PARTNERS_COUNT;k++) {
				partners[command[j]].push(command[k]);
				partners[command[k]].push(command[j]);
			}
	}
	s=new sorter<fstring>(namesStr,count);
	s->sort('q','a');
	numbers=new int[count];
	memset(numbers,0,count*sizeof(int));
	if(queue.getLength()) {
		numbers[queue[start]]=1;
		while(start<queue.getLength()) {
			for(int i=0;i<partners[queue[start]].getLength();i++)
				if(!numbers[partners[queue[start]][i]]) {
					numbers[partners[queue[start]][i]]=numbers[queue[start]]+1;
					queue.push(partners[queue[start]][i]);
				}
			start++;
		}
	}
	for(int i=0;i<count;i++) {
		temp=keypair<fstring,int>(namesStr[i],0);
		names.get(&temp);
		if(numbers[temp.value])
			cout<<namesStr[i]<<' '<<(numbers[temp.value]-1)<<'\n';
		else
			cout<<namesStr[i]<<" undefined\n";
	}
}