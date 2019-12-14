// метод Гаусса для матриц с диагональным преобладанием

void gauss_forward (double *a, int n)
{
	int i, j, k;
	double cur_multiplier;
	for (i = 0; i < n; i++)
	{
		cur_multiplier = 1.0 / *(a + i * (n + 1) + i);
		for (j = 0; j <= n; j++)
			*(a + i * (n + 1) + j) *= cur_multiplier;
		for (j = i + 1; j < n; j++)
		{
			cur_multiplier = *(a + j * (n + 1) + i);
			for (k = i; k <= n; k++)
				*(a + j * (n + 1) + k) -= cur_multiplier * *(a + i * (n + 1) + k);
		}
	}
}

void gauss_backward (double *a, int n)
{
	int i, j ,k;
	double cur_multiplier;
	for (i = n - 1; i > 0; i--)
		for (j = i - 1; j >= 0; j--)
		{
			cur_multiplier = *(a + j * (n + 1) + i);
			for (k = i; k <= n; k++)
				*(a + j * (n + 1) + k) -= cur_multiplier * *(a + i * (n + 1) + k);
		}
}

