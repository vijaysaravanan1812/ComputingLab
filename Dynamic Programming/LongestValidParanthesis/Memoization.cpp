
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Helper function to calculate the longest valid parentheses substring ending at index
int longestValidParenthesesMemo(const string& s, int index, vector<int>& dp) {
    if (index < 0) return 0;
    if (dp[index] != -1) return dp[index];

    int result = 0;
    if (s[index] == ')') {
        if (index > 0 && s[index - 1] == '(') {
            result = 2 + (index - 2 >= 0 ? longestValidParenthesesMemo(s, index - 2, dp) : 0);
        } else if (index > 0 && index - 1 - dp[index - 1] >= 0 && s[index - 1 - dp[index - 1]] == '(') {
            result = dp[index - 1] + 2 + (index - dp[index - 1] - 2 >= 0 ? longestValidParenthesesMemo(s, index - dp[index - 1] - 2, dp) : 0);
        }
    }

    dp[index] = result;
    return result;
}

// Main function to find the longest valid parentheses in the string
int longestValidParentheses(const string& s) {
    int n = s.length();
    if (n == 0) return 0;

    vector<int> dp(n, -1);
    int maxLength = 0;

    for (int i = 0; i < n; ++i) {
        maxLength = max(maxLength, longestValidParenthesesMemo(s, i, dp));
    }

    return maxLength;
}

int main() {
    string s = "((())";
    cout << "Longest valid parentheses length: " << longestValidParentheses(s) << endl;
    return 0;
}
