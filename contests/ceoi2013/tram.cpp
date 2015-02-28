#include <cassert>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

ifstream in("tram.in");
ofstream out("tram.out");

#define ll long long

const int max_n = 150005, inf = 0x3f3f3f3f;
int up[max_n], down[max_n], both[max_n], stack[max_n];
int inside;
int n, m;

set<int> uniq;
int x[max_n], y[max_n];

struct loc {
	int a, b;
	ll dist;
	loc() {
		a = b = dist = 0;	
	}
	pair<int, int> get_location() const {
		if (a + 1 == b) {
			pair<int,int> rez;
			rez.first = a;
			if (up[a] == 0) {
                rez.second = 1;
				return rez;
			}
			if (down[a] == 0) {
				rez.second = 2;
				return rez;
			}
			rez.first ++;
			if (up[b] == 0) {
				rez.second = 1;
				return rez;
			}
			if (down[b] == 0) {
				rez.second = 2;
				return rez;
			}
			rez.second = 0;
			cerr << a << ' ' << b << '\n';
			assert(0);
			return rez;
		}
		int dist = b - a - 1;
		pair<int, int> rez;
        if (dist == 1) {
            if (not up[a] && not up[b]) {
                rez.first = a + 1;
                rez.second = 1;
                return rez;
            }
            if (not down[a] && not down[b]) {
                rez.first = a + 1;
                rez.second = 2;
				return rez;
            }
            if (not up[a]) {
                rez.first = a;
                rez.second = 1;
                return rez;
            }
            if (not down[a]) {
                rez.first = a;
                rez.second = 2;
                return rez;
            }
            rez.first = a + 1;
            rez.second = 1;
            return rez;
        }
        if (dist == 2) {
            if (not up[a]) {
                rez.first = a + 1;
                rez.second = 1;
                return rez;
            }
            if (not down[a]) {
                rez.first = a + 1;
                rez.second = 2;
                return rez;
            }
            if (not up[b]) {
                rez.first = a + 2;
                rez.second = 1;
                return rez;
            }
            if (not down[b]) {
                rez.first = a + 2;
                rez.second = 2;
                return rez;
            }
            rez.first = a + 1;
            rez.second = 1;
            return rez;
        }
 		if (dist & 1) {
			rez.first = dist / 2 + a + 1;
			if (up[a] == 0 && up[b] == 0) {
				rez.second = 1;
				return rez;
			}
			if (down[a] == 0 && down[b] == 0) {
				rez.second = 2;
				return rez;
			}
			rez.second = 1;
			return rez;
		} else {
			if (both[a] == 0 || (both[b] == 1)) {
				rez.first = a + dist / 2;
				if (up[a])
					rez.second = 2;
				else
					rez.second = 1;
				return rez;
			} else {
 				rez.first = a + dist / 2 + 1;
				if (up[b])
					rez.second = 2;
				else
					rez.second = 1;
				return rez;
			}
		}
	}
	void get_dist() {
		if (a + 1 == b) {
			if (both[a] && both[b]) {
				dist = 0;
				return ;
			}
			dist = 1;
			return ;
		}
        if (a + 2 == b) {
            if (not up[a] && not up[b]) {
                dist = 2;
                return ;
            }
			if (not down[a] && not down[b]) {
				dist = 2;
				return ;
			}
            dist = 1;
            return ;
        }
        if (a + 3 == b) {
            if (not both[a] || not both[b])
                dist = 2;
            else
                dist = 1;
            return ;
        }
		int d = b - a - 1;
		if (d & 1) {
			d++;
			d /= 2;
			dist = 1LL * d * d;
			if (not up[a] && not up[b])
				dist ++;
			if (not down[a] && not down[b])
				dist ++;
		} else {
			d /= 2;
			dist = 1LL * d * d;
			if (not both[a] || not both[b])
				++dist;
		}
	}
	bool operator < (const loc &oth) const {
        if (dist == oth.dist) {
			if (a < oth.a)
				return 1;
			return 0;
		}
		return dist > oth.dist;
	}
} ;

set<loc> S;

void make_bounds(int ind) {
//	cerr << x[ind] << "#" << y[ind] << "COORDS <---\n";
	stack[x[ind]] ++;
	uniq.insert(x[ind]);
	set<int> :: iterator it = uniq.find(x[ind]);
	int st, dr;
	if (it == uniq.begin())
		st = -1;
	else {
		st = *(--it);
		++it;
	}
	++it;
	if (it == uniq.end())
		dr = -1;
	else
		dr = *(it);
	--it;
	if (stack[x[ind]] == 2) {
		if (st != -1) {
			loc aux;
			aux.a = st;
			aux.b = x[ind];
			aux.get_dist();
			S.erase(S.find(aux));
		}
		if (dr != -1) {
			loc aux;
			aux.a = x[ind];
			aux.b = dr;
			aux.get_dist();
			S.erase(S.find(aux));
		}
	} else {
		if (st != -1 && dr != -1) {
			loc aux;
			aux.a = st;
			aux.b = dr;
			aux.get_dist();
			S.erase(S.find(aux));
		}
	}
	if (y[ind] == 1) {
		assert(not up[x[ind]]);
		up[x[ind]] = 1;
	} 
	else {
		assert(not down[x[ind]]);
		down[x[ind]] = 1;
	}
	both[x[ind]] = up[x[ind]] & down[x[ind]];
	if (st != -1) {
		loc aux;
		aux.a = st;
		aux.b = x[ind];
		aux.get_dist();
		S.insert(aux);
	}
	if (dr != -1) {
		loc aux;
		aux.a = x[ind];
		aux.b = dr;
		aux.get_dist();
		S.insert(aux);
	}
}

void add_person(int ind) {
	ll st, dr;
	if (uniq.size()) {
		int aux = *uniq.begin();
		st = 1LL * (aux - 1) * (aux - 1) + 1 - both[aux];
		
		aux = *uniq.rbegin();
		dr = 1LL * (n - aux) * (n - aux) + 1 - both[aux];
	} else {
		st = 1LL * inf * inf;
		dr = 0;
	}
	ll mx;
	if (S.size()) {
		mx = S.begin()->dist;	
	} else {
		mx = 0;
	}
//	cerr << st << "#" << mx << "#" << dr << "\n";
    if (st >= dr && st >= mx) {
		x[ind] = 1;
		int w = *uniq.begin();
 		if (both[w] || up[w] == 0)
			y[ind] = 1;
		else
			y[ind] = 2;
		make_bounds(ind);
		return ;
	}
	if (mx >= dr) {
		pair <int, int> coord = S.begin()->get_location();
		x[ind] = coord.first;
		y[ind] = coord.second;
		make_bounds(ind);
		return ;
	}
	int w = *uniq.rbegin();
 	x[ind] = n;
	if (both[w] || (up[w] == 0))
		y[ind] = 1;
	else
		y[ind] = 2;
	make_bounds(ind);
}

void erase_person(int ind) {
	stack[x[ind]]--;
 	set<int> :: iterator it = uniq.find(x[ind]);
	int st, dr;
	if (it == uniq.begin())
		st = -1;
	else {
		st = *(--it);
		++it;
	}
	++it;
	if (it == uniq.end())
		dr = -1;
	else
		dr = *(it);
	--it;
	if (st != -1) {
		loc aux;
		aux.a = st;
		aux.b = x[ind];
		aux.get_dist();
		S.erase(S.find(aux));
	}
	if (dr != -1) {
		loc aux;
		aux.a = x[ind];
		aux.b = dr;
		aux.get_dist();
		S.erase(S.find(aux));
	}                 
 	if (y[ind] == 1)
		up[x[ind]] = 0;
	else
		down[x[ind]] = 0;
	both[x[ind]] = 0;
	if (stack[x[ind]]) {

		if (st != -1) {
			loc aux;
			aux.a = st;
			aux.b = x[ind];
			aux.get_dist();
			S.insert(aux);
		}
		if (dr != -1) {
			loc aux;
			aux.a = x[ind];
			aux.b = dr;
			aux.get_dist();
			S.insert(aux);
		}
	} else {
		uniq.erase(uniq.find(x[ind]));
		if (st != -1 && dr != -1) {
			loc aux;
			aux.a = st;
			aux.b = dr;
			aux.get_dist();
			S.insert(aux);
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		char type;
		cin >> type;
		if (type == 'E') {
			add_person(i);
			cout << x[i] << ' ' << y[i] << '\n';
		} else {
			int ind;
			cin >> ind;
 			erase_person(ind);
		}
/*		for (set<loc> :: iterator it = (S).begin(); it != (S).end(); ++it)
			cerr << it -> a << '\t' << it -> b << '\t' << it -> dist << '\n';
        cerr << '\n';
		for (set<int> :: iterator it = uniq.begin(); it != uniq.end(); ++it)
			cerr << *it << ' ';
 		cerr << '\n';
		cerr << "\n\n";*/
	}
	return 0;
}
