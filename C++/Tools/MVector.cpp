#include <vector>

using namespace std;

template <class T> class vector2
{
  private:
    vector<T>* data;
    int dim[2]; // dimensions of array

  public:
    ~vector2()
    {
      delete[]data;
    }

    vector2()
    {
      dim[0] = 0;
      dim[1] = 0;
      data = 0;
    }

    vector2(int n, int m, T value)
    {
      dim[0] = n;
      dim[1] = m;
      data = new vector<T>[n];
      for (int i = 0; i < n; i++) {
        data[i].assign(m, value);
      }
    }

    vector2(const vector2<T>& a)
    {
      dim[0] = a.dim[0];
      dim[1] = a.dim[1];
      data = new vector<T>[dim[0]];
      for (int i = 0; i < dim[0]; i++) {
        data[i] = a.data[i];
      }
    }

    vector2<T>& operator=(const vector2<T>& a)
    {
      delete[] data;
      dim[0] = a.dim[0];
      dim[1] = a.dim[1];
      data = new vector<T>[dim[0]];
      for (int i = 0; i < dim[0]; i++) {
        data[i] = a.data[i];
      }
    }

    vector<T>& operator[](int i) const
    {
      return data[i];
    }

    vector<T>& operator[](int i)
    {
      return data[i];
    }

    int size()
    {
      return dim[0] * dim[1];
    }

    void assign(int n, int m, T value)
    {
      delete[] data;
      dim[0] = n;
      dim[1] = m;
      data = new vector<T>[n];
      for (int i = 0; i < n; i++) {
        data[i].assign(m, value);
      }
    }
};

template <class T> class vector3
{
  private:
    vector2<T>* data;
    int dim[3];
  public:
    vector3();
    vector3(int n, int m, int k, T value = (T)0);
    vector3(vector3& a);
    void assign(int n, int m, int k, T value = (T)0);

    vector2<T>& operator[](int i) const
    {
      return data[i];
    }

    vector2<T>& operator[](int i)
    {
      return data[i];
    }

    int size()
    {
      return dim[0] * dim[1] * dim[2];
    }

    ~vector3()
    {
      delete[] data;
    }

    vector3()
    {
      dim[0] = 0;
      dim[1] = 0;
      dim[2] = 0;
      data = 0;
    }

    vector3(int n, int m, int k, T value)
    {
      dim[0] = n;
      dim[1] = m;
      dim[2] = k;
      data = new vector2<T>[n];
      for (int i = 0; i < n; i++) {
        data[i].assign(m, k, value);
      }
    }

    vector3(vector3& a)
    {
      dim[0] = a.dim[0];
      dim[1] = a.dim[1];
      dim[2] = a.dim[2];
      data = new vector2<T>[dim[0]];
      for (int i = 0; i < dim[0]; i++) {
        data[i] = a.data[i];
      }
    }

    void assign(int n, int m, int k, T value)
    {
      delete[] data;
      dim[0] = n;
      dim[1] = m;
      dim[2] = k;
      data = new vector2<T>[n];
      for (int i = 0; i < n; i++) {
        data[i].assign(m, k, value);
      }
    }
};
