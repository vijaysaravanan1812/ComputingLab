class Solution {
public:
    int characterReplacement(string s, int k) {
        //your code goes here
        unordered_map<char , int > Track;
        int right = 0 , left = 0;
        int maxFreq = 0;int maximum = 0;
        int size = s.length();
        while(right < size){
            Track[s[right]]++;
            maxFreq = max(maxFreq , Track[s[right]]);
            int windowSize = right - left + 1;
            if((windowSize - maxFreq) > k){
                Track[s[left]]--;
                left++;
            }
            maximum = max(right - left + 1, maximum);
            right++;
        }
        return maximum;
    }
};