class Solution {
    int Sum_(vector<vector<int>> &triangle, int i , int j, vector<vector<int>> &dp){
        if(i == triangle.size() -1)
            return triangle[i][j];
        if(dp[i][j] != -1)
            return dp[i][j];
        if(i < j ){
            cout<<"error\n"<< i<< " " << j <<"\n";
                        return dp[i][j] = INT_MAX;
        }

        int sum = triangle[i][j] + min(Sum_(triangle, i + 1, j, dp ) , Sum_(triangle, i + 1, j + 1, dp));
        return dp[i][j] = sum;
    }
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size(), m =triangle.size() ;  // example dimensions

   
           
        if (n == 0) return 0;

        // Create a dp table to store the minimum path sum from each cell
        vector<vector<int>> dp = triangle;
        for (int i = n - 2; i >= 0; --i) {
            // Iterate through each element in the current row
            for (int j = 0; j <= i; ++j) {
                // The minimum path from (i, j) is its value plus the minimum 
                // of the two paths directly below it.
                dp[i][j] = triangle[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
            }
        }
        return dp[0][0];

    }
};