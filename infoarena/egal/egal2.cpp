#include <cstdio>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int max_n = 100005;

int n;
vector<int> vertex[max_n];
vector<int> children;
vector<int> under[max_n];
pair<int,int> result[max_n]; // first -> key value ... second -> key count
int key[max_n];

int same_kind[max_n];

int line_poz[max_n], line[max_n];
int st[max_n], dr[max_n];
int next[max_n], last[max_n];

void delete_from_list (int ind) {
	int n, l;
	n = next[ind];
	l = last[ind];
 	if (l==0) {
		last[n] = 0;
		return ;
	}
	if (n==0) {
		next[l] = n+1;
		return ;
	}
 	next[l] = n;
	last[n] = l;
	return ;
}

void solve (int nod) {
 	for (vector<int> :: iterator it=vertex[nod].begin(); it!=vertex[nod].end(); ++it) {
		solve (*it);
	}
	cerr << nod << " <---\n";
	children.clear();
 	for (vector<int> :: iterator it=vertex[nod].begin(); it!=vertex[nod].end(); ++it) {
		children.push_back (*it);
	}
	children.push_back (nod);
	int mx = 0, i=0, poz=0;

	for (vector<int> :: iterator it = children.begin(); it!=children.end(); ++it) {
		cerr << "\t" << *it << "\n";
		if ((result[*it].second > result[nod].second) || (result[*it].second == result[nod].second && result[*it].first < result[nod].first)) {
			result[nod] = result[*it];
		}
        if (int(under[*it].size()) > mx) {
			poz = i;
			mx = under[*it].size();
		}
		i++;
	}
	cerr << poz << " <-------\n";
	int root = children[poz];
	int c_st = st[children[poz]], c_dr = dr[children[poz]];
	for (int ind = poz-1; ind >= 0; --ind) {
 		for (vector<int> :: iterator it = under[children[ind]].begin(); it != under[children[ind]].end(); ++it){
			// avem selectat elementul curent
			// vedem daca exista in intervalul st->dr
 			int el_next = next[*it];
			if (c_st <= el_next && el_next <= c_dr) {
				// exista, deci introducem elementele si il stergem.
 				same_kind[el_next] += same_kind[*it];
				same_kind[*it] = 0;

                if ((same_kind[el_next] > result[nod].second) || (same_kind[el_next] == result[nod].second && key[el_next]==result[nod].first))
					result[nod] = make_pair (key[el_next], same_kind[el_next]);

				delete_from_list (*it);
			}else{
				under[root].push_back (*it);
			}
		}
		c_st = st[children[ind]];
	}
 	c_st = st[children[poz]], c_dr = dr[children[poz]];
	for (int ind = poz+1; ind<int(children.size()); ++ind) {
		for (vector<int> :: iterator it = under[children[ind]].begin(); it != under[children[ind]].end(); ++it){
	 		int el_last = last[*it];   
			if (c_st <= el_last && el_last <= c_dr) {
				same_kind[el_last] += same_kind[*it];
				same_kind[*it] = 0;

                if ((same_kind[el_last] > result[nod].second) || (same_kind[el_last] == result[nod].second && key[el_last]==result[nod].first))
					result[nod] = make_pair (key[el_last], same_kind[el_last]);

				delete_from_list (*it);
			}else{
				under[root].push_back (*it);
			}
		}
		c_dr = dr[children[ind]];
	}
	swap (under[root], under[nod]);
	cerr << "\n\n";
}

void line_graph (int nod, int &ind) {
	st[nod] = ind;
	for (vector<int> :: iterator it = vertex[nod].begin(); it != vertex[nod].end(); ++it) {
		line_graph (*it, ind);
	}
 	line_poz[nod] = ind;
	line[ind] = nod;
	dr[nod] = ind;
	++ind;
}

int main() {
	freopen("egal.in", "r", stdin);
	freopen("egal.out", "w", stdout);

 	scanf ("%d", &n);
	for (int i=1, a, b; i<n; ++i) {
		scanf ("%d %d", &a, &b);
 		vertex[a].push_back(b);
	}
	for (int i=1, c; i<=n; ++i) {
		scanf ("%d", &c);
		key[i] = c;
	}
	//////////
	int ind_start = 1;
	line_graph (1, ind_start);
    //////////
    vector <int> key_vector;
	for (int i=1; i<=n; ++i) {
		key_vector.push_back(key[i]);
	}
	sort (key_vector.begin(), key_vector.end());
	key_vector.resize (unique (key_vector.begin(), key_vector.end()) - key_vector.begin());
 	for (int i=1; i<=n; ++i) {
		key[i] = lower_bound (key_vector.begin(), key_vector.end(), key[i]) - key_vector.begin();
 	}  
    //////////
	int last_seen[max_n];
	for (int i=0; i<int(key_vector.size()); ++i) 
		last_seen[i] = 0;

    for (int i=1; i<=n; ++i) {
		next[i] = n+1;
		last[i] = 0;
	}
	for (int i=1; i<=n; ++i) {
		under[i].push_back(i);
		if (last_seen[key[line[i]]]) {
			next[last_seen[key[line[i]]]] = line[i];
			last[i] = last_seen[key[line[i]]];
		}
		last_seen[key[i]] = line[i];
	}
	//////////
	for (int i=1; i<=n; ++i) {
		same_kind[i] = 1;
		result[i] = make_pair (key[i], 1);
	}
	solve (1);

	for (int i=1; i<=n; ++i) {
		printf ("%d %d\n", key_vector[result[i].first], result[i].second);
	}
	return 0;
}
