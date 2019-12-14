#include <iostream>
#include <queue>
#include <climits>

using namespace std;

template <class T> class array_2d
{
private:
  vector<T> *data;
  int dim[2];
public:
  array_2d()
  {
    dim[0]=0;
    dim[1]=0;
    data=NULL;
  }

  array_2d(int n,int m,T value=(T)0)
  {
    dim[0]=n;
    dim[1]=m;
    data=new vector<T>[n];
    for(int i=0;i<n;i++)
      data[i].assign(m,value);
  }

  array_2d(array_2d &a)
  {
    dim[0]=a.dim[0];
    dim[1]=a.dim[1];
    data=new vector<T>[dim[0]];
    for(int i=0;i<dim[0];i++)
      data[i]=a.data[i];
  }

  ~array_2d()
  {
    delete[]data;
  }

  void assign(int n,int m,T value=(T)0)
  {
    delete[]data;
    dim[0]=n;
    dim[1]=m;
    data=new vector<T>[n];
    for(int i=0;i<n;i++)
      data[i].assign(m,value);
  }

  vector<T> &operator[](int i) const
  {
    return data[i];
  }

  vector<T> &operator[](int i)
  {
    return data[i];
  }

  array_2d &operator=(const array_2d &a)
  {
    delete[]data;
    dim[0]=a.dim[0];
    dim[1]=a.dim[1];
    data=new vector<T>[dim[0]];
    for(int i=0;i<dim[0];i++)
      data[i]=a.data[i];
  }
};

int main() {
	const int PRICE = 4;
	array_2d<int> adj,prices;
	int n,m,l,k,mon,st,tc;
	cin>>n>>m;
	int *ln = new int[n];
	adj.assign(n,n);
	for (int i = 0; i < m; i++) {
		cin>>l;
		for (int j = 0; j < l; j++) {
			cin>>ln[j];
			for (int k = 0; k < j; k++) {
				adj[ln[j] - 1][ln[k] - 1]=PRICE;
				adj[ln[k] - 1][ln[j] - 1]=PRICE;
			}
		}
	}
	cin>>k;
	prices.assign(k,n,-1);
	for (int i = 0; i < k; i++) {
    cin>>mon>>st>>tc;
    queue<int> q;
    prices[i][st - 1]=0;
    q.push(st - 1);
    while (!q.empty()) {
      int c = q.front();
      q.pop();
      for (int j = 0; j < n; j++) {
        if (adj[c][j]>0 && prices[i][j] == -1) {
            if (tc) {
              prices[i][j]=0;
              q.push(j);
            } else if (prices[i][c]+adj[c][j]<=mon) {
              prices[i][j]=prices[i][c]+adj[c][j];
              q.push(j);
            }
        }
      }
    }
	}
	int min = INT_MAX;
	int minp = -1;
	for (int i = 0; i < n; i++) {
    bool ok = 1;
    int sum = 0;
    for (int j = 0; j < k; j++) {
      sum += prices[j][i];
      if (prices[j][i] == -1) {
        ok = 0;
        break;
      }
    }
    if (ok && min > sum) {
      min = sum;
      minp = i;
    }
	}
	if (minp<0) {
    cout<<0;
  }
  else {
    cout<<minp<<" "<<(min+1);
  }
	cin>>n;
}

