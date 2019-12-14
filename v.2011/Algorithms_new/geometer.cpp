#include <cmath>

using namespace std;

const double EPS=0.000000001; // точность сравнений
const double PI=3.1415926536; // точность сравнений

template <class type> class point {
public:
	type x,y;
	
	point() {}
	point(type x,type y);

	friend bool operator==(const point<double> &left,const point<double> &right);
	friend bool operator!=(const point<double> &left,const point<double> &right);
	friend bool operator==(const point<int> &left,const point<int> &right);
	friend bool operator!=(const point<int> &left,const point<int> &right);
};

template <class type> point<type>::point(type x,type y) {
	this->x=x;
	this->y=y;
}

bool operator==(const point<double> &left,const point<double> &right) {
	return (abs(left.x-right.x)<EPS)&&(abs(left.y-right.y)<EPS);
}

bool operator!=(const point<double> &left,const point<double> &right) {
	return (abs(left.x-right.x)>EPS)||(abs(left.y-right.y)>EPS);
}

bool operator==(const point<int> &left,const point<int> &right) {
	return (!(left.x-right.x)&&!(left.y-right.y));
}

bool operator!=(const point<int> &left,const point<int> &right) {
	return ((left.x-right.x)||(left.y-right.y));
}
