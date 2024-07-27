class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int prefix = 1, suffix = 1;
        int MaxProduct = INT_MIN;
        for(int i = 0 ; i < nums.size() ; i++){

            if(prefix == 0) prefix = 1;
            if(suffix == 0) suffix = 1;

            prefix = prefix * nums[i];
            suffix = suffix * nums[nums.size() - i - 1];
            
            MaxProduct = max(MaxProduct, max(prefix , suffix));

        }

        return MaxProduct;
    }
};