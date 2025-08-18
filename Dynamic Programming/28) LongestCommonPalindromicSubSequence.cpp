#include <bits/stdc++.h>
using namespace std;

class Solution {
    int LCS(int i, int j, string &s, string &t, vector<vector<int>> &dp) {
        if (i == 0 || j == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        if (s[i - 1] == t[j - 1])
            return dp[i][j] = 1 + LCS(i - 1, j - 1, s, t, dp);
        else
            return dp[i][j] = max(LCS(i - 1, j, s, t, dp),
                                  LCS(i, j - 1, s, t, dp));
    }

public:
    int longestPalindromeSubseq(string s) {
        string t = s;
        reverse(t.begin(), t.end());
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return LCS(n, n, s, t, dp);
    }
};

int main() {
    Solution sol;
    string str = "bbbab";
    cout << "Length of Longest Palindromic Subsequence: "
         << sol.longestPalindromeSubseq(str) << "\n";
}
