#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> memo;
public:
    bool isMatch(string s, string p) {
        memo = vector<vector<int>>(s.size()+1, vector<int>(p.size()+1, -1));
        return dp(0, 0, s, p);
    }

    bool dp(int i, int j, string &s, string &p) {
        if(memo[i][j] != -1) return memo[i][j];
        bool ans;
        if(j == p.size()) {
            ans = (i == s.size());
        } else {
            bool first_match = (i < s.size() && (s[i] == p[j] || p[j] == '.'));
            if(j+1 < p.size() && p[j+1] == '*') {
                ans = dp(i, j+2, s, p) || (first_match && dp(i+1, j, s, p));
            } else {
                ans = first_match && dp(i+1, j+1, s, p);
            }
        }
        return memo[i][j] = ans;
    }
};

