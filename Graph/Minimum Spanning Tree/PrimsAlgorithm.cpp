#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Edge;

int PrimsAlgorithm(vector<vector<Edge>>& Adj, int NumberOfVertex){
   
    priority_queue<Edge, vector<Edge>, greater<Edge>> MinHeap;
    vector<bool> visited(NumberOfVertex, false); // Use vector instead of array for visited
    int MinWeight[NumberOfVertex];
    int Parent[NumberOfVertex];
    fill(MinWeight, MinWeight + NumberOfVertex, INT_MAX);
    fill(Parent, Parent + NumberOfVertex , -1);

    
    MinHeap.push({0, 0}); // Start with node 0 and weight 0
    int sum = 0;
    while(!MinHeap.empty()){
        auto Edge = MinHeap.top();
        MinHeap.pop();
        int Weight = Edge.first;
        int Node = Edge.second;

        if(visited[Node])
            continue;
        
        visited[Node] = true;
        sum += Weight;
        
      
        for(auto u : Adj[Node]){
            int AdjacentNodeWeight = u.first;
            int AdjacentNode = u.second;
            if(!visited[AdjacentNode] && AdjacentNodeWeight <  MinWeight[AdjacentNode]){
                Parent[AdjacentNode] = Node; 
                MinWeight[AdjacentNode] = AdjacentNodeWeight; 
                MinHeap.push({AdjacentNodeWeight, AdjacentNode});
            }
        }
    } 
    cout<<"\nMST \n";
    // Printing the constructed MST
    cout << "Edge \tWeight\n";
    for (int i = 1; i < NumberOfVertex; ++i)
        cout << Parent[i] << " - " << i << "\t" << MinWeight[i] << "\n";

    return sum;
}

// Pass Adj by reference to modify the original list
void AddEdge(vector<vector<Edge>>& Adj, int U, int V, int Weight) {
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

    int mstWeight = PrimsAlgorithm(adjList, numVertices);
    cout<<"\n";
    cout << "Sum of weights in MST: " << mstWeight << "\n";

    return 0;
}
