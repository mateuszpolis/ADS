#include <bits/stdc++.h>

using namespace std;

class Edge {
public:
    int v;

    Edge(int v) {
        this->v = v;
    }
};

class Vertex {
public:
    int id;
    int time;
    int totalTime;
    bool visited;
    vector<Edge> edges;

    Vertex(int id, int time) {
        this->id = id;
        this->time = time;
        this->totalTime = 0;
        this->visited = false;  
    }

    void addEdge(int v) {
        edges.push_back(Edge(v));
    }
};

class Graph {
public:
    vector<Vertex> vertices;

    void addVertex(int id, int time) {
        vertices.push_back(Vertex(id, time));
    }

    void addEdge(int u, int v) {
        vertices[u].addEdge(v);
    }

    void dfs(int v) {
        vertices[v].visited = true;
        vertices[v].totalTime = vertices[v].time;

        for (auto& e : vertices[v].edges) {
            if (!vertices[e.v].visited) {
                dfs(e.v);
            }
            vertices[v].totalTime = max(vertices[v].totalTime, vertices[v].time + vertices[e.v].totalTime);
        }
    }

    int ComputeTime() {
        int maxTime = INT_MIN;

        for (int i = 0; i < vertices.size(); i++) {
            if (!vertices[i].visited) {
                dfs(i);
            }
        }

        for (auto &v: vertices) {
            if (v.totalTime > maxTime) {
                maxTime = v.totalTime;
            }
        }
        return maxTime;
    }
};

int main() {
    int z;
    cin >> z;
    while (z--) {
        int n, m;
        cin >> n >> m;
        Graph graph;
        for (int i = 0; i < n; i++) {
            int t;
            cin >> t;
            graph.addVertex(i, t);
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph.addEdge(u, v);
        }

        cout << graph.ComputeTime() << "\n";
    }
    return 0;
}
