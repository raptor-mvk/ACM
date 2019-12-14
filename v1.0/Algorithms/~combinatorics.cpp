// количество сочетаний из n элементов по k,
// количество размещений n элементов в k группах

int calc_d(int n, int k)
{
  int result=0;
  if(k<=0) return 0;
  if(k==1) return 1;
  for(int i=1;i<=n-k+1;i++)
    result+=calc_d(n-i,k-1)*calc_c(n,i);
  return result;
}
