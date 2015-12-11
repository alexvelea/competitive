#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<pair<int, int> > a;

int main() {
	a.push_back(make_pair(10, 10));
	a.push_back(make_pair(20, 20));
	a.push_back(make_pair(30, 30));
	a.push_back(make_pair(40, 40));
	cout << lower_bound(a.begin(), a.end(), make_pair(21, 0))->first << '\n';
	return 0;
}
