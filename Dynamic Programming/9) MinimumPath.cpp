

int f(int i, int j, vector<vector<int>> &grid) {
    if (i == 0 && j == 0) return grid[i][j];
    if (i < 0 || j < 0) return 1e9;
    int up = grid[i][j] + f(i - 1, j, grid);
    int left = grid[i][j] + f(i, j - 1, grid);
    return min(left, up);
}


//Memoization
#include <vector>
#include <algorithm>
using namespace std;

int f(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
    if (i == 0 && j == 0) return grid[i][j]; // Base case: Start cell
    if (i < 0 || j < 0) return 1e9; // Out of bounds

    if (dp[i][j] != -1) return dp[i][j]; // If already computed

    int up = grid[i][j] + f(i - 1, j, grid, dp);
    int left = grid[i][j] + f(i, j - 1, grid, dp);

    return dp[i][j] = min(left, up); // Store result in dp table
}

int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    // Initialize dp table with -1
    vector<vector<int>> dp(m, vector<int>(n, -1));

    return f(m - 1, n - 1, grid, dp); // Start recursion from bottom-right
}


//Tabulation
#include <vector>
#include <algorithm>
using namespace std;

int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    // Initialize dp table
    vector<vector<int>> dp(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = grid[i][j]; // Base case
            } else {
                int up = (i > 0) ? dp[i - 1][j] : 1e9;
                int left = (j > 0) ? dp[i][j - 1] : 1e9;
                dp[i][j] = grid[i][j] + min(up, left);
            }
        }
    }

    return dp[m - 1][n - 1]; // Return the result from bottom-right
}



//Space Optimization
#include <vector>
#include <algorithm>
using namespace std;

int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    // Initialize a single array for the current row
    vector<int> prev(n, 0);

    for (int i = 0; i < m; i++) {
        vector<int> curr(n, 0);
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                curr[j] = grid[i][j]; // Base case
            } else {
                int up = (i > 0) ? prev[j] : 1e9;
                int left = (j > 0) ? curr[j - 1] : 1e9;
                curr[j] = grid[i][j] + min(up, left);
            }
        }
        prev = curr; // Update the previous row
    }

    return prev[n - 1]; // Return the result from bottom-right
}
