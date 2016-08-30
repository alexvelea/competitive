#include <vector>

#include "messy.h"
#include <vector>
#include <map>
#include <iostream>
using namespace std;

const int kMaxN = 130;

vector<int> elements[7 * kMaxN];
pair<int, int> limits[7 * kMaxN];

int under[7 * kMaxN];
int parent[7 * kMaxN];

int cnt_segs = 0;

map<pair<int, int>, int> who;

void Init(int n) {
    for (int p = n - 1; p >= 0; p -= 1) {
        for (int start = 0; start < (1 << n); start += (1 << p)) {
            limits[cnt_segs] = {start, start + (1 << p)};
            who[{start, start + (1 << p)}] = cnt_segs;

            if (cnt_segs >= 2) {
                int a = start, b = (1 << (n - 1));
                if (start >= (1 << (n - 1))) {
                    b = 0;
                }

                under[cnt_segs] = who[{a, a + (1 << (p + 1))}];               
                parent[cnt_segs] = who[{b, b + (1 << (p + 1))}];
            }

            cnt_segs += 1;
        }
    }
    
    parent[0] = cnt_segs;
    parent[1] = cnt_segs;
    under[0] = cnt_segs + 1;
    under[1] = cnt_segs + 1;
    for (int i = 0; i < (1 << n); i += 1) {
        elements[cnt_segs + 1].push_back(i);
    }
}

void Add(int n) {
    string blank((1 << n), '0');
    for (int i = 0; i < cnt_segs; i += 2) {
        string add = blank;

        auto parent_limit = limits[parent[i]];
        for (int i = parent_limit.first; i < parent_limit.second; i += 1) {
            add[i] = '1';
        }

        auto limit = limits[i];
        for (int i = limit.first; i < limit.second; i += 1) {
            add[i] = '1';
//            fprintf(stderr, "Add:%s\n", add.c_str());
            add_element(add);
            add[i] = '0';
        }
    }
}

vector<int> Reconstruct(int n) {
    vector<int> result((1 << n));
    for (int i = 0; i < (1 << n); i += 1) {
        result[i] = elements[who[{i, i + 1}]][0];
    }
    
    vector<int> reversed((1 << n), 0);
    for (int i = 0; i < (1 << n); i += 1) {
        reversed[result[i]] = i;
    }

    return reversed;
}

vector<int> Guess(int n) {
    string blank((1 << n), '0');
    for (int i = 0; i < cnt_segs; i += 2) {
        string add = blank;
        for (auto itr : elements[parent[i]]) {
            add[itr] = '1';
        }

        for (auto itr : elements[under[i]]) {
            add[itr] = '1';
            if (check_element(add)) {
                elements[i].push_back(itr);
            } else {
                elements[i + 1].push_back(itr);
            }
            add[itr] = '0';
        }
    } 
/*
    for (int i = 0; i < cnt_segs; i += 1) {
        fprintf(stderr, "Paren:%d\tUnder:%d\n", parent[i], under[i]);
        cerr << i << '\t';
        for (auto itr : elements[i]) {
            cerr << itr << ' ';
        }
        cerr << '\n';
    }

    cerr << "DONE GUESS\n";
*/
    return Reconstruct(n);
}

vector<int> restore_permutation(int n, int w, int r) {
    w += 1;
    r += 1;

    for (int i = 0; i < n; i += 1) {
        if ((1 << i) == n) {
            n = i;
            break;
        }
    }

//    cerr << "START\n";
    Init(n);
//    cerr << "DONE INIT\n";
    Add(n);
//    cerr << "DONE ADD\n";
    compile_set();
    return Guess(n);
}
