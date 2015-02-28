//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("vlad.in");
ofstream out("vlad.out");

const int kMaxN = 10005, kMaxQ = 50005, kSq = 50;

struct Query {
	int st, dr, ind;
	Query() {
		st = dr = ind = 0;
	}
	pair<int, int> GetSeq() {
 		return make_pair(st / kSq, dr / kSq); 
	}	
	bool operator < (const Query &rhs) const {
		return make_pair(st / kSq, dr/kSq) < make_pair(rhs.st / kSq, rhs.dr / kSq);
	}
};

int el[kMaxN], finRez[kMaxQ];
Query Q[kMaxQ];

int ap[kMaxN], ap2[kMaxN], apInd[kMaxN];
vector<int> uniq;

int main() {
	int n, q;
	in >> n >> q;
	for (int i = 1; i <= n; ++i) {
		in >> el[i];
		uniq.push_back(el[i]);
	}

	for (int i = 1; i <= q; ++i) {
		in >> Q[i].st >> Q[i].dr;
		Q[i].ind = i;
	}
	
	sort(Q + 1, Q + q + 1);

	sort(uniq.begin(), uniq.end());
	uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());

 	for (int i = 1; i <= n; ++i)
		el[i] = lower_bound(uniq.begin(), uniq.end(), el[i]) - uniq.begin();

	int ind = 1;
//	for (int i = 1; i <= n; ++i)
//		cerr << el[i] << '\t';
//	cerr << '\n';
	for (int st = 0; st <= n / kSq; ++st) {

    	
		for (int i = 0; i < n; ++i)
			ap[i] = 0;
		int mx = 0, mxEl = 0;
 		for (int dr = st; dr <= n / kSq; ++dr) {

  			if (dr >= st + 2) {
//				cerr << st << '\t' << dr << '\t' << (dr - 1) * kSq << '\t' << dr * kSq << "!!\n";
				for (int i = (dr - 1) * kSq; i < min(n + 1, (dr) * kSq); ++i) {
//					cerr << i << '\n';
					++ap[el[i]];
					if (ap[el[i]] > mx) {
						mx = ap[el[i]];
						mxEl = el[i];
					}
				}
			}

			while (ind <= q and Q[ind].GetSeq() == make_pair(st, dr)) {
 				int rez = mx;
				int rezEl = mxEl;   				
/*				cerr << "~~~~~~~\n";
				for (int i = 0; i < int(uniq.size()); ++i)
					cerr << ap[i] << '\t';
				cerr << '\n';
				cerr << "PENIS!\n";
				cerr << Q[ind].st << '\t' << Q[ind].dr << '\n';*/
				for (int i = Q[ind].st; i < min(Q[ind].dr + 1, (st + 1) * kSq); ++i) {
//					cerr << i << '\t';
					if (apInd[el[i]] == ind) {
						++ap2[el[i]];
 						if (rez < ap2[el[i]] + ap[el[i]]) {
							rez = ap2[el[i]] + ap[el[i]];
							rezEl = el[i];
						}
					} else {
						ap2[el[i]] = 1;
						apInd[el[i]] = ind;
 						if (rez < ap2[el[i]] + ap[el[i]]) {
							rez = ap2[el[i]] + ap[el[i]];
							rezEl = el[i];
						}
					}
				}
				if (st != dr)
	 				for (int i = dr * kSq; i <= Q[ind].dr; ++i) {
	 					if (apInd[el[i]] == ind) {
							++ap2[el[i]];
 							if (rez < ap2[el[i]] + ap[el[i]]) {
								rez = ap2[el[i]] + ap[el[i]];
								rezEl = el[i];
							}
						} else {
							ap2[el[i]] = 1;
							apInd[el[i]] = ind;
 							if (rez < ap2[el[i]] + ap[el[i]]) {
								rez = ap2[el[i]] + ap[el[i]];
								rezEl = el[i];
							}
						}   					
					}
//				cerr << rez << "!\n";
 		   		finRez[Q[ind].ind] = rez; 
				++ind;
			}
	   	}
	}
	for (int i = 1; i <= q; ++i)
		out << finRez[i] << '\n';
    return 0;
}
