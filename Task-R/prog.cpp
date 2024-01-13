#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

enum EdgeType { T, F, B, C, U };

class Vertex {
public:
    int id;
    vector<pair<Vertex*, EdgeType> > neighbours;
    bool visited;
    int discoveryTime, finishTime;
    Vertex(int id) : id(id), visited(false), discoveryTime(0), finishTime(0) {}
};

int currentTime = 0;

EdgeType classifyEdge(Vertex& u, Vertex& v) {
    if (!v.visited) { 
        return T;
    } else if (u.discoveryTime < v.discoveryTime && v.finishTime != 0) {
        return F;
    } else if (u.discoveryTime > v.discoveryTime && u.finishTime < v.finishTime) {
        return C;
    } else {
        return B;
    }
}


void dfs(Vertex& v) {
    v.visited = true;
    v.discoveryTime = ++currentTime;
    for (auto& neighbour : v.neighbours) {
        Vertex& adjVertex = *neighbour.first;
        if (!adjVertex.visited) {
            neighbour.second = classifyEdge(v, adjVertex);
            dfs(adjVertex);
        } else {
            neighbour.second = classifyEdge(v, adjVertex);
        }
    }
    v.finishTime = ++currentTime;
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
            int x, y;
            cin >> x >> y;
            vertices[x].neighbours.push_back(make_pair(&vertices[y], U));
        }

        for (Vertex& v : vertices) {
            if (!v.visited) {
                dfs(v);
            }
        }
        
        for (const Vertex& v : vertices) {
            for (const auto& neighbour : v.neighbours) {
                cout << v.id << " " << neighbour.first->id << " ";
                switch (neighbour.second) {
                    case T: cout << "T\n"; break;
                    case F: cout << "F\n"; break;
                    case B: cout << "B\n"; break;
                    case C: cout << "C\n"; break;
                    default: cout << "U\n";
                }
            }
        }

        z--;
    }
    return 0;
}
