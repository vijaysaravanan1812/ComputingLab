
//Recursion 

class Solution {
    long f(int ind, int buy, vector<int> &values, int n) {
        if (ind >= n) return 0; // base case

        if (buy) {
            return max(-values[ind] + f(ind + 1, 0, values, n),  // buy
                       0 + f(ind + 1, 1, values, n));           // skip buy
        } else {
            return max(values[ind] + f(ind + 2, 1, values, n),   // sell + cooldown
                       0 + f(ind + 1, 0, values, n));           // skip sell
        }
    }
public:
    int maxProfit(vector<int>& values) {
        int n = values.size();
        return f(0, 1, values, n);
    }
};


//Memoization
class Solution {
    long f(int ind, int buy, vector<int> &values, int n, vector<vector<int>> &dp) {
        if (ind >= n) return 0;
        if (dp[ind][buy] != -1) return dp[ind][buy];

        if (buy) {
            dp[ind][buy] = max(-values[ind] + f(ind + 1, 0, values, n, dp),
                               0 + f(ind + 1, 1, values, n, dp));
        } else {
            dp[ind][buy] = max(values[ind] + f(ind + 2, 1, values, n, dp),
                               0 + f(ind + 1, 0, values, n, dp));
        }
        return dp[ind][buy];
    }
public:
    int maxProfit(vector<int>& values) {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return f(0, 1, values, n, dp);
    }
};

//Tabulation
class Solution {
public:
    int maxProfit(vector<int>& values) {
        int n = values.size();
        vector<vector<long>> dp(n + 2, vector<long>(2, 0)); // extra space for ind+2

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                if (buy) {
                    dp[ind][buy] = max(-values[ind] + dp[ind + 1][0],
                                        0 + dp[ind + 1][1]);
                } else {
                    dp[ind][buy] = max(values[ind] + dp[ind + 2][1],
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
    int maxProfit(vector<int>& values) {
        int n = values.size();

        vector<long> ahead1(2, 0), ahead2(2, 0), curr(2, 0);

        for (int ind = n - 1; ind >= 0; ind--) {
            curr[1] = max(-values[ind] + ahead1[0],  // buy
                           0 + ahead1[1]);           // skip buy

            curr[0] = max(values[ind] + ahead2[1],   // sell + cooldown
                           0 + ahead1[0]);           // skip sell

            ahead2 = ahead1;
            ahead1 = curr;
        }
        return ahead1[1];
    }
};

