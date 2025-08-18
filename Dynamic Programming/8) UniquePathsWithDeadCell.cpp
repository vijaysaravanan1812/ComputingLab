
//Memoization
#include <vector>
using namespace std;

int findPaths(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
    // Base cases
    if (i < 0 || j < 0 || grid[i][j] == -1) return 0; // Out of bounds or dead cell
    if (i == 0 && j == 0) return 1; // Start cell reached
    
    // If already computed, return the stored result
    if (dp[i][j] != -1) return dp[i][j];

    // Recursive calls: From top and left
    int up = findPaths(i - 1, j, grid, dp);
    int left = findPaths(i, j - 1, grid, dp);

    // Store the result in dp table
    return dp[i][j] = up + left;
}

int uniquePathsWithDeadCells(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    // If the start or end cell is dead, return 0
    if (grid[0][0] == -1 || grid[m - 1][n - 1] == -1) return 0;

    // DP table initialized with -1 (uncomputed state)
    vector<vector<int>> dp(m, vector<int>(n, -1));

    // Start recursion from the bottom-right cell
    return findPaths(m - 1, n - 1, grid, dp);
}



//Tabulation
int uniquePathsWithDeadCells(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    // DP table to store unique paths
    vector<vector<int>> dp(m, vector<int>(n, 0));

    // Base case: Starting cell is not a dead cell
    if (grid[0][0] == -1) return 0; // If start is dead, no paths
    dp[0][0] = 1;

    // Fill the DP table
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == -1) { 
                dp[i][j] = 0; // Dead cell: no paths
                continue;
            }
            // From top (if valid)
            if (i > 0) dp[i][j] += dp[i - 1][j];
            // From left (if valid)
            if (j > 0) dp[i][j] += dp[i][j - 1];
        }
    }

    // Result: Bottom-right cell
    return dp[m - 1][n - 1];
}

//Space Optimization
int uniquePathsWithDeadCells(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    // If the starting or ending cell is dead, return 0
    if (grid[0][0] == -1 || grid[m - 1][n - 1] == -1) return 0;

    // Previous row and current row
    vector<int> prev(n, 0), curr(n, 0);

    prev[0] = 1; // Base case: Start cell is not dead

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == -1) {
                curr[j] = 0; // Dead cell: no paths
            } else {
                curr[j] = 0; // Reset current cell
                if (j > 0) curr[j] += curr[j - 1]; // From left
                if (i > 0) curr[j] += prev[j];     // From top
            }
        }
        prev = curr; // Update previous row
    }

    // Result: Bottom-right cell
    return prev[n - 1];
}
