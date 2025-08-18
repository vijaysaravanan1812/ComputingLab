// LeetCode 188: Best Time to Buy and Sell Stock IV
// This code implements a solution to the problem of maximizing profit from stock transactions  
// Recursion, memoization, and tabulation techniques are used to solve the problem efficiently.
class Solution {
    int f(int ind, int buy, int cap, const vector<int> &prices) {
        if (ind == prices.size() || cap == 0) return 0;

        if (buy) {
            int buyNow  = -prices[ind] + f(ind + 1, 0, cap, prices);
            int skipBuy = f(ind + 1, 1, cap, prices);
            return max(buyNow, skipBuy);
        } else {
            int sellNow  = prices[ind] + f(ind + 1, 1, cap - 1, prices);
            int skipSell = f(ind + 1, 0, cap, prices);
            return max(sellNow, skipSell);
        }
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        return f(0, 1, k, prices);
    }
};

//Memoization solution to Buy and Sell Stocks IV
class Solution {
    int f(int ind, int buy, int cap, const vector<int> &prices,
          vector<vector<vector<int>>> &dp) {
        if (ind == prices.size() || cap == 0) return 0;
        if (dp[ind][buy][cap] != -1) return dp[ind][buy][cap];

        if (buy) {
            int buyNow  = -prices[ind] + f(ind + 1, 0, cap, prices, dp);
            int skipBuy = f(ind + 1, 1, cap, prices, dp);
            return dp[ind][buy][cap] = max(buyNow, skipBuy);
        } else {
            int sellNow  = prices[ind] + f(ind + 1, 1, cap - 1, prices, dp);
            int skipSell = f(ind + 1, 0, cap, prices, dp);
            return dp[ind][buy][cap] = max(sellNow, skipSell);
        }
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return f(0, 1, k, prices, dp);
    }
};

//Tabulation solution to Buy and Sell Stocks IV
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
                    if (buy) {
                        dp[ind][buy][cap] = max(-prices[ind] + dp[ind + 1][0][cap],
                                                 0 + dp[ind + 1][1][cap]);
                    } else {
                        dp[ind][buy][cap] = max(prices[ind] + dp[ind + 1][1][cap - 1],
                                                 0 + dp[ind + 1][0][cap]);
                    }
                }
            }
        }

        return dp[0][1][k];
    }
};


// Space optimized solution to Buy and Sell Stocks IV
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        vector<vector<int>> ahead(2, vector<int>(k + 1, 0));
        vector<vector<int>> curr(2, vector<int>(k + 1, 0));

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
                    if (buy) {
                        curr[buy][cap] = max(-prices[ind] + ahead[0][cap],
                                              0 + ahead[1][cap]);
                    } else {
                        curr[buy][cap] = max(prices[ind] + ahead[1][cap - 1],
                                              0 + ahead[0][cap]);
                    }
                }
            }
            ahead = curr;
        }

        return ahead[1][k];
    }
};

