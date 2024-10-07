#include <iostream>

using namespace std;

const int MAX = 100; 


int Directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};


int Matrix[MAX][MAX];
int Memo[MAX][MAX];
int Rows, Cols;


int Max(int a, int b) {
    return (a > b) ? a : b;
}


int DFS(int row, int col) {
  
    if (Memo[row][col] != -1) {
        return Memo[row][col];
    }

    int MaxLength = 1;

    // Explore all four directions
    for (int i = 0; i < 4; ++i) {
        int NewRow = row + Directions[i][0];
        int NewCol = col + Directions[i][1];

        if (NewRow >= 0 && NewRow < Rows && NewCol >= 0 && NewCol < Cols &&
            Matrix[NewRow][NewCol] > Matrix[row][col]) {
            MaxLength = Max(MaxLength, 1 + DFS(NewRow, NewCol));
        }
    }

    Memo[row][col] = MaxLength;
    return MaxLength;
}


int longestIncreasingPath() {
    int MaxLength = 0;

    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Cols; ++j) {
            Memo[i][j] = -1;
        }
    }

    
    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Cols; ++j) {
            MaxLength = Max(MaxLength, DFS(i, j));
        }
    }

    return MaxLength;
}

int main(int argc, char *argv[]) {

    if (argc < 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
 

    FILE *output = fopen("output.txt", "w");
    fclose(output);
    output = fopen("output.txt" , "a");

    Rows = 3;
    Cols = 3;


    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Cols; ++j) {
            fscanf(input, "%d", &Matrix[i][j]);
        }
    }

    fclose(input);


    fprintf(output, "Longest Increasing Path Length: %d \n", longestIncreasingPath());

    return 0;
}
