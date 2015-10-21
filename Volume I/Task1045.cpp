// Topic: games
// Subtopic: graph
// Idea: graph is a forest, so, every move either isolates a vertex
//       or divides a tree into two subtrees, it is sufficient to
//       remove only previous vertex while calculating possible moves

#include <iostream>
#include "../Tools/Graph.h"

using namespace std;

int get_move(int prev, int start, Graph *graph) {
  int move = -1;
  vector<int> neighbors;
  graph->getNeighbors(start, &neighbors);
  for (int i = 0, count = neighbors.size(); i < count; i++) {
    if (neighbors[i] != prev) {
      if (get_move(start, neighbors[i], graph) == -1) {
        if (move == -1 || move > neighbors[i]) {
          move = neighbors[i];
        }
      }
    }
  }
  return move;
}

int main() {
  int n, k;
  cin >> n >> k;
  Graph graph(n, false);
  graph.readEdgeList(cin, n - 1);
  n = get_move(-1, k - 1, &graph);
  if (n == -1) {
		cout << "First player loses";
  } else {
		cout << "First player wins flying to airport " << (n + 1);
  }
}
