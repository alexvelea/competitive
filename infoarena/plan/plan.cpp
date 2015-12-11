//Problem plan from Infoarena
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

ifstream in("plan.in");
ofstream out("plan.out");

bool viz[kMaxN];
int ord[kMaxN];

vector<int> vertex[kMaxN], vertex_back[kMaxN];
vector<int> ctc_el[kMaxN]; int ctc[kMaxN];
vector<int> ctc_vertex[kMaxN]; int ctc_in[kMaxN];

void df_1(int nod) {
	if (viz[nod])
		return ;
	viz[nod] = true;
	for (int it : vertex[nod])
		df_1(it);
 	ord[++ord[0]] = nod;   	
	return ;
}

void df_2 (int nod) {
	if (viz[nod])
		return ;
	viz[nod] = true;
	ctc[nod] = ctc[0];
	for (int itr : vertex_back[nod])
		df_2(itr);
	return ;
}

int start;

vector<int> match_vertex[kMaxN];
int match[kMaxN];
                 
void ctc_df(int nod) {
	if (viz[nod])
		return ;
	viz[nod] = true;
	if (ctc_vertex[nod].size() == 0)
		match_vertex[start].push_back(nod);
	for (int itr : ctc_vertex[nod])
		ctc_df(itr);
	return ;
}

bool find_aug_path(int nod) {
	if (viz[nod] == true)
		return false;
	viz[nod] = true;
	for (int itr : match_vertex[nod])
		if (match[itr] == 0) {
			match[itr] = nod;
			match[nod] = itr;
			return true;
		}
	
	for (int itr : match_vertex[nod])
		if (find_aug_path(match[itr])) {
			match[nod] = itr;
			match[itr] = nod;
			return true;
		}
	return false;
}

int main() {
	int n, m;
	in >> n >> m;

	for (int i = 1; i <= m; ++i) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertex_back[b].push_back(a);
	}
	
	for (int i = 1; i <= n; ++i)
		df_1(i);
	for (int i = 1; i <= n; ++i)
		viz[i] = 0;

	for (int i = n; i; --i)
		if (not viz[ord[i]]) {
			++ctc[0];
			df_2(ord[i]);
		}

	for (int i = 1; i <= n; ++i) {
		ctc_el[ctc[i]].push_back(i);
		for (int it : vertex[i])
			if (ctc[i] != ctc[it]) {
				ctc_vertex[ctc[i]].push_back(ctc[it]);
				ctc_in[ctc[it]]++;
			}
	}
	
	for (int i = 1; i <= ctc[0]; ++i)
		if (ctc_in[i] == 0 and ctc_vertex[i].size()) {
			start = i;
			ctc_df(i);
			for (int j = 1; j <= ctc[0]; ++j)
				viz[j] = 0;
		}

	while (1) {
		bool ok = false;
	
		for (int i = 1; i <= ctc[0]; ++i)
			viz[i] = 0;

		for (int i = 1; i <= ctc[0]; ++i) 
			if (match[i] == 0 and match_vertex[i].size())
				if (find_aug_path(i)) 
					ok = true;

		if (not ok)
			break;
	}

	vector<int> Start, End;
	vector<pair<int, int> > rez;
	int StartN = 0, EndN = 0;
 	for (int i = 1; i <= ctc[0]; ++i) {
		if (ctc_vertex[i].size() and ctc_in[i] == 0) {
			StartN = i;
			if (match[i] == 0)
				Start.push_back(i);
			else
				rez.push_back(make_pair(i, match[i]));
		}
		if (ctc_vertex[i].size() == 0 and ctc_in[i] != 0) {
			EndN = i;
			if (match[i] == 0)
				End.push_back(i);
		}
	}

	if (Start.size() > End.size()) {
		for (int i = 0; i < int(End.size()); ++i)
			rez.push_back(make_pair(Start[i], End[i]));
		for (int i = End.size(); i < int(Start.size()); ++i)
			rez.push_back(make_pair(Start[i], EndN));
	} else {
		for (int i = 0; i < int(Start.size()); ++i)
			rez.push_back(make_pair(Start[i], End[i]));
		for (int i = int(Start.size()); i < int(End.size()); ++i)
			rez.push_back(make_pair(StartN, End[i]));
	}
	
	if (rez.size())
		rez.push_back(*rez.begin());
	else
		rez.push_back(make_pair(0, 0));
	out << rez.size() - 1 << '\n';
	for (int i = 0; i + 1 < int(rez.size()); ++i)
		out << ctc_el[rez[i].second][0] << ' ' << ctc_el[rez[i + 1].first][0] << '\n';
	return 0;
}
