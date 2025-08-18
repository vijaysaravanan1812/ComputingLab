

//Recursive Solution
bool canPartitionHelper(int ind, int target, vector<int> &arr) {
    if (target == 0) return true;         // Subset with sum 0 is always possible
    if (ind == 0) return arr[0] == target; // Check if the first element equals target

    // Recursive cases
    bool notTake = canPartitionHelper(ind - 1, target, arr);
    bool take = false;
    if (arr[ind] <= target)
        take = canPartitionHelper(ind - 1, target - arr[ind], arr);

    return take || notTake;
}

bool canPartition(vector<int> &arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 2 != 0) return false; // If total sum is odd, partition is not possible
    int target = sum / 2;
    return canPartitionHelper(arr.size() - 1, target, arr);
}

//Memoization
bool canPartitionHelper(int ind, int target, vector<int> &arr, vector<vector<int>> &dp) {
    if (target == 0) return true; // Subset with sum 0 is always possible
    if (ind == 0) return arr[0] == target; // Only one element to check

    if (dp[ind][target] != -1) return dp[ind][target]; // Check memoized result

    // Recursive cases
    bool notTake = canPartitionHelper(ind - 1, target, arr, dp);
    bool take = false;
    if (arr[ind] <= target)
        take = canPartitionHelper(ind - 1, target - arr[ind], arr, dp);

    return dp[ind][target] = take || notTake;
}

bool canPartition(vector<int> &arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 2 != 0) return false; // If total sum is odd, partition is not possible

    int target = sum / 2;
    vector<vector<int>> dp(arr.size(), vector<int>(target + 1, -1));
    return canPartitionHelper(arr.size() - 1, target, arr, dp);
}


//Tabulation
bool canPartition(vector<int> &arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 2 != 0) return false; // If total sum is odd, partition is not possible

    int target = sum / 2;
    int n = arr.size();
    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

    // Base cases
    for (int i = 0; i < n; i++) dp[i][0] = true; // Subset with sum 0 is always possible
    if (arr[0] <= target) dp[0][arr[0]] = true; // First element can form subset if <= target

    // Fill the dp table
    for (int ind = 1; ind < n; ind++) {
        for (int t = 1; t <= target; t++) {
            bool notTake = dp[ind - 1][t];
            bool take = false;
            if (arr[ind] <= t)
                take = dp[ind - 1][t - arr[ind]];

            dp[ind][t] = take || notTake;
        }
    }

    return dp[n - 1][target];
}



//Space Optimization
bool canPartition(vector<int> &arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 2 != 0) return false; // If total sum is odd, partition is not possible

    int target = sum / 2;
    vector<bool> prev(target + 1, false);

    // Base cases
    prev[0] = true; // Subset with sum 0 is always possible
    if (arr[0] <= target) prev[arr[0]] = true; // First element can form subset if <= target

    // Fill the dp array
    for (int ind = 1; ind < arr.size(); ind++) {
        for (int t = target; t >= 0; t--) {
            bool notTake = prev[t];
            bool take = false;
            if (arr[ind] <= t)
                take = prev[t - arr[ind]];

            prev[t] = take || notTake;
        }
    }

    return prev[target];
}

