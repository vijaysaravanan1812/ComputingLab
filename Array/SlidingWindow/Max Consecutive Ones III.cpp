
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        
        int right = 0 , left = 0;
        int maxLength = 0;

        while(right < nums.size()){
         
          if(nums[right] == 0){
            k--;
          }  
          if(k < 0){
            if(nums[left] == 0){
                k++;
            }
        
            left++;
          }
          maxLength = max(maxLength , right - left + 1);
          right++;
        }
        return maxLength;
    }
};