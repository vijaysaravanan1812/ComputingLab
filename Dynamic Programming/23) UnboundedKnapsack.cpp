
// recursive solution
int knapsackRecursive(int ind, int W, vector<int> &val, vector<int> &wt) {
    if (ind == 0) {
        // Base case: Take as many of the first item as possible
        return (W / wt[0]) * val[0];
    }

    // Option 1: Do not take the current item
    int notTake = knapsackRecursive(ind - 1, W, val, wt);

    // Option 2: Take the current item (if possible)
    int take = 0;
    if (wt[ind] <= W) {
        take = val[ind] + knapsackRecursive(ind, W - wt[ind], val, wt);
    }

    return max(take, notTake);
}

int unboundedKnapsack(int n, int W, vector<int> &val, vector<int> &wt) {
    return knapsackRecursive(n - 1, W, val, wt);
}


// Memoization solution
int knapsackMemo(int ind, int W, vector<int> &val, vector<int> &wt, vector<vector<int>> &dp) {
    if (ind == 0) {
        return (W / wt[0]) * val[0];
    }

    if (dp[ind][W] != -1) return dp[ind][W];

    int notTake = knapsackMemo(ind - 1, W, val, wt, dp);
    int take = 0;
    if (wt[ind] <= W) {
        take = val[ind] + knapsackMemo(ind, W - wt[ind], val, wt, dp);
    }

    return dp[ind][W] = max(take, notTake);
}

int unboundedKnapsack(int n, int W, vector<int> &val, vector<int> &wt) {
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    return knapsackMemo(n - 1, W, val, wt, dp);
}




//Tabulation solution
int unboundedKnapsack(int n, int W, vector<int> &val, vector<int> &wt) {
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));

    // Base case: Fill for the first item
    for (int w = 0; w <= W; w++) {
        dp[0][w] = (w / wt[0]) * val[0];
    }

    for (int ind = 1; ind < n; ind++) {
        for (int w = 0; w <= W; w++) {
            int notTake = dp[ind - 1][w];
            int take = 0;
            if (wt[ind] <= w) {
                take = val[ind] + dp[ind][w - wt[ind]];
            }
            dp[ind][w] = max(take, notTake);
        }
    }

    return dp[n - 1][W];
}


//Space Optimization

int unboundedKnapsack(int n, int W, vector<int> &val, vector<int> &wt) {
    vector<int> prev(W + 1, 0), curr(W + 1, 0);

    // Base case: Fill for the first item
    for (int w = 0; w <= W; w++) {
        prev[w] = (w / wt[0]) * val[0];
    }

    for (int ind = 1; ind < n; ind++) {
        for (int w = 0; w <= W; w++) {
            int notTake = prev[w];
            int take = 0;
            if (wt[ind] <= w) {
                take = val[ind] + curr[w - wt[ind]];
            }
            curr[w] = max(take, notTake);
        }
        prev = curr;
    }

    return prev[W];
}
