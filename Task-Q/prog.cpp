#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Edge {
public:
  int u, v, w;
  Edge(int u, int v, int w) {
    this->u = u;
    this->v = v;
    this->w = w;
  }
};

void MST(vector<Edge> edges, int n) {
  vector<int> parent(n + 1);
  int count = 0;
  for (int i = 1; i <= n; i++) {
    parent[i] = i;
  }
  int cost = 0;
  for (Edge e : edges) {
    int u = e.u;
    int v = e.v;
    int w = e.w;
    while (parent[u] != u) {
      u = parent[u];
    }
    while (parent[v] != v) {
      v = parent[v];
    }
    if (u != v) {
      parent[u] = v;
      cost += w;
      count++;
    }
  }
  if (count == n - 1) {
    cout << cost << "\n";
  } else {
    cout << "-1\n";
  }
}

int main()
{	
	int z;
	cin >> z;
	while(z)
	{
    int n, m;
		cin >> n >> m;    
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
      int x, y, w;
      cin >> x >> y >> w;
      edges.push_back(Edge(x, y, w));
    }
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
      return a.w < b.w;
    });
    MST(edges, n);
		z--;
	}
	return 1;
}
