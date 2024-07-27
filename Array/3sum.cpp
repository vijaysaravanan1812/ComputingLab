class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin() , nums.end());
        set<vector<int>> Result; int left, right ;
        for(int i = 0 ; i < nums.size() - 2 ; i++){
            int left = i + 1; 
            int right = nums.size() - 1;
            while(left < right){
                int sum = nums[i] + nums[left] + nums[right];
                if(sum == 0){
                    Result.insert({nums[i], nums[left], nums[right]});
                    left++;
                    right--;
                }else if(sum < 0){
                    left++;
                }else if(sum > 0){
                    right--;
                }

            }
        }
        vector<vector<int>> ans;
        for(auto num : Result){
            ans.push_back(num);
        }
        return ans;
    }
};