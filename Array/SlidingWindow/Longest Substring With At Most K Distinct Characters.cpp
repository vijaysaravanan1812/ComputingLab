class Solution {
public:
    int kDistinctChar(string& s, int k) {
        //your code goes here
        unordered_map<char , int > Track;
        int right = 0 , left = 0;
        int size = s.length();
        int maximum = 0;
        while(right < size){
            Track[s[right]]++;
            if(Track.size() > k){
                Track[s[left]]--;
                if(Track[s[left]] == 0){
                    Track.erase(s[left]);
                }
                left++;
            }
            maximum = max(right - left + 1 , maximum);
            right++;
        } 
        return maximum;
    }
};