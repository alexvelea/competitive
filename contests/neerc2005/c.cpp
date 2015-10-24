//Problem c @ 14-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 10005;

#define int64 long long

vector<int> stack;

vector<pair<int, int> > vertex[kMaxN], reverseVertex[kMaxN];
bool viz[kMaxN];
int rez[kMaxN], maxVal[kMaxN], minVal[kMaxN], father[kMaxN];

void df(int nod) {
    viz[nod] = true;
    for (auto itr : vertex[nod]) {
        if (not viz[itr.first]) {
            df(itr.first);
        }
    }
    stack.push_back(nod);
}

void df2(int nod, int f) {
    viz[nod] = true;
    father[nod] = f;
    for (auto itr : reverseVertex[nod]) {
        if (not viz[itr.first]) {
            df2(itr.first, f);
        }
    }
    return ;
}

int main() {
	ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        vertex[a].push_back(make_pair(b, c));
        reverseVertex[b].push_back(make_pair(a, c));
    }

    for (int i = 1; i <= n; ++i) {
        viz[i] = false;
        vertex[i].push_back(make_pair(0, 0));
        reverseVertex[0].push_back(make_pair(i, 0));

        vertex[n + 1].push_back(make_pair(i, 0));
        reverseVertex[i].push_back(make_pair(n + 1, 0));
    }

    for (int i = 0; i <= n + 1; ++i) {
        viz[i] = false;
    }
        
    stack.clear();
    df(n + 1);

    reverse(stack.begin(), stack.end());
    for (int i = 0; i <= n + 1; ++i) {
        viz[i] = false;
    }  

    for (auto itr : stack) {
        if (not viz[itr]) {
            df2(itr, itr);
        }
    }

    for (int i = 0; i <= n + 1; ++i) {
        vector<pair<int, int> > aux = vertex[i];
        vertex[i].clear();
        for (auto itr : aux) {
            vertex[father[i]].push_back(make_pair(father[itr.first], itr.second));
        }

        aux = reverseVertex[i];
        
        reverseVertex[i].clear();
        for (auto itr : aux) {
            reverseVertex[father[i]].push_back(make_pair(father[itr.first], itr.second));
        } 
    }

    for (int i = 0; i <= n + 1; ++i) {
        for (auto itr : vertex[i]) {
            if (itr.first == i and itr.second != 0) {
                cout << "-1\n";
                return 0;
            }
        }
    }

    for (int i = 0; i <= n + 1; ++i) {
        viz[i] = false;
    }
        
    stack.clear();
    df(n + 1);   

    for (auto nod : stack) {
        for (auto itr : reverseVertex[nod]) {
            rez[itr.first] = max(rez[itr.first], itr.second + rez[nod]);
        }
    }
    
    for (int i = 0; i <= n + 1; ++i) {
        minVal[i] = rez[i] - 10000;
        rez[i] = -1;
    }


    int r = minVal[father[1]];
    for (int p = 20; p >= 0; --p) {
        for (int i = 0; i <= n + 1; ++i) {
            rez[i] = minVal[i];
        }
        
        rez[father[1]] = r + (1 << p);

        for (auto nod : stack) {
            for (auto itr : reverseVertex[nod]) {
                rez[itr.first] = max(rez[itr.first], itr.second + rez[nod]); 
            }
        }        

        bool ok = true;
        for (int i = 0; i <= n + 1; ++i) {
            if (rez[i] > 10000 or rez[i] < -10000) {
                ok = false;
            }
        }
        
        if (ok) {
            r += (1 << p);
        }
    }

        for (int i = 0; i <= n + 1; ++i) {
            rez[i] = minVal[i];
        }
        
        rez[father[1]] = r;

        for (auto nod : stack) {
            for (auto itr : reverseVertex[nod]) {
                rez[itr.first] = max(rez[itr.first], itr.second + rez[nod]); 
            }
        }       


        bool ok = true;
        for (int i = 0; i <= n + 1; ++i) {
            if (rez[i] > 10000 or rez[i] < -10000) {
                ok = false;
            }
        }

    if (ok == false) {
        cout << "-1\n";
        return 0;
    }


    
    for (int i = 1; i <= n; ++i) {
        cout << rez[father[i]] << ' ';
    }
	return 0;
}
