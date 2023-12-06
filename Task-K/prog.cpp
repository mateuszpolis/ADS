#include <iostream>
#include <vector>

using namespace std;

#define INF 2147483647

class Edge
{
public:
    int dest;
    int weight;

    Edge(int dest, int weight)
    {
        this->dest = dest;
        this->weight = weight;
    }
};

class Vertex
{
public:
    int id;
    bool visited;
    bool inS;
    int distance;
    vector<Edge> edges;

    Vertex(int id)
    {
        this->id = id;
        this->visited = false;
        if (id == 0)
        {
            this->inS = true;
            this->distance = 0;
        }
        else
        {
            this->inS = false;
            this->distance = INF;
        }
    }

    void AddEdge(int dest, int weight)
    {
        this->edges.push_back(Edge(dest, weight));
    }

    bool operator<(const Vertex &other) const
    {
        if (this->visited == false)
        {
            if (other.visited == true)
            {
                return true;
            }
            if (this->inS == true)
            {
                if (other.inS == false)
                {
                    return true;
                }
                if (this->distance < other.distance)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};

class Graph
{
public:
    vector<Vertex> vertices;
    vector<Vertex *> heap;

    Graph(int n)
    {
        heap = vector<Vertex *>(n + 1, nullptr);
        for (int i = 1; i < n + 1; i++)
        {
            Vertex *newVertex = new Vertex(i - 1);
            this->vertices.push_back(*newVertex);
            heap[i] = newVertex;
        }
    }

    void AddEdge(int u, int v, int weight)
    {
        this->vertices[u].AddEdge(v, weight);
    }

    void DownHeap()
    {
        int index = 1;
        while (index * 2 < heap.size())
        {
            int id = (*heap[index]).id;
            int left = (*heap[index * 2]).id;            
            if (index * 2 + 1 >= heap.size())
            {
                if (vertices[id] < vertices[left])
                {
                    break;
                }
                swap(heap[index * 2], heap[index]);
                index = index * 2;
                continue;
            }
            else
            {              
                int right = (*heap[index * 2 + 1]).id;            
                if (vertices[id] < vertices[left] && vertices[id] < vertices[right])
                {
                    break;
                }
                else if (vertices[left] < vertices[right])
                {
                    swap(heap[index * 2], heap[index]);
                    index = index * 2;
                }
                else
                {
                    swap(heap[index * 2 + 1], heap[index]);
                    index = index * 2 + 1;
                }
            }
        }
    }
};

void Dijkstra(Graph *graph)
{
    while (true)
    {    
        int topId = (*graph->heap[1]).id;
        if (graph->vertices[topId].visited || !graph->vertices[topId].inS)
        {
            break;
        }
        // cout << "Vertex: " << graph->vertices[topId].id << "\n";        
        for (int i = 0; i < graph->vertices[topId].edges.size(); i++)
        {
            // cout<< "-> " << graph->vertices[topId].edges[i].dest << ", weight: " << graph->vertices[topId].edges[i].weight << "\n";
            int dest = graph->vertices[topId].edges[i].dest;
            int weight = graph->vertices[topId].edges[i].weight;
            if (graph->vertices[topId].distance + weight < graph->vertices[dest].distance)
            {
                graph->vertices[dest].distance = graph->vertices[topId].distance + weight;
                graph->vertices[dest].inS = true;
                if (dest == graph->vertices.size() - 1)
                {
                    break;
                }
            }
        }
        graph->vertices[topId].visited = true;        
        graph->DownHeap();
    }
}

void PrintGraph(vector<Vertex> *graph)
{
    for (int i = 0; i < graph->size(); i++)
    {
        cout << "Vertex " << graph->at(i).id << ":\n";
        cout << "Distance: " << graph->at(i).distance << "\n";
        for (int j = 0; j < graph->at(i).edges.size(); j++) {
          cout << "\tEdge: " << graph->at(i).edges[j].dest << " " << graph->at(i).edges[j].weight << "\n";
        }
        cout << "\n";
    }
}

int main()
{
    int z;
    cin >> z;
    while (z > 0)
    {
        int n, m;
        cin >> n >> m;
        Graph graph(n);
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            graph.AddEdge(u, v, w);
        }
        // PrintGraph(&graph.vertices);
        // for (int i = 1; i < n + 1; i++) {
        //   int topId = (*graph.heap[i]).id;
        //   cout << "Vertex: " << graph.vertices[topId].id << "\n";
        // }
        Dijkstra(&graph);
        if (graph.vertices[n - 1].inS)
        {
            cout << graph.vertices[n - 1].distance << "\n";
        }
        else
        {
            cout << "-1\n";
        }
        z--;
    }
}
