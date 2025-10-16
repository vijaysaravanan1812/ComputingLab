class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        int num ;
        unordered_map<int , int > mp;
        for(int i = 0 ; i < nums.size() ; i++){
            num  = nums[i];
            if(num < 0){
                num = (num % value) + value;
            }
            num = num % value;
            mp[num]++;

        }
        int ans = 0 ; int req_val = 0;
        while(1){ 
            if(mp[req_val] > 0){
                mp[req_val]--;
                ans++;
            }else{
                break;
            }
            req_val = (req_val + 1) % value;
        }
        return ans;
    }
};