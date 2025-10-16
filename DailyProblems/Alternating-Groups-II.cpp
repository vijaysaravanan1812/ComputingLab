class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int ans = 0; 
        int maxLen = 1;
        int n =  colors.size();
        for(int i = 1;  i <= n - 1 + k -1 ; i++ ){
            if(colors[i % n]  != colors[(i - 1) % n]){
                maxLen++;
            }else{
                maxLen = 1;
            }
            if(maxLen >= k )
                ans++;
        }
        return ans;

    }
};