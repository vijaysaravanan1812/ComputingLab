class Solution {
string printSCS(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Step 1: Fill LCS DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    int len = dp[n][m]; // LCS length
    string ans(n + m - len, '$'); // Correct SCS length
    int index = n + m - len - 1;  // Last position in ans

    int i = n, j = m;

    // Step 2: Backtrack to build SCS
    while (i > 0 && j > 0) {
        if (s[i - 1] == t[j - 1]) {
            ans[index--] = s[i - 1];
            i--; j--;
        } 
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            ans[index--] = s[i - 1];
            i--;
        } 
        else {
            ans[index--] = t[j - 1];
            j--;
        }
    }

    while (i > 0) ans[index--] = s[--i];
    while (j > 0) ans[index--] = t[--j];

    return ans;
}

public:
    string shortestCommonSupersequence(string str1, string str2) {
        return printSCS(str1, str2);

    }
};