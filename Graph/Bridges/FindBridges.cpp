
#include<bits/stdc++.h>

using namespace std;

typedef pair<int , int> Edge;

void DFS(vector<vector<Edge>> &Adj, int Source, vector<Edge> &Bridge, 
            int Parent, int NumberOfVertices, bool visited[], int NumberOfSteps[], int LowerNumberOfSteps[], int &timer){
    int Node = Source;
    NumberOfSteps[Node] = timer;
    LowerNumberOfSteps[Node] = timer;
    timer++;
    visited[Node] = true;
    for(auto u : Adj[Node]){
        int AdjacentWeight = u.first;
        int AdjacentNode = u.second;
        if(AdjacentNode == Parent)
            continue;
        if(!visited[AdjacentNode]){
            DFS(Adj, AdjacentNode , Bridge, Node, NumberOfVertices, visited, NumberOfSteps, LowerNumberOfSteps, timer);
            LowerNumberOfSteps[Node] = min(LowerNumberOfSteps[AdjacentNode] , LowerNumberOfSteps[Node]);
            if(LowerNumberOfSteps[AdjacentNode] > NumberOfSteps[Node]){
                Bridge.push_back({Node, AdjacentNode});
            }
        }else{
            LowerNumberOfSteps[Node] = min(LowerNumberOfSteps[AdjacentNode] , LowerNumberOfSteps[Node]);
        }
    }
}

vector<Edge> FindBridges(vector<vector<Edge>> &Adj , int NumberOfVertices ){
    int NumberOfSteps[NumberOfVertices];
    int timer= 1;
    int LowerNumberOfSteps[NumberOfVertices];
    bool visited[NumberOfVertices];
    fill(visited , visited + NumberOfVertices, false);
    vector<Edge> Bridges;
    DFS(Adj , 0, Bridges , -1, NumberOfVertices, visited, NumberOfSteps, LowerNumberOfSteps, timer );
    return Bridges;
}

void AddEdge(vector<vector<Edge>> &Adj, int V, int U, int Weight){
    Adj[V].push_back({Weight , U});
    Adj[U].push_back({Weight , V});
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


int main(){

     int numVertices = 8;

    vector<vector<Edge>> adjList(numVertices);

    // Adding edges
    AddEdge(adjList, 0, 1, 1);
    AddEdge(adjList, 1, 2, 1);
    AddEdge(adjList, 2, 0, 1);
    AddEdge(adjList, 1, 3, 1);
    AddEdge(adjList, 3, 4, 1);
    AddEdge(adjList, 3, 5, 1);
    AddEdge(adjList, 3, 6, 1);
    AddEdge(adjList, 6, 7, 1);
    AddEdge(adjList, 4, 7, 1);
    

    // Print the graph
    cout << "Graph \n";
    PrintGraph(adjList, numVertices);

    vector<Edge> Bridge = FindBridges(adjList, numVertices);

    printf("Bridges \n");
    for(auto i : Bridge){
        cout<<i.first<<"---"<<i.second<<"\n";
    }
    cout<<"\n";
    
    return 0;
}