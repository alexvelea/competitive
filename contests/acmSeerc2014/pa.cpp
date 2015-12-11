#include <fstream>
#include <iostream>
#include <set>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

const int kMaxN = 10005;

set<pair<int, int> > S;
int el[kMaxN], n;

inline int Last(int x) {
	x--;
	if (x == 0)
		x = n;
	return x;
}

inline int Next(int x) {
	x++;
	if (x == n + 1)
		x = 1;
	return x;
}

void Erase(int ind) {
	S.erase(make_pair(el[ind], ind));
	S.erase(make_pair(el[Last(ind)], Last(ind)));
	S.erase(make_pair(el[Next(ind)], Next(ind)));
}

void Insert(int ind) {
	S.insert(make_pair(el[ind], ind));
	S.insert(make_pair(el[Last(ind)], Last(ind)));
	S.insert(make_pair(el[Next(ind)], Next(ind)));
}

int main() {
	in >> n;
	for (int i = 1; i <= n; ++i) {
		in >> el[i];
		S.insert(make_pair(el[i], i));
	}

	int rez = 0;

	while (S.begin()->first < 0) {
		int ind = S.begin()->second;
		Erase(ind);
		int x = -el[ind];
		el[ind] = x;
		el[Last(ind)] -= x;
		el[Next(ind)] -= x;
		Insert(ind);
		++rez;
	}
	out << rez << '\n';
	return 0;
}
