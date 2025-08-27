class Solution {   
    // A helper function you will write inside your Solution class
    int explore(vector<vector<int>>& grid, int r, int c, int dir, int expected, bool has_turned,
     vector<vector<vector<vector<int>>>> &dp) {
        
        
        // --- BASE CASES ---
        // Is (r, c) out of bounds? Or is grid[r][c] not the number we expect?
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] != expected) {
            return 0; // What do you return for a broken path?
        }

        int k = (int)has_turned;
        if(dp[r][c][dir][k] != -1)
            return dp[r][c][dir][k];

        // --- RECURSIVE STEP ---
        int dr[] = {1, 1, -1 , -1};
        int dc[] = {1, -1, -1, 1};

        // 1. Explore continuing straight
        int next_r_straight = r + dr[dir];
        int next_c_straight = c + dc[dir];
        int next_expected = 2 - expected; // The next number in the 2,0,2,0 sequence
    
        int len_straight = explore(grid, next_r_straight, next_c_straight, dir, next_expected, has_turned, dp);

        // 2. Explore making a turn (only if we haven't turned yet)
        int len_turned = 0;
        if (!has_turned) {
            int turned_dir = (dir + 1) % 4;
            int next_r_turned = r + dr[turned_dir];
            int next_c_turned = c + dc[turned_dir];

            // The recursive call for the turned path goes here...
            // What arguments do you pass? Pay close attention to the 'has_turned' flag.
            len_turned = explore(grid, next_r_turned, next_c_turned, turned_dir, next_expected, true, dp);
        }

        // 3. Return the length from this point
        return  dp[r][c][dir][k] = 1 + max(len_straight, len_turned);
    }
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        // Inside lenOfVDiagonal...
        int dr[] = {1, 1, -1 , -1};
        int dc[] = {1, -1, -1, 1};

        int maxLength = 0;
        int rows = grid.size();
        int cols = grid[0].size();
                int a = rows, b = cols, c = 4, d = 2; // dimensions

        vector<vector<vector<vector<int>>>> dp(
            a, vector<vector<vector<int>>>(
                b, vector<vector<int>>(
                    c, vector<int>(d, -1)
                )
            )
        );

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // What do you check for here?
                if (grid[i][j] == 1 ) {
                    for(int dir = 0 ; dir < 4 ; dir++){
                        int curMax = explore(grid, i + dr[dir], j + dc[dir], dir, 2, false, dp); 
                        maxLength = max(curMax + 1 , maxLength);
                    }
                    // If it's a valid start, we explore from here.
       
                }
            }
        }
        return maxLength  ;
    }
};