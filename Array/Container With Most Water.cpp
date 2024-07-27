class Solution {
public:
    int maxArea(vector<int>& height) {
        // int Area = 0, MaxArea = 0;
        // for(int i = 0 ; i < height.size() - 1 ; i++){
        //     for(int j = i + 1 ; j < height.size(); j++){
        //         Area = (((j - i))) * min(height[i] , height[j]);
        //         if(MaxArea < Area){
        //             MaxArea = Area;
        //         }
        //     }
        // }
        // return MaxArea;

        int left = 0, right = height.size() - 1;
        int MaxArea = 0, Area = 0; 
        while(left < right){
            Area = (right - left) * min(height[left] , height[right]);
            if(MaxArea < Area){
                MaxArea  = Area;
            }

            if(height[left] < height[right]){
                left++;
            }else{
                right--;
            }
        }
        return MaxArea;
    }
};