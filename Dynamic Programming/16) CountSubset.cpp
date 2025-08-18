

//Recursion
#include <iostream>
using namespace std;

int countSubsetsRecursive(int arr[], int n, int target) {
    if (target == 0) return 1; // Found a subset
    if (n == 0) return 0;      // No more elements to consider

    // Exclude the current element
    int exclude = countSubsetsRecursive(arr, n - 1, target);

    // Include the current element if it's less than or equal to the target
    int include = 0;
    if (arr[n - 1] <= target)
        include = countSubsetsRecursive(arr, n - 1, target - arr[n - 1]);

    return include + exclude;
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 4;

    cout << "Number of subsets: " << countSubsetsRecursive(arr, n, target) << endl;
    return 0;
}

//Memoization
#include <iostream>
#include <vector>
using namespace std;

int countSubsetsMemoization(int arr[], int n, int target, vector<vector<int>> &dp) {
    if (target == 0) return 1; // Found a subset
    if (n == 0) return 0;      // No more elements to consider

    if (dp[n][target] != -1) return dp[n][target]; // Return cached result

    // Exclude the current element
    int exclude = countSubsetsMemoization(arr, n - 1, target, dp);

    // Include the current element if it's less than or equal to the target
    int include = 0;
    if (arr[n - 1] <= target)
        include = countSubsetsMemoization(arr, n - 1, target - arr[n - 1], dp);

    return dp[n][target] = include + exclude;
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 4;

    vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));

    cout << "Number of subsets: " << countSubsetsMemoization(arr, n, target, dp) << endl;
    return 0;
}


//Tabulation
#include <iostream>
#include <vector>
using namespace std;

int countSubsetsTabulation(int arr[], int n, int target) {
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

    // Base case: target = 0 can always be achieved with an empty subset
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int t = 1; t <= target; t++) {
            // Exclude the current element
            dp[i][t] = dp[i - 1][t];

            // Include the current element if it's less than or equal to the target
            if (arr[i - 1] <= t)
                dp[i][t] += dp[i - 1][t - arr[i - 1]];
        }
    }

    return dp[n][target];
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 4;

    cout << "Number of subsets: " << countSubsetsTabulation(arr, n, target) << endl;
    return 0;
}

//Space Optimization
int findWays(vector<int>& num, int tar) {
    int n = num.size();
    vector<int> prev(tar + 1, 0), cur(tar + 1);
    prev[0] = cur[0] = 1;
    if (num[0] <= tar) prev[num[0]] = 1;

    for (int ind = 1; ind < n; ind++) {
        for (int sum = 0; sum <= tar; sum++) {
            int notTake = prev[sum];
            int take = 0;
            if (num[ind] <= sum) take = prev[sum - num[ind]];
            cur[sum] = notTake + take;
        }
        prev = cur;
    }
    return prev[tar];
}