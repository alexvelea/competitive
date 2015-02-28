#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 1000005, inf = 0x3f3f3f3f;
const int kMod[2] = {1000000007, 1000000009}, sigma[2] = {31, 29};

ifstream in("cenzura.in");
ofstream out("cenzura.out");


struct Trie
{
    Trie *nxt[26], *back;
    bool finish; int len;
    
    Trie() {
        memset(nxt, 0, sizeof(nxt));
        back = NULL;
        finish = false;
        len = 0;
    }
	
	~Trie() {
		for (int i = 0; i < 26; ++i) {
			if (nxt[i]) {
				delete(nxt[i]);
			}
		}
	}
} *R;


void insertT(Trie *T, char *now) {
    if (*now == 0) {
        T->finish = true;
        return;
    }

    if (T->nxt[*now - 'a'] == 0) {
        T->nxt[*now - 'a'] = new Trie();
        T->nxt[*now - 'a']->len = T->len + 1;
    }

    insertT(T->nxt[*now - 'a'], now + 1);
}

queue<Trie*> Q;



char txt[kMaxN], B[kMaxN];
int imp[kMaxN], limit[kMaxN], dp[kMaxN], deq[kMaxN];


int main() {
	int t;
	in >> t;
	while (t--) {
        R = new Trie;

		int n;
		in >> n;
		in >> txt;
		for (int i = 0; i < n; ++i) {
			in >> imp[i];
		}

		int m;
		in >> m;
        for (int i = 1; i <= m; ++i) {
            in >> B;
            insertT(R, B);
        }
        
        Q.push(R);
        while (!Q.empty()) {
            Trie *now = Q.front();
            Q.pop();
            
            for (int i = 0; i < 26; ++i)
                if (now->nxt[i] != NULL) {
                    Trie *aux = now->back;
                    
                    while (aux != NULL && aux->nxt[i] == NULL) {
                        aux = aux->back;
					}
                    
                    if (aux == 0) {
                        now->nxt[i]->back = R;
                    } else {
                        now->nxt[i]->back = aux->nxt[i];
                    }
                    
                    Q.push(now->nxt[i]);
                }
        }
        
        Trie *tnow = R;
        for (int i = 0; txt[i] != 0; ++i) {
            while (tnow != 0 && tnow->nxt[txt[i] - 'a'] == 0) {
                tnow = tnow->back;
			}
            
            if (tnow == 0) {
				tnow = R;
            } else {
				tnow = tnow->nxt[txt[i] - 'a'];
			}
            
            if (tnow->finish == true) {
                limit[i] = tnow->len;
                tnow = tnow->back;
                if (tnow == 0) {
                    tnow = R;
				}
            }
        }
        
 		for (int i = 0; i <= n; ++i) {
			dp[i] = +inf;
		}
		
		int st = 0, dr = 0;
		deq[0] = 0;
		dp[0] = 0;

		for (int i = n; i; --i) {
			limit[i] = limit[i - 1];
			imp[i] = imp[i - 1];
		}
		++n;
		
		for (int i = 1; i <= n; ++i) {
 			dp[i] = dp[deq[st]] + imp[i];
			while (st <= dr and dp[deq[dr]] > dp[i])
				--dr;
			deq[++dr] = i;
			while (limit[i] and st <= dr and deq[st] <= i - limit[i])
				++st;
		}
		for (int i = 0; i < n; ++i)
			cerr << limit[i] << '\t';
		cerr << '\n';
		for (int i = 0; i <= n; ++i) {
			cerr << dp[i] << '|' << imp[i] << '\t';
		}
		cerr << "\n\n";
		out << dp[n] << '\n';

		delete(R);
		for (int i = 0; i <= n; ++i) {
			limit[i] = 0;
		}
	}
	return 0;
}
