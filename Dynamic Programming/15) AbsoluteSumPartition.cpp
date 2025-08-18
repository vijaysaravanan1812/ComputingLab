
//Recursive solution
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int subsetSumRecursive(int ind, int target, vector<int>& arr) {
    if (target == 0) return true; // Subset sum is achieved
    if (ind == 0) return arr[0] == target; // Only one element left to check

    // Not take the current element
    bool notTake = subsetSumRecursive(ind - 1, target, arr);

    // Take the current element if possible
    bool take = false;
    if (arr[ind] <= target) {
        take = subsetSumRecursive(ind - 1, target - arr[ind], arr);
    }

    return take || notTake;
}

int findMinSubsetDifferenceRecursive(vector<int>& arr, int n) {
    int totalSum = 0;
    for (int num : arr) totalSum += num;

    int minDiff = INT_MAX;
    for (int sum1 = 0; sum1 <= totalSum / 2; sum1++) {
        if (subsetSumRecursive(n - 1, sum1, arr)) {
            int sum2 = totalSum - sum1;
            minDiff = min(minDiff, abs(sum2 - sum1));
        }
    }
    return minDiff;
}

int main() {
    vector<int> arr = {1, 6, 11, 5};
    int n = arr.size();
    cout << "Minimum Difference (Recursive): " << findMinSubsetDifferenceRecursive(arr, n) << endl;
    return 0;
}


// Memoization
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool subsetSumMemo(int ind, int target, vector<int>& arr, vector<vector<int>>& dp) {
    if (target == 0) return true;
    if (ind == 0) return arr[0] == target;

    if (dp[ind][target] != -1) return dp[ind][target];

    // Not take the current element
    bool notTake = subsetSumMemo(ind - 1, target, arr, dp);

    // Take the current element if possible
    bool take = false;
    if (arr[ind] <= target) {
        take = subsetSumMemo(ind - 1, target - arr[ind], arr, dp);
    }

    return dp[ind][target] = take || notTake;
}

int findMinSubsetDifferenceMemo(vector<int>& arr, int n) {
    int totalSum = 0;
    for (int num : arr) totalSum += num;

    int k = totalSum / 2;
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));

    int minDiff = INT_MAX;
    for (int sum1 = 0; sum1 <= k; sum1++) {
        if (subsetSumMemo(n - 1, sum1, arr, dp)) {
            int sum2 = totalSum - sum1;
            minDiff = min(minDiff, abs(sum2 - sum1));
        }
    }
    return minDiff;
}

int main() {
    vector<int> arr = {1, 6, 11, 5};
    int n = arr.size();
    cout << "Minimum Difference (Memoization): " << findMinSubsetDifferenceMemo(arr, n) << endl;
    return 0;
}


//Tabulation
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int findMinSubsetDifferenceTabulation(vector<int>& arr, int n) {
    int totalSum = 0;
    for (int num : arr) totalSum += num;

    int k = totalSum / 2;
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));

    // Base case: sum = 0 is always possible
    for (int i = 0; i < n; i++) dp[i][0] = true;

    // Base case: only the first element can form a subset
    if (arr[0] <= k) dp[0][arr[0]] = true;

    // Fill the DP table
    for (int ind = 1; ind < n; ind++) {
        for (int target = 1; target <= k; target++) {
            bool notTake = dp[ind - 1][target];
            bool take = false;
            if (arr[ind] <= target) {
                take = dp[ind - 1][target - arr[ind]];
            }
            dp[ind][target] = take || notTake;
        }
    }

    // Find the largest `sum1` <= totalSum / 2
    int minDiff = INT_MAX;
    for (int sum1 = 0; sum1 <= k; sum1++) {
        if (dp[n - 1][sum1]) {
            int sum2 = totalSum - sum1;
            minDiff = min(minDiff, abs(sum2 - sum1));
        }
    }
    return minDiff;
}

int main() {
    vector<int> arr = {1, 6, 11, 5};
    int n = arr.size();
    cout << "Minimum Difference (Tabulation): " << findMinSubsetDifferenceTabulation(arr, n) << endl;
    return 0;
}
