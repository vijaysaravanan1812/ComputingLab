class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        unordered_map<int , int > Map;
        for(int i = 0 ; i < nums.size();i++){
            Map[nums[i]]++;
        }
        int MaxFrequency = INT_MIN;
        for(auto x : Map){
            if(x.second > MaxFrequency){
                MaxFrequency = x.second;
            }
        }
        int count = 0;
        for(auto x : Map){
            if(x.second == MaxFrequency){
                count++;
            }
        }
        return  count * MaxFrequency;
    }
};