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
    void minInsDelToConvert(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        int lcs_len = LCS(n, m, str1, str2, dp);

        int deletions = n - lcs_len;
        int insertions = m - lcs_len;
        int totalOps = deletions + insertions;

        cout << "LCS length: " << lcs_len << "\n";
        cout << "Deletions: " << deletions << "\n";
        cout << "Insertions: " << insertions << "\n";
        cout << "Total operations: " << totalOps << "\n";
    }
};

int main() {
    Solution sol;
    string str1 = "heap";
    string str2 = "pea";
    sol.minInsDelToConvert(str1, str2);
}
