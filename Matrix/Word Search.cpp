class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (search(board, word, i, j, 0))
                    return true;
            }
        }
        
        return false;
    }
    
private:
    bool search(vector<vector<char>>& board, string& word, int i, int j, int k) {
        if (k == word.length())
            return true;
        
        int m = board.size();
        int n = board[0].size();
        
        if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] != word[k])
            return false;
        
        char temp = board[i][j];
        board[i][j] = '*'; // Mark the cell as visited
        
        bool found = search(board, word, i + 1, j, k + 1) ||
                     search(board, word, i - 1, j, k + 1) ||
                     search(board, word, i, j + 1, k + 1) ||
                     search(board, word, i, j - 1, k + 1);
        
        board[i][j] = temp; // Backtrack by restoring the original value
        
        return found;
    }
};
