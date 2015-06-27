//Problem disconnect from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>
 
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
#define int64 long long
 
const int inf = 0x3f3f3f3f, kMaxN = 100005;
 
int n, m;
 
bool viz[kMaxN];
int deep[kMaxN];
 
int rmq[kMaxN * 3][20], euler[3 * kMaxN], aib[3 * kMaxN];
int st[kMaxN], dr[kMaxN];
 
vector<int> vertex[kMaxN];
 
void df(int nod) {
    euler[++euler[0]] = nod;
    st[nod] = euler[0];
    viz[nod] = true;
 
    for (int itr : vertex[nod]) {
        if (not viz[itr]) {
            deep[itr] = deep[nod] + 1;
            df(itr);
            euler[++euler[0]] = nod;        
        }
    }
    euler[++euler[0]] = nod;
    dr[nod] = euler[0];
    return ;
}
 
int lca(int a, int b) {
    a = st[a];
    b = st[b];
    if (a > b)
        swap(a, b);
    if (a == b)
        return euler[a];
     
    int p = 0;
    while (b - a + 1 > (1 << (p + 1)))
        ++p;
    b -= (1 << p) - 1;
    if (deep[rmq[a][p]] < deep[rmq[b][p]])
        return rmq[a][p];
    else
        return rmq[b][p];
}

int k;

int dist[305][305];
int Right[305], Left[305];
int a[305], b[305];

bool cuplaj(int nod, int val) {
	if (viz[nod])
		return false;
	viz[nod] = true;
	for (int i = 1; i <= k; ++i) {
		if (dist[nod][i] <= val and Right[i] == 0) {
			Right[i] = nod;
			Left[nod] = i;
			return true;
		}
	}
	for (int i = 1; i <= k; ++i) {
		if (dist[nod][i] <= val and i != nod and cuplaj(Right[i], val)) {
			Left[nod] = i;
			Right[i] = nod;
			return true;
		}
	}
	return false;
}

bool solve(int val) {
	for (int i = 1; i <= k; ++i) {
		Left[i] = Right[i] = 0;
	}
	bool ok = true;
	int nr = 0;
	while (nr < k and ok == true) {
		ok = false;
		for (int i = 1; i <= k; ++i) {
			viz[i] = false;
		}

		for (int i = 1; i <= k; ++i) 
			if (Left[i] == 0 and viz[i] == 0) {
				if (cuplaj(i, val)) {
					ok = true;
					++nr;
				}
			}
	}
	return nr == k;
}

int main() {
    cin >> n >> k;
	
	for (int i = 1; i <= k; ++i) {
		cin >> a[i];
	}
	
	for (int i = 1; i <= k; ++i) {
		cin >> b[i];
	}

    for (int i = 1; i < n; ++i) {
		int a, b; cin >> a >> b;
		vertex[a].push_back(b);
        vertex[b].push_back(a);
    }
    df(1);
    
	for (int i = 1; i <= euler[0]; ++i)
        rmq[i][0] = euler[i];
    for (int p = 1; (1 << p) <= euler[0]; ++p) {
        for (int i = 1; i + (1 << p) - 1 <= euler[0]; ++i) {
            if (deep[rmq[i][p - 1]] < deep[rmq[i + (1 << (p - 1))][p - 1]])
                rmq[i][p] = rmq[i][p - 1];
            else
                rmq[i][p] = rmq[i + (1 << (p - 1))][p - 1];
        }
    }
 
    for (int i = 1; i <= k; ++i) {
		for (int j = 1; j <= k; ++j) {
	 		dist[i][j] = deep[a[i]] + deep[b[j]] - 2 * deep[lca(a[i], b[j])];   	
		}
	}
    if (solve(0)) {
		cout << "0\n";
		return 0;
	}

	int p = 20;
 	int rez = 0;
	for (; p >= 0; --p) {
		if (solve((1 << p) + rez) == false) {
			rez += (1 << p);
		}
	}
	cout << rez + 1;
	return 0;
}
