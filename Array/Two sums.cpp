class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map <int , int> HashMap;
        for(int i = 0 ; i < nums.size(); i++){
            if (HashMap.find(target - nums[i]) != HashMap.end()){
                return {HashMap[target - nums[i]] , i};
            }
            HashMap[nums[i]] = i;

        }        
        return  {};     
    }
};