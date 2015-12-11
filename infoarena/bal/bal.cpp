#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 100005;

#define FORIT(it, v) for(vector<int> :: iterator it = (v).begin(); it != (v).end(); ++it)

ifstream in("bal.in");
ofstream out("bal.out");

vector<int> boy[kMaxN], girl[kMaxN];
int nr_b[kMaxN], nr_g[kMaxN], rez[kMaxN];
bool viz_b[kMaxN], viz_g[kMaxN];

int n, m, remain;

int find_g(int x) {
	FORIT(it, boy[x])
		if (viz_g[*it] == false)
			return *it;
	return 0;
}

int find_b(int x) {
	FORIT(it, girl[x])
		if (viz_b[*it] == false)
			return *it;
	return 0;
}

void solve(int i) {
 	if (nr_b[i] == 1 and viz_b[i] == false) {
		int g = find_g(i);
		rez[i] = g;
		viz_g[g] = true;
		viz_b[i] = true;

		FORIT(it, boy[i]) {
			nr_g[*it]--;
			if (nr_g[*it] == 1 and viz_g[*it] == false)
				solve(*it);
		}

 		FORIT(it, girl[g]) {
			nr_b[*it]--;
			if (nr_b[*it] == 1 and viz_b[*it] == false)
				solve(*it);
		}   	
		remain--;
	} 
	if (nr_g[i] == 1 and viz_g[i] == false) {
		int b = find_b(i);
		viz_b[b] = true;
		viz_g[i] = true;
		rez[b] = i;

 		FORIT(it, boy[b]) {
			nr_g[*it]--;
			if (nr_g[*it] == 1 and viz_g[*it] == false)
				solve(*it);
		}

 		FORIT(it, girl[i]) {
			nr_b[*it]--;
			if (nr_b[*it] == 1 and viz_b[*it] == false)
				solve(*it);
		}   	

		remain--;
	}
}

#define MaxChar 1000000
#define verf ( (++CharB >= MaxChar) ? (in.read(Buffer, MaxChar), CharB = 0) : (1))

long CharB = MaxChar;
char Buffer[MaxChar];

void cit (int &a) {
	if (CharB >= MaxChar)
		verf;
    bool ok=0;
    for ( ; !((Buffer[CharB] >= '0' && Buffer[CharB] <= '9') || (Buffer [CharB] == '-')); verf)
        ;
    if (Buffer[CharB] == '-') {
        verf;
        ok=1;
    }
    for (a = 0; (Buffer[CharB] >= '0' && Buffer[CharB] <= '9'); a *= 10,a += (Buffer[CharB] - '0'), verf)
        ;
    if (ok) {
        a=-a;
    }
}


int main() {
	cit(n);
	cit(m);
	remain = n;
	while (m--) {
		int a, b;
		cit(a);
		cit(b);
		boy[a].push_back(b);
		girl[b].push_back(a);
	}
	for (int i = 1; i <= n; ++i) {
		sort(boy[i].begin(), boy[i].end());
		sort(girl[i].begin(), girl[i].end());

		boy[i].resize(unique(boy[i].begin(), boy[i].end()) - boy[i].begin());
		girl[i].resize(unique(girl[i].begin(), girl[i].end()) - girl[i].begin());

		nr_b[i] = boy[i].size();
		nr_g[i] = girl[i].size();
	}
	for (int i = 1; i <= n; ++i)
		solve(i);
	if (remain == 0) {
		out << "DA\n";
		for (int i = 1; i <= n; ++i)
			out << rez[i] << '\n';
	} else
		out << "NU\n";
	return 0;
}
