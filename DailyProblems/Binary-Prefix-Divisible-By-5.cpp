class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        int i = 0;
        int cur = 0;
        vector<bool> res;
        while (i < nums.size()) {

            cur = ((cur % 5) << 1) + nums[i];
            if (cur % 5 == 0) {
                res.push_back(true);
            } else {
                res.push_back(false);
            }
            i++;
        }
        return res;
    }
};