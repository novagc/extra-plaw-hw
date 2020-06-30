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

bool Next(vector<int> &a) {
    int j = a.size() - 2;

    while (j != -1 && a[j] >= a[j + 1]) 
        j--;

    if (j == -1)
        return false;

    int k = a.size() - 1;

    while (a[j] >= a[k]) 
        k--;

    swap(a[j], a[k]);

    int l = j + 1;
    int r = a.size() - 1;

    while (l < r)
        swap(a[l++], a[r--]);

    return true;
}

void Print(vector<int> &a) {
    for (int i = 0; i < a.size(); i++) {
        cout << a[i];
    }

    cout << '\n';
}

int main() {
    int n; 
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++)
        a[i] = i + 1;

    Print(a);

    while (Next(a))
        Print(a);

    return 0;
}