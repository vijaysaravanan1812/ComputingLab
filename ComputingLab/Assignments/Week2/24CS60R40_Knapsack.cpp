#include <iostream>
#include <cstring>

using namespace std;

struct Item {
    int weight;
    int value;
    double ratio;
};

typedef struct Item Item;

void Sort(Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[i].ratio < items[j].ratio) {
                
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

int Clause2(int n, int W, int Weights[], int Values[]) {
    Item items[n];
    for (int i = 0; i < n; i++) {
        items[i].weight = Weights[i];
        items[i].value = Values[i];
        items[i].ratio = (double)Values[i] / Weights[i];
    }

    Sort(items, n);

    int TotalValue = 0, RemainingWeight = W;

    for (int i = 0; i < n; i++) {
        if (items[i].weight <= RemainingWeight) {
            TotalValue += items[i].value;
            RemainingWeight -= items[i].weight;
        }
    }

    return TotalValue;
}

int Clause3(int n, int W, int weights[], int values[]) {
    if (n == 0 || W == 0)
        return 0;

    if (weights[n - 1] > W)
        return Clause3(n - 1, W, weights, values);

    return max(values[n - 1] + Clause3(n - 1, W - weights[n - 1], weights, values),
               Clause3(n - 1, W, weights, values));
}

int Clause4Util(int n, int W, int weights[], int values[], int memo[][100]) {
    if (n == 0 || W == 0)
        return 0;

    if (memo[n][W] != -1)
        return memo[n][W];

    if (weights[n - 1] > W)
        return memo[n][W] = Clause4Util(n - 1, W, weights, values, memo);

    return memo[n][W] = max(values[n - 1] + Clause4Util(n - 1, W - weights[n - 1], weights, values, memo),
                            Clause4Util(n - 1, W, weights, values, memo));
}

int Clause4(int n, int W, int weights[], int values[]) {
    int memo[100][100];
    memset(memo, -1, sizeof(memo));
    return Clause4Util(n, W, weights, values, memo);
}

int main() {
    int n = 4, W = 30;

    int Weights[] = {25, 10, 12, 15};
    int Values[] = {100, 30, 35, 90};

    cout << "Clause 2: " << Clause2(n, W, Weights, Values) << "\n";
    cout << "Clause 3: " << Clause3(n, W, Weights, Values) << "\n";
    cout << "Clause 4: " << Clause4(n, W, Weights, Values) << "\n";

    return 0;
}
