#include <iostream>
#include <vector>

using namespace std;

#define INF 2147483647;

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
      if (id == 0) {
        this->inS = true;
        this->distance = 0;
      } else {
        this->inS = false;
        this->distance = INF;
      }
    }

    void AddEdge(int dest, int weight)
    {
      this->edges.push_back(Edge(dest, weight));
    }
};

void FindMinDistance(vector<Vertex> *graph, int *minDistance, int *minVertex)
{
  for (int i = 0; i < graph->size(); i++)
  {
    if (!graph->at(i).visited && graph->at(i).inS && graph->at(i).distance < *minDistance)
    {
      *minDistance = graph->at(i).distance;
      *minVertex = i;
    }
  }
  if (*minVertex != -1)
  {
    graph->at(*minVertex).visited = true;
  }
}

void Dijkstra(vector<Vertex> *graph)
{ 
  vector<int> visitedVertices;
  int n = graph->size();
  int minDistance = INF;
  int minVertex = -1;
  while (true)
  {
    FindMinDistance(graph, &minDistance, &minVertex);
    // cout << "Min vertex: " << minVertex << "\n";
    if (minVertex == -1)
    {
      break;
    }
    for (int i = 0; i < graph->at(minVertex).edges.size(); i++)
    {
      // cout << "Edge to: " << graph->at(minVertex).edges[i].dest << "\n";
      int dest = graph->at(minVertex).edges[i].dest;
      int weight = graph->at(minVertex).edges[i].weight;
      if (graph->at(minVertex).distance + weight < graph->at(dest).distance)
      {
        // cout << "Updating distance of " << dest << " to " << graph->at(minVertex).distance + weight << "\n";
        graph->at(dest).distance = graph->at(minVertex).distance + weight;
        graph->at(dest).inS = true;
      }
    }
    minVertex = -1;
    minDistance = INF;
  }
} 

void PrintGraph(vector<Vertex> *graph)
{
  for (int i = 0; i < graph->size(); i++)
  {
    cout << "Vertex " << graph->at(i).id << ":\n";
    cout << "Distance: " << graph->at(i).distance << "\n";
    // cout << "Edges: ";
    // for (int j = 0; j < graph->at(i).edges.size(); j++)
    // {
    //   cout << graph->at(i).edges[j].dest << " ";
    // }
    cout << "\n";
  }
}

int main ()
{
  int z;
  cin >> z;
  while (z > 0)
  {
    int n, m;
    cin >> n >> m;
    vector<Vertex> graph;
    for (int i = 0; i < n; i++)
    {
      graph.push_back(Vertex(i));
    }
    for (int i = 0; i < m; i++)
    {
      int u, v, w;
      cin >> u >> v >> w;
      graph[u].AddEdge(v, w);
    }
    // PrintGraph(&graph);
    // cout << "\n";
    Dijkstra(&graph);
    // PrintGraph(&graph);
    // cout << "\n";
    if (graph[n - 1].inS == false) {
      cout << -1 << "\n";
    } else {
      cout << graph[n - 1].distance << "\n";
    }
    z--;
  }
}