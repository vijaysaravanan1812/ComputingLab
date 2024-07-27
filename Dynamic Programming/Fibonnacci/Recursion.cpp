
#include<iostream>
#include<vector>

using namespace std;

long long int Fibonnacci(int n , vector<long long int> &dp){
    if(n <= 1)
        return dp[n] = n;

    if(dp[n] != -1)
        return dp[n];

    return dp[n] = Fibonnacci(n - 1, dp) + Fibonnacci(n - 2, dp);

}

int main(){
    long long int Number = 210;
    vector<long long int> dp(Number + 1, -1);
    cout<<"Fibonnaci Number: "<<Number<<"  "<<Fibonnacci(Number , dp)<<" \n";


    return 0;
}