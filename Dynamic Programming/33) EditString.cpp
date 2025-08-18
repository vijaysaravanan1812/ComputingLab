
// LeetCode 72. Edit Distance
// https://leetcode.com/problems/edit-distance/
// This problem is about finding the minimum number of operations required to convert one string into another.
// The allowed operations are insert, delete, and replace a character.
//Recursion solution to Edit Distance
class Solution {
    int f(string &s, string &t, int i, int j) {
        if (i == 0) return j; // insert all t chars
        if (j == 0) return i; // delete all s chars

        if (s[i - 1] == t[j - 1])
            return f(s, t, i - 1, j - 1);

        int insertOp = 1 + f(s, t, i, j - 1);
        int deleteOp = 1 + f(s, t, i - 1, j);
        int replaceOp = 1 + f(s, t, i - 1, j - 1);

        return min({insertOp, deleteOp, replaceOp});
    }
public:
    int minDistance(string word1, string word2) {
        return f(word1, word2, word1.size(), word2.size());
    }
};

// Memoization solution to Edit Distance
class Solution {
    int f(string &s, string &t, int i, int j, vector<vector<int>> &dp) {
        if (i == 0) return j;
        if (j == 0) return i;

        if (dp[i][j] != -1) return dp[i][j];

        if (s[i - 1] == t[j - 1])
            return dp[i][j] = f(s, t, i - 1, j - 1, dp);

        int insertOp = 1 + f(s, t, i, j - 1, dp);
        int deleteOp = 1 + f(s, t, i - 1, j, dp);
        int replaceOp = 1 + f(s, t, i - 1, j - 1, dp);

        return dp[i][j] = min({insertOp, deleteOp, replaceOp});
    }
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return f(word1, word2, n, m, dp);
    }
};

// Tabulation solution to Edit Distance
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Base cases
        for (int i = 0; i <= n; i++) dp[i][0] = i;
        for (int j = 0; j <= m; j++) dp[0][j] = j;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + min({dp[i][j - 1],    // insert
                                        dp[i - 1][j],    // delete
                                        dp[i - 1][j - 1] // replace
                                       });
            }
        }
        return dp[n][m];
    }
};

// Space optimized solution to Edit Distance
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> prev(m + 1), curr(m + 1);

        // Base case for i = 0
        for (int j = 0; j <= m; j++) prev[j] = j;

        for (int i = 1; i <= n; i++) {
            curr[0] = i; // base case for j = 0
            for (int j = 1; j <= m; j++) {
                if (word1[i - 1] == word2[j - 1])
                    curr[j] = prev[j - 1];
                else
                    curr[j] = 1 + min({curr[j - 1], prev[j], prev[j - 1]});
            }
            prev = curr;
        }
        return prev[m];
    }
};

// Space optimized solution to Edit Distance using 1D array
// This is a further optimized version that uses only one array.    
// This is possible because we only need the previous row to compute the current row.
// This is a common optimization technique in dynamic programming.
// This solution is efficient in both time and space.
// It runs in O(n * m) time and uses O(m) space.
// This is the final solution.
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> dp(m + 1);

        // Base case: i = 0
        for (int j = 0; j <= m; j++) dp[j] = j;

        for (int i = 1; i <= n; i++) {
            int prevDiagonal = dp[0]; // old dp[i-1][j-1]
            dp[0] = i; // base case for j = 0

            for (int j = 1; j <= m; j++) {
                int temp = dp[j]; // store old dp[i-1][j]
                if (word1[i - 1] == word2[j - 1])
                    dp[j] = prevDiagonal;
                else
                    dp[j] = 1 + min({dp[j - 1], dp[j], prevDiagonal});
                prevDiagonal = temp;
            }
        }
        return dp[m];
    }
};

