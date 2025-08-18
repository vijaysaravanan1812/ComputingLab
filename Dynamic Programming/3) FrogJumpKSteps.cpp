

//Recurence Solution
Frog_Jump_K_Steps(int index, vector<int> &Height){
    if(index == 0)
        return 0;
    MinimumSteps = INT_MAX
    for(int j = 1; j <= k; j++){
        if(index > 0){
            int Step = Frog_Jump_K_Steps(index - i, Height) + abs(Height[index] , Height[index - i])
            MinimumSteps =  min(Step, MinimumSteps);
        }
    }

    return MiniimumSteps
}

//Memoization
Frog_Jump_K_Steps(int index, vector<int> &Height, vector<int> &Dp){
    if(index == 0)
        return Dp[index] = 0;
    if(Dp[index] != -1)
        return Dp[index];
    else{
        MinimumSteps = INT_MAX
        for(int j = 1; j <= k; j++){
            if(index > 0){
                int Step = Frog_Jump_K_Steps(index - i, Height) + abs(Height[index] , Height[index - i])
                MinimumSteps =  min(Step, MinimumSteps);
            }
        }

        return Dp[index] = MiniimumSteps
    }

}

//Tabulation
Frog_Jump_K_Steps(int NumberOfSteps , vector<int> &Height, vector<int> &Dp){
    
    Dp[0] = 0;

    for(int i = 0 ; i < NumberOfSteps; i++){
        MinimumSteps = INT_MAX
        for(int j = 1; j >= 0 ; j++ ){
            if(i - j >= 0){
                int Step = Dp[i - j] + abs(Height[i] - Height[i -j])
                MiniimumSteps = min(MiniimumSteps , Step)
            }
        }
        Dp[i] = MiniimumSteps
    }
    return Dp[i];

}

