#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void BFS(vector<int> adj[], int v, int s) {
    vector<bool> visited(v, false);

    queue<int> BFS_Traversal;
    visited[s] = true;
    BFS_Traversal.push(s);

    while (!BFS_Traversal.empty()) {
        int Node = BFS_Traversal.front();
        BFS_Traversal.pop();
        cout << Node << " ";
        
        for (auto v : adj[Node]) {
            if (!visited[v]) {
                visited[v] = true;
                BFS_Traversal.push(v);
            }
        }
    }
    cout << "\n";
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
    // Test Case 1: Simple linear graph
    {
        cout << "Test Case 1: Simple linear graph\n";
        int v = 4;
        vector<int> adj[v];
        addEdge(adj, 0 ,1);
        addEdge(adj , 1, 2);
        addEdge(adj, 2, 3);
        printGraph(adj, v);
        cout << "BFS starting from node 0:\n";
        BFS(adj, v, 0);
        cout << "-------------------------\n";
    }

    // Test Case 2: Complete graph
    {
        cout << "Test Case 2: Complete graph\n";
        int v = 4;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 0, 2);
        addEdge(adj, 0, 3);
        addEdge(adj, 1, 2);
        addEdge(adj, 1, 3);
        addEdge(adj, 2, 3);
        printGraph(adj, v);
        cout << "BFS starting from node 0:\n";
        BFS(adj, v, 0);
        cout << "-------------------------\n";
    }

    // Test Case 3: Disconnected graph
    {
        cout << "Test Case 3: Disconnected graph\n";
        int v = 5;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 0, 2);
        addEdge(adj, 3, 4);
        printGraph(adj, v);
        cout << "BFS starting from node 0:\n";
        BFS(adj, v, 0);
        cout << "BFS starting from node 3:\n";
        BFS(adj, v, 3);
        cout << "-------------------------\n";
    }

    // Test Case 4: Graph with cycles
    {
        cout << "Test Case 4: Graph with cycles\n";
        int v = 4;
        vector<int> adj[v];
        addEdge(adj, 0, 1);
        addEdge(adj, 1, 2);
        addEdge(adj, 2, 0);
        addEdge(adj, 2, 3);
        printGraph(adj, v);
        cout << "BFS starting from node 0:\n";
        BFS(adj, v, 0);
        cout << "-------------------------\n";
    }

    // Test Case 5: Single node graph
    {
        cout << "Test Case 5: Single node graph\n";
        int v = 1;
        vector<int> adj[v];
        printGraph(adj, v);
        cout << "BFS starting from node 0:\n";
        BFS(adj, v, 0);
        cout << "-------------------------\n";
    }

    return 0;
}
