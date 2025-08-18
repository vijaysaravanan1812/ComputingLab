class Solution {
    void backtrack(vector<int>& state, 
                   vector<int>& choices, 
                   vector<bool>& used, 
                   vector<vector<int>>& res) {
        if (state.size() == choices.size()) {
            res.push_back(state);
            return;
        }

        for (int i = 0; i < choices.size(); i++) {
            // If already used, skip
            if (used[i]) continue;

            // Skip duplicates:
            // If current number == previous number
            // AND the previous identical number was not used in this branch
            if (i > 0 && choices[i] == choices[i-1] && !used[i-1]) 
                continue;

            state.push_back(choices[i]);
            used[i] = true;

            backtrack(state, choices, used, res);

            state.pop_back();
            used[i] = false;
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> state;
        vector<bool> used(nums.size(), false);

        // Step 1: Sort to handle duplicates
        sort(nums.begin(), nums.end());

        backtrack(state, nums, used, res);
        return res;
    }
};
