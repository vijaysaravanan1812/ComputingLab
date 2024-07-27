#include<iostream>
#include<vector>

using namespace std;

bool DFS_Rec(vector<int> adj[], int s, bool Visited[], bool RecursionStack[]){
    Visited[s] = true;
    RecursionStack[s] = true;

    for(auto u : adj[s]){
        if(Visited[u] == false){
            if(DFS_Rec(adj, u, Visited, RecursionStack)){
                return true;
            }
        }else if(RecursionStack[u] == true){
            return true;
        }
    }

    RecursionStack[s] = false;
    return false;
}

bool DFS(vector<int> adj[], int v){
    bool RecursionStack[v];
    bool Visited[v];
    for(int i = 0 ; i < v ; i ++){
        RecursionStack[i] = false;
        Visited[i] = false;
    }

    for(int i = 0 ; i < v; i++){
        if(Visited[i] == false){
            if(DFS_Rec(adj, i, Visited, RecursionStack)){
                return true;
            }
        }
    }

    return false;
}

void addEdge(vector<int> adj[], int v, int u) {
    adj[v].push_back(u);
}

int main() {
    int V1 = 4;
    vector<int> adj1[V1];
    addEdge(adj1, 0, 1);
    addEdge(adj1, 1, 2);
    addEdge(adj1, 2, 0);
    addEdge(adj1, 2, 3);
    addEdge(adj1, 3, 3);
    cout << "Graph 1 has cycle: " << (DFS(adj1, V1) ? "Yes" : "No") << endl;

    int V2 = 3;
    vector<int> adj2[V2];
    addEdge(adj2, 0, 1);
    addEdge(adj2, 1, 2);
    cout << "Graph 2 has cycle: " << (DFS(adj2, V2) ? "Yes" : "No") << endl;

    int V3 = 6;
    vector<int> adj3[V3];
    addEdge(adj3, 0, 1);
    addEdge(adj3, 1, 2);
    addEdge(adj3, 2, 3);
    addEdge(adj3, 3, 4);
    addEdge(adj3, 4, 5);
    addEdge(adj3, 5, 3);
    cout << "Graph 3 has cycle: " << (DFS(adj3, V3) ? "Yes" : "No") << endl;

    int V4 = 5;
    vector<int> adj4[V4];
    addEdge(adj4, 0, 1);
    addEdge(adj4, 1, 2);
    addEdge(adj4, 2, 3);
    addEdge(adj4, 3, 4);
    cout << "Graph 4 has cycle: " << (DFS(adj4, V4) ? "Yes" : "No") << endl;

    return 0;
}
