#include <iostream>
#include <string>
class Solution {
public:
    string largestGoodInteger(string num) {
     
       
        int n = num.size();
        int Max=-1;
        string ans = "";
        for(int i = 0; i <= n - 3; i++){
            if(num[i] == num[i + 1] && num[i + 2] == num[i + 1]){
                int Digit = num[i] - '0';
                cout<<Digit<<" ";
                Max = max(Max , Digit);
            }
        }
        if(Max != -1)
        {
            int i = 3;
            while(i > 0){
                ans +=  Max + '0';
                i--;
            }
        }
        return ans;

    }
};