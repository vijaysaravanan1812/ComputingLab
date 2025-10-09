class Solution {
public:
    int numberOfSubstrings(string s) {
        int lasta = -1, lastb = -1, lastc = -1;
        int count = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'a') {
                lasta = i;
            }
            if (s[i] == 'b') {
                lastb = i;
            }
            if (s[i] == 'c') {
                lastc = i;
            }
            if (lasta != -1 && lastb != -1 && lastc != -1 )
            {
                int minIndex = min({lasta , lastb , lastc});
                count += minIndex + 1;
            }

            
        }
        return count;
    }
};