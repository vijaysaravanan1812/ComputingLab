class Solution {
public:
    // Return the length of the smallest repunit (111...1) divisible by k,
    // or -1 if no such repunit exists (cycle detected).
    int smallestRepunitDivByK(int k) {
        if (k == 0) return -1;            // avoid division/modulo by zero
        unordered_set<int> seen;          // remainders seen so far
        int cur = 1 % k;                  // remainder of "1"
        int res = 1;                      // length of current repunit ("1" has length 1)

        while (cur != 0) {                // while not divisible
            if (seen.count(cur)) return -1;   // cycle -> no solution
            seen.insert(cur);
            // append '1' to the repunit: remainder of (repunit*10 + 1)
            cur = (cur * 10 + 1) % k;
            ++res;
        }

        return res;
    }
};