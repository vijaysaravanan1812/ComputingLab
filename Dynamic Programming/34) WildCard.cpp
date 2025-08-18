
//  
// LeetCode 44. Wildcard Matching
// https://leetcode.com/problems/wildcard-matching/
// This problem is about matching a string against a pattern with wildcards.
bool matchRec(const string &s, const string &p, int i, int j) {
    // both strings empty
    if (i == 0 && j == 0) return true;
    // pattern empty but string not
    if (j == 0 && i > 0) return false;
    // string empty, pattern can only match if all '*' so far
    if (i == 0 && j > 0) {
        for (int k = 1; k <= j; k++)
            if (p[k - 1] != '*') return false;
        return true;
    }

    if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
        return matchRec(s, p, i - 1, j - 1);
    if (p[j - 1] == '*')
        return matchRec(s, p, i, j - 1) || matchRec(s, p, i - 1, j);

    return false;
}

// Memoization solution to Wildcard Matching
bool matchMemo(const string &s, const string &p, int i, int j, vector<vector<int>> &dp) {
    if (i == 0 && j == 0) return true;
    if (j == 0 && i > 0) return false;
    if (i == 0 && j > 0) {
        for (int k = 1; k <= j; k++)
            if (p[k - 1] != '*') return false;
        return true;
    }
    if (dp[i][j] != -1) return dp[i][j];

    if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
        return dp[i][j] = matchMemo(s, p, i - 1, j - 1, dp);
    if (p[j - 1] == '*')
        return dp[i][j] = matchMemo(s, p, i, j - 1, dp) || matchMemo(s, p, i - 1, j, dp);

    return dp[i][j] = false;
}

bool isMatch(string s, string p) {
    vector<vector<int>> dp(s.size() + 1, vector<int>(p.size() + 1, -1));
    return matchMemo(s, p, s.size(), p.size(), dp);
}

// Tabulation solution to Wildcard Matching
bool isMatch(string s, string p) {
    int n = s.size(), m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;
    // initialize first row (s is empty)
    for (int j = 1; j <= m; j++) {
        dp[0][j] = (p[j - 1] == '*') && dp[0][j - 1];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
                dp[i][j] = dp[i - 1][j - 1];
            else if (p[j - 1] == '*')
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
        }
    }

    return dp[n][m];
}
// Space optimized solution to Wildcard Matching
bool isMatch(string s, string p) {
    int n = s.size(), m = p.size();
    vector<bool> prev(m + 1, false), curr(m + 1, false);

    prev[0] = true;
    for (int j = 1; j <= m; j++) {
        prev[j] = (p[j - 1] == '*') && prev[j - 1];
    }

    for (int i = 1; i <= n; i++) {
        curr[0] = false; // non-empty s can't match empty p
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
                curr[j] = prev[j - 1];
            else if (p[j - 1] == '*')
                curr[j] = curr[j - 1] || prev[j];
            else
                curr[j] = false;
        }
        prev = curr;
    }

    return prev[m];
}
