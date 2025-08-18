

// Recurence Solution
int f(int i, int j) {
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;
    int up = f(i - 1, j);
    int left = f(i, j - 1);
    return up + left;
}

int uniquePaths(int m, int n) {
    return f(m - 1, n - 1);
}

//Memoization
#include <vector>
using namespace std;

int f(int i, int j, vector<vector<int>> &dp) {
    if (i == 0 && j == 0) return 1; // Base case: start position
    if (i < 0 || j < 0) return 0;   // Out of bounds
    if (dp[i][j] != -1) return dp[i][j]; // Return cached result

    int up = f(i - 1, j, dp);   // Move up
    int left = f(i, j - 1, dp); // Move left

    return dp[i][j] = up + left; // Store and return result
}

int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, -1)); // Initialize dp array with -1
    return f(m - 1, n - 1, dp);
}

///Tabulation
#include <vector>
using namespace std;

int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0)); // Initialize dp table with 0

    // Base case: Start position (0,0)
    dp[0][0] = 1;

    // Fill the dp table
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0) dp[i][j] += dp[i - 1][j]; // Move down
            if (j > 0) dp[i][j] += dp[i][j - 1]; // Move right
        }
    }

    return dp[m - 1][n - 1]; // Return the bottom-right cell
}


//Space optimization
#include <vector>
using namespace std;

int uniquePaths(int m, int n) {
    vector<int> prev(n, 0); // Previous row initialized to 0

    // Base case: Start position
    prev[0] = 1;

    // Fill the dp table row by row
    for (int i = 0; i < m; i++) {
        vector<int> curr(n, 0); // Current row
        for (int j = 0; j < n; j++) {
            if (j > 0) curr[j] += curr[j - 1]; // From left
            curr[j] += prev[j]; // From top
        }
        prev = curr; // Update previous row
    }

    return prev[n - 1]; // Return the last cell of the last row
}


