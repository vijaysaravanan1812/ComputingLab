1#include <bits/stdc++.h>
2using namespace std;
3
4class Solution {
5public:
6    long long maxRunTime(int n, vector<int>& batteries) {
7        long long total = 0;
8        for (int x : batteries) total += (long long)x;
9
10        // upper bound: if energy perfectly shared among n computers
11        long long low = 0;
12        long long high = total / n;
13
14        while (low < high) {
15            long long mid = low + (high - low + 1) / 2; // try candidate minutes
16            if (canRunFor(n, batteries, mid)) {
17                low = mid;   // mid is possible -> try larger
18            } else {
19                high = mid - 1; // mid impossible -> try smaller
20            }
21        }
22        return low;
23    }
24
25private:
26    // Check feasibility for T minutes
27    static bool canRunFor(int n, const vector<int>& batteries, long long T) {
28        long long available = 0;
29        for (int b : batteries) {
30            // each battery contributes at most T minutes
31            available += min((long long)b, T);
32            // early exit to avoid unnecessary addition (optional)
33            if (available >= (long long)n * T) return true;
34        }
35        return available >= (long long)n * T;
36    }
37};
38