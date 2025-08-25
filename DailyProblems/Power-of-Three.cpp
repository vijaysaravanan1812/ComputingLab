class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n <= 0)
            return false;
        int count = 0;
        while(n > 0){
            int digit = n % 3;
            if(digit == 1) count++;
            if(digit == 2) return false;
            n = n/3;
        }
        return count== 1;
    }
};