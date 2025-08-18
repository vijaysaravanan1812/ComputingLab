
//Recursion
int LCS_Recursion_0Index(string &s1, string &s2, int i, int j) {
    if (i < 0 || j < 0)
        return 0;

    if (s1[i] == s2[j])
        return 1 + LCS_Recursion_0Index(s1, s2, i - 1, j - 1);
    else
        return max(LCS_Recursion_0Index(s1, s2, i - 1, j),
                   LCS_Recursion_0Index(s1, s2, i, j - 1));
}


//Memoization
int LCS_Memoization_0Index(string &s1, string &s2, int i, int j,
                           vector<vector<int>> &dp) {
    if (i < 0 || j < 0)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (s1[i] == s2[j])
        return dp[i][j] = 1 + LCS_Memoization_0Index(s1, s2, i - 1, j - 1, dp);
    else
        return dp[i][j] = max(LCS_Memoization_0Index(s1, s2, i - 1, j, dp),
                              LCS_Memoization_0Index(s1, s2, i, j - 1, dp));
}

//Tabulation
int LCS_Tabulation_0Index(string &s1, string &s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

//Space Optimized
int LCS_SpaceOptimized_0Index(string &s1, string &s2
) {
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        prev = curr;
    }
    return prev[m];
}