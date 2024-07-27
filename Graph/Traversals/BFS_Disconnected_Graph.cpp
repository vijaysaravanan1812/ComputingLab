#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void BFS(vector<int> adj[], int v, bool visited[]) {
    queue<int> BFS_Traversal;
    visited[v] = true;
    BFS_Traversal.push(v);

    while (!BFS_Traversal.empty()) {
        int Node = BFS_Traversal.front();
        BFS_Traversal.pop();
        cout << " " << Node << " ";
        for (auto neighbor : adj[Node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                BFS_Traversal.push(neighbor);
            }
        }
    }
}

void BFS_Disconnected(vector<int> adj[], int v) {
    bool visited[v];
    for (int i = 0; i < v; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            BFS(adj, i, visited);
            cout << "\n";
        }
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
        cout << "BFS for disconnected graph:\n";
        BFS_Disconnected(adj, v);
        cout << "-------------------------\n";
    }

    // Test Case 2: Multiple disconnected components
    {
        cout << "Test Case 2: Multiple disconnected components\n";
        int v = 6;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 2, 3);
        addEdge(adj, 4, 5);
        printGraph(adj, v);
        cout << "BFS for disconnected graph:\n";
        BFS_Disconnected(adj, v);
        cout << "-------------------------\n";
    }

    // Test Case 3: Graph with cycles and disconnected components
    {
        cout << "Test Case 3: Graph with cycles and disconnected components\n";
        int v = 6;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 1, 2);
        addEdge(adj, 2, 0); // Cycle
        addEdge(adj, 3, 4);
        addEdge(adj, 4, 5);
        addEdge(adj, 5, 3); // Cycle
        printGraph(adj, v);
        cout << "BFS for disconnected graph:\n";
        BFS_Disconnected(adj, v);
        cout << "-------------------------\n";
    }

    // Test Case 4: Disconnected graph with isolated nodes
    {
        cout << "Test Case 4: Disconnected graph with isolated nodes\n";
        int v = 7;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 2, 3);
        // Nodes 4, 5, 6 are isolated
        printGraph(adj, v);
        cout << "BFS for disconnected graph:\n";
        BFS_Disconnected(adj, v);
        cout << "-------------------------\n";
    }

    // Test Case 5: Single node graph
    {
        cout << "Test Case 5: Single node graph\n";
        int v = 1;
        vector<int> adj[v];
        printGraph(adj, v);
        cout << "BFS for disconnected graph:\n";
        BFS_Disconnected(adj, v);
        cout << "-------------------------\n";
    }

    // Test Case 6: Simple linear graph (not disconnected, but for completeness)
    {
        cout << "Test Case 6: Simple linear graph\n";
        int v = 4;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 1, 2);
        addEdge(adj, 2, 3);
        printGraph(adj, v);
        cout << "BFS for disconnected graph:\n";
        BFS_Disconnected(adj, v);
        cout << "-------------------------\n";
    }

    return 0;
}
