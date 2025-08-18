

//Recursive solution
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int f(int ind, int W, vector<int> &wt, vector<int> &val) {
    if (ind == 0) {
        if (wt[0] <= W) return val[0];
        return 0;
    }

    int notTake = 0 + f(ind - 1, W, wt, val);
    int take = INT_MIN;
    if (wt[ind] <= W) {
        take = val[ind] + f(ind - 1, W - wt[ind], wt, val);
    }

    return max(take, notTake);
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) {
    return f(n - 1, maxWeight, weight, value);
}

int main() {
    vector<int> weight = {1, 2, 4, 5};
    vector<int> value = {5, 4, 8, 6};
    int maxWeight = 5;
    int n = weight.size();

    cout << "Maximum value: " << knapsack(weight, value, n, maxWeight) << endl;
    return 0;
}



//Memoization
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int f(int ind, int W, vector<int> &wt, vector<int> &val, vector<vector<int>> &dp) {
    if (ind == 0) {
        if (wt[0] <= W) return val[0];
        return 0;
    }

    if (dp[ind][W] != -1) return dp[ind][W];

    int notTake = 0 + f(ind - 1, W, wt, val, dp);
    int take = INT_MIN;
    if (wt[ind] <= W) {
        take = val[ind] + f(ind - 1, W - wt[ind], wt, val, dp);
    }

    return dp[ind][W] = max(take, notTake);
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) {
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
    return f(n - 1, maxWeight, weight, value, dp);
}

int main() {
    vector<int> weight = {1, 2, 4, 5};
    vector<int> value = {5, 4, 8, 6};
    int maxWeight = 5;
    int n = weight.size();

    cout << "Maximum value: " << knapsack(weight, value, n, maxWeight) << endl;
    return 0;
}


//Tabulation
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) {
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, 0));

    for (int W = weight[0]; W <= maxWeight; W++) {
        dp[0][W] = value[0];
    }

    for (int ind = 1; ind < n; ind++) {
        for (int W = 0; W <= maxWeight; W++) {
            int notTake = dp[ind - 1][W];
            int take = INT_MIN;
            if (weight[ind] <= W) {
                take = value[ind] + dp[ind - 1][W - weight[ind]];
            }
            dp[ind][W] = max(take, notTake);
        }
    }

    return dp[n - 1][maxWeight];
}

int main() {
    vector<int> weight = {1, 2, 4, 5};
    vector<int> value = {5, 4, 8, 6};
    int maxWeight = 5;
    int n = weight.size();

    cout << "Maximum value: " << knapsack(weight, value, n, maxWeight) << endl;
    return 0;
}
