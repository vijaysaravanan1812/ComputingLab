#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<int> TopologicalSorting(vector<int> adj[], int v){
    int Indegree[v]; 
    vector<int> TopologicalArray;
    for(int i = 0; i < v ; i++){
        Indegree[i] = 0;
    }

    for(int i = 0 ; i < v ; i++){
        for(auto u : adj[i]){
            Indegree[u] += 1;
        }
    }

    queue<int> TopologicalSortingQueue;
    for(int i = 0 ; i < v ; i++){
        if(Indegree[i] == 0){
            TopologicalSortingQueue.push(i);
        }
    }

    while(!TopologicalSortingQueue.empty()){
        int Node = TopologicalSortingQueue.front();
        TopologicalArray.push_back(Node);
        TopologicalSortingQueue.pop();
        for(auto u : adj[Node]){
            Indegree[u]--;
            if(Indegree[u] ==  0){
                TopologicalSortingQueue.push(u);
            }
        }
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
    // Test case 1
    int V1 = 4;
    vector<int> adj1[V1];
    addEdge(adj1, 0, 1);
    addEdge(adj1, 1, 2);
    addEdge(adj1, 0, 2);
    addEdge(adj1, 1, 3);
    addEdge(adj1, 2, 3);

    vector<int> TopologicalSort1 = TopologicalSorting(adj1, V1);
    cout << "Topological Sort for Test Case 1: ";
    printTopologicalSort(TopologicalSort1);

    // Test case 2
    int V2 = 6;
    vector<int> adj2[V2];
    addEdge(adj2, 5, 2);
    addEdge(adj2, 5, 0);
    addEdge(adj2, 4, 0);
    addEdge(adj2, 4, 1);
    addEdge(adj2, 2, 3);
    addEdge(adj2, 3, 1);

    vector<int> TopologicalSort2 = TopologicalSorting(adj2, V2);
    cout << "Topological Sort for Test Case 2: ";
    printTopologicalSort(TopologicalSort2);

    // Test case 3
    int V3 = 3;
    vector<int> adj3[V3];
    addEdge(adj3, 0, 1);
    addEdge(adj3, 1, 2);

    vector<int> TopologicalSort3 = TopologicalSorting(adj3, V3);
    cout << "Topological Sort for Test Case 3: ";
    printTopologicalSort(TopologicalSort3);

    // Test case 4
    int V4 = 5;
    vector<int> adj4[V4];
    addEdge(adj4, 0, 1);
    addEdge(adj4, 0, 2);
    addEdge(adj4, 1, 3);
    addEdge(adj4, 2, 3);
    addEdge(adj4, 3, 4);

    vector<int> TopologicalSort4 = TopologicalSorting(adj4, V4);
    cout << "Topological Sort for Test Case 4: ";
    printTopologicalSort(TopologicalSort4);

    return 0;
}
