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

vector<int> ans;

void Generate(int pos, int min, int now) {
    if (now == 0) {
        for (int i = 0; i < pos; ++i)
            cout << ans[i] << ' ';
        cout << '\n';
    }
    else {
        for (int i = now; i >= min; --i) {
            ans[pos] = i;
            Generate(pos + 1, i, now - i);
        }
    }
}

int main() {
    int n;
    cin >> n;

    ans.resize(n + 10);

    Generate(0, 1, n);
    return 0;
}