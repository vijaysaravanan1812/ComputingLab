class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {

        int n = nums.size();
        vector<int> increasing(n, 1);
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) {
                increasing[i] += increasing[i - 1];
            } else {
                increasing[i] = 1;
            }
        }
        for (int i = k; i < n; i++) {
            // first subarray: ends at i-1, second subarray: ends at i+k-1
            if (increasing[i - 1] >= k) {
                int len = 1;
                // compute second subarray increasing length
                for (int j = i + 1; j < n && nums[j] > nums[j - 1]; j++)
                    len++;
                if (len >= k)
                    return true;
            }
        }
        return false;
    }
};