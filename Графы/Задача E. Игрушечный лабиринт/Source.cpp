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

vector<vector<int>> mp;
vector<vector<int>> ln;

vector<vector<bool>> vs;

int n;
int m;

void DebugPrint() {
    cout << '\n' << "MAP:\n";

    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++)
            cout << mp[i][j] << ' ';
        cout << '\n';
    }

    cout << '\n' << "VISITED:\n";

    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++)
            cout << vs[i][j] << ' ';
        cout << '\n';
    }

    cout << '\n' << "LENGTH:\n";

    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++)
            cout << ln[i][j] << ' ';
        cout << '\n';
    }
}

void Answer(int result) {
    //DebugPrint();
    cout << result;
    exit(0);
}

struct Direction {
    int x;
    int y;
    int len;

    Direction(int _len = 0) {
        x = 0;
        y = 0;

        len = _len;
    }

    Direction(int _x, int _y, int _len) {
        x = _x;
        y = _y;

        len = _len;
    }

    Direction& Len(int _len) {
        len = _len;

        return *this;
    }

    Direction& Up() {
        x = 0;
        y = -1;

        return *this;
    }

    Direction& Down() {
        x = 0;
        y = 1;

        return *this;
    }

    Direction& Left() {
        x = -1;
        y = 0;

        return *this;
    }

    Direction& Right() {
        x = 1;
        y = 0;

        return *this;
    }

    Direction& Back() {
        x *= -1;
        y *= -1;

        return *this;
    }
};

struct Point {
    int x;
    int y;

    Point(Point* p) {
        x = p->x;
        y = p->y;
    }

    Point(int _x = 0, int _y = 0) {
        x = _x;
        y = _y;
    }

    Point GetNewPoint(Direction mov) {
        return Point(this).Move(mov);
    }

    Point& Move(Direction mov) {
        x += mov.x;
        y += mov.y;

        vs[y][x] = true;
        ln[y][x] = mov.len;

        return *this;
    }

    bool TryMove(Direction mov, bool unvisited = false) {
        bool res;
        int temp = mp[y + mov.y][x + mov.x];
        
        if (temp == 2) {
            vs[y + mov.y][x + mov.x] = true;
            ln[y + mov.y][x + mov.x] = mov.len;
            Answer(mov.len);
        }

        return unvisited ? !vs[y + mov.y][x + mov.x] && temp == 0 : temp == 0;
    }
};

struct Movement {
    Point point;
    Direction dir;

    Movement() {}

    Movement(Point p, Direction d) {
        point = p;
        dir = d;
    }

    Movement& CD(Direction _dir) {
        dir = _dir;
        return *this;
    }

    Movement& MoveWhileCan() {
        while (Move());
        return *this;
    }

    bool Move() {
        if (point.TryMove(dir)) {
            point.Move(dir);
            return true;
        }

        return false;
    }
};

Point Move(Movement mov) {
    while (mov.Move());
    return mov.point;
}

void BFS(Point cur) {
    Direction dirs[] = {
        Direction(1).Up(), 
        Direction(1).Right(), 
        Direction(1).Down(), 
        Direction(1).Left()
    };

    queue<Movement> q;
    Movement t1;
    Point t2;
    int t3;

    if (cur.TryMove(dirs[1]))
        q.push(Movement(cur.GetNewPoint(dirs[1]), dirs[1]));

    if (cur.TryMove(dirs[2]))
        q.push(Movement(cur.GetNewPoint(dirs[2]), dirs[2]));

    while (!q.empty()) {
        t1 = q.front();
        t2 = Move(t1);
        t3 = t1.dir.len + 1;

        q.pop();

        if (t2.TryMove(dirs[0].Len(t3), true))
            q.push(Movement(t2, dirs[0]));

        if (t2.TryMove(dirs[1].Len(t3), true))
            q.push(Movement(t2, dirs[1]));

        if (t2.TryMove(dirs[2].Len(t3), true))
            q.push(Movement(t2, dirs[2]));

        if (t2.TryMove(dirs[3].Len(t3), true))
            q.push(Movement(t2, dirs[3]));
    }
}

int main() {
    cin >> n;
    cin >> m;

    vs = vector<vector<bool>>(n + 2, vector<bool>(m + 2, false));
    mp = vector<vector<int>>(n + 2, vector<int>(m + 2, 1));
    ln = vector<vector<int>>(n + 2, vector<int>(m + 2));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> mp[i][j];

    vs[1][1] = true;
    
    Point p(1, 1);
    Direction mv(4);

    BFS(p);
            
    return 0;
}