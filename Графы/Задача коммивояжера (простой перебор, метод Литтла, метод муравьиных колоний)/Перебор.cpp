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

int W[9][9];
int way[9];
int bestWay[9];
int N, K, best;
bool Vizit[9];

void FindCycles(int start, int cur, int remains)
{
    if (remains == 1)
    {
        if (W[cur][start] != 0)
        {
            way[K] = start;
            int prev = start, len = 0;
            for (int i = 1; i <= K; i++)
            {
                len += W[prev][way[i]];
                prev = way[i];
            }
            if (len < best)
            {
                best = len;
                for (int i = 0; i <= K; i++)
                    bestWay[i] = way[i];
            }
        }
        return;
    }

    Vizit[cur] = true;

    for (int i = start + 1; i <= N; i++)
    {
        if (!Vizit[i] && W[cur][i] != 0)
        {
            way[K - remains + 1] = i;
            FindCycles(start, i, remains - 1);
        }
    }
    Vizit[cur] = false;
}

int main()
{
    cin >> N;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) 
            cin >> W[i][j];

    K = N;

    best = INT32_MAX;

    for (int i = 1; i <= N; i++)
    {
        way[0] = i; 
        FindCycles(i, i, K);
    }

    if (best == INT32_MAX)
        cout << 0 << '\n';

    else
    {
        cout << best << '\n';

        for (int i = 0; i <= K; i++)
            cout << bestWay[i] << ' ';

        cout << endl;
    }

    return 0;
}