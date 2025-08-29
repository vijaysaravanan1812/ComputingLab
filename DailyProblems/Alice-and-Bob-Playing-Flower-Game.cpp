class Solution {
public:
    long long flowerGame(int n, int m) {
        // Use long long to prevent overflow during multiplication
        long long N = n;
        long long M = m;

        // Number of odd and even numbers in the range [1, n]
        long long odd_n = (N + 1) / 2;
        long long even_n = N / 2;

        // Number of odd and even numbers in the range [1, m]
        long long odd_m = (M + 1) / 2;
        long long even_m = M / 2;

        // Case 1 (x is odd, y is even) + Case 2 (x is even, y is odd)
        return (odd_n * even_m) + (even_n * odd_m);
    }
};