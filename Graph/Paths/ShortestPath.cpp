#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

vector<int> BFS(vector<int> adj[], int v, int s){
    queue<int> LevelQueue;
    vector<int> Distance(v , INT_MAX);
    vector<int> visited(v , false);

    LevelQueue.push(s);
    Distance[s] = 0;

    while(!LevelQueue.empty()){
        int Node = LevelQueue.front();
        cout << Node << " ";
        visited[Node] = true;
        LevelQueue.pop();
        for(auto u : adj[Node]){
            if(!visited[u]){
                Distance[u] = Distance[Node] + 1; 
                LevelQueue.push(u);
                visited[u] = true;  // Mark as visited when enqueued to avoid repeated enqueueing
            }
        }
    }

    return Distance;
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

void runTestCase(const string& description, int v, vector<pair<int, int>> edges, int startNode) {
    cout << description << endl;
    vector<int> adj[v];
    for (auto edge : edges) {
        addEdge(adj, edge.first, edge.second);
    }
    printGraph(adj, v);
    
    vector<int> distance = BFS(adj, v, startNode);
    cout << "\nDistance:\n";
    for (auto element : distance) {
        cout << element << " ";
    }
    cout << "\n\n";
}

int main() {
    // Test Case 1: Simple linear graph
    runTestCase(
        "Test Case 1: Simple linear graph",
        4,
        {{0, 1}, {1, 2}, {2, 3}},
        0
    );

    // Test Case 2: Disconnected graph
    runTestCase(
        "Test Case 2: Disconnected graph",
        6,
        {{0, 1}, {1, 2}, {3, 4}, {4, 5}},
        0
    );

    // Test Case 3: Cyclic graph
    runTestCase(
        "Test Case 3: Cyclic graph",
        4,
        {{0, 1}, {1, 2}, {2, 3}, {3, 0}},
        0
    );

    // Test Case 4: Graph with isolated node
    runTestCase(
        "Test Case 4: Graph with isolated node",
        5,
        {{0, 1}, {1, 2}, {2, 3}},
        0
    );

    // Test Case 5: Complete graph
    runTestCase(
        "Test Case 5: Complete graph",
        4,
        {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}},
        0
    );

    // Test Case 6: Single node graph
    runTestCase(
        "Test Case 6: Single node graph",
        1,
        {},
        0
    );

    return 0;
}
