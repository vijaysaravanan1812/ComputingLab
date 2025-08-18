

//Recursive solution
int f(int ind, int N, vector<int> &price) {
    if (ind == 0) {
        return N * price[0]; // Use as many pieces of length 1 as possible
    }

    // Option 1: Do not take the current length
    int notTake = f(ind - 1, N, price);

    // Option 2: Take the current length (if possible)
    int take = INT_MIN;
    int rodLength = ind + 1;
    if (rodLength <= N) {
        take = price[ind] + f(ind, N - rodLength, price);
    }

    return max(take, notTake);
}

int cutRod(vector<int> &price, int N) {
    return f(price.size() - 1, N, price);
}


//Memoization
int f(int ind, int N, vector<int> &price, vector<vector<int>> &dp) {
    if (ind == 0) {
        return N * price[0];
    }

    if (dp[ind][N] != -1) return dp[ind][N];

    int notTake = f(ind - 1, N, price, dp);
    int take = INT_MIN;
    int rodLength = ind + 1;
    if (rodLength <= N) {
        take = price[ind] + f(ind, N - rodLength, price, dp);
    }

    return dp[ind][N] = max(take, notTake);
}

int cutRod(vector<int> &price, int N) {
    int n = price.size();
    vector<vector<int>> dp(n, vector<int>(N + 1, -1));
    return f(n - 1, N, price, dp);
}


//Tabulation
int cutRod(vector<int> &price, int N) {
    int n = price.size();
    vector<vector<int>> dp(n, vector<int>(N + 1, 0));

    // Base case: Fill for the first row
    for (int len = 0; len <= N; len++) {
        dp[0][len] = len * price[0];
    }

    for (int ind = 1; ind < n; ind++) {
        for (int len = 0; len <= N; len++) {
            int notTake = dp[ind - 1][len];
            int take = INT_MIN;
            int rodLength = ind + 1;
            if (rodLength <= len) {
                take = price[ind] + dp[ind][len - rodLength];
            }
            dp[ind][len] = max(take, notTake);
        }
    }

    return dp[n - 1][N];
}


//Space Optimization
int cutRod(vector<int> &price, int N) {
    int n = price.size();
    vector<int> dp(N + 1, 0);

    // Base case: Fill for the first item
    for (int len = 0; len <= N; len++) {
        dp[len] = len * price[0];
    }

    for (int ind = 1; ind < n; ind++) {
        for (int len = 0; len <= N; len++) {
            int take = INT_MIN;
            int rodLength = ind + 1;
            if (rodLength <= len) {
                take = price[ind] + dp[len - rodLength];
            }
            dp[len] = max(dp[len], take);
        }
    }

    return dp[N];
}
