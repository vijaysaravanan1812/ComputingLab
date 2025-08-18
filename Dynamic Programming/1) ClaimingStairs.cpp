


// Recursive Solution
ClaimingStairs(index){

    if(index == 0){
        return 1;
    }
    if(index == 1){
        return 1;
    }
    int Left = ClaimingStairs(index - 1);
    int Right = ClaimingStairs(index - 2);
    return Left + Right; 

}

//Memoization Top Down
// Declare DP Array

int Dp[n + 1] 
ClaimingStairs(index){

    if(index == 0){
        return 1;
    }
    if(index == 1){
        return 1;
    }
    if(Dp[index] != -1){
        return Dp[index];
    }
    int Left = ClaimingStairs(index - 1);
    int Right = ClaimingStairs(index - 2);
    return Dp[index] =  Left + Right; 
   
}

//Bottom Up
Dp[0] = 0 , Dp[1] = 1;
for(int i = 2; i <= N ; i++){
    Dp[i] = Dp[i - 1] + Dp[i - 2];
}

// Space Optimization
Prev2 = 0 , Prev1 = 1
for(int i = 2 ; i <= N ; i++){
    Current = Prev2 + Prev1
    Prev2 = Prev1;
    Prev1 = Current; 
}