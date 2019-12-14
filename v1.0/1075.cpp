#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int N = 3;
const int M = 2;
const double PI = acos(-1.0);

double acos1(double angle)
{
	if (angle > 1.0)
		return 0;
	if (angle < -1.0)
		return PI;
	return acos(angle);
}

double get_length(int *vect)
{
	int i;
	double length = 0.0;
	for (i = 0; i < N; i++)
		length += (double)*(vect + i) * (double)*(vect + i);
	return sqrt(length);
}

double get_angle(int *first, int *second)
{
	int i;
	double angle = 0.0;
	for (i = 0; i < N; i++)
		angle += (double)*(first + i) * (double)*(second + i);
	return acos1(angle / get_length(first) / get_length(second));
}

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int a[N], b[N], c[N], i, r;
	double a2[M], b2[M], angle, temp, temp2;
	char same_pts = 1;
	for (i = 0; i < N; i++)
		scanf("%d", a + i);
	for (i = 0; i < N; i++)
		scanf("%d", b + i);
	for (i = 0; i < N; i++)
		scanf("%d", c + i);
	scanf("%d", &r);
	for (i = 0; i < N; i++)
		if (*(a + i) != *(b + i))
		{
			same_pts = 0;
			break;
		}
	if (same_pts != 0)
	{
		printf("0.00\n");
		return 0;
	}
	for (i = 0; i < N; i++)
	{
		*(a + i) = *(a + i) - *(c + i);
		*(b + i) = *(b + i) - *(c + i);
	}
	*a2 = get_length(a);
	*(a2 + 1) = 0;
	angle = get_angle(a, b);
	*b2 = get_length(b) * cos(angle);
	*(b2 + 1) = get_length(b) * sin(angle);
	angle -= acos1((double)r / sqrt(*b2 * *b2 + *(b2 + 1) * *(b2 + 1))) + acos1((double)r /
		sqrt(*a2 * *a2 + *(a2 + 1) * *(a2 + 1)));
	temp = (*b2 - *a2) / sqrt((*b2 - *a2) * (*b2 - *a2) + (*(b2 + 1) - *(a2 + 1)) * (*(b2 + 1) -
		*(a2 + 1)));
	temp2 = *b2 / sqrt(*b2 * *b2 + *(b2 + 1) * *(b2 + 1));
	if ((temp < -sqrt(*a2 * *a2 - (double)r * (double)r) / *a2) && (temp2 < (double)r / *a2))
			printf("%.2f\n", sqrt(*a2 * *a2 + *(a2 + 1) * *(a2 + 1) - (double)r * (double)r) +
				sqrt(*b2 * *b2 + *(b2 + 1) * *(b2 + 1) - (double)r * (double)r) + angle * (double)r);
	else
		printf("%.2f\n", sqrt((*a2 - *b2) * (*a2 - *b2) + (*(a2 + 1) - *(b2 + 1)) * (*(a2 + 1) -
			*(b2 + 1))));
}