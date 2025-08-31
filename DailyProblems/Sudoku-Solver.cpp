#include <vector>

class Solution {
public:
    /**
     * @brief Solves the Sudoku puzzle by modifying the board in-place.
     * * @param board The 9x9 Sudoku board represented as a vector of vectors of characters.
     * Empty cells are denoted by '.'.
     */
    void solveSudoku(std::vector<std::vector<char>>& board) {
        solve(board);
    }

private:
    /**
     * @brief The recursive backtracking function.
     * * @param board The Sudoku board.
     * @return true if a solution is found, false otherwise.
     */
    bool solve(std::vector<std::vector<char>>& board) {
        // Iterate through each cell to find an empty one
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                
                // Found an empty cell
                if (board[row][col] == '.') {
                    
                    // Try placing numbers '1' through '9'
                    for (char num = '1'; num <= '9'; ++num) {
                        
                        // Check if the current number is a valid placement
                        if (isValid(board, row, col, num)) {
                            
                            // Place the number (make a choice)
                            board[row][col] = num;

                            // Recurse with the updated board
                            if (solve(board)) {
                                return true; // If the recursion finds a solution, we're done
                            } else {
                                // Backtrack: undo the choice if it led to a dead end
                                board[row][col] = '.';
                            }
                        }
                    }
                    
                    // If we tried all numbers and none worked, this path is a failure.
                    // Trigger backtracking in the previous call.
                    return false;
                }
            }
        }
        
        // Base case: If we iterate through the entire board and find no empty cells,
        // it means the board is solved.
        return true;
    }

    /**
     * @brief Checks if placing a number in a given cell is valid according to Sudoku rules.
     * * @param board The Sudoku board.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @param num The character ('1'-'9') to check.
     * @return true if the placement is valid, false otherwise.
     */
    bool isValid(const std::vector<std::vector<char>>& board, int row, int col, char num) {
        // Check if 'num' is already in the current row or column
        for (int i = 0; i < 9; ++i) {
            if (board[row][i] == num) return false; // Check row
            if (board[i][col] == num) return false; // Check column
        }

        // Check if 'num' is already in the current 3x3 sub-box
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[startRow + i][startCol + j] == num) {
                    return false;
                }
            }
        }

        // If all checks pass, the placement is valid
        return true;
    }
};