// Require MVector.cpp

#include <iostream>
#include <cstring>

class Graph
{
  private:
    static const int NO_EDGE = -1;

    vector2<int> adj; // adjacency matrix
    bool isOriented;
    int verticesCount;
  public:
    Graph(int n, bool isOriented)
    {
      adj.assign(n, n, NO_EDGE);
      verticesCount = n;
      this->isOriented = isOriented;
    }

    // read k edges from stream
    void readEdgeList(istream& stream, int k, bool weighed = false)
    {
      int start, finish, weight;
      for (int i = 0; i < k; i++) {
        stream >> start >> finish;
        if (weighed) {
          stream >> weight;
        } else {
          weight = 1;
        }
        addEdge(start - 1, finish - 1, weight);
      }
    }

    // add edge from i to j
    void addEdge(int i, int j, int weight = 1)
    {
      adj[i][j] = weight;
      if (!isOriented) {
        adj[j][i] = weight;
      }
    }

    // way search between 'first' and 'last' using lee algorithm
    void findWayLee(int first, int last, vector<int>* way)
    {
      vector<int> queue;
      int* was;
      unsigned int start = 0;
      was = new int[verticesCount];
      memset(was, 0, verticesCount * sizeof(int));
      queue.push_back(first);
      was[first] = 1;
      while (start < queue.size()) {
        for (int i = 0; i < verticesCount; i++) {
          if (adj[queue[start]][i] != NO_EDGE && (!was[i] || was[i] >
            was[queue[start]] + 1)) {
              was[i] = was[queue[start]] + 1;
              if (i == last) {
                break;
              }
              queue.push_back(i);
          }
        }
        start++;
      }
      if (was[last]) {
        way->push_back(last);
        for (int i = 0; i < was[last] - 1; i++) {
          for (int j = 0; j < verticesCount; j++) {
            if (adj[j][(*way)[i]] != NO_EDGE && was[j] == was[(*way)[i]] - 1) {
              way->push_back(j);
              break;
            }
          }
        }
      }
    }

    // gets all neighbors of kth vertex
    void getNeighbors(int k, vector<int>* result)
    {
      for (int i = 0; i < verticesCount; i++) {
        if (adj[k][i] != NO_EDGE) {
          result->push_back(i);
        }
      }
    }

    vector<int>& operator[](int i) const
    {
      return adj[i];
    }

    vector<int>& operator[](int i)
    {
      return adj[i];
    }
};
