// LeetCode 115. Distinct Subsequences
// https://leetcode.com/problems/distinct-subsequences/


class Solution {
    int solve(string &s, string &t, int i, int j) {
        if (j == 0) return 1; // matched entire t
        if (i == 0) return 0; // s is empty, t still left

        if (s[i - 1] == t[j - 1])
            return solve(s, t, i - 1, j - 1) + solve(s, t, i - 1, j);
        else
            return solve(s, t, i - 1, j);
    }
public:
    int numDistinct(string s, string t) {
        return solve(s, t, s.size(), t.size());
    }
};

// Memoization solution to Distinct Subsequences
class Solution {
    int solve(string &s, string &t, int i, int j, vector<vector<int>> &dp) {
        if (j == 0) return 1;
        if (i == 0) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        if (s[i - 1] == t[j - 1])
            return dp[i][j] = solve(s, t, i - 1, j - 1, dp) + solve(s, t, i - 1, j, dp);
        else
            return dp[i][j] = solve(s, t, i - 1, j, dp);
    }
public:
    int numDistinct(string s, string t) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, -1));
        return solve(s, t, s.size(), t.size(), dp);
    }
};

// Tabulation solution to Distinct Subsequences
class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));

        // Base case: empty t => 1 subsequence for all i
        for (int i = 0; i <= n; i++) dp[i][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }
        return dp[n][m];
    }
};

// Space optimized solution to Distinct Subsequences
class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<long long> prev(m + 1, 0), curr(m + 1, 0);

        prev[0] = curr[0] = 1; // empty t

        for (int i = 1; i <= n; i++) {
            curr[0] = 1; // empty t
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1])
                    curr[j] = prev[j - 1] + prev[j];
                else
                    curr[j] = prev[j];
            }
            prev = curr;
        }
        return prev[m];
    }
};

// Optimized space solution using 1D DP
class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<long long> dp(m + 1, 0);
        dp[0] = 1; // empty t

        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) { // reverse order
                if (s[i - 1] == t[j - 1])
                    dp[j] = dp[j - 1] + dp[j];
            }
        }
        return dp[m];
    }
};
