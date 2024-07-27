class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        
        int N = nums.size() ;
        if (N == 1)
            return ;
        
        //find the peak  
        int i = 1;
        int lastinc = -1;
        while(i < N )
        {
            if(nums[i] > nums[i - 1])
                lastinc = i;
            i++;
        }

         //if no peaks appeared
        if(lastinc == -1){
            sort(nums.begin() , nums.end());
            return;
        }
        
        int index = lastinc;
        for( i = lastinc ; i < N; i++){
            if(nums[lastinc - 1] < nums[i] )
                index = i;
        }
        swap(nums[index] , nums[lastinc - 1]);
        sort(nums.begin() + lastinc , nums.end());
        
    }
};