1#include <bits/stdc++.h>
2using namespace std;
3
4class Solution {
5public:
6    static constexpr long long MOD = 1000000007LL;
7
8    static long long comb2(long long v) {
9        if (v < 2) return 0;
10        return (v * (v - 1) / 2) % MOD;
11    }
12
13    // LeetCode expects this signature
14    int countTrapezoids(vector<vector<int>>& points) {
15        unordered_map<int,long long> countByY;
16        countByY.reserve(points.size()*2);
17
18        for (const auto &p : points) {
19            // p is a vector<int> of size 2: [x, y]
20            int y = p[1];
21            ++countByY[y];
22        }
23
24        long long res = 0;
25        long long prev = 0;
26        for (const auto &kv : countByY) {
27            long long v = kv.second;
28            long long curr = comb2(v);
29            res = (res + (curr * prev) % MOD) % MOD;
30            prev = (prev + curr) % MOD;
31        }
32        return static_cast<int>(res);
33    }
34};
35