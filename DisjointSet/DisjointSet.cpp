#include <iostream>

const int MAX = 1000;

class DisjointSet {
private:
    int parent[MAX];
    int rank[MAX];

public:
    // Initialize each node to be its own parent
    void makeSet(int n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Find the root of the set with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union two sets by rank
    void unionSets(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot == yRoot)
            return;

        // Union by rank
        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }

    // For testing: print the parent of each node
    void printSets(int n) {
        for (int i = 0; i < n; ++i) {
            std::cout << "Node " << i << " -> Set " << find(i) << std::endl;
        }
    }
};

int main() {
    DisjointSet dsu;
    int n = 6; // Number of nodes (0 to 5)

    dsu.makeSet(n);

    dsu.unionSets(0, 1);
    dsu.unionSets(1, 2);
    dsu.unionSets(3, 4);

    std::cout << "After unions:\n";
    dsu.printSets(n);

    dsu.unionSets(2, 4);

    std::cout << "\nAfter more unions:\n";
    dsu.printSets(n);

    return 0;
}
