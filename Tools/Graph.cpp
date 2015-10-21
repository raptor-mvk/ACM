#include "Graph.h"

Graph::Graph(int n, bool isOriented) {
  adj.assign(n, n, NO_EDGE);
  verticesCount = n;
  this->isOriented = isOriented;
}

void Graph::readEdgeList(istream &stream, int k) {
  int start, finish;
  for (int i = 0; i < k; i++) {
    stream >> start >> finish;
    adj[--start][--finish] = 1;
    if (!isOriented) {
      adj[finish][start] = 1;
    }
  }
}

void Graph::getNeighbors(int k, vector<int> *result) {
  for (int i = 0; i < verticesCount; i++) {
    if (adj[k][i] != NO_EDGE) {
      result->push_back(i);
    }
  }
}
