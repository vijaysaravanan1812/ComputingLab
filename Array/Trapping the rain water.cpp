class Solution {
public:
    int trap(vector<int>& height) {
        vector<int> PrefixMax(height.size() , 0);
        vector<int> SuffixMax(height.size() , 0);
        int MaxFromLeft = 0, MaxFromRight = 0;

        // Computing the prefix sum
        int i = 0;
        while(i < height.size()){
            if(MaxFromLeft < height[i]){
                MaxFromLeft = height[i];
            }
            PrefixMax[i] = MaxFromLeft;
            i++;
        }

        // Computing the suffix sum
        int j = height.size() - 1; 
        while(j >= 0){
            if(MaxFromRight  <  height[j]){
                MaxFromRight = height[j];
            }
            SuffixMax[j] =  MaxFromRight;
            j--;
        }
        // Compute the amount of water stored on each height
        int WaterStored = 0;
        for(int i = 0 ; i < height.size() ; i++){
            WaterStored += min(PrefixMax[i] , SuffixMax[i]) - height[i]; 
        }

        return WaterStored;

    }
};