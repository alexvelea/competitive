//Problem #C from Codeforces rocket
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 0
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

const int inf = 0x3f3f3f3f, kMaxP = 200005;

vector<pair<int, int> > A;
vector<int> cost[kMaxP];
vector<int> B, C;
int maxP = -1;

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		int a, b;
    	cin >> a >> b;
		A.push_back(make_pair(a, b));
		cost[a].push_back(b);
		if (a > maxP)
			maxP = a;
		B.push_back(b);
	}
	sort(A.begin(), A.end());
	reverse(A.begin(), A.end());
	int t = A[k - 1].first;
	
	sort(B.begin(), B.end());
	int64 rez = 1LL * inf * inf;

	// t + 2

	if (B.size() >= t + 2) {
		rez = 0;
		for (int i = 0; i < t + 2; ++i)
			rez += 1LL * B[i];
	}

	if (DEBUG) {
		cerr << t << '\t' << rez << '\n';
	}

	// t + 1

	B.clear();
	int bigger = 0;
	for (int i = t + 2; i <= maxP; ++i)
		bigger += cost[i].size();
	
	int target = k - bigger - 1;
	int other = t + 1;
	if (DEBUG)
		cerr << "target \t" << target << '\n';
	int64 c = 0;
	sort(cost[t].begin(), cost[t].end());
	sort(cost[t + 1].begin(), cost[t + 1].end());
	if (DEBUG)
		cerr << "c-dupa grupa de t\t" << c << '\n';
 
 	B.clear();
	C.clear();
 	for (int T = t; T <= t + 1; ++T) {
		for (int i = 0; i < cost[T].size(); ++i)
			C.push_back(cost[T][i]);
	}            
	sort(C.begin(), C.end());

	for (int i = 0; i < int(C.size()); ++i) {
    	if (i + target < C.size()) {
        	c += 1LL * C[i];
			--other;
		} else {
			B.push_back(C[i]);
		}
	} 

	for (int T = 0; T <= maxP; ++T) {
		if (T == t + 1)
			continue;
		if (T == t)
			continue;

		for (int i = 0; i < cost[T].size(); ++i)
			B.push_back(cost[T][i]);
	}

	sort(B.begin(), B.end());

	for (int i = 0; i < int(B.size()) and other > 0; ++i) {
		c += B[i];
		other--;
	}
	if (other <= 0) {
		if (DEBUG)
			cerr << "T + 1" << '\t' << c << "\ttarget:" << target << '\n';
		if (rez > c)
			rez = c;
	}
	
	
    // t
	bigger += cost[t + 1].size();
	target = k - bigger - 1;
	other = t;
	c = 0;

	B.clear();
	C.clear();
 	for (int T = max(t - 1, 0); T <= t; ++T) {
		for (int i = 0; i < cost[T].size(); ++i)
			C.push_back(cost[T][i]);
	}            
	sort(C.begin(), C.end());

	for (int i = 0; i < int(C.size()); ++i) {
    	if (i + target < C.size()) {
        	c += 1LL * C[i];
			if (DEBUG)
				cerr << "trebe sa iau\t" << C[i] << '\n';
			--other;
		} else {
			if (DEBUG)
				cerr << "Pun la pastrat\t" << C[i] << '\n';
			B.push_back(C[i]);
		}
	} 
 
 	for (int T = 0; T <= maxP; ++T) {
		if (T == t - 1)
			continue;
		if (T == t)
			continue;
		for (int i = 0; i < cost[T].size(); ++i)
			B.push_back(cost[T][i]);
	}                         
 
 	sort(B.begin(), B.end());
	for (int i = 0; i < int(B.size()) and other > 0; ++i) {
		c += B[i];
		other--;
	}
	if (other <= 0)
		if (rez > c)
			rez = c; 

	if (rez == 1LL * inf * inf)
		cout << -1;
	else
		cout << rez << '\n';
    return 0;
}

