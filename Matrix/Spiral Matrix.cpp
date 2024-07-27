class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        int n = matrix.size();
        int m = matrix[0].size();

        int left = 0, top = 0 ; 
        int buttom = n - 1, right = m - 1;
        int dir = 0;

        while(top <= buttom && left <= right){
            if(dir == 0){
                for(int i = left; i <= right ; i++){
                    result.push_back(matrix[top][i]);
                }
                top++;
            }else if(dir == 1){
                for(int i = top ; i <= buttom ; i++){
                    result.push_back(matrix[i][right]);
                }
                right--;
            }else if(dir == 2){
                for(int i = right ; i >= left ; i--){
                    result.push_back(matrix[buttom][i]);
                }
                buttom--;
            }else if(dir == 3){
                for(int i = buttom; i >= top ; i--){
                    result.push_back(matrix[i][left]);
                }
                left++;
            }
            dir = (dir + 1)%4;
        } 
        return result;
    }
};