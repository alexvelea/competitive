#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define ll long long

const int kMaxN = 200005, inf = 0x3f3f3f3f;
ifstream in("pante.in");
ofstream out("pante.out");


int aib[kMaxN], n;

vector<pair<int, int> > point;
vector<ll> uniq;


void aib_update(int poz, int val) {
	while (poz <= n) {
		aib[poz] += val;
		poz += poz & (-poz);
	}
	return ;
}


int aib_query(int ind) {
	int rez = 0;
	while (ind) {
		rez += aib[ind];
		ind -= ind & (-ind);
	}
	return rez;
}


ll solve(int a, int b, bool equal) {
	/*                  /
 		(yst - ydr) / (xst - xdr) <= a/b
		b * (yst - ydr) <= a * (xst - xdr)
		b * yst - a * xst <= b * ydr - a * ydr
	*/
	uniq.clear();
	uniq.push_back(-1LL * inf * inf);
	for (int i = 0; i < n; ++i) {
		uniq.push_back(- 1LL * a * point[i].first + 1LL * b * point[i].second);
	}
	sort(uniq.begin(), uniq.end());
	uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());
	ll rez = 0;
	for (int i = 0; i < n; ++i) {
		ll nr = - 1LL * a * point[i].first + 1LL * b * point[i].second;
		nr = lower_bound(uniq.begin(), uniq.end(), nr) - uniq.begin();
		if (equal)
			rez += 1LL * aib_query(nr);
		else
			rez += 1LL * aib_query(nr - 1);
		aib_update(nr, 1);
	}
	cerr << '\n';
	for (int i = 0; i <= n; ++i)
		aib[i] = 0;
	return rez;
}

int main() {
	int A, B, C, D;
	in >> n;
	in >> A >> B >> C >> D;
	for (int i = 0; i < n; ++i) {
		pair<int, int> aux;
		in >> aux.first >> aux.second;
		point.push_back(aux);
	}
	sort(point.begin(), point.end());
	reverse(point.begin(), point.end());

 	ll rez = solve(C, D, 1);
	rez -= solve(A, B, 0);
	out << rez << '\n';
	return 0;
}
