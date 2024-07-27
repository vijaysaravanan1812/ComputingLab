#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> Edge;

void DFS(vector<vector<Edge>> &Adj, int Node, set<int> &ArticulationPoints, 
         int Parent, int NumberOfVertices, bool visited[], int DiscoveryTime[], 
         int Low[], int &timer){
    DiscoveryTime[Node] = Low[Node] = ++timer;
    visited[Node] = true;
    int children = 0;

    for(auto u : Adj[Node]){
        int AdjacentNode = u.second;
        if(AdjacentNode == Parent)
            continue;
        if(!visited[AdjacentNode]){
            children++;
            DFS(Adj, AdjacentNode, ArticulationPoints, Node, NumberOfVertices, visited, DiscoveryTime, Low, timer);
            Low[Node] = min(Low[Node], Low[AdjacentNode]);

            // If Node is not root and low value of one of its child is more than discovery value of Node.
            if(Parent != -1 && Low[AdjacentNode] >= DiscoveryTime[Node])
                ArticulationPoints.insert(Node);
        } else {
            // Update low value of Node for parent function calls.
            Low[Node] = min(Low[Node], DiscoveryTime[AdjacentNode]);
        }
    }
    // If Node is root of DFS tree and has two or more children.
    if(Parent == -1 && children > 1)
        ArticulationPoints.insert(Node);
}

vector<int> FindArticulationPoints(vector<vector<Edge>> &Adj, int NumberOfVertices){
    int DiscoveryTime[NumberOfVertices];
    int Low[NumberOfVertices];
    bool visited[NumberOfVertices];
    fill(visited, visited + NumberOfVertices, false);
    set<int> ArticulationPoints;
    int timer = 0;

    for (int i = 0; i < NumberOfVertices; i++) {
        if (!visited[i]) {
            DFS(Adj, i, ArticulationPoints, -1, NumberOfVertices, visited, DiscoveryTime, Low, timer);
        }
    }

    vector<int> result(ArticulationPoints.begin(), ArticulationPoints.end());
    sort(result.begin(), result.end());  // Optional: sort the articulation points
    return result;
}

void AddEdge(vector<vector<Edge>> &Adj, int V, int U, int Weight){
    Adj[V].push_back({Weight, U});
    Adj[U].push_back({Weight, V});
}

void PrintGraph(const vector<vector<Edge>> &Adj, int NumberOfVertex){
    for (int i = 0; i < NumberOfVertex; i++){
        cout << "Vertex " << i << " : \n";
        for (const auto &u : Adj[i]){
            int Weight = u.first;
            int Node = u.second;
            cout << "\tWeight: " << Weight << " Node: " << Node << "\n";
        }
    }
}

int main(){
    int numVertices = 8;
    vector<vector<Edge>> adjList(numVertices);

    // Adding edges
    AddEdge(adjList, 0, 1, 1);
    AddEdge(adjList, 1, 2, 1);
    AddEdge(adjList, 2, 0, 1);
    AddEdge(adjList, 1, 3, 1);
    AddEdge(adjList, 3, 4, 1);
    AddEdge(adjList, 3, 5, 1);
    AddEdge(adjList, 3, 6, 1);
    AddEdge(adjList, 6, 7, 1);
    

    // Print the graph
    cout << "Graph \n";
    PrintGraph(adjList, numVertices);

    vector<int> ArticulationPoints = FindArticulationPoints(adjList, numVertices);

    cout << "Articulation Points\n";
    for(auto i : ArticulationPoints){
        cout << i << "\n";
    }

    return 0;
}
