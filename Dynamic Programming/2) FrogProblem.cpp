

//Recursive Solution
FrogJump(int index){
    if(index == 0)
        return 0;
    int left = FrogJump(index - 1) + abs(Height[index] - Height[index - 1])
    int right = INT_MAX
    if(index > 1)
        right = FrogJump(index - 2) + abs(Height[index] - Height[index - 2] )

    return min(left , right);

}

// Top Down Approach
FrogJump(int index, vector<int> &Heights, vector<int>&Dp){
    if(index == 0)
        return Dp[index] = 0
    if(Dp[index] == -1){
        int left = FrogJump(index - 1) + abs(Height[index] - Height[index - 1])
        int right = INT_MAX
        if(index > 1)
            right = FrogJump(index - 2) + abs(Height[index] - Height[index - 2] )
        return Dp[index] = min(left , right);
    }else{
        return Dp[index];
    }
}

//Bottom Up Approaxch
FrogJump(vector<int> &Heights, vector<int>&Dp){
    int Dp[n + 1]
    Dp[0] = 0
    for(int i = 1 ; i <= n - 1; i++){
    
        int left = Dp[i - 1] + abs(Heights[i] , Heights[i -1])
        int right = INT_MAX
        if(i > 1)
            right = Dp[i - 2] + abs(Heights[i] , Heights[i - 2])
        Dp[i] = min(left , right)
    }
    return Dp[n - 1]

}