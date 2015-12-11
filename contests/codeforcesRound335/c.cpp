//Problem c @ 09-12-2015
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 1e5 + 5;
const long double eps = 1e-7;

#define int64 long long

#define x first
#define y second
 
typedef pair<long double, long double> Point;
 
int n;
Point v[kMaxN];
 
Point stack[kMaxN];
int head;
 
inline long double cross_product(const Point& A, const Point& B, const Point& C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}
 
inline int cmp(const Point& p1, const Point& p2) {
    return cross_product(v[1], p1, p2) < 0;
}
 
void sort_points() {
    int pos = 1;
    for (int i = 2; i <= n; ++i)
        if (v[i] < v[pos])
            pos = i;
    swap(v[1], v[pos]);
    sort(v + 2, v + n + 1, cmp);
}
 
void convex_hull() {
    sort_points();
 
    stack[1] = v[1];
    stack[2] = v[2];
    head = 2;
    for (int i = 3; i <= n; ++i) {
        while (head >= 2 && cross_product(stack[head - 1], stack[head], v[i]) > 0)
            --head;
        stack[++head] = v[i];
    }
}
 
int main() {
    int n, a, b; cin >> n >> a >> b;
    long double mxX = 0, mxY = 0;
    for (int i = 1; i <= n; i += 1) {
    	cin >> v[i].x >> v[i].y;
    	if (v[i].x > mxX) {
    		mxX = v[i].x;
    	}
    	if (v[i].y > mxY) {
    		mxY = v[i].y;
    	}
    }
    v[n + 1].x = v[n + 1].y = 0;
    v[n + 2].x = mxX;
    v[n + 2].y = 0;

    v[n + 3].x = 0;
    v[n + 3].y = mxY;
    n += 3; 

    convex_hull();

    cerr << "!";
    for (int i = 1; i <= head; i += 1) {
    	if (fabs(a / stack[i].x - b / stack[i].y) < 1e-6) {
    		cout << fixed << setprecision(9) << 1.0 * a / stack[i].x << '\n';
    		return 0;
    	}
    }

    pair<long double, long double> target, origin;
    target = {a, b};
    origin = {0, 0};

    for (int i = 1; i <= head; i += 1) {
    	int next = i + 1;
    	if (next == head + 1) {
    		next = 1;
    	}

    	if (stack[i] == origin) {
    		continue;
    	}
    	
    	if (stack[next] == origin) {
    		continue;
    	}


    	if ((cross_product(stack[i], origin, target) >= 0) != (cross_product(target, origin, stack[next]) >= 0)) {
    		cout << fixed << setprecision(11) << ((target.y * (stack[i].x - stack[i].y) - target.x * (stack[next].x - stack[next].y)) / (stack[i].x * stack[next].y - stack[i].y - stack[next].x)) << '\n';
    		return 0;
    	}
    }
}