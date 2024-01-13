#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define INF 2147483647

class Edge;
class Vertex;

class Vertex {
public:
    int id;
    int dist;
    vector<Edge> edges;

    Vertex(int id) {
        this->id = id;
        if (id == 0) {
            this->dist = 0;
        } else {
            this->dist = INF;
        }
    }
};

class Edge {
public:    
    int v;
    int w;    

    Edge(int v, int w) {
        this->v = v;
        this->w = w;
    }
};

void BellmanFord(vector<Vertex>& vertices, int n, int m) {    
    bool hasUpdated = false;
    int i = 0;
    for (i; i < n; i++) {
        hasUpdated = false;
        for (auto& v: vertices) {            
            for (auto& e: v.edges) {
                if (v.dist != INF && vertices[e.v].dist > v.dist + e.w) {
                    vertices[e.v].dist = v.dist + e.w;
                    hasUpdated = true;                    
                }                
            }
        }
        if (!hasUpdated) {
            break;
        }
    }
    if (hasUpdated && i == n) {
        cout << "NC";
    } else {
        for (auto& v: vertices) {
            if (v.dist == INF) {
                cout << "I ";
            } else {
                cout << v.dist << " ";
            }
        }
    }
    cout << "\n";
}

int main() {
    int z;
    cin >> z;
    while (z > 0) {
        int n, m;
        cin >> n >> m;
        vector<Vertex> vertices;
        for (int i = 0; i < n; i++) {
            vertices.push_back(Vertex(i));
        }
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            vertices[u].edges.push_back(Edge(v, w));
        }
        BellmanFord(vertices, n, m);
        z--;
    }

    return 0;
}
