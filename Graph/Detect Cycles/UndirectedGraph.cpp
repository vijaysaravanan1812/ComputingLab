#include <iostream>
#include <vector>

using namespace std;

bool DFS_Rec(vector<int> adj[], int s, bool visited[], int parent) {
    visited[s] = true;
    for (int i = 0; i < adj[s].size(); i++) {
        int NextNode = adj[s][i];
        if (!visited[NextNode]) {
            if (DFS_Rec(adj, NextNode, visited, s)) {
                return true;
            }
        } else if (NextNode != parent) {
            return true; // Cycle detected
        }
    }
    return false;
}

bool DFS(vector<int> adj[], int v) {
    bool visited[v];
    for (int i = 0; i < v; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            if (DFS_Rec(adj, i, visited, -1)) {
                return true;
            }
        }
    }
    return false;
}

void printGraph(vector<int> adj[], int v) {
    for (int i = 0; i < v; i++) {
        cout << " " << i << "-->";
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

void testCase1() {
    int v = 4;
    vector<int> adj[v];
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    cout << "Test Case 1 - Graph with a cycle: " << (DFS(adj, v) ? "Graph contains cycle" : "Graph doesn't contain cycle") << endl;
}

void testCase2() {
    int v = 4;
    vector<int> adj[v];
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    cout << "Test Case 2 - Graph without a cycle: " << (DFS(adj, v) ? "Graph contains cycle" : "Graph doesn't contain cycle") << endl;
}

void testCase3() {
    int v = 1;
    vector<int> adj[v];
    cout << "Test Case 3 - Single node without edges: " << (DFS(adj, v) ? "Graph contains cycle" : "Graph doesn't contain cycle") << endl;
}

void testCase4() {
    int v = 2;
    vector<int> adj[v];
    addEdge(adj, 0, 1);
    cout << "Test Case 4 - Two nodes with one edge: " << (DFS(adj, v) ? "Graph contains cycle" : "Graph doesn't contain cycle") << endl;
}

void testCase5() {
    int v = 6;
    vector<int> adj[v];
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 2);
    addEdge(adj, 3, 4);
    cout << "Test Case 5 - Disconnected graph: " << (DFS(adj, v) ? "Graph contains cycle" : "Graph doesn't contain cycle") << endl;
}

void testCase6() {
    int v = 10;
    vector<int> adj[v];
    addEdge(adj, 0, 1);
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);
    addEdge(adj, 4, 5);
    addEdge(adj, 5, 6);
    addEdge(adj, 6, 7);
    addEdge(adj, 7, 8);
    addEdge(adj, 8, 9);
    cout << "Test Case 6 - Large graph with no cycle: " << (DFS(adj, v) ? "Graph contains cycle" : "Graph doesn't contain cycle") << endl;
}

int main() {
    testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();
    testCase6();
    return 0;
}
