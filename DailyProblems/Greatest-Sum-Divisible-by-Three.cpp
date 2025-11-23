
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        long long total = 0;
        long long smallest_one = LLONG_MAX;  // smallest sum that gives remainder 1
        long long smallest_two = LLONG_MAX;  // smallest sum that gives remainder 2

        for (int n : nums) {
            total += n;
            int r = n % 3;
            if (r == 1) {
                // update smallest_two using current n + previous smallest_one
                if (smallest_one != LLONG_MAX) smallest_two = min(smallest_two, (long long)n + smallest_one);
                // update smallest_one as candidate single element
                smallest_one = min(smallest_one, (long long)n);
            } else if (r == 2) {
                // update smallest_one using current n + previous smallest_two
                if (smallest_two != LLONG_MAX) smallest_one = min(smallest_one, (long long)n + smallest_two);
                // update smallest_two as candidate single element
                smallest_two = min(smallest_two, (long long)n);
            }
        }

        if (total % 3 == 0) {
            return (int)total;
        } else if (total % 3 == 1) {
            if (smallest_one == LLONG_MAX) return 0; // can't fix remainder
            return (int)(total - smallest_one);
        } else { // total % 3 == 2
            if (smallest_two == LLONG_MAX) return 0; // can't fix remainder
            return (int)(total - smallest_two);
        }
    }
};