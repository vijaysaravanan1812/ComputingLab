class Solution{
  public:
    int longestNonRepeatingSubstring(string& s){
        
        //To track uniqueness 
        set<int> seen;
        
        //Two pointers
        int right = 0, left = 0;
        int size = s.length();

        //Keep track of current length and max Length
        int currentLength = 0 ; 
        int maxLength = 0;

        // Window keep unique characters
        // First check the right pointer character already seen
        // And insert left character into set depends on condition
        // Keep track of max length
        while(right < size){
            while(seen.count(s[right])){
                seen.erase(s[left]);
                left++;
            }
            seen.insert(s[right]);
            currentLength = right - left + 1;
            maxLength = max(currentLength ,  maxLength);
            right++;
        }
        return maxLength;
    }
};