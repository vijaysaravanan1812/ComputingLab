
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Edge;

int* BellmanFordAlgorithm(vector<vector<Edge>> &Adj, int V, int Source)
{
    int* Dist = (int * )malloc(sizeof(int) * V);
    fill(Dist, Dist + V, INT_MAX);
    Dist[Source] = 0;

    for (int j = 0; j < V - 1; j++)
    {
        for (int i = 0; i < V; i++)
        {
            for (auto u : Adj[i])
            {
                int Weight = u.first;
                int Vertex = u.second;
                if (Dist[i] != INT_MAX && Dist[Vertex] > Dist[i] + Weight)
                {
                    Dist[Vertex] = Dist[i] + Weight;
                }
            }
        }
    }

    for (int i = 0; i < V; i++)
    {
        for (auto u : Adj[i])
        {
            int Weight = u.first;
            int Vertex = u.second;
            if (Dist[i] != INT_MAX && Dist[Vertex] > Dist[i] + Weight)
            {
                return NULL;
            }
        }
    }

    return Dist;
}

// Pass Adj by reference to modify the original list
void AddEdge(vector<vector<Edge>> &Adj, int U, int V, int Weight)
{
    Adj[U].push_back({Weight, V});
}

void PrintGraph(const vector<vector<Edge>> &Adj, int NumberOfVertex)
{
    for (int i = 0; i < NumberOfVertex; i++)
    {
        cout << "Vertex " << i << " : \n";
        for (const auto &u : Adj[i])
        {
            int Weight = u.first;
            int Node = u.second;
            cout << "\tWeight: " << Weight << " Node: " << Node << "\n";
        }
    }
}

int main()
{
    int numVertices = 8;

    vector<vector<Edge>> adjList(numVertices);

    // Adding edges
    AddEdge(adjList, 0, 1, 2);
    AddEdge(adjList, 1, 2, 4);
    AddEdge(adjList, 2, 0, 7);
    AddEdge(adjList, 1, 3, 5);
    AddEdge(adjList, 3, 4, 3);
    AddEdge(adjList, 4, 3, 7);
    AddEdge(adjList, 3, 5, 8);
    AddEdge(adjList, 3, 6, 1);
    AddEdge(adjList, 6, 5, 5);
    AddEdge(adjList, 6, 7, 1);
    AddEdge(adjList, 7, 6, 5);

    // Print the graph
    cout << "Graph \n";
    PrintGraph(adjList, numVertices);

    int *Dist = BellmanFordAlgorithm(adjList , numVertices , 0);
    for(int i = 0 ; i  < numVertices ; i++){
        cout<<Dist[i]<<" ";
    }
    cout<<"\n";

    return 0;
}