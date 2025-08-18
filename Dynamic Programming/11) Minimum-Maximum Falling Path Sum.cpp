

//Recursion solution
int f(int i, int j, vector<vector<int>> &matrix) {
    if (j < 0 || j >= matrix[0].size()) return -1e8;
    if (i == 0) return matrix[0][j];

    int u = matrix[i][j] + f(i - 1, j, matrix);
    int ld = matrix[i][j] + f(i - 1, j - 1, matrix);
    int rd = matrix[i][j] + f(i - 1, j + 1, matrix);

    return max(u, max(ld, rd));
}

int getMaxPathSum(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    int maxi = -1e8;
    for (int j = 0; j < m; j++) {
        maxi = max(maxi, f(n - 1, j, matrix));
    }
    return maxi;
}


//Memoization
#include <vector>
#include <algorithm>
using namespace std;

int f(int i, int j, vector<vector<int>> &matrix, vector<vector<int>> &dp) {
    if (j < 0 || j >= matrix[0].size()) return -1e8;
    if (i == 0) return matrix[0][j];
    if (dp[i][j] != -1) return dp[i][j];

    int u = matrix[i][j] + f(i - 1, j, matrix, dp);
    int ld = matrix[i][j] + f(i - 1, j - 1, matrix, dp);
    int rd = matrix[i][j] + f(i - 1, j + 1, matrix, dp);

    return dp[i][j] = max(u, max(ld, rd));
}

int getMaxPathSum(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));

    int maxi = -1e8;
    for (int j = 0; j < m; j++) {
        maxi = max(maxi, f(n - 1, j, matrix, dp));
    }
    return maxi;
}


//Tabulation
#include <vector>
#include <algorithm>
using namespace std;

int getMaxPathSum(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    // Base case: Fill the first row
    for (int j = 0; j < m; j++) {
        dp[0][j] = matrix[0][j];
    }

    // Fill the DP table
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = dp[i - 1][j];
            int ld = (j > 0) ? dp[i - 1][j - 1] : -1e8;
            int rd = (j < m - 1) ? dp[i - 1][j + 1] : -1e8;
            dp[i][j] = matrix[i][j] + max(u, max(ld, rd));
        }
    }

    // Find the maximum in the last row
    int maxi = -1e8;
    for (int j = 0; j < m; j++) {
        maxi = max(maxi, dp[n - 1][j]);
    }

    return maxi;
}


//Space Optimization
#include <vector>
#include <algorithm>
using namespace std;

int getMaxPathSum(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<int> prev(m, 0), curr(m, 0);

    // Initialize the first row
    for (int j = 0; j < m; j++) {
        prev[j] = matrix[0][j];
    }

    // Compute row by row
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = prev[j];
            int ld = (j > 0) ? prev[j - 1] : -1e8;
            int rd = (j < m - 1) ? prev[j + 1] : -1e8;
            curr[j] = matrix[i][j] + max(u, max(ld, rd));
        }
        prev = curr; // Update the previous row
    }

    // Find the maximum in the last row
    int maxi = -1e8;
    for (int j = 0; j < m; j++) {
        maxi = max(maxi, prev[j]);
    }

    return maxi;
}
