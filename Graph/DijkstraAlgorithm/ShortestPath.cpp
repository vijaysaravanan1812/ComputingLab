
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Edge;

int* DijkstraAlgorithm(vector<vector<Edge>> Adj, int V, int Source){
    priority_queue<Edge, vector<Edge> , greater<Edge>> MinHeap;
    bool Visited[V] ;
    int *Dist = (int *)malloc(sizeof(int) * V);
    fill(Visited , Visited + V, false);
    fill(Dist , Dist + V, 1e9);   
    Dist[Source] = 0; 

    MinHeap.push({0 , Source});

    while(!MinHeap.empty()){
        auto Node = MinHeap.top();
        MinHeap.pop();
        Visited[Node.second] = true;
        int Weight = Node.first;
        int Vertex = Node.second;
        for(auto u : Adj[Vertex]){
            int AdjacentWeight = u.first;
            int AdjacentVertex = u.second;
            if(!Visited[AdjacentVertex] && Dist[AdjacentVertex] > Dist[Vertex] +   AdjacentWeight ){
                Dist[AdjacentVertex] = Dist[Vertex] +   AdjacentWeight  ;
                MinHeap.push({Dist[AdjacentVertex] , AdjacentVertex});
            }
            
        }
    }

    return Dist;


} 


// Pass Adj by reference to modify the original list
void AddEdge(vector<vector<Edge>> &Adj, int U, int V, int Weight) {
    Adj[U].push_back({Weight, V});
    Adj[V].push_back({Weight, U});
}

void PrintGraph(const vector<vector<Edge>>& Adj, int NumberOfVertex) {
    for (int i = 0; i < NumberOfVertex; i++) {
        cout << "Vertex " << i << " : \n";
        for (const auto& u : Adj[i]) {
            int Weight = u.first;
            int Node = u.second;
            cout << "\tWeight: " << Weight << " Node: " << Node << "\n";
        }
    }
}

int main() {
    int numVertices = 5;

    vector<vector<Edge>> adjList(numVertices);

    // Adding edges
    AddEdge(adjList, 0, 1, 2);
    AddEdge(adjList, 0, 3, 6);
    AddEdge(adjList, 1, 2, 3);
    AddEdge(adjList, 1, 3, 8);
    AddEdge(adjList, 1, 4, 5);
    AddEdge(adjList, 2, 4, 7);
    AddEdge(adjList, 3, 4, 9);

    // Print the graph
    cout<<"Graph \n";
    PrintGraph(adjList, numVertices);
   
    int *Distance = DijkstraAlgorithm(adjList, numVertices, 0);
    for(int i = 0 ; i < numVertices; i++ ){
        cout<<Distance[i]<<" ";
    }
    cout<<"\n";

    return 0;
}
