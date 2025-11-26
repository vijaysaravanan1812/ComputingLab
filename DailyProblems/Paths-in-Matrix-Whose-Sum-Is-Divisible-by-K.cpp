1#include <bits/stdc++.h>
2using namespace std;
3
4class Solution {
5public:
6    int numberOfPaths(vector<vector<int>>& grid, int k) {
7        const int MOD = 1e9 + 7;
8        int m = grid.size();
9        int n = grid[0].size();
10
11        // dp[i][j][r] = number of ways to reach (i,j) with sum % k == r
12        // Using 3D vector: m x n x k
13        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k, 0)));
14
15        int r0 = ((grid[0][0] % k) + k) % k;
16        dp[0][0][r0] = 1;
17
18        for (int i = 0; i < m; ++i) {
19            for (int j = 0; j < n; ++j) {
20                if (i == 0 && j == 0) continue;
21                int add = ((grid[i][j] % k) + k) % k;
22
23                // combine from top
24                if (i > 0) {
25                    for (int r = 0; r < k; ++r) {
26                        if (dp[i-1][j][r] == 0) continue;
27                        int nr = (r + add) % k;
28                        dp[i][j][nr] = (dp[i][j][nr] + dp[i-1][j][r]) % MOD;
29                    }
30                }
31
32                // combine from left
33                if (j > 0) {
34                    for (int r = 0; r < k; ++r) {
35                        if (dp[i][j-1][r] == 0) continue;
36                        int nr = (r + add) % k;
37                        dp[i][j][nr] = (dp[i][j][nr] + dp[i][j-1][r]) % MOD;
38                    }
39                }
40            }
41        }
42
43        return dp[m-1][n-1][0];
44    }
45};
46