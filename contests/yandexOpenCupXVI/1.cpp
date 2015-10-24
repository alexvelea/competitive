//Problem 1 @ 04-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

vector<pair<double, double> > points;

double crossProd(pair<double, double> a, pair<double, double> b, pair<double, double> c) {
    double rez = a.first * b.second + a.second * c.first + b.first * c.second
        - a.first * c.second - a.second * b.first - b.second * c.first;
    return rez;
}

int main() {
	ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        double x, y; cin >> x >> y;
        points.push_back(make_pair(x, y));
    }

    for (int i = 1; i <= m; ++i) {
        pair<double, double> a, b;
        cin >> a.first >> a.second >> b.first >> b.second;
        for (auto &itr : points) {
            if (crossProd(b, a, itr) >= 0.0) {
                
            }
//          cout << itr.first << '\t' << itr.second << '\t' << crossProd(b, a, itr) << '\n'; 
        }
    }
	return 0;
}
