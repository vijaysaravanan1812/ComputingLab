

#include<bits/stdc++.h>

using namespace std;


int LongestValidParentheses( const char* s, int index, int* dp) {
    if (index < 0) return 0;
    if (dp[index] != -1) return dp[index];

    int result = 0;

    if (s[index] == ')') {
        if (index > 0 && s[index - 1] == '(') {

            result = 2 + (index - 2 >= 0 ? LongestValidParentheses(s, index - 2, dp) : 0);

        } else if (index > 0 && index - 1 - dp[index - 1] >= 0 && s[index - 1 - dp[index - 1]] == '(') {

            result = dp[index - 1] + 2 + (index - dp[index - 1] - 2 >= 0 ? LongestValidParentheses(s, index - dp[index - 1] - 2, dp) : 0);

        }
    }

    dp[index] = result;
    
    return result;
}


int longestValidParentheses(const char* s) {
    int n = strlen(s);
    if (n == 0) return 0;

    int* dp = (int*)malloc(n * sizeof(int));

    for(int i = 0 ; i  < n ; i++ ){
        dp[i] = -1;
    }

    int MaxLength = 0;

    for (int i = 0; i < n; ++i) {
        MaxLength = max(MaxLength, LongestValidParentheses(s, i, dp));
    }

    free(dp);
    return MaxLength;
}

int main() {
    const char* s = "((())";
    cout << "Longest valid parentheses length: " << longestValidParentheses(s) << endl;
    return 0;
}
