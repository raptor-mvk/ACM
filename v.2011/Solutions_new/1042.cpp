#include <iostream>

using namespace std;

int main() {
  char *matrix,*ans;
  int n,cur;
  cin>>n;
	matrix=new char[n*n];
	ans=new char[n];
  memset(matrix,0,n*n*sizeof(char));
  memset(ans,1,n*sizeof(char));
  for(int i=0;i<n;i++) {
		cin>>cur;
    while(cur!=-1) {
      matrix[(cur-1)*n+i]=1;
      cin>>cur;
    }
  }
  for(int i=0;i<n-1;i++)
    if(matrix[i*n+i]) {
      for(int j=i+1;j<n;j++)
        if(matrix[j*n+i]) {
          for(int k=0;k<n;k++)
            matrix[j*n+k]^=matrix[i*n+k];
          ans[j]^=ans[i];
        }
    }    
    else {
      int j=i;
      while(!matrix[(++j)*n+i]);
      for(int k=0;k<n;k++)
        matrix[i*n+k]^=matrix[j*n+k];
      ans[i]^=ans[j];
      for(;j<n;j++)
        if(matrix[j*n+i]) {
          for(int k=0;k<n;k++)
            matrix[j*n+k]^=matrix[i*n+k];
          ans[j]^=ans[i];
        }
    }
  for(int i=n-1;i>0;i--)
    for(int j=0;j<i;j++)
      if(matrix[j*n+i]) {
        for(int k=0;k<n;k++)
          matrix[j*n+k]^=matrix[i*n+k];
        ans[j]^=ans[i];
      }
  for(int i=0;i<n;i++)
    if(ans[i])
			cout<<(i+1)<<' ';
}
