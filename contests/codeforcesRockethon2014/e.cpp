//Problem #E from Codeforces rocket
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

#define int64 long long

int64 cost_under[3][kMaxN], cost_up[3][kMaxN], under[3][kMaxN];
int64 rez[3][kMaxN];
int64 mx[3];

bool viz[kMaxN];
int n[3];
vector<int> vertex[3][kMaxN];

void get_max(int64 &a, int64 b) {
	if (a < b)
		a = b;
}

void dfA(int nod, int t) {
	viz[nod] = true;
	for (int itr : vertex[t][nod]) 
		if (not viz[itr]) {
			dfA(itr, t);
        	cost_under[t][nod] += 1LL * cost_under[t][itr];
			under[t][nod] += 1 + under[t][itr];
		}
	cost_under[t][nod] += 1LL * under[t][nod];
}

void dfB(int nod, int t) {
	viz[nod] = true;
	for (int itr : vertex[t][nod]) 
		if (not viz[itr]) {
		    cost_up[t][itr] = cost_up[t][nod] + cost_under[t][nod] - cost_under[t][itr] - 1 - under[t][itr] + (n[t] - under[t][itr] - 1);
			dfB(itr, t);
		}
	rez[t][nod] = 1LL * (cost_up[t][nod] + cost_under[t][nod]);
}

int a, b;
int64 mx_rez;

pair<int64, int64> dfSolve(int nod, int t) {
	viz[nod] = true;
	int64 A = 0, B = 0;
 	get_max(A, 1LL * a * rez[t][nod]);
	get_max(B, 1LL * b * rez[t][nod]);   
	for (int itr : vertex[t][nod])
		if (not viz[itr]) {
			pair<int64, int64> rez_under = dfSolve(itr, t);
			get_max(mx_rez, rez_under.first + B);
			get_max(mx_rez, rez_under.second + A);
			get_max(A, rez_under.first);
			get_max(B, rez_under.second);
		}
	return make_pair(A + 1LL * a * b, B + 1LL * a * b);
}

int main() {
	cin >> n[0] >> n[1] >> n[2];
	for (int i = 0; i < 3; ++i)
		for (int j = 1; j < n[i]; ++j) {
			int a, b;
			cin >> a >> b;
			vertex[i][a].push_back(b);
			vertex[i][b].push_back(a);
		}
	for (int t = 0; t < 3; ++t) {
		for (int i = 0; i <= n[t]; ++i)
			viz[i] = 0;
		dfA(1, t);
		for (int i = 0; i <= n[t]; ++i)
			viz[i] = 0;
		dfB(1, t);
	}
	for (int t = 0; t < 3; ++t) {
		for (int i = 1; i <= n[t]; ++i) 
			if (mx[t] < 1LL * (rez[t][i]))
				mx[t] = 1LL * (rez[t][i]);
	}
	
	int64 final = 0;
	for (int t = 0; t < 3; ++t) {
		int64 act = 0;
		mx_rez = 0;
		a = n[(t + 1) % 3];
		b = n[(t + 2) % 3];

		if (a < b)
			swap(a, b);

		act += 1LL * (n[t]) * (n[0] + n[1] + n[2] - n[t]);
		act += 1LL * (mx[0] + mx[1] + mx[2] - mx[t] ) * (n[t]);
		act += 1LL * (n[(t + 1) % 3]) * (mx[(t + 2) % 3]);
		act += 1LL * (n[(t + 2) % 3]) * (mx[(t + 1) % 3]);
		act += 2LL * a * b;
			
		for (int i = 0; i <= n[t]; ++i)
			viz[i] = false;
		
		dfSolve(1, t);

		mx_rez += act;
		if (mx_rez > final)
			final = mx_rez;
	}
	
	int64 aux = 0;
	for (int t = 0; t < 3; ++t)
		for (int i = 1; i <= n[t]; ++i)
			aux += rez[t][i];
	aux /= 2;
	final += aux;
	
//	if (DEBUG)
// 		for (int t = 0; t < 3; ++t, cerr << '\n')
//			for (int i = 1; i <= n[t]; ++i)
//				cerr << cost_up[t][i] << '\n';
	cout << final << '\n';
    return 0;
}

