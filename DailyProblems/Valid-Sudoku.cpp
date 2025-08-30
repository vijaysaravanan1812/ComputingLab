class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row = board.size();
        int col = board[0].size();
        unordered_map<int , set<int>> RowMap , ColMap, SubGrid;
        
        for(int i = 0 ; i < 9; i++){
            for(int j = 0 ; j < 9 ; j++){
                int boxIndex = (i/3) * 3 + j/3;
                if(board[i][j] == '.')
                    continue;
                if(RowMap[i].count(board[i][j]) ||
                    ColMap[j].count(board[i][j]) ||
                    SubGrid[boxIndex].count(board[i][j]) 
                     )
                    return false;
                RowMap[i].insert(board[i][j]);
                ColMap[j].insert(board[i][j]);
                SubGrid[boxIndex].insert(board[i][j]);
            }
        } 
        return true;
    }
};