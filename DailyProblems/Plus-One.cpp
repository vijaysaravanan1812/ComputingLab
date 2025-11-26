1class Solution {
2public:
3    vector<int> plusOne(vector<int>& digits) {
4        int n = digits.size();
5
6        // Start from last digit
7        for (int i = n - 1; i >= 0; i--) {
8            if (digits[i] < 9) {
9                digits[i]++;   // no carry
10                return digits;
11            }
12            // if digits[i] == 9
13            digits[i] = 0;     // set to 0 and continue
14        }
15
16        // If all digits were 9 (e.g., 9,99,999)
17        digits.insert(digits.begin(), 1);
18        return digits;
19    }
20};
21