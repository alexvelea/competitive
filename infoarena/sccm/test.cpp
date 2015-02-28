#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
	vector<int> x;
	x.push_back(10);
	x.push_back(20);
	cout << *lower_bound(x.begin(), x.end(), 11);
}
