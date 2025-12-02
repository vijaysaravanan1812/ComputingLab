1#include <bits/stdc++.h>
2using namespace std;
3
4class Solution {
5public:
6    long long maxRunTime(int n, vector<int>& batteries) {
7        sort(batteries.begin(), batteries.end());
8        int m = batteries.size();
9
10        // sum of all batteries except the largest n -> extra pool
11        long long extra = 0;
12        for (int i = 0; i < m - n; ++i) {
13            extra += batteries[i];
14        }
15
16        // live contains the largest n batteries (as long long)
17        vector<long long> live;
18        live.reserve(n);
19        for (int i = m - n; i < m; ++i) {
20            live.push_back((long long) batteries[i]);
21        }
22
23        // try to level up live[0..i] to live[i+1]
24        for (int i = 0; i < n - 1; ++i) {
25            long long gap = live[i+1] - live[i];
26            long long need = gap * (long long)(i + 1);
27
28            if (extra < need) {
29                // not enough extra to reach the next level -> distribute what remains evenly
30                return live[i] + extra / (i + 1);
31            }
32
33            // use the extra to level them and continue
34            extra -= need;
35        }
36
37        // all leveled to live[n-1], distribute remaining extra equally over n
38        return live.back() + extra / n;
39    }
40};
41