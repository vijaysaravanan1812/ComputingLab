class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char , int> Map;
        int MaxFrequency = 0, MaxLenght = 0;
        int Left = 0, Right = 0 , n = s.length();
        while(Right < n){
            Map[s[Right]] += 1;
            MaxFrequency = max(MaxFrequency , Map[s[Right]]);
            if(((Right - Left + 1) - MaxFrequency) > k) {
                Map[s[Left]] -= 1;
                Left++;
            }  
            Right++;
        }
        return Right - Left;
    }
};