//Recursion
class Solution {
    long f(int ind, int buy, vector<int> &values, int n, int fee) {
        if (ind == n) return 0;

        if (buy) {
            return max(-values[ind] + f(ind + 1, 0, values, n, fee),
                        0 + f(ind + 1, 1, values, n, fee));
        } else {
            return max(values[ind] - fee + f(ind + 1, 1, values, n, fee),
                        0 + f(ind + 1, 0, values, n, fee));
        }
    }
public:
    int maxProfit(vector<int>& values, int fee) {
        int n = values.size();
        return f(0, 1, values, n, fee);
    }
};

//Memoization
class Solution {
    long f(int ind, int buy, vector<int> &values, int n, vector<vector<int>> &dp, int fee) {
        if (ind == n) return 0;
        if (dp[ind][buy] != -1) return dp[ind][buy];

        if (buy) {
            dp[ind][buy] = max(-values[ind] + f(ind + 1, 0, values, n, dp, fee),
                               0 + f(ind + 1, 1, values, n, dp, fee));
        } else {
            dp[ind][buy] = max(values[ind] - fee + f(ind + 1, 1, values, n, dp, fee),
                               0 + f(ind + 1, 0, values, n, dp, fee));
        }
        return dp[ind][buy];
    }
public:
    int maxProfit(vector<int>& values, int fee) {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return f(0, 1, values, n, dp, fee);
    }
};

//Tabulation
class Solution {
public:
    int maxProfit(vector<int>& values, int fee) {
        int n = values.size();
        vector<vector<long>> dp(n + 1, vector<long>(2, 0));

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                if (buy) {
                    dp[ind][buy] = max(-values[ind] + dp[ind + 1][0],
                                        0 + dp[ind + 1][1]);
                } else {
                    dp[ind][buy] = max(values[ind] - fee + dp[ind + 1][1],
                                        0 + dp[ind + 1][0]);
                }
            }
        }
        return dp[0][1];
    }
};

//Space Optimized
class Solution {
public:
    int maxProfit(vector<int>& values, int fee) {
        int n = values.size();
        vector<long> ahead(2, 0), curr(2, 0);

        for (int ind = n - 1; ind >= 0; ind--) {
            curr[1] = max(-values[ind] + ahead[0],
                           0 + ahead[1]);

            curr[0] = max(values[ind] - fee + ahead[1],
                           0 + ahead[0]);

            ahead = curr;
        }
        return ahead[1];
    }
};
