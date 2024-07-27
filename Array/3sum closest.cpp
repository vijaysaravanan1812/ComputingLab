class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin() , nums.end());
        int MinDifference = INT_MAX;
        int difference = 0 ;
        int ResultSum = nums[0] + nums[1] + nums[2];

        for(int i = 0 ; i < nums.size() - 2; i++){
            int left = i + 1;
            int right = nums.size() - 1;
            while(left < right){
                int sum = nums[left] + nums[right] + nums[i];
                if(sum == target){
                    return sum;
                }else if (sum < target){
                    left++;
                }else if(sum > target) {
                    right--;
                }

                difference = abs(sum - target);
                if(difference < MinDifference){
                    MinDifference = difference;
                    ResultSum = sum;
                }
            } 
        }

        return ResultSum;
    }
};