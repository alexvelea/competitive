#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 100005;


int aib[kMaxN];
int n;
vector<int> el;
vector<pair<int, int> > nr;


void aib_update(int ind, int el) {
	while (ind < kMaxN) {
		if (aib[ind] < el)
			aib[ind] = el;
		ind += ind & (-ind);
	}
}


int aib_query(int ind) {
	int rez = 0;
	while (ind) {
		if (rez < aib[ind])
			rez = aib[ind];
		ind -= ind & (-ind);
	}
	return rez;
}


bool mysort(pair<int, int> a, pair<int, int> b) {
	if (a.first == b.first)
		return a.second > b.second;
	return a.first < b.first;
}


int main() {

	ifstream fin("plicuri.in");
	ofstream fout("plicuri.out");

	fin >> n;
	for (int i = 1; i <= n; ++i) {
		int a, b;
		fin >> a >> b;
		if (a > b)
			swap(a, b);
		nr.push_back(make_pair(a, b));
	}
	sort(nr.begin(), nr.end(), mysort);
 	for (int i = 0; i < n; ++i) {
		el.push_back(nr[i].second);
	}
	int mx = 0;
	for (int i = 0; i < n; ++i) {
		int act = 0;
		act = aib_query(el[i] - 1);
		act ++;
		aib_update(el[i], act);
		if (mx < act)
			mx = act;
	}
	fout << mx << '\n';
	return 0;
}                               
