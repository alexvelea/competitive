#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int kMaxN = 1e5 + 5;

ifstream fin("puzzle2.in");
ofstream fout("puzzle2.out");

bool visited[kMaxN];

pair<int, int> dir[] = {{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};

int n, m, solved_cnt;;
vector<int> vertex[kMaxN];

map<pair<int, int>,  int> matrix;
vector<int> sizes[5];
vector<pair<int, int> > where(kMaxN, {-1, -1});

pair<int, int> operator+ (const pair<int, int> &lhs, const pair<int, int> &rhs) {
    pair<int, int> result;
    result.first = lhs.first + rhs.first;
    result.second = lhs.second + rhs.second;
    return result;
}

void SetMatrix(int id, pair<int, int> position) {
//    cerr << "V->\t" << id << '\t' << position.first << '\t' << position.second << '\n';
    solved_cnt += 1;
    matrix[position] = id;
    where[id] = position;
    visited[id] = true;
    for (auto oth : vertex[id]) {
        sz[oth]--;
    }
    return ;
}

bool Check(int id, pair<int, int> position) {
    bool ok = true;
    cerr << id << "???\n";
    for (auto itr : vertex[id]) {
        if (not visited[itr]) {
            continue;
        }
        cerr << "!\n";
    
        int d = abs(position.first - where[itr].first) + abs(position.second - where[itr].second);
        if (d != 1) {
            ok = false;
        }
    }

    for (int d = 0; d < 4; d += 1) {
        pair<int, int> ne = position + dir[d];
        auto itr = matrix.find(ne);
        if (itr == matrix.end()) {
            continue;
        }

        cerr << itr->second << "##\n";

        bool here = false;
        for (auto _ : vertex[id]) {
            cerr << _ << '\n';
            if (_ == itr->second) {
                here = true;
            }
        }
        ok &= here;
    }

    return ok;
}



void Read() {
    fin >> n >> m;
    for (int i = 0; i < m; i += 1) {
        int a, b; fin >> a >> b;
        a--;
        b--;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }

    for (int i = 0; i < n; i += 1) {
        sizes[vertex[i].size()].push_back(i);
    }
}

void Solve() {
    cerr << n << "?\n";
    int start = -1;
    for (int i = 0; i < n and start == -1; i+= 1) {
        if (sz[i] == 1) {
            start = i;
        }
    }   

    for (int i = 0; i < n and start == -1; i+= 1) {
        if (sz[i] == 2) {
            start = i;
        }
    }

    cerr << "!" << start << '\n';

    SetMatrix(start, {0, 0});

    auto do_shit = [&](int node, pair<int, int> pos) {
        int d = 0;
        while (1) {
            cerr << pos.first << '\t' << pos.second << '\n';
            cerr << start << '\n';
            bool found = false;
            // check for neighbours
            pos = pos + dir[d];

            for (auto itr : vertex[node]) {
                if (not Check(itr, pos)) {
                    continue;
                }

                if (not visited[itr] and sz[itr] == 0) {
                    cerr << node << "->" << itr << " 0\n";
                    SetMatrix(itr, pos);
                    found = false;
                    break;
                }

                if (not visited[itr] and sz[itr] == 1) {
                    cerr << node << "->" << itr << " 1\n";
                    SetMatrix(itr, pos);
                    if (n - 1 != m) {
                       d += 1;
                    }
                    d &= 3;
                    found = true;
                    node = itr;
                    break;
                }
            }

            if (not found) {
                break;
            }

            for (auto itr : vertex[node]) {
                if (not Check(itr, pos)) {
                    continue;
                }

                cerr << itr << '\n';
                if (not visited[itr] and sz[itr] == 2) {
                    cerr << node << "->" << itr << " 2\n";
                    SetMatrix(itr, pos);
                    found = true;
                    node = itr;
                    break;               
                }
            }

            if (not found) {
                break;
            }
        }        
    };
    
    do_shit(start, {0, 0}); 
    return ;
}

void Print() {
    int n = 0, m = 0;
    for (auto itr : matrix) {
        n = max(n, itr.first.first);
        m = max(m, itr.first.second);
    }

    fout << n + 1 << ' ' << m + 1<< '\n';
    for (int i = 0; i <= n; i += 1) {
        for (int j = 0; j <= m; j += 1) {
            fout << 1 + matrix[{i, j}] << ' ';
        }
        fout << '\n';
    }
}
int main() {
    Read();
    Solve();
    Print();
}
