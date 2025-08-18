

//Brute force
#include <iostream>
#include <climits>
using namespace std;

// Recursive function
int minElements(int arr[], int index, int target) {
    if (index == 0) {
        // Base case: If only one coin type is left
        if (target % arr[0] == 0) return target / arr[0];
        return INT_MAX;
    }

    // Not take: Move to the next index
    int notTake = minElements(arr, index - 1, target);

    // Take: Stay at the same index (due to infinite supply)
    int take = INT_MAX;
    if (arr[index] <= target) {
        int subRes = minElements(arr, index, target - arr[index]);
        if (subRes != INT_MAX) take = 1 + subRes;
    }

    // Return the minimum of both
    return min(notTake, take);
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int X = 7;

    int result = minElements(arr, n - 1, X);
    if (result == INT_MAX) {
        cout << "-1 (Not possible)" << endl;
    } else {
        cout << "Minimum elements: " << result << endl;
    }
    return 0;
}


//Memoization
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Recursive function with memoization
int minElementsUtil(int arr[], int index, int target, vector<vector<int>>& dp) {
    if (index == 0) {
        // Base case: If only one coin type is left
        if (target % arr[0] == 0) return target / arr[0];
        return INT_MAX;
    }

    if (dp[index][target] != -1) return dp[index][target];

    // Not take: Move to the next index
    int notTake = minElementsUtil(arr, index - 1, target, dp);

    // Take: Stay at the same index (due to infinite supply)
    int take = INT_MAX;
    if (arr[index] <= target) {
        int subRes = minElementsUtil(arr, index, target - arr[index], dp);
        if (subRes != INT_MAX) take = 1 + subRes;
    }

    // Store and return the result
    return dp[index][target] = min(notTake, take);
}

int minElements(int arr[], int n, int X) {
    vector<vector<int>> dp(n, vector<int>(X + 1, -1)); // Memoization table
    int result = minElementsUtil(arr, n - 1, X, dp);
    return (result == INT_MAX) ? -1 : result;
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int X = 7;

    int result = minElements(arr, n, X);
    cout << "Minimum elements: " << result << endl;
    return 0;
}


//Tabulation
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int minElements(int arr[], int n, int X) {
    vector<vector<int>> dp(n, vector<int>(X + 1, INT_MAX));

    // Base case: If index is 0
    for (int t = 0; t <= X; t++) {
        if (t % arr[0] == 0) dp[0][t] = t / arr[0];
    }

    // Fill the DP table
    for (int i = 1; i < n; i++) {
        for (int t = 0; t <= X; t++) {
            int notTake = dp[i - 1][t];
            int take = INT_MAX;
            if (arr[i] <= t && dp[i][t - arr[i]] != INT_MAX) {
                take = 1 + dp[i][t - arr[i]];
            }
            dp[i][t] = min(notTake, take);
        }
    }

    return (dp[n - 1][X] == INT_MAX) ? -1 : dp[n - 1][X];
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int X = 7;

    int result = minElements(arr, n, X);
    cout << "Minimum elements: " << result << endl;
    return 0;
}


//Space Optimization
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int minElements(int arr[], int n, int X) {
    vector<int> dp(X + 1, INT_MAX);

    // Base case: If index is 0
    for (int t = 0; t <= X; t++) {
        if (t % arr[0] == 0) dp[t] = t / arr[0];
    }

    // Fill the DP array
    for (int i = 1; i < n; i++) {
        for (int t = X; t >= 0; t--) {
            if (arr[i] <= t && dp[t - arr[i]] != INT_MAX) {
                dp[t] = min(dp[t], 1 + dp[t - arr[i]]);
            }
        }
    }

    return (dp[X] == INT_MAX) ? -1 : dp[X];
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int X = 7;

    int result = minElements(arr, n, X);
    cout << "Minimum elements: " << result << endl;
    return 0;
}
