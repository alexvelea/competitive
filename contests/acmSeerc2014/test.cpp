#include <iostream>
#include <iomanip>
#include <ctime>
#include <set>
using namespace std;

bool viz[200000000];

set<pair<int, int> > s;

int main() {
	s.insert(make_pair(2, 5));
	s.insert(make_pair(1, 5));
	s.insert(make_pair(0, 5));
	set<pair<int, int> > :: iterator it = s.lower_bound(make_pair(1, 0));
	for (auto it : s)
		cerr << it->first << '\t' << it->second << '\n';
	return 0;
}
