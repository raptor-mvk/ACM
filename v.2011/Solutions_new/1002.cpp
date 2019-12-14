#include <iostream>

using namespace std;

const int MAX_DATA_SIZE=300*1024+1;

template <class type> class array;
template <class type> ostream &operator<<(ostream &stream,
	const array<type> &arr);

template <class type> class array {
private:
	type *data; // данные
	int allocated; // объем выделенной памяти
	int length; // текущая длина массива

	void expand(); // расширение массива на одну страницу
public:
	static const int PAGE_SIZE=1024;
	static char delimiter; // разделитель при печати

	array();
	array(const array<type> &arr);
	array(int length);
	void push(type item); // добавление элемента в конец массива
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
	static const int MAX_LENGTH=152; // максимальная длина строки
	static char delimiter; // разделитель
	static char nonSymbol; // символ, который не встречается в строках
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

	// возвращает строку, обработанную строку функцией processFunc
	fstring process(char(*processFunc)(char));

	// возвращает префикс-функцию подстроки [start,end], где end - конец строки
	void prefixFunc(int *pfvalues,int start); 

	// возвращает все позиции вхождений строки substr
	array<int> find(fstring substr);

	// возвращает подстроку [start,start+length-1]
	fstring substrl(int start,int length) {
		return fstring(this->data+start,length);
	}

	// возвращает подстроку [start,finish]
	fstring substrf(int start,int finish) {
		return fstring(this->data+start,finish-start+1);
	}

	// возвращает подстроку [start,end], где end - конец строки
	fstring substr(int start) {
		return fstring(this->data+start,this->length-start);
	}
	
	// уменьшает длину строки на count
	void trimEnd(int count) {
		this->length-=count;
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
	bool found;
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

class reader {
private:
	const char *buffer; // буфер для чтения данных
	int maxLength; // размер буфера
	int length; // текущий размер данных в буфере
	int startPos; // текущая позиция с начала буфера
	int endPos; // текущая позиция с конца буфера
	istream &in; // входной поток для чтения данных
public:
	reader(istream &in,const char* buffer,int maxLength);
	void reinit(const char* buffer, int maxLength); // задание нового буфера
	void fill(); // заполнение буфера данными

	// игнорирование count символов в направлении dir
	void ignore(int count,char dir);

	// считывание целого числа из буфера в направлении dir (вместе со стандартными
	// разделителями, если readln = true)
	template <typename type> bool getNext(type *number,char dir,bool readln);

	// считывание без модификации слова в направлении dir(вместе со стандартными
	// разделителями, если readln = true), функция checkFunc должна возвращать
	// true для разделителя
	fstring getNext(bool(*checkFunc)(char symbol),char dir,bool readln);

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

template <typename type> bool reader::getNext(type *number,char dir,
	bool readln) {
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
				if(readln)
					while(((this->buffer[this->startPos]==' ')||
						(this->buffer[this->startPos]=='\t')||
						(this->buffer[this->startPos]=='\n'))&&(this->startPos<=this->endPos))
							this->startPos++;
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
				if(readln)
					while(((this->buffer[this->startPos]==' ')||
						(this->buffer[this->startPos]=='\t')||
						(this->buffer[this->startPos]=='\n'))&&(this->startPos<=this->endPos))
							this->endPos--;
				return true;
		}
}

void reader::ignore(int count,char dir) {
	switch(dir) {
		case 'f': // сдвиг начала данных
			this->startPos+=count;
			return;
		case 'b': // сдвиг конца данных
			this->endPos-=count;
			return;
	}
}

fstring reader::getNext(bool(*checkFunc)(char symbol),char dir,bool readln) {
	int start,length=0;
	switch (dir) {
		case 'f': // поиск с начала данных
			start=this->startPos;
			while(this->startPos<=this->endPos)
				if(checkFunc(this->buffer[this->startPos]))
					break;
				else {
					this->startPos++;
					length++;
				}
			if(readln)
				while(this->startPos<=this->endPos)
					if(!checkFunc(this->buffer[this->startPos]))
						break;
					else
						this->startPos++;
			return fstring((char*)this->buffer+start,length);
		case 'b': // поиск с конца данных
			start=this->endPos;
			while(this->startPos<=this->endPos)
				if(checkFunc(this->buffer[this->endPos]))
					break;
				else {
					this->endPos--;
					length++;
				}
			if(readln)
				while(this->startPos<=this->endPos)
					if(!checkFunc(this->buffer[this->endPos]))
						break;
					else
						this->endPos--;
			return fstring((char*)this->buffer+start-length+1,length);
	}
}

bool checkFunc(char symbol) {
	if((symbol==' ')||(symbol=='\n')||(symbol=='\t'))
		return true;
	return false;
}

char processFunc(char symbol) {
	switch (symbol)
	{
	case 'i': case 'j':
		return '1';
	case 'a': case 'b': case 'c':
		return '2';
	case 'd': case 'e': case 'f':
		return '3';
	case 'g': case 'h':
		return '4';
	case 'k': case 'l':
		return '5';
	case 'm': case 'n':
		return '6';
	case 'p': case 'r': case 's':
		return '7';
	case 't': case 'u': case 'v':
		return '8';
	case 'w': case 'x': case 'y':
		return '9';
	case 'o': case 'q': case 'z':
		return '0';
	}
}

class graph {
private:
	int n;
	int *adjMatrix;
	bool oriented;
	
public:
	graph(int n,bool oriented);
	void addEdge(int i,int j,int weight); // добавить ребро (i,j)

	// поиск пути из [first,last] методом "волна"
	array<int> wave(int first,int last); 

	// возвращает вес ребра (i,j)
	int getWeight(int i,int j) {
		return this->adjMatrix[i*this->n+j];
	}

	~graph() {
		delete [] this->adjMatrix;
	}
};

graph::graph(int n,bool oriented) {
	this->n=n;
	this->oriented=oriented;
	this->adjMatrix=new int[n*n];
	memset(this->adjMatrix,0,n*n*sizeof(int));
}

void graph::addEdge(int i,int j,int weight) {
	this->adjMatrix[i*this->n+j]=weight;
	if(!this->oriented)
		this->adjMatrix[j*this->n+i]=weight;
}

array<int> graph::wave(int first,int last) {
	array<int> way,queue;
	int *was,start=0;
	was=new int[this->n];
	memset(was,0,this->n*sizeof(int));
	queue.push(first);
	was[first]=1;
	while(start<queue.getLength()) {
		for(int i=0;i<=this->n;i++) {
			if((this->adjMatrix[queue[start]*this->n+i])&&(!was[i]||(was[i]>
				was[queue[start]]+1))) {
					was[i]=was[queue[start]]+1;
					if(i==last)
						break;
					queue.push(i);
			}
		}
		start++;
	}
	if(was[last]) {
		way.push(last);
		for(int i=0;i<was[last]-1;i++)
			for(int j=0;j<this->n;j++)
				if((this->adjMatrix[j*this->n+way[i]])&&(was[j]==was[way[i]]-1)) {
					way.push(j);
					break;
				}
	}
	return way;
}

int main() {
	int n;
	char *data;
	fstring phone,*dictionary,*words;
	reader *r;
	graph *g;
	data=new char[MAX_DATA_SIZE];
	array<int> pos;
	r=new reader(cin,data,MAX_DATA_SIZE);
	r->fill();
	while(true) {
		phone=r->getNext(&checkFunc,'f',true);
		if(phone[0]=='-')
			break;
		g=new graph(phone.getLength()+1,true);
		r->getNext<int>(&n,'f',true);
		dictionary=new fstring[n];
		words=new fstring[n];
		for(int i=0;i<n;i++) {
			words[i]=r->getNext(&checkFunc,'f',true);
			dictionary[i]=words[i].process(&processFunc);
			pos=phone.find(dictionary[i]);
			for(int j=0;j<pos.getLength();j++)
				g->addEdge(pos[j],pos[j]+dictionary[i].length,i+1);
		}
		pos=g->wave(0,phone.getLength());
		if(pos.getLength())
			for(int i=pos.getLength()-1;i>0;i--) {
				cout<<words[g->getWeight(pos[i],pos[i-1])-1];
				if(i>1)
					cout<<' ';
				else
					cout<<'\n';
			}
		else
			cout<<"No solution.\n";
		break;
		delete [] dictionary;
		delete [] words;
		delete g;
	}
}
