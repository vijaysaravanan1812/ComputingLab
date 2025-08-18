

// recursion solution
int f(int i, int j1, int j2, int r, int c, vector<vector<int>> &grid) {
    // Base cases
    if (j1 < 0 || j2 < 0 || j1 >= c || j2 >= c) {
        return -1e8;
    }
    if (i == r - 1) {
        if (j1 == j2) 
            return grid[i][j1];
        else 
            return grid[i][j1] + grid[i][j2];
    }

    // Explore all paths of Alice and Bob simultaneously
    int maxi = -1e8;
    for (int dj1 = -1; dj1 <= +1; dj1++) {
        for (int dj2 = -1; dj2 <= +1; dj2++) {
            int value = 0;
            if (j1 == j2) 
                value = grid[i][j1];
            else 
                value = grid[i][j1] + grid[i][j2];
            value += f(i + 1, j1 + dj1, j2 + dj2, r, c, grid);
            maxi = max(maxi, value);
        }
    }
    return maxi;
}

int getMaxChocolates(int r, int c, vector<vector<int>> &grid) {
    return f(0, 0, c - 1, r, c, grid);
}



// Memoization
int f(int i, int j1, int j2, int r, int c, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp) {
    // Base cases
    if (j1 < 0 || j2 < 0 || j1 >= c || j2 >= c) {
        return -1e8; // Invalid move
    }
    if (i == r - 1) { // Last row
        if (j1 == j2) 
            return grid[i][j1];
        else 
            return grid[i][j1] + grid[i][j2];
    }

    // Check if already computed
    if (dp[i][j1][j2] != -1) {
        return dp[i][j1][j2];
    }

    // Explore all paths of Alice and Bob simultaneously
    int maxi = -1e8;
    for (int dj1 = -1; dj1 <= +1; dj1++) {
        for (int dj2 = -1; dj2 <= +1; dj2++) {
            int value = 0;
            if (j1 == j2) 
                value = grid[i][j1];
            else 
                value = grid[i][j1] + grid[i][j2];
            value += f(i + 1, j1 + dj1, j2 + dj2, r, c, grid, dp);
            maxi = max(maxi, value);
        }
    }

    // Store the result in the DP table
    return dp[i][j1][j2] = maxi;
}

int getMaxChocolates(int r, int c, vector<vector<int>> &grid) {
    // Initialize DP table with -1
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, -1)));
    return f(0, 0, c - 1, r, c, grid, dp);
}


// Tabulation
int getMaxChocolates(int r, int c, vector<vector<int>> &grid) {
    // Initialize a 3D DP table
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, 0)));

    // Base case: Fill the last row
    for (int j1 = 0; j1 < c; j1++) {
        for (int j2 = 0; j2 < c; j2++) {
            if (j1 == j2) {
                dp[r - 1][j1][j2] = grid[r - 1][j1];
            } else {
                dp[r - 1][j1][j2] = grid[r - 1][j1] + grid[r - 1][j2];
            }
        }
    }

    // Fill the DP table from the second last row to the first row
    for (int i = r - 2; i >= 0; i--) {
        for (int j1 = 0; j1 < c; j1++) {
            for (int j2 = 0; j2 < c; j2++) {
                int maxi = -1e8;

                // Explore all possible moves for Alice and Bob
                for (int dj1 = -1; dj1 <= +1; dj1++) {
                    for (int dj2 = -1; dj2 <= +1; dj2++) {
                        int value = 0;

                        if (j1 == j2) {
                            value = grid[i][j1];
                        } else {
                            value = grid[i][j1] + grid[i][j2];
                        }

                        int nextJ1 = j1 + dj1;
                        int nextJ2 = j2 + dj2;

                        // Check bounds for the next positions
                        if (nextJ1 >= 0 && nextJ1 < c && nextJ2 >= 0 && nextJ2 < c) {
                            value += dp[i + 1][nextJ1][nextJ2];
                        } else {
                            value += -1e8; // Invalid move
                        }

                        maxi = max(maxi, value);
                    }
                }

                dp[i][j1][j2] = maxi;
            }
        }
    }

    // The answer is the maximum chocolates collected starting from (0, 0) and (0, c-1)
    return dp[0][0][c - 1];
}



//Space optimization
int getMaxChocolates(int r, int c, vector<vector<int>> &grid) {
    // Two 2D DP tables for current and next rows
    vector<vector<int>> next(c, vector<int>(c, 0)), curr(c, vector<int>(c, 0));

    // Base case: Fill the last row
    for (int j1 = 0; j1 < c; j1++) {
        for (int j2 = 0; j2 < c; j2++) {
            if (j1 == j2) {
                next[j1][j2] = grid[r - 1][j1];
            } else {
                next[j1][j2] = grid[r - 1][j1] + grid[r - 1][j2];
            }
        }
    }

    // Fill the DP table from the second last row to the first row
    for (int i = r - 2; i >= 0; i--) {
        for (int j1 = 0; j1 < c; j1++) {
            for (int j2 = 0; j2 < c; j2++) {
                int maxi = -1e8;

                // Explore all possible moves for Alice and Bob
                for (int dj1 = -1; dj1 <= +1; dj1++) {
                    for (int dj2 = -1; dj2 <= +1; dj2++) {
                        int value = 0;

                        if (j1 == j2) {
                            value = grid[i][j1];
                        } else {
                            value = grid[i][j1] + grid[i][j2];
                        }

                        int nextJ1 = j1 + dj1;
                        int nextJ2 = j2 + dj2;

                        // Check bounds for the next positions
                        if (nextJ1 >= 0 && nextJ1 < c && nextJ2 >= 0 && nextJ2 < c) {
                            value += next[nextJ1][nextJ2];
                        } else {
                            value += -1e8; // Invalid move
                        }

                        maxi = max(maxi, value);
                    }
                }

                curr[j1][j2] = maxi;
            }
        }
        // Swap the current and next rows
        next = curr;
    }

    // The answer is the maximum chocolates collected starting from (0, 0) and (0, c-1)
    return next[0][c - 1];
}
