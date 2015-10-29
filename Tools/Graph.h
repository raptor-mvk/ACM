#include <iostream>
#include <cstring>
#include "MVector.h"

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

class Graph {
  private:
    static const int NO_EDGE = -1;

    vector2<int> adj; // adjacency matrix
    bool isOriented;
    int verticesCount;
  public:
    Graph(int n, bool isOriented);

    // read k edges from stream
    void readEdgeList(istream &stream, int k, bool weighed = false);

    void addEdge(int i, int j, int weight = 1); // add edge from i to j

    // way search between 'first' and 'last' using lee algorithm
    void findWayLee(int first, int last, vector<int> *way);

    // gets all neighbors of kth vertex
    void getNeighbors(int k, vector<int> *result);

    vector<int> &operator[](int i) const {
      return adj[i];
    }

    vector<int> &operator[](int i) {
      return adj[i];
    }
};

#endif // GRAPH_H_INCLUDED
