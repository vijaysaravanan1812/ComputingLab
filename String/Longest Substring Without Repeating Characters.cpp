class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map <char , int> Map; 
        int left = 0, right = 0, n = s.size();
        int len = 0;
        while(right < n){
            if(Map.find(s[right]) != Map.end())
                left = max(Map[s[right]] + 1 , left );

            Map[s[right]] = right;
            len = max(len , right - left + 1);
            right++;
        } 
        return len;
        
    }
};