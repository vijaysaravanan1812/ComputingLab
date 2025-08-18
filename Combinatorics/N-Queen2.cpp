class Solution {
    bool isSafe(int row , int col , vector<string> &board, int n ){
        for(int i = 0 ; i < row ; i++){
            if(board[i][col] == 'Q' ) return false;
        }
        for(int i = row -1 , j = col - 1; i >= 0 && j >= 0 ; i-- , j--){
            if(board[i][j] == 'Q') return false;
        }
        for(int i = row - 1, j = col + 1 ; i >= 0 && j < n ; i--, j++){
            if(board[i][j] == 'Q' ) return false;
        }
        return true;
    }
    void solve(vector<string>& board, int row, vector<vector<string>> &config, int n, int &count){
        if(row == n)
        {
            config.push_back(board);
            count++;
            return ;
        }
        for(int col = 0 ; col < n ; col++){
            if(isSafe(row , col, board,n)){
                board[row][col] = 'Q';
                solve(board , row + 1, config, n , count);
                board[row][col] = '.';
            }
        }
     
    }
public:
    int totalNQueens(int n) {
        int count = 0;
         vector<string> board(n, string(n, '.'));
         vector<vector<string>> config;
         solve(board,0,config ,  n, count);
         return count;
    }
};