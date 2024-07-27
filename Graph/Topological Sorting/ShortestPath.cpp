#include <iostream>
#include <vector>
#include <utility>  // for std::pair
#include <list>
#include <bits/stdc++.h>

using namespace std;

// Class to represent a weighted directed graph
class Graph
{
private:
    int V;                            // Number of vertices
    vector<list<pair<int, int>>> adj; // Adjacency list to store (node, weight) pairs

public:
    // Constructor
    Graph(int V)
    {
        this->V = V;
        adj.resize(V); // Resize the vector to hold V lists
    }

    vector<int> TopologicalSorting(vector<list<pair<int, int>>> adj, int v)
    {
        int Indegree[v];
        vector<int> TopologicalArray;
        queue<int> TopologicalQueue;
        for (int i = 0; i < v; i++)
            Indegree[i] = 0;

        for (int i = 0; i < v; i++)
        {
            for (auto u : adj[i])
            {
                Indegree[u.first]++;
            }
        }

        for (int i = 0; i < v; i++)
        {
            if (Indegree[i] == 0)
            {
                TopologicalQueue.push(i);
            }
        }

        while (!TopologicalQueue.empty())
        {
            int Node = TopologicalQueue.front();
            TopologicalArray.push_back(Node);
            TopologicalQueue.pop();
            for (auto u : adj[Node])
            {
                Indegree[u.first]--;
                if (Indegree[u.first] == 0)
                {
                    TopologicalQueue.push(u.first);
                }
            }
        }

        return TopologicalArray;
    }

    vector<int> FiindShortestPath(int s, int v)
    {
        vector<int> DistanceArray(v, INT_MAX);
        vector<int> TopologicalArray;

        TopologicalArray = TopologicalSorting(adj, v);
        DistanceArray[s] = 0;

        for (int i = 0; i < TopologicalArray.size(); i++)
        {
            int Node = TopologicalArray[i];
            for (auto j : adj[Node])
            {
                int Neighbour = j.first;
                int Weight = j.second;
                if (DistanceArray[Neighbour] > DistanceArray[Node] + getWeight(Node, Neighbour))
                {
                    DistanceArray[Neighbour] = DistanceArray[Node] + getWeight(Node, Neighbour);
                }
            }
        }

        return DistanceArray;
    }

    // Function to add an edge to the graph with weight
    void addEdge(int u, int v, int weight)
    {
        adj[u].push_back(make_pair(v, weight)); // Add v to u's list with the given weight
    }

    // Function to find weight of an edge (u, v)
    int getWeight(int u, int v)
    {
        for (auto edge : adj[u])
        {
            if (edge.first == v)
            {
                return edge.second; // Return weight if edge (u, v) exists
            }
        }
        return -1; // Return -1 if edge (u, v) does not exist
    }

    // Function to print the graph
    void printGraph()
    {
        for (int i = 0; i < V; ++i)
        {
            cout << "Node " << i << " has edges to:\n";
            for (auto edge : adj[i])
            {
                cout << "\tNode " << edge.first << " with edge weight = " << edge.second << "\n";
            }
            cout << "\n";
        }
    }
};

int main()
{
    // Test Case 1:
    int V = 5;
    Graph g1(V);
    g1.addEdge(0, 1, 10);
    g1.addEdge(0, 4, 5);
    g1.addEdge(1, 2, 1);
    g1.addEdge(1, 4, 2);
    g1.addEdge(2, 3, 4);
    g1.addEdge(4, 2, 9);
    g1.addEdge(4, 3, 2);

    vector<int> Distance1 = g1.FiindShortestPath(0, V);
    cout << "Shortest path from node 0 in Test Case 1:\n";
    for (int i = 0; i < Distance1.size(); i++)
    {
        cout << "Distance to node " << i << " is " << Distance1[i] << "\n";
    }
    cout << "\n";

    // Test Case 2:
    Graph g2(V);
    g2.addEdge(0, 1, 10);
    g2.addEdge(0, 4, 5);
    g2.addEdge(1, 2, 1);
    g2.addEdge(1, 4, 2);
    g2.addEdge(2, 3, 4);
    g2.addEdge(3, 0, 7);
    g2.addEdge(3, 2, 6);
    g2.addEdge(4, 1, 3);
    g2.addEdge(4, 2, 9);
    g2.addEdge(4, 3, 2);

    vector<int> Distance2 = g2.FiindShortestPath(0, V);
    cout << "Shortest path from node 0 in Test Case 2:\n";
    for (int i = 0; i < Distance2.size(); i++)
    {
        cout << "Distance to node " << i << " is " << Distance2[i] << "\n";
    }
    cout << "\n";

    // Test Case 3:
    Graph g3(0);
    vector<int> Distance3 = g3.FiindShortestPath(0, 0);
    cout << "Shortest path from node 0 in Test Case 3:\n";
    for (int i = 0; i < Distance3.size(); i++)
    {
        cout << "Distance to node " << i << " is " << Distance3[i] << "\n";
    }
    cout << "\n";

    // Test Case 4:
    Graph g4(V);
    g4.addEdge(0, 1, -5);
    g4.addEdge(1, 2, 2);
    g4.addEdge(2, 3, 1);
    g4.addEdge(3, 4, 1);
    g4.addEdge(4, 1, -2);

    vector<int> Distance4 = g4.FiindShortestPath(0, V);
    cout << "Shortest path from node 0 in Test Case 4:\n";
    for (int i = 0; i < Distance4.size(); i++)
    {
        cout << "Distance to node " << i << " is " << Distance4[i] << "\n";
    }
    cout << "\n";

    // Test Case 5:
    Graph g5(V);
    g5.addEdge(0, 1, 10);
    g5.addEdge(1, 2, 20);
    g5.addEdge(2, 3, 30);
    g5.addEdge(3, 4, 40);
    g5.addEdge(4, 0, -50);

    vector<int> Distance5 = g5.FiindShortestPath(0, V);
    cout << "Shortest path from node 0 in Test Case 5:\n";
    for (int i = 0; i < Distance5.size(); i++)
    {
        cout << "Distance to node " << i << " is " << Distance5[i] << "\n";
    }
    cout << "\n";

    // Test Case 6:
    Graph g6(V);
    g6.addEdge(0, 1, 1);
    g6.addEdge(1, 2, 1);
    g6.addEdge(2, 0, 1);

    vector<int> Distance6 = g6.FiindShortestPath(0, V);
    cout << "Shortest path from node 0 in Test Case 6:\n";
    for (int i = 0; i < Distance6.size(); i++)
    {
        cout << "Distance to node " << i << " is " << Distance6[i] << "\n";
    }
    cout << "\n";

    // Test Case 7:
    Graph g7(V);
    g7.addEdge(0, 1, 1);
    g7.addEdge(1, 2, 1);
    g7.addEdge(2, 3, 1);
    g7.addEdge(3, 4, 1);
    g7.addEdge(4, 0, -1);

    vector<int> Distance7 = g7.FiindShortestPath(0, V);
    cout << "Shortest path from node 0 in Test Case 7:\n";
    for (int i = 0; i < Distance7.size(); i++)
    {
        cout << "Distance to node " << i << " is " << Distance7[i] << "\n";
    }
    cout << "\n";

    // Test Case 8:
    Graph g8(V);
    g8.addEdge(0, 1, 1);
    g8.addEdge(1, 2, 1);
    g8.addEdge(3, 4, 1); // Disconnected component

    vector<int> Distance8 = g8.FiindShortestPath(0, V);
    cout << "Shortest path from node 0 in Test Case 8:\n";
    for (int i = 0; i < Distance8.size(); i++)
    {
        cout << "Distance to node " << i << " is " << Distance8[i] << "\n";
    }
    cout << "\n";

    // Test Case 9: (Graph with duplicate edges)
    Graph g9(V);
    g9.addEdge(0, 1, 1);
    g9.addEdge(0, 1, 3); // duplicate edge with different weight
    g9.addEdge(1, 2, 2);
    g9.addEdge(1, 2, 4); // duplicate edge with different weight
    g9.addEdge(2, 3, 3);
    g9.addEdge(3, 4, 4);

    vector<int> Distance9 = g9.FiindShortestPath(0, V);
    cout << "Shortest path from node 0 in Test Case 9:\n";
    for (int i = 0; i < Distance9.size(); i++)
    {
        cout << "Distance to node " << i << " is " << Distance9[i] << "\n";
    }
    cout << "\n";

    // Test Case 10: (Empty graph)
    Graph g10(0);
    vector<int> Distance10 = g10.FiindShortestPath(0, 0);
    cout << "Shortest path from node 0 in Test Case 10:\n";
    for (int i = 0; i < Distance10.size(); i++)
    {
        cout << "Distance to node " << i << " is " << Distance10[i] << "\n";
    }
    cout << "\n";

    return 0;
}
