#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void DFS_Rec(vector<int> adj[], int s, stack<int> &TopologicalStack, vector<bool> &visited) {
    visited[s] = true;
    for(auto u : adj[s]) {
        if(visited[u] == false)
            DFS_Rec(adj, u, TopologicalStack, visited);
    }
    TopologicalStack.push(s);
}

vector<int> DFS(vector<int> adj[], int v) {
    stack<int> TopologicalStack;
    vector<bool> visited(v, false);

    for(int i = 0; i < v; i++) {
        if(visited[i] == false)
            DFS_Rec(adj, i, TopologicalStack, visited);
    }

    vector<int> TopologicalArray;
    while(!TopologicalStack.empty()) {
        TopologicalArray.push_back(TopologicalStack.top());
        TopologicalStack.pop();
    }

    return TopologicalArray;
}

void addEdge(vector<int> adj[], int v, int u) {
    adj[v].push_back(u);
}

void printTopologicalSort(const vector<int>& TopologicalSort) {
    for(int i = 0; i < TopologicalSort.size(); i++) {
        cout << TopologicalSort[i] << " ";
    }
    cout << "\n";
}

int main() {
    // Test case 1: Simple DAG
    int V1 = 4;
    vector<int> adj1[V1];
    addEdge(adj1, 0, 1);
    addEdge(adj1, 1, 2);
    addEdge(adj1, 0, 2);
    addEdge(adj1, 1, 3);
    addEdge(adj1, 2, 3);

    cout << "Topological Sort for Test Case 1: ";
    vector<int> TopologicalArray1 = DFS(adj1, V1);
    printTopologicalSort(TopologicalArray1);

    // Test case 2: Larger DAG with multiple valid topological orders
    int V2 = 6;
    vector<int> adj2[V2];
    addEdge(adj2, 5, 2);
    addEdge(adj2, 5, 0);
    addEdge(adj2, 4, 0);
    addEdge(adj2, 4, 1);
    addEdge(adj2, 2, 3);
    addEdge(adj2, 3, 1);

    cout << "Topological Sort for Test Case 2: ";
    vector<int> TopologicalArray2 = DFS(adj2, V2);
    printTopologicalSort(TopologicalArray2);

    // Test case 3: Graph with no edges
    int V3 = 3;
    vector<int> adj3[V3];
    // No edges added

    cout << "Topological Sort for Test Case 3: ";
    vector<int> TopologicalArray3 = DFS(adj3, V3);
    printTopologicalSort(TopologicalArray3);

    // Test case 4: Single node
    int V4 = 1;
    vector<int> adj4[V4];
    // No edges needed

    cout << "Topological Sort for Test Case 4: ";
    vector<int> TopologicalArray4 = DFS(adj4, V4);
    printTopologicalSort(TopologicalArray4);

    return 0;
}
