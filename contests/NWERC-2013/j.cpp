#include <cassert>
#include <algorithm>
#include <iostream>                                                             
#include <vector>
#include <unordered_map>
using namespace std;

const int kMaxN = 3005, inf = 0x3f3f3f3f;
vector<int> vertex[kMaxN];
int under[kMaxN];
int nrOfNodes = 0;

int df(string txt, int &poz) {
    int nod = ++nrOfNodes;
    ++poz;
    while (txt[poz] == '(' || txt[poz] == 'B') {
        if (txt[poz] == 'B') {
            under[nod]++;
            ++poz;
        } else {
            int oth = df(txt, poz);
            vertex[nod].push_back(oth);
        }
    }
    ++poz;
    for (auto itr : vertex[nod]) {
        under[nod] += under[itr];
    }
    return nod;
}

vector<int> solve(int nod, vector<int> &require) {
    vector<int> rez;
   if (vertex[nod].size() == 0) {
        for (auto itr : require) {
            int r = 0;
            if (abs(itr) >= 2) {
                r = +inf;
            }
            if (itr == -1 and under[nod] == 0) {
                r = +inf;
            }
            if (itr == +1 and under[nod] == 1) {
                r = +inf;
            }
            rez.push_back(r);
        }
/*    cerr << under[nod] << '\t' << nod << "\n";
    for (auto itr : require) {
        cerr << itr << "@\t";
    }
    cerr << '\n';
    for (auto itr : rez) {
        cerr << itr << "#\t";
    }
    cerr << "\n\n"; */
        
        return rez;
    }

    if (vertex[nod].size() == 1) {
        return solve(vertex[nod][0], require);    
    }

    vector<int> requireA, requireB;
    vector<int> rezA, rezB;
    int a = vertex[nod][0];
    int b = vertex[nod][1];
    for (auto itr : require) {
        int u = under[nod] + itr;
        vector<pair<int, int> > options = {};
        if (u % 2 == 0) {
            options = {{u/2, u/2}};
        } else {
            options = {{u/2 + 1, u/2}, {u/2, u/2 + 1}};
        }
        for (auto o : options) {
            requireA.push_back(o.first - under[a]);
            requireB.push_back(o.second - under[b]);
        }
    }

    sort(requireA.begin(), requireA.end());
    sort(requireB.begin(), requireB.end());
    requireA.resize(unique(requireA.begin(), requireA.end()) - requireA.begin());
    requireB.resize(unique(requireB.begin(), requireB.end()) - requireB.begin());

    rezA = solve(a, requireA);
    rezB = solve(b, requireB);
    assert(rezA.size() == requireA.size());
    assert(rezB.size() == requireB.size());
    unordered_map<int, int> A, B;
    
    for (int i = 0; i < int(rezA.size()); ++i) {
        A[requireA[i]] = rezA[i];
    }
    for (int i = 0; i < int(rezB.size()); ++i) {
        B[requireB[i]] = rezB[i];
    }   

    for (auto itr : require) {
        int u = under[nod] + itr;
        vector<pair<int, int> > options = {};
        if (u % 2 == 0) {
            options = {{u/2, u/2}};
        } else {
            options = {{u/2 + 1, u/2}, {u/2, u/2 + 1}};
        }
        int mn = inf;
        for (auto o : options) {
            mn = min(mn, max(0, o.first - under[a]) + max(0, o.second - under[b])
                + A[o.first - under[a]] 
                + B[o.second - under[b]]);
        }         
        mn -= max(0, itr);
        rez.push_back(mn);
    }
/*    cerr << under[nod] << '\t' << nod << "\n";
    for (auto itr : require) {
        cerr << itr << "@\t";
    }
    cerr << '\n';
    for (auto itr : rez) {
        cerr << itr << "#\t";
    }
    cerr << '\n';
    for (auto itr : vertex[nod]) {
        cerr << itr << "->";
    }
    cerr << '\n';
    cerr << '\n'; */
    return rez;
}

int main() {
    string txt;
    while (cin >> txt) {
        for (int i = 0; i < kMaxN; ++i) {
            vertex[i].clear();
            under[i] = 0;
        }
        nrOfNodes = 0;
        int poz = 0;
        int root = df(txt, poz); 
        vector<int> aux = {0};
        auto rez = solve(root, aux);
        if (rez[0] == inf) {
            cout << "impossible\n";
        } else { 
            cout << rez[0] << '\n';
        }
    }
    return 0;
}
