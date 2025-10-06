class Solution {
    vector<int> TopologicalSorting(vector<int> adj[], int v) {
        int Indegree[v];
        vector<int> TopologicalArray;
        for (int i = 0; i < v; i++) {
            Indegree[i] = 0;
        }

        for (int i = 0; i < v; i++) {
            for (auto u : adj[i]) {
                Indegree[u] += 1;
            }
        }

        queue<int> TopologicalSortingQueue;
        for (int i = 0; i < v; i++) {
            if (Indegree[i] == 0) {
                TopologicalSortingQueue.push(i);
            }
        }

        while (!TopologicalSortingQueue.empty()) {
            int Node = TopologicalSortingQueue.front();
            TopologicalArray.push_back(Node);
            TopologicalSortingQueue.pop();
            for (auto u : adj[Node]) {
                Indegree[u]--;
                if (Indegree[u] == 0) {
                    TopologicalSortingQueue.push(u);
                }
            }
        }

        return TopologicalArray;
    }
    void addEdge(vector<int> adj[], int v, int u) { adj[v].push_back(u); }

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[numCourses];
        for(auto x : prerequisites){
            addEdge(adj , x[1] , x[0]);
        }
        vector<int> courses = TopologicalSorting(adj, numCourses);
        return courses.size() == numCourses; 
    }
};