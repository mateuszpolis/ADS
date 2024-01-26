#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 2147483647

class Edge;
class Vertex;

class Vertex {
public:
    int id;
    int dist;
    int pred = -1;
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

bool ConstructPath(vector<Vertex>& vertices, vector<int>& path) {
    Vertex current = vertices[vertices.size() - 1];
    while (current.pred != -1) {
        path.push_back(current.id);
        current = vertices[current.pred];
    }
    if (current.id != 0) {
        return false;
    } else {
        path.push_back(current.id);
        reverse(path.begin(), path.end());
        return true;
    }
}

void BellmanFord(vector<Vertex>& vertices, int n, int m) {    
    bool hasUpdated = false;
    int i = 0;
    for (i; i < n; i++) {
        hasUpdated = false;
        for (auto& v: vertices) {            
            for (auto& e: v.edges) {
                if (v.dist != INF && vertices[e.v].dist > v.dist + e.w) {
                    vertices[e.v].dist = v.dist + e.w;
                    vertices[e.v].pred = v.id;
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
        vector<int> path;
        if (ConstructPath(vertices, path)) {
            cout << vertices[vertices.size() - 1].dist << "\n";
            for (int v: path) {
                cout << v << " ";
            }
        } else {
            cout << "I";
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
