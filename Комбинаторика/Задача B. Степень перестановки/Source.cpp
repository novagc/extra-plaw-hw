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

int dfs(vector<bool>& visited, vector<int>& arr, int cur) {
	if (visited[cur])
		return 0;

	visited[cur] = true;

	return dfs(visited, arr, arr[cur] - 1) + 1;
}	

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
	return a * b / gcd(a, b);
}

int main()
{
	int res = 1;
	
	int n;
	cin >> n;

	vector<bool> visited(n, false);
	vector<int> temp(n);

	for (int i = 0; i < n; i++) 
		cin >> temp[i];
		
	for (int i = 0; i < n; i++)
		if (!visited[i])
			res = lcm(res, dfs(visited, temp, i));

	cout << res;

	return 0;
}
