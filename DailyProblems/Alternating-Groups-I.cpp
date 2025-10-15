class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors) {
        int ans = 0;
        int n = colors.size();
        for(int i = 1 ; i <= colors.size() ; i++){

            if(colors[(i - 1) % n] != colors[i % n] &&colors[(i + 1) % n] != colors[(i ) % n] ){
                ans++;
            }
        }
        return ans;
    }
};