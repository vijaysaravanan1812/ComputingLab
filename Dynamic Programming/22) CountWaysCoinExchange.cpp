
//Recursive solution
long f(int ind, int T, int *a) {
    // Base case: If we are at the first coin
    if (ind == 0) {
        // Check if T is divisible by the first coin
        return (T % a[0] == 0);
    }

    // Recursive case
    long nonTake = f(ind - 1, T, a); // Do not take the current coin
    long take = 0;
    if (a[ind] <= T) {
        take = f(ind, T - a[ind], a); // Take the current coin
    }

    return take + nonTake; // Total ways
}

long countWaysToMakeChange(int *denominations, int n, int value) {
    return f(n - 1, value, denominations);
}


//Memoization
#include <cstring> // For memset

long f(int ind, int T, int *a, long **dp) {
    if (ind == 0) {
        return (T % a[0] == 0); // If divisible, there's one way; otherwise, zero ways.
    }
    if (dp[ind][T] != -1) return dp[ind][T];

    long nonTake = f(ind - 1, T, a, dp);
    long take = 0;
    if (a[ind] <= T) take = f(ind, T - a[ind], a, dp);

    return dp[ind][T] = take + nonTake;
}

long countWaysToMakeChange(int *denominations, int n, int value) {
    long **dp = new long*[n];
    for (int i = 0; i < n; i++) {
        dp[i] = new long[value + 1];
        memset(dp[i], -1, sizeof(long) * (value + 1));
    }
    long result = f(n - 1, value, denominations, dp);
    for (int i = 0; i < n; i++) delete[] dp[i];
    delete[] dp;
    return result;
}


//Tabulation
long countWaysToMakeChange(int *denominations, int n, int value) {
    long dp[n][value + 1];

    // Base case: If T = 0, there's one way (choose no coins)
    for (int i = 0; i < n; i++) dp[i][0] = 1;

    // Base case: If only the first coin is available
    for (int T = 1; T <= value; T++) {
        dp[0][T] = (T % denominations[0] == 0);
    }

    // Fill the DP table
    for (int ind = 1; ind < n; ind++) {
        for (int T = 1; T <= value; T++) {
            long nonTake = dp[ind - 1][T];
            long take = 0;
            if (denominations[ind] <= T) take = dp[ind][T - denominations[ind]];
            dp[ind][T] = take + nonTake;
        }
    }

    return dp[n - 1][value];
}


//Space Optimization
long countWaysToMakeChange(int *denominations, int n, int value) {
    long prev[value + 1], curr[value + 1];

    // Base case: If T = 0, there's one way (choose no coins)
    memset(prev, 0, sizeof(prev));
    prev[0] = 1;

    for (int T = 1; T <= value; T++) {
        prev[T] = (T % denominations[0] == 0);
    }

    for (int ind = 1; ind < n; ind++) {
        curr[0] = 1; // Base case for current row
        for (int T = 1; T <= value; T++) {
            long nonTake = prev[T];
            long take = 0;
            if (denominations[ind] <= T) take = curr[T - denominations[ind]];
            curr[T] = take + nonTake;
        }
        memcpy(prev, curr, sizeof(curr));
    }

    return prev[value];
}
