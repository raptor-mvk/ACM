#include <iostream>

using namespace std;

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
	static const int SIZE=211;
	
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
	static const int MAX_LENGTH=21; // максимальна€ длина строки
	
public:
	static char delimiter; // разделитель
	char *data; // содержимое строки
	int length; // длина строки
	fstring();
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

int readTime() {
	char tmp,tmp2;
	int result;
	cin.get(tmp);
	cin.get(tmp2);
	if(tmp2==':')
		result=(tmp-'0')*600;
	else {
		result=(tmp-'0')*6000+(tmp2-'0')*600;
		cin.get(tmp);
	}
	cin.get(tmp);
	cin.get(tmp2);
	if(tmp2=='.')
		result+=(tmp-'0')*10;
	else {
		result+=(tmp-'0')*100+(tmp2-'0')*10;
		cin.get(tmp);
	}
	cin.get(tmp);
	result+=(tmp-'0');
	cin.ignore(1);
	return result;
}

int main() {
	int n,time,min=0,count=0;
	fstring str;
	char tmp,tmp2;
	reader *r;
	hashtable<fstring,int> names(&hashFunc);
	keypair<int,fstring> *finish;
	keypair<fstring,int> temp;
	fstring *leaders;
	sorter<keypair<int,fstring> > *s1;
	sorter<fstring> *s2;
	r=new reader(cin,0,0);
	r->readln<int>(&n);
	finish=new keypair<int,fstring>[n];
	leaders=new fstring[n];
	fstring::delimiter=' ';
	for(int i=0;i<n;i++) {
		cin>>str;
		time=readTime();
		names.push(keypair<fstring,int>(str,time));
		if(min<time)
			min=time;
		finish[i]=keypair<int,fstring>(time+i*300,str);
	}
	s1=new sorter<keypair<int,fstring> >(finish,n);
	s1->sort('q','a');
	for(int i=0;i<n;i++) {
		temp=keypair<fstring,int>(finish[i].value,finish[i].key);
		names.get(&temp);
		if(temp.value<=min) {
			min=temp.value;
			leaders[count++]=temp.key;
		}
	}
	s2=new sorter<fstring>(leaders,count);
	s2->sort('q','a');
	cout<<count<<'\n';
	for(int i=0;i<count;i++)
		cout<<leaders[i]<<'\n';
}
