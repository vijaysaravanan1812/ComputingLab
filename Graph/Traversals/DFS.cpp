#include <iostream>
#include <vector>
#include <cstring> // for memset

using namespace std;

// DFS recursive function
vector<int> DFS_Rec(vector<int> adj[], int v, bool visited[], vector<int> &DFS_Traversal) {
    visited[v] = true;
    DFS_Traversal.push_back(v);
    for (auto u : adj[v]) {
        if (!visited[u]) {
            DFS_Rec(adj, u, visited, DFS_Traversal);
        }
    }
    return DFS_Traversal;
}

// DFS function
void DFS(vector<int> adj[], int v, int s) {
    bool visited[v];
    memset(visited, false, sizeof(visited)); // Initialize visited array to false

    vector<int> Result;
    Result = DFS_Rec(adj, s, visited, Result);
    for (int i = 0; i < Result.size(); i++) {
        cout << Result[i] << " ";
    }
    cout << "\n";
}

// Function to add an edge
void addEdge(vector<int> adj[], int v, int u) {
    adj[v].push_back(u);
    adj[u].push_back(v); 
}

// Function to print the adjacency list
void PrintEdge(vector<int> adj[], int v) {
    for (int i = 0; i < v; i++) {
        cout << i << " ->"; 
        for (auto u : adj[i]) {
            cout << " " << u << " ";
        }
        cout << "\n";
    }
}

int main() {
    // Test Case 1: Basic Test
    {
        int v = 5;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 1, 4);
        addEdge(adj, 1, 3);
        addEdge(adj, 2, 0);

        cout << "Test Case 1: Basic Test" << endl;
        cout << "Expected: 0 1 4 3 2" << endl;
        cout << "Actual: ";
        DFS(adj, v, 0);
        cout << endl;
    }

    // Test Case 2: Disconnected Graph
    {
        int v = 5;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 2, 3);
        addEdge(adj, 3, 4);

        cout << "Test Case 2: Disconnected Graph" << endl;
        cout << "Expected from 0: 0 1" << endl;
        cout << "Actual from 0: ";
        DFS(adj, v, 0);
        cout << endl;

        cout << "Expected from 2: 2 3 4" << endl;
        cout << "Actual from 2: ";
        DFS(adj, v, 2);
        cout << endl;
    }

    // Test Case 3: Cyclic Graph
    {
        int v = 4;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 1, 2);
        addEdge(adj, 2, 0);
        addEdge(adj, 2, 3);

        cout << "Test Case 3: Cyclic Graph" << endl;
        cout << "Expected: 0 1 2 3" << endl;
        cout << "Actual: ";
        DFS(adj, v, 0);
        cout << endl;
    }

    // Test Case 4: Single Node
    {
        int v = 1;
        vector<int> adj[v];

        cout << "Test Case 4: Single Node" << endl;
        cout << "Expected: 0" << endl;
        cout << "Actual: ";
        DFS(adj, v, 0);
        cout << endl;
    }

    // Test Case 5: Complete Graph
    {
        int v = 4;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 0, 2);
        addEdge(adj, 0, 3);
        addEdge(adj, 1, 2);
        addEdge(adj, 1, 3);
        addEdge(adj, 2, 3);

        cout << "Test Case 5: Complete Graph" << endl;
        cout << "Expected: 0 1 2 3" << endl;
        cout << "Actual: ";
        DFS(adj, v, 0);
        cout << endl;
    }

    return 0;
}
