

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if(nums.size() < 4)
            return {};
        sort(nums.begin() , nums.end());
        set<vector<int>> Result;
        vector<vector<int>> ans;
        long long sum = 0;

        for(int i = 0; i < nums.size() - 3 ; ++i){
            for(int j = i + 1 ; j < nums.size() - 2; ++j){
                int left = j + 1; 
                int right = nums.size() - 1;
             
                while(left < right) {
                    sum = static_cast<long long>(nums[i]) + static_cast<long long>(nums[j]) + static_cast<long long>(nums[left]) + static_cast<long long>(nums[right]);
                    if(sum == target){
                        vector<int> temp;
                        temp.push_back(nums[i]);
                        temp.push_back(nums[j]);
                        temp.push_back(nums[left]);
                        temp.push_back(nums[right]);
                        sort(temp.begin() , temp.end());
                        Result.insert(temp);
                        left++;
                        right--;
                    }else if(sum < target){
                        left++;
                    }else if(sum > target){
                        right--;
                    }
                }
            } 
        }
        for(auto element : Result){
            ans.push_back(element);
        }

        return ans;
    }
};
