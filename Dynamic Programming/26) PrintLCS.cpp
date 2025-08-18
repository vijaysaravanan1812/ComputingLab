#include <bits/stdc++.h>
using namespace std;

void printLCS(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Step 1: Fill DP table (1-based indexing)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Step 2: Backtrack to find LCS string
    int len = dp[n][m];
    string ans(len, '$'); // placeholder string of correct length

    int i = n, j = m, index = len - 1;
    while (i > 0 && j > 0) {
        if (s[i - 1] == t[j - 1]) {
            ans[index] = s[i - 1];
            i--; j--; index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    cout << "LCS: " << ans << "\n";
}

int main() {
    string s = "abcde";
    string t = "bde";
    printLCS(s, t);
}
