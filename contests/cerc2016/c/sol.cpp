#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point {
	double x, y;

	Point(double x, double y) : x(x), y(y) {}

	bool operator < (const Point& other) {
		if (x != other.x) {
			return x < other.x;
		}
		return y < other.y;
	}
};

double det(const Point& a, const Point& b, const Point& c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

double dist(const Point& a, const Point& b) {
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

vector<Point> get_triangle() {
	return {Point(0, 0), Point(1, 0), Point(0.5, sqrt(0.75))};
}

vector<Point> get_square() {
	return {Point(0, 0), Point(0, 1), Point(1, 0), Point(1, 1)};
}

vector<Point> get_circle() {
	return {Point(0.5, 0), Point(0.5, 1)};
}

double pi() {
	return 2*acos(0);
}

vector<Point> get_big_circle() {
	vector<Point> v;

	int div = 100000;
	for (int i = 0; i < div; ++i) {
		double angle = 2*pi()*i/div;
		v.push_back(Point(cos(angle) * 0.5 + 0.5, sin(angle) * 0.5 + 0.5));
	}
	return v;
}

void shift(vector<Point>& v, int x) {
	for (int i = 0; i < v.size(); ++i) {
		v[i].x += x;
	}
}

vector<Point> hull(vector<Point> v) {
	vector<Point> ch;
	sort(v.begin(), v.end());
	vector<int> st(v.size()+10);
	int k = 0;

	for (int i = 0; i < v.size(); ++i) {
		while (k > 1 && det(v[st[k-1]], v[st[k]], v[i]) <= 0)
			--k;
		st[++k] = i;
	}

	for (int i = 1; i <= k; ++i) {
		ch.push_back(v[st[i]]);
	}

	k = 0;
	for (int i = v.size()-1; i >= 0; --i) {
		while (k > 1 && det(v[st[k-1]], v[st[k]], v[i]) <= 0)
			--k;
		st[++k] = i;
	}
	for (int i = 2; i < k; ++i) {
		ch.push_back(v[st[i]]);
	}
	return ch;
}

double perimeter(vector<Point> v) {
	double ans = 0;
	for (int i = 0; i < v.size(); ++i) {
		int ii = (i+1)%v.size();
		ans += dist(v[i], v[ii]);
	}
	return ans;
}

void solve() {
	int n;
	cin >> n;
	string s;
	cin >> s;

	int last = -1, first = -1;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == 'C') {
			last = i;
			if (first == -1)
				first = i;
		}
	}

	vector<Point> points;
	for (int i = 0; i < s.length(); ++i) {
		vector<Point> v;
		if (s[i] == 'T') {
			v = get_triangle();
		} else if (s[i] == 'S') {
			v = get_square();
		} else if (i == first || i == last) {
			v = get_big_circle();
		} else {
			v = get_circle();
		}
		shift(v, i);

		points.insert(points.end(), v.begin(), v.end());
	}
	cout.flush();

	auto conv = hull(points);
	// for (int i = 0; i < 100; ++i) {
	// 	cout << conv[i].x << " " << conv[i].y << "\n";
	// }


	// cout << "Here\n";
	double d = perimeter(conv);
	cout << fixed << setprecision(7) << d << "\n";
}

int main() {
	int k = 1;
	for (; k <= 1; ++k) {
		solve();
	}
}