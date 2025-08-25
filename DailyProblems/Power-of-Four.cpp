class Solution {
    bool hasEvenTrailingZeros_Modulo(unsigned int n) {
        unsigned int lsb = n & -n; // safe in unsigned
        return (lsb - 1) % 3 == 0;
    }
public:
    bool isPowerOfFour(int n) {
        if (n <= 0) return false; // reject negatives and zero
        unsigned int x = n;       // work in unsigned
        if ((x & (x - 1)) != 0) return false; // not power of two
        return hasEvenTrailingZeros_Modulo(x);
    }
};
