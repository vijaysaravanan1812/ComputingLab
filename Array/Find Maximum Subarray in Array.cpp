class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0 ; 
        int Maximum = INT_MIN;
        for(int i = 0 ; i < nums.size() ; i++){
            sum += nums[i];
            Maximum = max(sum , Maximum);
            if(sum < 0) sum = 0; 
        }
        return Maximum;
    }
};