#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

class Vertex {
  public:
    int id;
    int dfs_num, dfs_low;
    int ssc_id;
    bool visited;
    bool inStack;
    vector<int> edges;
  
    Vertex(int id) {
      this->id = id;
      this->visited = false;
      this->inStack = false;
      this->dfs_num = -1;
      this->dfs_low = -1;
    };    
};

class Scc {
  public:
    int id;
    int size;
    vector<int> vertices;
  
    Scc(int id) {
      this->id = id;
      this->size = 0;
    };
  
    void addVertex(int v) {
      this->vertices.push_back(v);
      this->size++;
    };
};

class Graph {
  public:
    vector<Vertex> vertices;
    stack<int> st;
    vector<Scc> sccs;
    int time;
  
    Graph(int n) {
      for (int i = 0; i < n; i++) {
        this->vertices.push_back(Vertex(i));
      }                         
      this->time = 0;      
    };
  
    void addEdge(int u, int v) {
      vertices[u].edges.push_back(v);
    };

    void printGraph() {
      for (Vertex v : vertices) {
        cout << v.id << ": ";
        for (int edge : v.edges) {
          cout << edge << " ";
        }
        cout << "\n";
      }
    }; 

    void printSccs() {
      for (Scc scc : sccs) {
        cout << scc.id << ": ";
        for (int v : scc.vertices) {
          cout << v << "(" << vertices[v].dfs_low << ") ";
        }
        cout << "\n";
      }
    };

    void DFS(int v) {
        vertices[v].visited = true;
        vertices[v].dfs_num = vertices[v].dfs_low = time++;
        st.push(v);
        vertices[v].inStack = true;

        for (int edge : vertices[v].edges) {
            if (!vertices[edge].visited) {
                DFS(edge);                
                vertices[v].dfs_low = min(vertices[v].dfs_low, vertices[edge].dfs_low);                
            } else if (vertices[edge].inStack) {                               
                vertices[v].dfs_low = min(vertices[v].dfs_low, vertices[edge].dfs_num);                
            }
        }

        if (vertices[v].dfs_low == vertices[v].dfs_num) {
            Scc scc = Scc(vertices[v].dfs_low); 
            while (!st.empty() && st.top() != v) {
                int top = st.top();
                st.pop();
                vertices[top].inStack = false;
                // cout << vertices[top].id << " dfs_low: " << vertices[top].dfs_low << " dfs_num: " << vertices[top].dfs_num << "\n";
                scc.addVertex(top); 
                vertices[top].ssc_id = scc.id;                   
            }            
            st.pop();
            vertices[v].inStack = false;
            // cout << vertices[v].id << " dfs_low: " << vertices[v].dfs_low << " dfs_num: " << vertices[v].dfs_num << "\n";
            scc.addVertex(v);      
            sccs.push_back(scc);  
            vertices[v].ssc_id = scc.id;           
        }
    }

    bool hasOutgoingEdges(int v) {
        for (int edge : vertices[v].edges) {
            if (vertices[edge].ssc_id != vertices[v].ssc_id) {
                // cout << "v: " << v << " edge: " << edge << "\n";
                return true;
            }
        }
        return false;
    }

    void getMinSccSize() {
        int minSize = 1000000;
        for (Scc scc : sccs) {
            bool hasOutgoing = false;
            for (int v : scc.vertices) {
                if (hasOutgoingEdges(v)) {                    
                    hasOutgoing = true;
                    break;
                }                
            }
            if (!hasOutgoing) {
                minSize = min(minSize, scc.size);
            }
        }
        cout << minSize << "\n";
    }
};

int main()
{	
	int z;
	cin >> z;
	while(z)
	{
    int n, m;
		cin >> n >> m;
    Graph graph = Graph(n);
		for(int i = 0; i < m; i++)
		{
			int x, y;
      cin >> x >> y;
      graph.addEdge(x, y);
		}		    
    for (int v = 0; v < n; v++) {
      if (!graph.vertices[v].visited) {
        graph.DFS(v);
      }
    }
    graph.getMinSccSize();
    // graph.printSccs();
		z--;
	}
	return 1;
}
