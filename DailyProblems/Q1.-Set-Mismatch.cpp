class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        set<int> ActualNumber;
        unordered_map<int,int> Map;
        int n = nums.size();

        // fill set with 1..n
        for (int i = 1; i <= n; ++i) ActualNumber.insert(i);

        // count occurrences and remove seen numbers from the set
        for (int x : nums) {
            Map[x]++;
            if (ActualNumber.count(x)) ActualNumber.erase(x);
        }

        int missing = -1, dup = -1;
        for (int i = 1; i <= n; ++i) {
            if (Map[i] > 1) dup = i;
            if (Map[i] == 0) missing = i;
        }
        return {dup, missing};
    }
};
