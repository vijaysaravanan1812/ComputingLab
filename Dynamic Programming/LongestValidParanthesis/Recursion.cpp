#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int longestValidParenthesesUtil(const string& s, int index, int openCount) {
    // Base cases
    if (index < 0) {
        return openCount == 0 ? 0 : -1;  // Return 0 if all opened parentheses are matched
    }

    // If we encounter '(', increase the open count and call recursively
    if (s[index] == '(') {
        if (openCount > 0) {
            int res = longestValidParenthesesUtil(s, index - 1, openCount - 1);
            return res != -1 ? res + 2 : -1;  // Match found, increase length by 2
        }
        return longestValidParenthesesUtil(s, index - 1, openCount);
    } else {
        // If we encounter ')', increase open count and call recursively
        return longestValidParenthesesUtil(s, index - 1, openCount + 1);
    }
}

int longestValidParentheses(const string& s) {
    int maxLength = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
        int length = longestValidParenthesesUtil(s, i, 0);
        if (length > maxLength) {
            maxLength = length;
        }
    }
    return maxLength;
}

int main() {
    string s;
    cin >> s;
    cout << longestValidParentheses(s) << endl;
    return 0;
}
