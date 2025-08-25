class Solution {
public:
    double soupServings(int n) {
        // For very large n, probability approaches 1
        if (n >= 4800) return 1.0;

        int m = (n + 24) / 25; // scale to units of 25 mL

        // memoization table initialized to -1 (uncomputed)
        vector<vector<double>> dp(m + 1, vector<double>(m + 1, -1.0));

        function<double(int,int)> f = [&](int a, int b) -> double {
            // base cases
            if (a <= 0 && b <= 0) return 0.5;
            if (a <= 0 && b > 0) return 1.0;
            if (a > 0 && b <= 0) return 0.0;

            // memo check
            if (dp[a][b] >= 0.0) return dp[a][b];

            // recurrence: average of the 4 possible operations
            dp[a][b] = 0.25 * (
                f(a - 4, b) +
                f(a - 3, b - 1) +
                f(a - 2, b - 2) +
                f(a - 1, b - 3)
            );

            return dp[a][b];
        };

        return f(m, m);
    }
};