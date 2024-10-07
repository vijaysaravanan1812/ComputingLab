#include<bits/stdc++.h>

using namespace std;


const int MAX_M = 100;
const int MAX_N = 100;
const int MAX_LEN = 10; 


void CountZerosOnes(const char* str, int &zeros, int &ones) {
    zeros = 0;
    ones = 0;
    while (*str) {
        if (*str == '0') {
            ++zeros;
        } else if (*str == '1') {
            ++ones;
        }
        ++str;

    }
}


int FindMaximumSubset(int index, int m, int n, char strs[][MAX_LEN], int strsSize, int dp[MAX_M + 1][MAX_N + 1]) {
    if (index >= strsSize) return 0;
    if (dp[m][n] != -1) return dp[m][n];

    int zeros, ones;
    CountZerosOnes(strs[index], zeros, ones);

    int maxSize = FindMaximumSubset(index + 1, m, n, strs, strsSize, dp);

    if (m >= zeros && n >= ones) {
        maxSize = max(maxSize, 1 + FindMaximumSubset(index + 1, m - zeros, n - ones, strs, strsSize, dp));
        
    }

    dp[m][n] = maxSize;
    return maxSize;
}

int findMaxSubsetSize(char strs[][MAX_LEN], int strsSize, int m, int n) {
    int dp[MAX_M + 1][MAX_N + 1];
    memset(dp, -1, sizeof(dp));

    return FindMaximumSubset(0, m, n, strs, strsSize, dp);
}

int main() {
    const int strsSize = 5;
    char strs[strsSize][MAX_LEN] = {"10", "0001", "111001", "1", "0"};
    int m = 5;
    int n = 3;

    cout<<"Largest subset size: "<<findMaxSubsetSize(strs, strsSize, m, n)<<"\n";

    return 0;
}
