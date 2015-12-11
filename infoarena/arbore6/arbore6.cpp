#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int max_n = 2005;

int root;
vector <pair<int,int> > edges;

int get_number (int a, int b, int c) {
	cout << a << " " << b << " " << c << "\n";
	cout.flush();
	int d;
	cin >> d;
	return d;
}

bool point_sort (int a, int b) {
 	return get_number (root, a, b) == a;
}

void solve (vector <int> arb) {
	if (arb.size() == 1)
		return ;
	if (arb.size() == 2) {
		edges.push_back (make_pair (arb.front(), arb.back()));
		return ;
	}

	int ind = rand() % arb.size();
	int r = arb[ind];
	arb[ind] = arb.back(); arb.pop_back();

	ind = rand() % arb.size();
	int p = arb[ind];
	arb[ind] = arb.back(); arb.pop_back();

	vector<int> group[max_n], main_branch;

 	for (vector<int> :: iterator it = arb.begin(); it != arb.end(); ++it) {
		int mid = get_number (r, p, *it);
		if (mid == r) {
			group[r].push_back (*it);
			continue ;
		}
		if (mid == p) {
			group[p].push_back (*it);
			continue ;
		}
		if (mid == *it) {
			main_branch.push_back (*it);
			continue ;
		}
		group[mid].push_back (*it);
	}
 	root = r;
 	sort (main_branch.begin(), main_branch.end(), point_sort);
	main_branch.push_back(p);
	edges.push_back (make_pair (r, main_branch.front()));
	for (int i = 0; i < int(main_branch.size())-1; ++i) 
		edges.push_back (make_pair (main_branch[i], main_branch[i+1]));
	for (int i = 0; i < max_n; ++i) {
		if (group[i].size()) {
			group[i].push_back (i);
			solve (group[i]);
			group[i].clear();
		}
	}
}

int main() {
	srand (time (NULL));
	int n;
	cin >> n;
	vector <int> arb;
	for (int i = 1; i <= n; ++i) {
		arb.push_back (i);
	}
	solve (arb);
	for (vector< pair<int,int> > :: iterator it = edges.begin(); it != edges.end(); ++it) 
		cout << it -> first << " " << it -> second << "\n";
	return 0;
}
