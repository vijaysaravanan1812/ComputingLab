




// Recursive function with memoization
int f(int day, int last, vector<vector<int>> &points, vector<vector<int>> &dp) {

    if (day == 0) {
        int maxi = 0;
        for (int task = 0; task < 3; task++) {
            if (task != last) {
                maxi = max(maxi, points[0][task]);
            }
        }
        return maxi;
    }


    if (dp[day][last] != -1) return dp[day][last];

    int maxi = 0;
    for (int task = 0; task < 3; task++) {
        if (task != last) {
            int point = points[day][task] + f(day - 1, task, points, dp);
            maxi = max(maxi, point);
        }
    }


    return dp[day][last] = maxi;
}

// Main function
int ninjaTraining(int n, vector<vector<int>> &points) {

    vector<vector<int>> dp(n, vector<int>(4, -1));
    return f(n - 1, 3, points, dp);
}

//Tabulation

int ninjaTraining(int n, vector<vector<int>> &points) {
    // DP table: dp[day][last]
    vector<vector<int>> dp(n, vector<int>(4, 0));

    // Base case: Fill for day 0
    dp[0][0] = max(points[0][1], points[0][2]); // If task 0 was last
    dp[0][1] = max(points[0][0], points[0][2]); // If task 1 was last
    dp[0][2] = max(points[0][0], points[0][1]); // If task 2 was last
    dp[0][3] = max({points[0][0], points[0][1], points[0][2]}); // No task restriction

    // Bottom-up DP: Iterate over days
    for (int day = 1; day < n; day++) {
        for (int last = 0; last < 4; last++) {
            dp[day][last] = 0; // Initialize
            for (int task = 0; task < 3; task++) {
                if (task != last) { // Task cannot be same as last day's task
                    int point = points[day][task] + dp[day - 1][task];
                    dp[day][last] = max(dp[day][last], point);
                }
            }
        }
    }


    return dp[n - 1][3];
}


//Space Optimization
int ninjaTraining(int n, vector<vector<int>> &points) {
    vector<int> prev(4, 0); // Store the maximum points for the previous day

    // Base case: 
    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max({points[0][0], points[0][1], points[0][2]}); // No task restriction

    // Iterate over days
    for (int day = 1; day < n; day++) {
        vector<int> curr(4, 0);
        for (int last = 0; last < 4; last++) {
            curr[last] = 0;
            for (int task = 0; task < 3; task++) {
                if (task != last) { // Task cannot be same as last day's task
                    curr[last] = max(curr[last], points[day][task] + prev[task]);
                }
            }
        }
        prev = curr; // Update previous day with current day
    }

    return prev[3]; // Maximum points on the last day with no task restriction
}
