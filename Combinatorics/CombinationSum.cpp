//https://leetcode.com/problems/combination-sum/

class Solution {
    void FindCombination(int index , int target , vector<int>& current , vector<int>& candidates , vector<vector<int>>& result){
        if(target == 0){
            result.push_back(current);
            return;
        }

        for(int i = index ; i < candidates.size(); i++ ){
            if(candidates[i] <= target){
                current.push_back(candidates[i]);
                FindCombination(i , target - candidates[i] , current , candidates, result);
                current.pop_back();
            }
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        FindCombination(0, target , current , candidates, result);
        return result;
    }
};