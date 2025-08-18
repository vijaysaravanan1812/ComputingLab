
// https://leetcode.com/problems/combination-sum-ii/
class Solution {
    void FindCombination(int index , int target , vector<int>& current , vector<int>& candidates , vector<vector<int>>& result){
        if(target == 0){
            result.push_back(current);
            return;
        }

        for(int i = index ; i < candidates.size(); i++ ){
                 if(i > index && candidates[i] == candidates[i-1]) continue;
            if(candidates[i] <= target){
                current.push_back(candidates[i]);
                FindCombination(i + 1 , target - candidates[i] , current , candidates, result);
                current.pop_back();
            }
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
           sort(candidates.begin(), candidates.end()); 
        vector<int> current;
        FindCombination(0, target , current , candidates, result);
        return result;
    }
};