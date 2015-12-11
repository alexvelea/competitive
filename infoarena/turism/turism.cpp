//Problem turism from Infoarena
// "We are drowning in information and starved for knowledge."
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 30005;

ifstream in("turism.in");
ofstream out("turism.out");

priority_queue<pair<int, int> > IPQ, OPQ;
vector<int> vertex[kMaxN];

int comps;
int father[kMaxN];
int In[kMaxN], Out[kMaxN];
bool viz[kMaxN];

int get_father(int nod) {
	if (father[nod] != nod)
		father[nod] = get_father(father[nod]);
	return father[nod];
}

void unite(int a, int b) {
	a = get_father(a);
	b = get_father(b);
	if (a == b)
		return ;
	father[a] = b;
	In[b] += In[a];
	Out[b] += Out[a];
	In[a] = Out[a] = 0;
	--comps;
	return;
}

void df(int nod) {
	viz[nod] = true;
 	for (int itr : vertex[nod]) {
		if (not viz[itr]) {
			unite(nod, itr);
			df(itr);
		}
	}
}

int main() {
	int n, m;
	in >> n >> m;
	comps = n;
	for (int i = 1; i <= m; ++i) {
		int a, b;
		in >> a >> b;
		Out[a]++;
		In[b]++;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}

    for (int i = 1; i <= n; ++i)
		father[i] = i;

	for (int i = 1; i <= n; ++i) {
		if (Out[i] >= In[i]) {
			Out[i] -= In[i];
			In[i] = 0;
			if (Out[i])
				OPQ.push(make_pair(-i, Out[i]));
		} else {
			In[i] -= Out[i];
			Out[i] = 0;
			if (In[i])
				IPQ.push(make_pair(-i, In[i]));
		}
	}

	for (int i = 1; i <= n; ++i)
		if (not viz[i]) {
			df(i);
        	int f = get_father(i);
			if (In[f] == 0) {
				In[f]++;
				Out[f]++;
				OPQ.push(make_pair(-i, 1));
				IPQ.push(make_pair(-i, 1));
			}
		}

	vector<pair<int, int> > rez;
	
	while (IPQ.size()) {
		pair<int, int> I, O;
		I = IPQ.top(); IPQ.pop();
		O = OPQ.top(); OPQ.pop();

 		if (comps != 1 and get_father(-I.first) == get_father(-O.first) and In[get_father(-I.first)] == 1) {
			pair<int, int> oth;
           	oth = OPQ.top();
			OPQ.pop();
			OPQ.push(O);
			O = oth;
		}
 		unite(-I.first, -O.first);
		In[get_father(-I.first)]--;   	
		I.second--;
		O.second--;
		if (I.second)
			IPQ.push(I);
		if (O.second)
			OPQ.push(O);
		rez.push_back(make_pair(-I.first, -O.first));
	}

	out << rez.size() << '\n';
	for (auto itr : rez) {
		out << itr.first << ' ' << itr.second << '\n';
	}

	return 0;
}
