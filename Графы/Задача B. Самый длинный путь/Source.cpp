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

int main()
{
	int n;
	cin >> n;
	vector<vector<int>>mp(n, vector<int>(n));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> mp[i][j];

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (mp[i][j] > mp[i][k] + mp[k][j])
					mp[i][j] = mp[i][k] + mp[k][j];

	int mx = -1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (mx < mp[i][j])
				mx = mp[i][j];

	cout << mx;

	return 0;
}