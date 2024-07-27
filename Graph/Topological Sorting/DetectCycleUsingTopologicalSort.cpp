#include<iostream>
#include<vector>
#include<queue>

using namespace std;

bool TopologicalSorting(vector<int> adj[], int v) {
    int Indegree[v]; 
    int CountZeroIndegreeVertex = 0;

    for(int i = 0; i < v ; i++) {
        Indegree[i] = 0;
    }

    for(int i = 0 ; i < v ; i++) {
        for(auto u : adj[i]) {
            Indegree[u] += 1;
        }
    }

    queue<int> TopologicalSortingQueue;
    for(int i = 0 ; i < v ; i++) {
        if(Indegree[i] == 0) {
            TopologicalSortingQueue.push(i);
        }
    }

    while(!TopologicalSortingQueue.empty()) {
        int Node = TopologicalSortingQueue.front();
        TopologicalSortingQueue.pop();

        for(auto u : adj[Node]) {
            Indegree[u]--;
            if(Indegree[u] ==  0) {
                TopologicalSortingQueue.push(u);
            }
        }
        CountZeroIndegreeVertex++;
    }

    // If all vertices are not visited, then there is a cycle
    return (CountZeroIndegreeVertex != v);
}

void addEdge(vector<int> adj[], int v, int u) {
    adj[v].push_back(u);
}

int main() {
    // Test case 1: No cycle
    int V1 = 4;
    vector<int> adj1[V1];
    addEdge(adj1, 0, 1);
    addEdge(adj1, 1, 2);
    addEdge(adj1, 0, 2);
    addEdge(adj1, 1, 3);
    addEdge(adj1, 2, 3);

    cout << "Graph 1 has cycle: " << (TopologicalSorting(adj1, V1) ? "Yes" : "No") << endl;

    // Test case 2: Graph with a cycle
    int V2 = 4;
    vector<int> adj2[V2];
    addEdge(adj2, 0, 1);
    addEdge(adj2, 1, 2);
    addEdge(adj2, 2, 0); // This edge creates a cycle
    addEdge(adj2, 2, 3);

    cout << "Graph 2 has cycle: " << (TopologicalSorting(adj2, V2) ? "Yes" : "No") << endl;

    // Test case 3: Larger graph with no cycle
    int V3 = 6;
    vector<int> adj3[V3];
    addEdge(adj3, 5, 2);
    addEdge(adj3, 5, 0);
    addEdge(adj3, 4, 0);
    addEdge(adj3, 4, 1);
    addEdge(adj3, 2, 3);
    addEdge(adj3, 3, 1);

    cout << "Graph 3 has cycle: " << (TopologicalSorting(adj3, V3) ? "Yes" : "No") << endl;

    // Test case 4: Graph with no edges
    int V4 = 3;
    vector<int> adj4[V4];
    // No edges added

    cout << "Graph 4 has cycle: " << (TopologicalSorting(adj4, V4) ? "Yes" : "No") << endl;

    return 0;
}
