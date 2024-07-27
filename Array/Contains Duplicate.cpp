class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        
        //Key --> index and value --> Count  
        unordered_map<int, int> Map;
        int count = 0; 
        for(int i = 0 ; i < nums.size() ; i++ ){
            if(Map.find(nums[i]) != Map.end()){
                Map[nums[i]]++;
            }else{
                Map[nums[i]] = 1;
            }
        }
      

        for(int i = 0 ; i < nums.size() ; i++){
            if(Map[nums[i]] != 1){
                return true;
            }
        }
        return false;
    }
};