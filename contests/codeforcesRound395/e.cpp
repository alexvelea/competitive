#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5;

vector<int> vertex[kMaxN];
vector<int> el_left[kMaxN], el_right[kMaxN];
int num_left[kMaxN], num_right[kMaxN];

int perm[15];
void Normalize(vector<int>& a, int next = 0) {
    for (int i = 0; i < 15; i += 1) {
        perm[i] = 0;
    }

    for (auto itr : a) {
        if (perm[itr] == 0) {
            perm[itr] = ++next;
        }
    }

    for (auto& itr : a) {
        itr = perm[itr];
    }
}

void Left(int node) {
    auto last_nodes = el_left[node - 1];

    vector<int> perm(7, 0);
    for (int i = 0; i <= 6; i += 1) {
        perm[i] = i;
    }

    int start_el = node - last_nodes.size();
    for (auto itr : vertex[node]) {
        if (itr > node) {
            continue;
        }

        perm[last_nodes[itr - start_el]] = 6;
    }

    int num_nodes = num_left[node - 1];
    num_nodes += 1;
    for (int itr = 0; itr < 7; itr += 1) {    
        if (perm[itr] != itr) {
            num_nodes -= 1;
        }
    }

    for (auto& itr : last_nodes) {
        itr = perm[itr];
    }

    num_left[node] = num_nodes;
    last_nodes.push_back(6);
    if (last_nodes.size() == 6) {
        last_nodes.erase(last_nodes.begin());
    }

    Normalize(last_nodes);
    el_left[node] = last_nodes;
}

void Right(int node) {
    auto last_nodes = el_right[node + 1];

    vector<int> perm(7, 0);
    for (int i = 0; i <= 6; i += 1) {
        perm[i] = i;
    }

    int start_el = node - last_nodes.size();
    for (auto itr : vertex[node]) {
        if (itr > node) {
            continue;
        }

        perm[last_nodes[itr - start_el]] = 6;
    }

    int num_nodes = num_right[node + 1];
    num_nodes += 1;
    for (int itr = 0; itr < 7; itr += 1) {    
        if (perm[itr] != itr) {
            num_nodes -= 1;
        }
    }

    for (auto& itr : last_nodes) {
        itr = perm[itr];
    }

    num_right[node] = num_nodes;
    last_nodes.push_back(6);
    if (last_nodes.size() == 6) {
        last_nodes.erase(last_nodes.begin());
    }

    Normalize(last_nodes);
    el_right[node] = last_nodes;  
}

int Query(int start_el, vector<int> el) {
    int last_el = start_el + el.size() - 1;
    int r = 0;
    for (int i = start_el; i <= last_el; i += 1) {
        for (auto itr : vertex[i]) {
            if (not (start_el <= itr and itr <= last_el)) {
                continue;
            }

            if (el[itr - start_el] == 0) {
                continue;
            }

            if (el[i - start_el] == el[itr - start_el]) {
                continue;
            }
            
            // merge this 2
            int v = el[itr - start_el];
            int q = el[i - start_el];
            for (auto& itr : el) {
                if (itr == q) {
                    itr = v;
                }
            }
        }
    }
    return r;
}


int main() {
    ios_base::sync_with_stdio(false);
    int n, k, m; cin >> n >> k >> m;
    for (int i = 0; i < m; i += 1) {
        int a, b; cin >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }

    num_left[1] = 1;
    el_left[1] = {1};
    for (int i = 2; i <= n; i += 1) {
        Left(i);
    }

    num_right[n] = 1;
    el_right[n] = {1};
    for (int i = n - 1; i >= 1; i -= 1) {
        Right(i);
    }

    for (int i = 1; i <= n; i += 1) {
        cout << num_left[i] << '\t' << num_right[i] << '\n';
    }

    int q; cin >> q;
    for (int i = 0; i < q; i += 1) {
        int l, r; cin >> l >> r;
        l += 1;
        r -= 1;
        if (r - l > k) {
            cout << num_left[l - 1] + num_right[r + 1] << '\n';
            continue;
        }
        auto start_el = l - 1 - el_left[l - 1].size() + 1;
        vector<int> perms = el_left[l - 1];
        for (int i = l; i <= r; i += 1) {
            perms.push_back(0);
        }
        auto q = el_right[r + 1];
        Normalize(q, 6);
        for (auto itr : q) {
            perms.push_back(itr);
        }

        cout << num_left[l - 1] + num_right[r + 1] - Query(start_el, perms) << '\n';
    }
    return 0;
}
