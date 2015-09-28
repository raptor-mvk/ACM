#include "Huge.h"
#include <iomanip>

int Huge::huge_foundation = 1e4;
int Huge::power = 4170;
int Huge::max_length = 250;

Huge::Huge() {
	this->length = 1;
	this->number = new int[max_length];
	memset(this->number, 0, max_length * sizeof(int));
}

Huge::Huge(int number) {
	this->length = 0;
	this->number = new int[max_length];
	memset(this->number, 0, max_length * sizeof(int));
	while (number) {
		this->number[this->length++] = number % huge_foundation;
		number /= huge_foundation;
	}
}

Huge::Huge(const Huge &number) {
	this->length = number.length;
	this->number = new int[max_length];
	memset(this->number, 0, max_length * sizeof(int));
	memcpy(this->number, number.number, number.length * sizeof(int));
}

Huge::Huge(const FString &str) {
	int tmp = 0, mul = 1;
	this->number = new int[max_length];
	this->length = !str.length;
	for (int i = str.length - 1; i >= 0;i--) {
		tmp += (str[i] - '0') * mul;
		mul *= this->FOUNDATION;
		if (mul == this->huge_foundation) {
			this->number[this->length++] = tmp;
			mul = 1;
			tmp = 0;
		}
	}
	if (tmp || !this->length) {
		this->number[this->length++] = tmp;
	}
}

void Huge::shift(int count) {
	if (count) {
		memmove(this->number + count, this->number, this->length * sizeof(int));
		memset(this->number, 0, count * sizeof(int));
		this->length += count;
	}
}

void Huge::mul(int number, int shift) {
	int carry = 0;
	for (int i = 0; i < this->length; i++) {
		carry += this->number[i] * number;
		this->number[i] = carry % huge_foundation;
		carry /= huge_foundation;
	}
	if (carry) {
		this->number[this->length++] = carry;
	}
	this->shift(shift);
}

Huge::operator FString() const {
	FString res;
	int tmp, mul;
	bool started = false;
	tmp = this->number[this->length - 1];
	mul = this->huge_foundation / this->FOUNDATION;
	while (mul) {
		if (tmp / mul) {
			started = true;
		}
		if (started) {
			res[res.length++] = tmp / mul + '0';
		}
		tmp = tmp % mul;
		mul /= this->FOUNDATION;
	}
	for (int i = this->length - 2; i >= 0; i--) {
		tmp = this->number[i];
		mul = this->huge_foundation / this->FOUNDATION;
		for (int j = 0; j < this->power; j++) {
			res[res.length++] = tmp / mul + '0';
			tmp = tmp % mul;
			mul /= this->FOUNDATION;
		}
	}
	return res;
}

Huge::operator FString() {
	FString res;
	int tmp, mul;
	bool started = false;
	tmp = this->number[this->length - 1];
	mul = this->huge_foundation / this->FOUNDATION;
	while (mul) {
		if (tmp / mul) {
			started = true;
		}
		if (started) {
			res[res.length++] = tmp / mul + '0';
		}
		tmp = tmp % mul;
		mul /= this->FOUNDATION;
	}
	for (int i = this->length - 2; i >= 0; i--) {
		tmp = this->number[i];
		mul = this->huge_foundation / this->FOUNDATION;
		for (int j = 0; j < this->power; j++) {
			res[res.length++] = tmp / mul + '0';
			tmp = tmp % mul;
			mul /= this->FOUNDATION;
		}
	}
	return res;
}

Huge &Huge::operator=(const Huge &number) {
	delete [] this->number;
	this->length = number.getLength();
	this->number = new int[max_length];
	memcpy(this->number, number.number, number.getLength() * sizeof(int));
	return *this;
}

Huge &Huge::operator=(const int &number) {
	int temp = number;
	delete [] this->number;
	this->length = 0;
	this->number = new int[max_length];
	while (temp) {
		this->number[this->length++] = temp % huge_foundation;
		temp /= huge_foundation;
	}
	return *this;
}

ostream &operator<<(ostream &stream, Huge const &number) {
	stream << number[number.length - 1];
	for (int i = number.length - 2; i >= 0; i--) {
		stream << setw(Huge::power) << setfill('0') << number[i];
	}
	return stream;
}

Huge operator+(const Huge &left, const int &right) {
	Huge result(left);
	int temp = right, carry = 0, length = 0;
	while (temp) {
		carry += result[length] + temp % Huge::huge_foundation;
		result[length++] = carry % Huge::huge_foundation;
		carry /= Huge::huge_foundation;
		temp /= Huge::huge_foundation;
	}
	while (carry) {
		carry += result[length];
		result[length++] = carry % Huge::huge_foundation;
		carry /= Huge::huge_foundation;
	}
	if (length > result.length) {
		result.length = length;
	}
	return result;
}

Huge operator+(const Huge &left, const Huge &right) {
	Huge result(left);
	int carry = 0, length = right.length;
	for (int i = 0; i < right.length; i++) {
		carry += result[i] + right[i];
		result[i] = carry % Huge::huge_foundation;
		carry /= Huge::huge_foundation;
	}
	while (carry) {
		carry += result[length];
		result[length++] = carry % Huge::huge_foundation;
		carry /= Huge::huge_foundation;
	}
	if (length > result.length) {
		result.length = length;
	}
	return result;
}

Huge operator*(const Huge &left, const int &right) {
	Huge result, temp;
	int temp2 = right, shift = 0;
	while (temp2) {
		temp = left;
		temp.mul(temp2 % Huge::huge_foundation, shift++);
		result += temp;
		temp2 /= Huge::huge_foundation;
	}
	return result;
}

Huge operator*(const Huge &left, const Huge &right) {
	Huge result,temp;
	for (int i = 0; i < right.length; i++) {
		temp = left;
		temp.mul(right[i], i);
		result += temp;
	}
	return result;
}

Huge &Huge::operator+=(const int &right) {
	int temp = right, carry = 0, length = 0;
	while (temp) {
		carry += this->number[length] + temp % huge_foundation;
		this->number[length++] = carry % huge_foundation;
		carry /= huge_foundation;
		temp /= huge_foundation;
	}
	while (carry) {
		carry += this->number[length];
		this->number[length++] = carry % huge_foundation;
		carry /= huge_foundation;
	}
	if (length > this->length) {
		this->length = length;
	}
	return *this;
}

Huge &Huge::operator+=(const Huge &right) {
	int carry = 0, length = right.length;
	for (int i = 0; i < right.length; i++) {
		carry += this->number[i] + right[i];
		this->number[i] = carry % huge_foundation;
		carry /= huge_foundation;
	}
	while (carry) {
		carry += this->number[length];
		this->number[length++] = carry % huge_foundation;
		carry /= huge_foundation;
	}
	if(length > this->length) {
		this->length = length;
	}
	return *this;
}

Huge &Huge::operator*=(const int &right) {
	Huge result, temp;
	int temp2 = right, shift = 0;
	while (temp2) {
		temp = *this;
		temp.mul(temp2 % huge_foundation, shift++);
		result += temp;
		temp2 /= huge_foundation;
	}
	*this = result;
	return *this;
}

Huge &Huge::operator*=(const Huge &right) {
	Huge result, temp;
	for (int i = 0; i < right.length; i++) {
		temp = *this;
		temp.mul(right[i], i);
		result += temp;
	}
	*this = result;
	return *this;
}

bool operator<(const Huge &left,const Huge &right) {
	int len = left.length > right.length ? right.length : left.length;
	for (int i = 0; i < len; i++) {
		if (left[i] < right[i]) {
			return true;
		}	else if (left[i] > right[i]) {
				return false;
		}
	}
	return left.length < right.length;
}

bool operator<=(const Huge &left,const Huge &right) {
	int len = left.length > right.length ? right.length : left.length;
	for (int i = 0; i < len; i++) {
		if (left[i] < right[i]) {
			return true;
		} else if (left[i] > right[i]) {
				return false;
		}
	}
	return left.length <= right.length;
}

bool operator>(const Huge &left,const Huge &right) {
  return right<left;
}

bool operator>=(const Huge &left,const Huge &right) {
  return right<=left;
}

bool operator==(const Huge &left,const Huge &right) {
	if (right.length != left.length) {
		return false;
	}
	for (int i = 0; i < left.length; i++) {
		if (left[i] != right[i]) {
			return false;
		}
	}
	return true;
}

bool operator!=(const Huge &left,const Huge &right) {
  return !(left == right);
}
