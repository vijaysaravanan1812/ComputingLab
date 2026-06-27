class Solution {
public:
    string minWindow(string s, string t) {
         //your code goes here
        unordered_map<char , int> need, Track;
        for(auto character : t){
            need[character]++;
        }
        int size = s.length();
        int required = need.size();
        int have = 0, left = 0 , right = 0;
        int minWindow = INT_MAX;
        int start = 0;
        while(right < size){
            Track[s[right]]++;
            if(Track[s[right]] == need[s[right]])
                have++;
            while(required == have){
                if(right - left + 1 < minWindow){
                    minWindow = right - left + 1;
                    start = left;
                }
                
                Track[s[left]]--;
                if(Track[s[left]] < need[s[left]]){
                    have--;
                }
                left++;
            }    
            right++;
        }
        if(minWindow == INT_MAX){
            return "";
        }
        return s.substr(start , minWindow);
    }
};