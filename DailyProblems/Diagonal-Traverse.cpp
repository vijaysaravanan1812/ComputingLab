class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        unordered_map<int , vector<int>> MyMap;
        int row = mat.size();
        int col = mat[0].size();
        bool flag = true;
        for(int i = 0 ; i < row; i++){
            for(int j = 0 ; j < col ; j++){
                int key = i + j;
                MyMap[key].push_back(mat[i][j]);
            }
        }
        vector<int > res;
        for(int j = 0 ; j <  MyMap.size() ; j++){
            if(flag){
                for(int i = MyMap[j].size() - 1  ; i >= 0 ; i--){
                    res.push_back(MyMap[j][i]);
                }
                flag = false;
            }else{
                  for(int i = 0 ; i < MyMap[j].size() ; i++){
                    res.push_back(MyMap[j][i]);
                }
                     flag = true;
            }
        }
        return res;
    }
};