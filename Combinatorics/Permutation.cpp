
//https://leetcode.com/problems/permutations/description/

class Solution {
  void backtrack(vector<int>& state, 
               vector<int>& choices, 
               vector<bool>& used, vector<vector<int>> &res) {
    if (state.size() == choices.size()) {
        res.push_back(state);
        return;
    }

    for (int i = 0; i < choices.size(); i++) {
        if (!used[i]) {
            state.push_back(choices[i]);
            used[i] = true;

            backtrack(state, choices, used, res);

            state.pop_back();    // undo
            used[i] = false;     // undo
        }
    }
}
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> choices = nums;
        vector<int> state;
        vector<bool> used(choices.size(), false);

        backtrack(state, choices, used, res);

        return res;
    }
};


