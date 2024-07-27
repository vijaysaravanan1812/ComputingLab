#include <iostream>
#include <vector>

using namespace std;

vector<int> DFS_Rec(vector<int> adj[], int s, bool visited[], vector<int> result) {
    visited[s] = true;
    result.push_back(s);
    for (auto v : adj[s]) {
        if (!visited[v]) {
            return DFS_Rec(adj, v, visited, result);
        }
    }
    return result;
}

void DFS(vector<int> adj[], int v) {
    bool visited[v];
    for (int i = 0; i < v; i++) {
        visited[i] = false;
    }

    vector<vector<int>> WholeGraph;
    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            vector<int> Result;
            Result = DFS_Rec(adj, i, visited, Result);
            WholeGraph.push_back(Result);
        }
    }
    
    cout<<"Graph \n";
    for (int i = 0; i < WholeGraph.size(); i++) {
        for (int j = 0; j < WholeGraph[i].size(); j++) {
            cout << WholeGraph[i][j] << " ";
        }
        cout << "\n";
    }
}

void printGraph(vector<int> adj[], int v) {
    for (int i = 0; i < v; i++) {
        cout << i << "-->";
        for (auto x : adj[i]) {
            cout << x << "  "; 
        }
        cout << "\n";
    }
}

void addEdge(vector<int> adj[], int v, int u) {
    adj[v].push_back(u);
    adj[u].push_back(v);
}

int main() {
    // Test Case 1: Disconnected graph with two components
    {
        cout << "Test Case 1: Disconnected graph with two components\n";
        int v = 5;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 0, 2);
        addEdge(adj, 3, 4);
        printGraph(adj, v);
        DFS(adj, v);
        cout << endl;
    }

    // Test Case 2: Disconnected graph with three components
    {
        cout << "Test Case 2: Disconnected graph with three components\n";
        int v = 6;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 2, 3);
        addEdge(adj, 4, 5);
        printGraph(adj, v);
        DFS(adj, v);
        cout << endl;
    }

    // Test Case 3: Disconnected graph with isolated nodes
    {
        cout << "Test Case 3: Disconnected graph with isolated nodes\n";
        int v = 6;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 2, 3);
        // Nodes 4 and 5 are isolated
        printGraph(adj, v);
        DFS(adj, v);
        cout << endl;
    }

    // Test Case 4: Single component with one disconnected node
    {
        cout << "Test Case 4: Single component with one disconnected node\n";
        int v = 5;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 1, 2);
        addEdge(adj, 2, 3);
        // Node 4 is disconnected
        printGraph(adj, v);
        DFS(adj, v);
        cout << endl;
    }

    // Test Case 5: Multiple disconnected subgraphs
    {
        cout << "Test Case 5: Multiple disconnected subgraphs\n";
        int v = 8;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 0, 2);
        addEdge(adj, 3, 4);
        addEdge(adj, 5, 6);
        // Node 7 is isolated
        printGraph(adj, v);
        DFS(adj, v);
        cout << endl;
    }

    return 0;
}
