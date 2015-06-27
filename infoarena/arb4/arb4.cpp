//Problem arb4 @ 27-06-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

ifstream fin("arb4.in");
ofstream fout("arb4.out");
 

#define kMaxChar 1000000
#define verf ((++BufferChar >= kMaxChar) ? (fin.read(Buffer, kMaxChar), BufferChar = 0) : (1))

int BufferChar = kMaxChar;
char Buffer[kMaxChar];

void getInt (int &a) {
    if (BufferChar >= kMaxChar)
        verf;
    bool minus = false;
    for ( ;!((Buffer[BufferChar] >= '0' && Buffer[BufferChar] <= '9') || (Buffer [BufferChar] == '-')); verf)
        ;
    if (Buffer[BufferChar] == '-') {
        verf;
        minus = true;
    }
    for (a = 0; (Buffer[BufferChar] >= '0' && Buffer[BufferChar] <= '9'); a *= 10,a += (Buffer[BufferChar] - '0'), verf)
        ;
    if (minus)
        a *= -1;
    return ;
}


const int kMaxN = 3e5 + 5, kLog = 20;

#define int64 long long


int father[kLog][kMaxN];
int fatherEdge[kMaxN];

pair<int, int> edge[kMaxN];
vector<int> edges[kMaxN];
int rez[kMaxN], cost[kMaxN];

int deep[kMaxN];
bool viz[kMaxN];

int other(int ind, int nod) {
    return edge[ind].first + edge[ind].second - nod;
}

void df(int nod) {
    viz[nod] = true;
    for (auto itr : edges[nod]) {
        int oth = other(itr, nod);
        if (not viz[oth]) {
            deep[oth] = deep[nod] + 1;
            father[0][oth] = nod;
            fatherEdge[oth] = itr;
            df(oth);
        }
    }
}

int lca(int a, int b) {
    if (a == b) {
        return a;
    }
    if (deep[a] < deep[b]) {
        swap(a, b);
    }
    
    for (int p = kLog - 1; p >= 0; --p) {
        if (deep[a] - (1 << p) >= deep[b]) {
            a = father[p][a];
        }
    }
    
    if (a == b) {
        return a;
    }

    for (int p = kLog - 1; p >= 0; --p) {
        if (father[p][a] != father[p][b]) {
            a = father[p][a];
            b = father[p][b];
        }
    }
    return father[0][a];
}

pair<int, int> qEdge[kMaxN];
int qCost[kMaxN];

bool stillGoodUp[kMaxN];
int nextUp[kMaxN];

int goUp(int nod, int minD, int _rez) {
    if (deep[nod] <= minD) {
        return nod;
    }

    if (stillGoodUp[nod] == true) {
        rez[fatherEdge[nod]] = _rez;
        stillGoodUp[nod] = false;
    }
    nextUp[nod] = goUp(nextUp[nod], minD, _rez);
    return nextUp[nod];
}

int main() {
    int n, m; 
//    fin >> n >> m;
    getInt(n); getInt(m);
    m -= n - 1;
    for (int i = 1; i < n; ++i) {
//	    fin >> edge[i].first >> edge[i].second >> cost[i];
        getInt(edge[i].first); getInt(edge[i].second); getInt(cost[i]);
        edges[edge[i].first].push_back(i);
        edges[edge[i].second].push_back(i);
    }

    df(0);
    for (int i = 1; i < n; ++i) {
        stillGoodUp[i] = true;
        nextUp[i] = father[0][i];
    }

    for (int l = 1; l < kLog; ++l) {
        for (int i = 0; i < n; ++i) {
            father[l][i] = father[l - 1][father[l - 1][i]];
        }
    }

    vector<pair<int, int> > events;
    for (int i = 1; i <= m; ++i) {
//        fin >> qEdge[i].first >> qEdge[i].second >> qCost[i];
        getInt(qEdge[i].first); getInt(qEdge[i].second); getInt(qCost[i]);
        events.push_back(make_pair(qCost[i], i));
    }
    sort(events.begin(), events.end());
   
    for (int i = 1; i < n; ++i) {
        rez[i] =  -1 -n + 2;
    }
    
    for (auto itr : events) {
        int ind = itr.second;
        int a = qEdge[ind].first;
        int b = qEdge[ind].second;
        int l = lca(a, b);
        
        int dl = deep[l];
        
        goUp(a, dl, ind);
        goUp(b, dl, ind);
    }
    
    for (int i = 1; i < n; ++i) {
        fout << rez[i] + n - 2 << '\n';
    }
    return 0;
}
