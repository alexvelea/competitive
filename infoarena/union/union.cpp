#include <cassert>
#include <ctime>
#include <cstdlib>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void read_vector(vector<int> &a, ifstream &in);
void read(vector<int> &a, vector<int> &b, int &k);

int solve(vector<int> &a, vector<int> &b, int k) {
	int stA = 0, stB = 0;
	
	while (k != 1 and stA < int(a.size()) and stB < int(b.size())) {
		int indA = min(k / 2, int(a.size()) - stA);
		int indB = min(k / 2, int(b.size()) - stB);

		if (a[stA + indA - 1] <= b[stB + indB - 1]) {
			stA += indA;
			k -= indA;
		} else {
			stB += indB;
			k -= indB;
		}
	}

	if (stA == int(a.size()))
		return b[stB + k - 1];
	if (stB == int(b.size()))
		return a[stA + k - 1];

	assert(k == 1);
	return min(a[stA], b[stB]);
}

int main() {
	vector<int> a, b;
	int k;
	read(a, b, k);
	
	cerr << solve(a, b, k);
	return 0;
}

void read_vector(vector<int> &a, ifstream &in) {
	int n;
	in >> n;
	a.reserve(n);
	while (n--) {
		int x;
		in >> x;
		a.push_back(x);
	}
	return ;
}

void read(vector<int> &a, vector<int> &b, int &k) {
	ifstream in("data.txt");
	read_vector(a, in);
	read_vector(b, in);
	in >> k;
	in.close();
	return ;
}
