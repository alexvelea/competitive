#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define int64 long long

ifstream fin("input.txt");
ofstream fout("output.txt");

#define cin fin
#define cout fout

struct Point {
	int x, y;
	Point() {}

	Point(int _x, int _y): x(_x), y(_y) {}

	int64 Distance(const Point &rhs) const {
		return 1LL * (x - rhs.x) * (x - rhs.x) + 1LL * (y - rhs.y) * (y - rhs.y);
	}
};

int main() {
	int nr_of_testcases; cin >> nr_of_testcases;
	for (int test = 1; test <= nr_of_testcases; test += 1) {
		int n; cin >> n;
		vector<Point> points;
		for (int i = 1; i <= n; i += 1) {
			int x, y; cin >> x >> y;
			points.push_back(Point(x, y));
		}

		int answer = 0;

		for (auto start_point : points) {
			unordered_map<int64, int> distances;
			for (auto other : points) {
				distances[start_point.Distance(other)] += 1;
			}

			for (auto itr : distances) {
				answer += itr.second * (itr.second - 1) / 2;
			}
		}

		cout << "Case #" << test << ": " << answer << '\n';
	}	
	return 0;
}
