//Problem divizori2 @ 17-09-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

const int kMaxN = 1e5 + 5;

#define int64 long long

ifstream fin("divizori2.in");
ofstream fout("divizori2.out");

int n;
vector<int> vertex[kMaxN];

int graphColor[kMaxN];

bool viz[kMaxN];
int father[kMaxN];

void color(int nod, int colorId) {
    if (graphColor[nod] != -1) {
        return ;
    }

    graphColor[nod] = colorId;

    for (auto itr : vertex[nod]) {
        if (itr != father[nod]) {
            color(itr, colorId);
        }
    }
}

int colorGraph(int nod, int target) {
    int under = 1;
    viz[nod] = true;
    for (auto itr : vertex[nod]) {
        if (itr != father[nod]) {
            father[itr] = nod;
            under += colorGraph(itr, target);
        }
    }

    if (under == target) {
        under = 0;
        color(nod, graphColor[0]);
        ++graphColor[0];
    }
    viz[nod] = false;
    return under;
}

int dfStack[kMaxN];
int where;

void depthDF(int nod, int depth, tuple<int, int, int> &rez) {
    dfStack[depth] = nod;
    viz[nod] = true;
    
    if (depth > get<0>(rez)) {
        int a = 0, b = 0;
        if (depth % 2 == 1) {
            a = dfStack[(depth + 1) / 2];
            b = 0;
        } else {
            a = dfStack[depth / 2];
            b = dfStack[(depth / 2) + 1];
        }
        where = nod;
        rez = make_tuple(depth, a, b);
    }

    for (auto itr : vertex[nod]) {
        if (graphColor[nod] == graphColor[itr] and not viz[itr]) {
            depthDF(itr, depth + 1, rez);
        }
    }

    viz[nod] = false;
}

pair<int, int>findCenter(int nod) {
    tuple<int, int, int> aux = make_tuple(0, 0, 0);
    int a; depthDF(nod, 1, aux); a = where;
    aux = make_tuple(0, 0, 0);
    depthDF(a, 1, aux);

    int d, _a, _b;
    tie(d, _a, _b) = aux;
    return make_pair(_a, _b);
}

const int hashMod = 666013, hashSigma = 31;

int getHash(int nod) {
    viz[nod] = true;
    vector<int> childHash(0, vertex[nod].size()); childHash.clear();
    for (auto itr : vertex[nod]) {
        if (not viz[itr] and graphColor[itr] == graphColor[nod]) {
            childHash.push_back(getHash(itr));
        }
    }
    
    sort(childHash.begin(), childHash.end());
    
    int rez = 1;
    for (auto itr : childHash) {
        rez *= hashSigma;
        rez += itr;
        rez %= hashMod;
    }
    viz[nod] = false;
    return rez;
}

const int inf = 0x3f3f3f;

bool solve(int div) {
    graphColor[0] = 0;

    for (int i = 1; i <= n; ++i) {
        viz[i] = 0;
        graphColor[i] = -1;
        father[i] = 0;
    }
    
    int x = colorGraph(1, div);
    if (x != 0) {
        return false;
    }

    int nrG = n / div;
    vector<pair<int, int> > graphNodes(nrG, {0, 0});
    
    for (int i = 1; i <= n; ++i) {
        graphNodes[graphColor[i]] = {i, 0};
    }

    int rez = 0;

    for (auto &itr : graphNodes) {
        itr = findCenter(itr.first);
        itr.first = getHash(itr.first);
        if(itr.second) {
            itr.second = getHash(itr.second);
        } else {
            itr.second = +inf;
        }
    }

    rez = min(graphNodes.begin()->first, graphNodes.begin()->second);

    for (auto itr : graphNodes) {
        if (rez != min(itr.first, itr.second)) {
            return false;
        }
    }
    
    return true;
}

int main() {
    fin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b; fin >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }
    
    int rez = 2;
    for (int i = 2; i < n; ++i) {
        if (n % i == 0) {
            rez += solve(i);
        }
    }
    fout << rez << '\n';
	return 0;
}
