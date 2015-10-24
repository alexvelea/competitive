//Problem d @ 15-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

const int kMaxN = 5e4 + 5;

#define int64 long long

int n, m; 
vector<int> badEdges, badNodes;
vector<int> badEdgeNode[kMaxN], matchingEdges[kMaxN];

unordered_map<int, int> has[kMaxN];

bool solved[kMaxN], taken[kMaxN];
bool solvedNode[kMaxN], reallyBad[kMaxN], chainViz[kMaxN], matchingViz[kMaxN];
int availableEdges[kMaxN];
int colorBad[kMaxN], numberBad[kMaxN];

int a[kMaxN], b[kMaxN], cost[kMaxN], color[kMaxN];

int alias[kMaxN], paired[2 * kMaxN];

int other(int itr, int nod) {
    return a[itr] + b[itr] - nod;
}

void badDf(int nod) {
    if (availableEdges[nod] == 1) {
        for (auto itr : badEdgeNode[nod]) {
            if (solved[itr] == false) {
                solved[itr] = true;
                taken[itr] = true;

                solvedNode[a[itr]] = true;
                solvedNode[b[itr]] = true;

                availableEdges[a[itr]]--;
                availableEdges[b[itr]]--;
                badDf(other(itr, nod));
            }
        }
    }

    for (auto itr : badEdgeNode[nod]) {
        if (solved[itr] == false) {
            solved[itr] = true;
            availableEdges[a[itr]]--;
            availableEdges[b[itr]]--;
            if (availableEdges[a[itr]] == 1) {
                badDf(a[itr]);
            }
            if (availableEdges[b[itr]] == 1) {
                badDf(a[itr]);
            }
        }
    }
}

void greedyThisShit() {
    for (auto itr : badNodes) {
        availableEdges[itr] = 0;
    }
    for (auto itr : badEdges) {
        if (solved[itr] == false) {
            availableEdges[a[itr]]++;
            availableEdges[b[itr]]++;
        }
    }

    for (auto itr : badNodes) {
        if (reallyBad[itr] and availableEdges[itr] == 1) {
            badDf(itr);
        }
    }
}

void findMargins(int nod, vector<int> &a) {
    a.push_back(nod);
    chainViz[nod] = true;
    if (not reallyBad[nod]) {
        return ;
    }

    for (auto itr : badEdgeNode[nod]) {
        int oth = other(itr, nod);
        if (not chainViz[oth]) {
            findMargins(oth, a);
        }
    }
    return ;
}

bool findAugPath(int nod) {
    for (auto itr : matching 
}

bool ok(int p) {
    for (auto itr : badNodes) {
        solvedNode[itr] = false;
        chainViz[itr] = false;
    }

    for (auto itr : badEdges) {
        matchingEdges[itr].clear();
        solved[itr] = false;
        taken[itr] = false;
        if (cost[itr] > p) {
            solved[itr] = true;
        }
    }

    greedyThisShit();

    for (auto nod : badNodes) {
        if (solvedNode[nod] == false and reallyBad[nod]) {
            int v = 0;
            for (auto edge : badEdgeNode[nod]) {
                v++;
                v -= solved[edge];
            }
            if (v == 0) { 
                // 1 nu e posibil
                // doar 2 ramane
                return false;
            }
        }
    }
    
    for (int i = 1; i <= n + m; ++i) {
        paired[i] = 0;
    }

    vector<int> matchingNodes;

    for (auto nod : badNodes) {
        if (reallyBad[nod] and solvedNode[nod] == false and chainViz[nod] == false) {
            vector<int> aux = {nod};
            solvedNode[nod] = true;
            chainViz[nod] = true;
            findMargins(other(badEdgeNode[nod][0], nod), aux);
            reverse(aux.begin(), aux.end());
            findMargins(other(badEdgeNode[nod][1], nod), aux);
            if (aux.size() % 2 == 0) {
                for (int i = 1; i + 1 < int(aux.size()); i += 2) {
                    for (auto itr : badEdgeNode[aux[i]]) {
                        int oth = other(itr, aux[i]);
                        solved[itr] = true;
                        if (aux[i + 1] == oth) {
                            taken[itr] = true;
                        }
                    }
                }
            } else {
                matchingEdges[aux[0]].push_back(m + aux[1]);
                matchingEdges[aux[aux.size() - 1]].push_back(m + aux[1]);
                alias[aux[1]] = aux[aux.size() - 2];
                matchingNodes.push_back(aux[0]);
                matchingNodes.push_back(aux[aux.size() - 1]);
            }
        }
    }

    sort(matchingNodes.begin(), matchingNodes.end());
    matchingNodes.resize(unique(matchingNodes.begin(), matchingNodes.end()) - matchingNodes.begin());

    bool ok = true;
    while (ok) {
        ok = false;
        for (auto itr : matchingNodes) {
            matchingViz[itr] = false;
        }
        for (auto itr : matchingNodes) {
            if (not paired[itr]) {
                findAugPath(itr);
            }
        }
    }

    for (auto itr : matchingNodes) {
        if (paired[itr] == false) {
            continue;
        }            
        for (auto edge : badEdgeNode[itr]) {
            for (auto nod : {paired[itr] - m, alias[paired[itr] - m]}) {
                int oth = other(edge, itr);
                if (oth == nod) {
                    solvedNode[itr] = true;
                    solvedNode[oth] = true;
                    taken[edge] = true;
                    solved[edge] = true;
                }
            }
        }
    }

    return false;
}

int main() {
	ios::sync_with_stdio(false);
    cin >> n >> m;
    vector<pair<int, int> > sortedE;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i] >> b[i] >> color[i] >> cost[i];
        for (auto itr : {a[i], b[i]}) {
            has[itr][color[i]]++;
            if (has[itr][color[i]] >= 2) {
                ++numberBad[itr];
                reallyBad[itr] = true;
                colorBad[itr] = color[i];
            }
            if (numberBad[itr] > 1) {
                cout << "No\n";
                return 0;
            }
        }
        sortedE.push_back(make_pair(cost[i], i));
    }
    
    for (int i = 1; i <= m; ++i) {
        badEdges.push_back(i);
        if (colorBad[a[i]] == color[i] || colorBad[b[i]] == color[i]) {
            badNodes.push_back(a[i]);
            badNodes.push_back(b[i]);
            badEdgeNode[a[i]].push_back(i);
            badEdgeNode[b[i]].push_back(i);
        }
    }

    sort(badNodes.begin(), badNodes.end());
    badNodes.resize(unique(badNodes.begin(), badNodes.end()) - badNodes.begin());

    if (not ok(1e9 + 5)) {
        cout << "No\n";
        return 0;
    }

    int rez = -1;

    for (int p = 30; p >= 0; --p) {
        if (not ok(rez + (1 << p))) {
            rez += (1 << p);
        }
    }
    
    cout << rez + 1 << '\n';	
    return 0;
}
