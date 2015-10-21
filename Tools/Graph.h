#include <iostream>
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

    void readEdgeList(istream &stream, int k); // read k edges from stream

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
