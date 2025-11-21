class Solution {
public:
    int countPalindromicSubsequence(string s) {
        unordered_map<char, int> right;
        for(char c : s){
            right[c]++;
        }

        unordered_set<char> left;
        set<pair<char,char>> res; // (mid, outer)

        for(char middle : s)
        {
            right[middle]--;   // reduce frequency from right side

            for(char c : left)
            {
                if(right[c] > 0)   // c appears on the right
                {
                    res.insert({middle, c});
                }
            }

            left.insert(middle); // add m into left seen-set
        }

        return res.size();
    }
};
