#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>
#include <limits.h>

#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>
#include <random>
#include <deque>
#include <queue>
#include <stack>
#include <ctime>
#include <cmath>
#include <regex>
#include <tuple>
#include <map>
#include <set>

using namespace std;

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    return a.second < b.second;
}

void Sort(vector<pair<int, int>>& ans) {
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans.size(); j++) {
            if (ans[i].first < ans[j].first || (ans[i].first == ans[j].first && ans[i].second < ans[j].second)) {
                swap(ans[i], ans[j]);
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;

    int m;
    cin >> m;

    vector<pair<int, int>> edgs(n - 1);

    vector<int> v(n, 0);
    vector<int> color(n);
    vector<vector<int>> map(n, vector<int>(n, 0));

    for (int i = 0, t1, t2; i < m; i++) {
        cin >> t1 >> t2;
        map[t1 - 1][t2 - 1] = 1;
    }

    for (int i = 0; i < n; i++) {
        color[i] = i;
    }

    for (int i = 0; i < n - 1; i++) {
        edgs[i] = make_pair(-1, -1);
    }

    for (int k = 0, mn, iCol, jCol; k < n - 1; k++) {
        mn = INT32_MAX;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (map[i][j] != 0 && color[i] != color[j] && map[i][j] < mn) {
                    mn = map[i][j];

                    edgs[k].first = i;
                    edgs[k].second = j;

                    iCol = color[i];
                    jCol = color[j];
                }
            }
        }

        if (edgs[k].first > edgs[k].second) {
            swap(edgs[k].first, edgs[k].second);
        }

        for (int i = 0; i < n; i++) {
            if (color[i] == jCol) {
                color[i] = iCol;
            }
        }
    }

    Sort(edgs);

    for (int i = 0; i < n - 1; i++) {
        cout << edgs[i].first + 1 << ' ' << edgs[i].second + 1 << '\n';
    }

    return 0;
}