#include <algorithm>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("drumuri4.in");
ofstream out("drumuri4.out");

const int kBufferSize = 1000005;
int BufferInd = kBufferSize;
char Buffer[kBufferSize];
#define verf ((++BufferInd >= kBufferSize) ? (in.read(Buffer, kBufferSize), BufferInd = 0) : (0))
#define BufferC (Buffer[BufferInd])
#define char_ok (((BufferC >= '0' and BufferC <= '9') or BufferC == '-') ? (1) : (0))

void cit(int &n) {
	verf;
	for (; not char_ok; verf)
		;
	
	bool sign = false;
	if (BufferC == '-') {
		verf;
		sign = true;
	}
    
	n = 0;
	for (; char_ok; verf) {
		n *= 10;
		n += BufferC - '0';
	}
	if (sign)
		n *= -1;
}



const int kMaxN = 40005, D = 200;

vector<int> rez;
pair<int, int> edge[kMaxN], edgeD[kMaxN];

bool is_end(int nod) {
	if (edge[nod].first == 0 or edge[nod].second == 0)
		return true;
	return false;
}


int go_as_much(int nod, int last) {
	if (edge[nod].first == last or edgeD[nod].first == last) {
		// mergem pe second de acum
		if (edgeD[nod].second)
			return go_as_much(edgeD[nod].second, nod);
		if (edge[nod].second)
			return go_as_much(edge[nod].second, nod);
		return nod;
	}

	if (edgeD[nod].first)
		return go_as_much(edgeD[nod].first, nod);
	if (edge[nod].first)
		return go_as_much(edge[nod].first, nod);
	return nod;
}

void get_first_d(int nod, int last, vector<pair<int, bool> > &el) {
 	for (int i = 1; i <= D; ++i) {
		if (nod == 0)
			break;
		if (edge[nod].first == last) {
			el.push_back(make_pair(nod, 0));
			last = nod;
			nod = edge[nod].second;
		} else {
			el.push_back(make_pair(nod, 1));
			last = nod;
			nod = edge[nod].first;
		}
	}
}

void unite(int a, int b) {
	if (edge[a].first == 0)
		edge[a].first = b;
	else
		edge[a].second = b;
	
	if(edge[b].first == 0)
		edge[b].first = a;
	else
		edge[b].second = a;
	
	vector<pair<int, bool> > A, B;
	
	get_first_d(a, b, A);
	get_first_d(b, a, B);

	for (int i = 0; i < int(A.size()); ++i) {
		int oth = D - i - 1;
		if (B.size() > oth) {
			int q = A[i].first;
			int p = B[oth].first;

			int dA = A[i].second;
			int dB = B[oth].second;

			if (dA == 0)
				edgeD[q].first = p;
			else
				edgeD[q].second = p;

			if (dB == 0)
				edgeD[p].first = q;
			else
				edgeD[p].second = q;
		}
	}
}

pair<int, int> query_end(int nod) {
	pair<int, int> rez = make_pair(nod, nod);
	if (edge[nod].first)
		rez.first = go_as_much(edge[nod].first, nod);

	if (edge[nod].second)
		rez.second = go_as_much(edge[nod].second, nod);
	
	return rez;
}

void show() {
	sort(rez.begin(), rez.end());
	rez.resize(unique(rez.begin(), rez.end()) - rez.begin());
	out << rez.size() << ' ';
	for (int i = 0; i < int(rez.size()); ++i)
		out << rez[i] << ' ';
	out << '\n';
	rez.clear();
}

void split(int a, int b) {
	vector<pair<int, bool> > A, B;
	get_first_d(a, b, A);
	get_first_d(b, a, B);
    
	if (edge[a].first == b)
		edge[a].first = 0;
	else
		edge[a].second = 0;
	
	if (edge[b].first == a)
		edge[b].first = 0;
	else
		edge[b].second = 0;

	for (int i = 0; i < int(A.size()); ++i) {
		int dir = A[i].second;
		if (dir == 0)
			edgeD[A[i].first].first = 0;
		else
			edgeD[A[i].first].second = 0;
	}

	for (int i = 0; i < int(B.size()); ++i) {
		int dir = B[i].second;
		if (dir == 0)
			edgeD[B[i].first].first = 0;
		else
			edgeD[B[i].first].second = 0;
	}
}

void query_dist(int nod, int last, int d) {
	if (nod == 0)
		return ;

	if (d == 0) {
		rez.push_back(nod);
		return ;
	}
	
	if (edge[nod].first != last and edgeD[nod].first != last) {
		if (d >= D)
			query_dist(edgeD[nod].first, nod, d - D);
		else
			query_dist(edge[nod].first, nod, d - 1);
	}

	if (edge[nod].second != last and edgeD[nod].second != last) {
		if (d >= D)
			query_dist(edgeD[nod].second, nod, d - D);
		else
			query_dist(edge[nod].second, nod, d - 1);
	}
}

int n;

void debug() {
	for (int i = 1; i <= n; ++i)
		cerr << edge[i].first << '|' << edgeD[i].first << '\t';
	cerr << '\n';
	for (int i = 1; i <= n; ++i)
		cerr << edge[i].second << '|' << edgeD[i].second << '\t';
	cerr << "\n\n";
}

int main() {
	int m;
	cit(n);
	cit(m);
	for (int i = 1; i <= m; ++i) {
//		debug();
		int t;
		cit(t);
		if (t == 1) {
			// insert
			int a, b;
			cit(a);
			cit(b);
			if (is_end(a) and is_end(b))
				;
			else {
				out << "0\n";
				continue;
			}

			if (edge[a].first == b or edge[a].second == b) {
				out << "0\n";
				continue;
			}
			
			pair<int, int> q_end = query_end(a);
			
			if (q_end.first == b or q_end.second == b) {
				out << "0\n";
				continue;
			}
			
			unite(a, b);
			out << "1\n";
		}
		if (t == 2) {
			// erase
			int a, b;
			cit(a);
			cit(b);
			if (edge[a].first == b or edge[a].second == b)
				;
			else {
				out << "0\n";
				continue;
			}
			split(a, b);
			out << "1\n";
		}
		if (t == 3) {
			int a, d;
			cit(a);
			cit(d);
			query_dist(a, n + 1, d);
			show();
		}
		if (t == 4) {
			int a;
			cit(a);
			pair<int, int> q_end = query_end(a);
			rez.clear();
			rez.push_back(q_end.first);
			rez.push_back(q_end.second);
			show();
		}
	}
}
