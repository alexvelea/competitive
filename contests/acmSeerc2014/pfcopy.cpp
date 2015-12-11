#include <ctime>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

const int kMaxN = 61006, Buffer = 250, inf = 0x3f3f3f3f;

set<pair<int, int> > elements[kMaxN / Buffer];
int el[kMaxN], all[kMaxN / Buffer];

int n, k, rez, under;

void bigger_rez () {
//	cerr << "->rez\n";
	rez++;
	for (int i = 0; i * Buffer <= n; ++i) {
		set<pair<int, int> > :: iterator it = elements[i].lower_bound(make_pair(rez - all[i], 0));
		if (it->first == rez - all[i])
			under += it->second;
	}
//	cerr << "<-rez\n";
}

void Insert(int ind) {
//	cerr << "->Insert\n";
	if (el[ind] + all[ind / Buffer] <= rez)
		++under;
	set<pair<int, int> > :: iterator it = elements[ind / Buffer].lower_bound(make_pair(el[ind], 0));
// 	cerr << "~~~\t" << elements[0].size() << '\n';   
 
// 	for (auto it : elements[0])
//		cerr << "~+++~\t" << it.first << '\t' << it.second << '\n';   

	pair<int, int> aux = make_pair(el[ind], 0);
//	cerr << el[ind] << '\t' << it->first << "~~" << it->second << "~~\n";

	if (it->first == el[ind]) {
		aux.second = it->second;
		elements[ind / Buffer].erase(it);
	}
	
	aux.second++;
	elements[ind / Buffer].insert(aux);
//	cerr << "<-Insert\n";
}

void Erase(int ind) {
	if (el[ind] + all[ind / Buffer] <= rez)
		--under;
 	set<pair<int, int> > :: iterator it = elements[ind / Buffer].lower_bound(make_pair(el[ind], 0));
	pair<int, int> aux = *it;
//	cerr << "!!!\t" << elements[ind / Buffer].size() << '\n';
//	cerr << "!!!!!!\t" << el[ind] << '\n';
//	cerr << it->first << "\t" << it->second << '\n';
//	cerr << "~~~~~~~\n";
//	if (it == elements[ind / Buffer].end())
//		cerr << "PENIS!";
	elements[ind / Buffer].erase(it);
	aux.second--;
	if (aux.second > 0)
		elements[ind / Buffer].insert(aux);   
}

int main() {
while (1) {
//	cerr << "QWERTYUIOIYTREWQWERTYU\n";
	under = rez = 0;
	in >> n >> k;
	if (n == 0)
		break;

 	for (int i = 0; i * Buffer <= n; ++i) {
		all[i] = 0;
		elements[i].clear();
		elements[i].insert(make_pair(-inf, 0));
		elements[i].insert(make_pair(inf, 0));
	}

	vector<int> e;

	for (int i = 1; i <= n; ++i) {
		in >> el[i];
		e.push_back(el[i]);
	}
	sort(e.begin(), e.end());
	rez = e[(n + 1) / 2];
    for (int i = 1; i <= n; ++i) {
		Insert(i);
	}

	e.clear();
	
	while (k--) {
		int st, dr;
		in >> st >> dr;
        for (int i = 0; i * Buffer <= n; ++i) {
			int c1 = i * Buffer;
			int c2 = (i + 1) * Buffer - 1; 
			if (st <= c1 and c2 <= dr) {
				set< pair<int, int> > :: iterator it = elements[i].lower_bound(make_pair(rez - all[i], 0));
				if (it->first == rez - all[i])
					under -= it->second;
				all[i]++;
 			} else {
				int C1 = max(c1, st);
				int C2 = min(c2, dr);
//				cerr << "!";
				for (int j = C1; j <= C2; ++j) {
					Erase(j);
					el[j]++;
					Insert(j);
				}
//				cerr << "~";
			}
		}

//		for (int i = 1; i <= n; ++i)
//			cerr << el[i] << ' ';
//		cerr << "\n";
//		for (auto it : elements[0])
//			cerr << "~~~~\t" << it.first << '\t' << it.second << '\n';

		while (under < (n + 1) / 2) {
			bigger_rez();
		}
//		cerr << rez << '\t' << under << "\n\n";
		out << rez << '\n';
	}
}
return 0;
}
