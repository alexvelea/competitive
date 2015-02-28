#include <fstream>
#include <iostream>
#include <map>
using namespace std;

ifstream in("vlad.in");
ofstream out("vlad2.out");

map<int, int> mp;

int el[100005];

int main() {
	int n, q;
	in >> n >> q;
	for (int i = 1; i <= n; ++i) {
		in >> el[i];
	}
	while (q--) {
		int st, dr;
		in >> st >> dr;
		mp.clear();
		int mx = 0;
		for (int i = st; i <= dr; ++i) {
	    	mp[el[i]]++;
			mx = max(mx, mp[el[i]]);
		}
		out << mx << '\n';
	}
	return 0;
}
