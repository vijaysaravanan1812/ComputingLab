
//Recursion
bool subsetSumToKHelper(int ind, int target, vector<int> &arr) {
    // Base cases
    if (target == 0) return true;          // Subset sum of 0 is always possible
    if (ind == 0) return arr[0] == target; // Only one element to check

    // Recursive cases
    bool notTake = subsetSumToKHelper(ind - 1, target, arr); // Do not include current element
    bool take = false;
    if (arr[ind] <= target)                                 // Include current element if possible
        take = subsetSumToKHelper(ind - 1, target - arr[ind], arr);

    return take || notTake; // Return true if either take or notTake is true
}

bool subsetSumToK(int n, int k, vector<int> &arr) {
    return subsetSumToKHelper(n - 1, k, arr);
}



//Memoization
bool f(int ind, int target, vector<int> &arr, vector<vector<int>> &dp) {
    if (target == 0) return true;
    if (ind == 0) return arr[0] == target;
    if (dp[ind][target] != -1) return dp[ind][target];

    bool notTake = f(ind - 1, target, arr, dp);
    bool take = false;
    if (arr[ind] <= target) take = f(ind - 1, target - arr[ind], arr, dp);

    return dp[ind][target] = take || notTake;
}

bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));
    return f(n - 1, k, arr, dp);
}


//Tabulation
bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));

    // Base cases
    for (int i = 0; i < n; i++) dp[i][0] = true;
    if (arr[0] <= k) dp[0][arr[0]] = true;

    for (int ind = 1; ind < n; ind++) {
        for (int target = 1; target <= k; target++) {
            bool notTake = dp[ind - 1][target];
            bool take = false;
            if (arr[ind] <= target) take = dp[ind - 1][target - arr[ind]];

            dp[ind][target] = take || notTake;
        }
    }

    return dp[n - 1][k];
}


//Space Optimization
bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<bool> prev(k + 1, false);

    // Base cases
    prev[0] = true;
    if (arr[0] <= k) prev[arr[0]] = true;

    for (int ind = 1; ind < n; ind++) {
        vector<bool> curr(k + 1, false);
        curr[0] = true;
        for (int target = 1; target <= k; target++) {
            bool notTake = prev[target];
            bool take = false;
            if (arr[ind] <= target) take = prev[target - arr[ind]];

            curr[target] = take || notTake;
        }
        prev = curr;
    }

    return prev[k];
}



