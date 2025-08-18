

int MaximumNotAdjacentSubsequence(vector<int> &arr) {
    int size = arr.size();
    if (size == 0) return 0; // Edge case: empty array
    if (size == 1) return arr[0]; // Edge case: single element

    vector<int> Dp(size, 0); // DP table initialized to 0

    // Base cases
    Dp[0] = arr[0]; // If we pick the first element
    Dp[1] = max(arr[0], arr[1]); // Pick the max of first two elements

    // Iterative DP
    for (int i = 2; i < size; i++) {
        int pick = arr[i] + Dp[i - 2]; // Pick current element and add Dp[i-2]
        int notPick = Dp[i - 1];       // Do not pick current element
        Dp[i] = max(pick, notPick);    // Store the maximum result
    }

    return Dp[size - 1]; // Result is the maximum sum at the last index
}


int main(){
    vector<int> Array;
    vector<int> temp1 = Array(0 , n -1);
    vector<int> temp2 = Array(1 , n);
    int Max = Max(MaximumNotAdjacentSubsequence(temp1), MaximumNotAdjacentSubsequence(temp1))
    return Max;
}