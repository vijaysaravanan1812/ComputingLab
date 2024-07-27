#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Edge;

void TopologicalSortUsingDFS(vector<vector<Edge>> &Adj, bool visited[], int Source, stack<int> &Stack) {
    visited[Source] = true;
    for (auto u : Adj[Source]) {
        int Vertex = u.second;
        if (!visited[Vertex]) {
            TopologicalSortUsingDFS(Adj, visited, Vertex, Stack);
        }
    }
    Stack.push(Source);
}

stack<int> TopologicalSort(vector<vector<Edge>> &Adj, int V) {
    bool visited[V];
    stack<int> Stack;
    fill(visited, visited + V, false);

    for (int i = 1; i < i%V; i++) {
        if (!visited[i]) {
            TopologicalSortUsingDFS(Adj, visited, i, Stack);
        }
    }


    return Stack;
}

void ReverseGraph(vector<vector<Edge>> &Adj, vector<vector<Edge>> &AdjTranspose, int V) {
    AdjTranspose.resize(V);
    for (int i = 0; i < V; i++) {
        for (auto u : Adj[i]) {
            int weight = u.first;
            int vertex = u.second;
            AdjTranspose[vertex].push_back({weight, i});
        }
    }
}

void DFS(vector<vector<Edge>> &Adj, bool visited[], int Source) {
    visited[Source] = true;
    for (auto u : Adj[Source]) {
        int Vertex = u.second;
        if (!visited[Vertex]) {
            DFS(Adj, visited, Vertex);
        }
    }
}

int KosarajuAlgorithm(vector<vector<Edge>> &Adj, int V) {
    vector<vector<Edge>> AdjTranspose;
    auto Stack = TopologicalSort(Adj, V);
    ReverseGraph(Adj, AdjTranspose, V);

    int StronglyConnectedComponent = 0;
    bool visited[V];
    fill(visited, visited + V, false);
    while(!Stack.empty()) {
        int node = Stack.top();
        cout<<node<<" ";
        Stack.pop();
        if (!visited[node]) {
            StronglyConnectedComponent++;
            DFS(AdjTranspose, visited, node);
        }
    }
    cout<<"\n";

    return StronglyConnectedComponent;
}

// Pass Adj by reference to modify the original list
void AddEdge(vector<vector<Edge>>& Adj, int U, int V, int Weight) {
    Adj[U].push_back({Weight, V});
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
    int numVertices = 8;

    vector<vector<Edge>> adjList(numVertices);

    // Adding edges
    AddEdge(adjList, 0, 1, 2);
    AddEdge(adjList, 1, 2, 6);
    AddEdge(adjList, 2, 0, 3);
    AddEdge(adjList, 1, 3, 8);
    AddEdge(adjList, 3, 4, 5);
    AddEdge(adjList, 4, 3, 7);
    AddEdge(adjList, 3, 5, 9);
    AddEdge(adjList, 3, 6, 9);
    AddEdge(adjList, 6, 5, 9);
    AddEdge(adjList, 6, 7, 9);
    AddEdge(adjList, 7, 6, 9);

    // Print the graph
    cout << "Graph \n";
    PrintGraph(adjList, numVertices);

    cout << "Number of Strongly Connected Components: " << KosarajuAlgorithm(adjList, numVertices) << "\n";

    return 0;
}
