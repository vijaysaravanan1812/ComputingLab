
//Recursive Solution
int f(int i, int j, vector<vector<int>>& triangle, int n) {
    if (i == n - 1) {
        return triangle[n - 1][j];
    }
    int d = triangle[i][j] + f(i + 1, j, triangle, n);
    int dg = triangle[i][j] + f(i + 1, j + 1, triangle, n);
    return min(d, dg);
}


//Memoization
#include <vector>
#include <algorithm>
using namespace std;

int f(int i, int j, vector<vector<int>>& triangle, int n, vector<vector<int>>& dp) {
    if (i == n - 1) return triangle[n - 1][j]; // Base case: Last row
    if (dp[i][j] != -1) return dp[i][j]; // If already computed

    int d = triangle[i][j] + f(i + 1, j, triangle, n, dp);
    int dg = triangle[i][j] + f(i + 1, j + 1, triangle, n, dp);

    return dp[i][j] = min(d, dg); // Store result in dp table
}

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, -1)); // Initialize DP table
    return f(0, 0, triangle, n, dp); // Start recursion from top
}


//Tabulation
#include <vector>
#include <algorithm>
using namespace std;

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Fill the last row of dp table
    for (int j = 0; j < n; j++) {
        dp[n - 1][j] = triangle[n - 1][j];
    }

    // Fill the DP table from bottom to top
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            int d = triangle[i][j] + dp[i + 1][j];
            int dg = triangle[i][j] + dp[i + 1][j + 1];
            dp[i][j] = min(d, dg);
        }
    }

    return dp[0][0]; // Return the result from the top
}


//Space Optimization
#include <vector>
#include <algorithm>
using namespace std;

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> next(n, 0);

    // Initialize the last row
    for (int j = 0; j < n; j++) {
        next[j] = triangle[n - 1][j];
    }

    // Compute from bottom to top
    for (int i = n - 2; i >= 0; i--) {
        vector<int> curr(n, 0);
        for (int j = 0; j <= i; j++) {
            int d = triangle[i][j] + next[j];
            int dg = triangle[i][j] + next[j + 1];
            curr[j] = min(d, dg);
        }
        next = curr; // Update the next row
    }

    return next[0]; // Return the result from the top
}
