class Solution {
public:
    int longestBalanced(string s) {
        int maxLength = INT_MIN;
        // int currentLength = 0;

        int n = s.length();
        int temp = 0;
        for (int i = 0; i < n; i++) {
            unordered_map<char, int> Freq;
            bool isBalance = true;
            for (int j = i; j < n; j++) {
                Freq[s[j]] += 1;
                set<int> SetC;
                temp = Freq[s[j]];
                for(auto x : Freq){
                    if(!(temp == x.second)){
                        isBalance = false;
                        break;

                    }
                }
                if(isBalance == false){
                    isBalance =true;
                    continue;
                }else {

                    maxLength = max(maxLength, j - i + 1);
                }
            }

   
        }
        return maxLength;
    }
};