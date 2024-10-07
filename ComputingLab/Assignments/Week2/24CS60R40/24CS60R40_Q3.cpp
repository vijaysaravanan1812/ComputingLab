
#include<bits/stdc++.h>

using namespace std;

int MinimumPath(int** Grid, int m, int n, int i, int j) {
    if (i == 0 && j == 0) {
        return Grid[i][j];
        
    }

    
    if (i == 0) {
        return Grid[i][j] + MinimumPath(Grid, m, n, i, j - 1);
    }
    
    if (j == 0) {
        return Grid[i][j] + MinimumPath(Grid, m, n, i - 1, j);
    }
    
    return Grid[i][j] + min(MinimumPath(Grid, m, n, i - 1, j), MinimumPath(Grid, m, n, i, j - 1));
}

int main() {
    int m = 2, n = 3;
    
    int** Grid = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; ++i) {
        Grid[i] = (int*)malloc(n * sizeof(int));
    }
    
    int values[2][3] = {{1, 2, 3}, {4, 5, 6}};
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            Grid[i][j] = values[i][j];
        }

    }
    
  
    cout << "Minimum path sum: " << MinimumPath(Grid, m, n, m - 1, n - 1) << "\n";

    for (int i = 0; i < m; ++i) {
        free(Grid[i]);

    }
    free(Grid);
    
    return 0;
}
