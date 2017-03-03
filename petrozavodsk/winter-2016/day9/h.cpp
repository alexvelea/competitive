#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

const int kMaxN = 1e6, kMod = 1e9+7;

int perm[kMaxN];
int ord[4];

int n;

struct DSU {
    int father[kMaxN];
    int size[kMaxN];
    int num_dsu;
    
    void Reset() {
        for (int i = 0; i < n; i += 1) {
            father[i] = -1;
            size[i] = 0;
        }
        num_dsu = 0;
    }

    void Add(int val) {
        father[val] = val;
        size[val] = 1;
        num_dsu += 1;

        if (val and size[val - 1]) {
            Join(val - 1, val);
        }

        if (val + 1 < n and size[val + 1]) {
            Join(val, val + 1);
        }
    }

    int GetFather(int node) {
        static vector<int> st;
        st.clear();
        while (node != father[node]) {
            st.push_back(node);
            node = father[node];
        }
        for (auto itr : st) {
            father[itr] = node;
        }
        
        return node;
    }

    bool Inside(int v) {
        return size[v] != 0;
    }

    int Size(int v) {
        if (not Inside(v)) {
            return 0;
        }

        return size[GetFather(v)];
    }

    void Join(int a, int b) {
        a = GetFather(a);
        b = GetFather(b);
        if (a == b) {
            return;
        }

        num_dsu -= 1;
        if (size[a] < size[b]) {
            swap(a, b);
        }

        size[a] += size[b];
        father[b] = a;
    }
} dsu;

void Reverse() {
    reverse(perm + 0, perm + n);
    reverse(ord + 0, ord + 4);
}

void Inverse() {
    for (int i = 0; i < n; i += 1) {
        perm[i] = n - perm[i] - 1;
    } 

    for (int i = 0; i < 4; i += 1) {
        ord[i] = 3 - ord[i];
    }
}

vector<pair<int, int>> intervals;
int where[kMaxN];

void ComputeIntervals() {
    intervals.clear();

    for (int i = 0; i < n; i += 1) {
        where[perm[i]] = i;
    }

    int mx = 0;
    int left = where[0], right = where[0];
    auto Add = [&](int val) {
        int old = mx;
        mx = max(mx, val);
        if (mx == old) {
            return;
        }

        while (right - left < mx) {
            int w = where[old + 1];
            for (int l = w; l < left; l += 1) {
                mx = max(mx, perm[l]);
            }               

            for (int r = right + 1; r <= w; r += 1) {
                mx = max(mx, perm[r]);
            }

            right = max(right, w);
            left = min(left, w);
            old += 1;
        }

        intervals.push_back({left, right});
    };

    intervals.push_back({where[0], where[0]});

    for (int i = 0; i < n; i += 1) {
        Add(i);
    }
}

int cv[kMaxN];

int here[kMaxN];
int sum_here[kMaxN];

void ComputePrefix() {
    for (int i = 0; i < n; i += 1) {
        cv[i] = 0;
    }

    ComputeIntervals();

    bool off = false;
    if (ord[0] + ord[1] != 1) {
        // nearby shits
        off = true;
    }

    dsu.Reset();

    if (ord[0] == 0) {
        for (auto itr : intervals) {
            if (itr.first != 0) {
                continue;
            }
            sum_here[itr.second] += 1;
        }

        for (int i = 0; i < n; i += 1) {
            if (i) {
                sum_here[i] += sum_here[i - 1];
            }
        }
    } else {
        for (auto itr : intervals) {
            if (itr.first == 0) {
                continue;
            }
            here[itr.second] += 1;
        }
    }

    map<pair<int, int>, int> intervals_e;
    if (ord[1] == 0 and off) {
        for (auto itr : intervals) {
            intervals_e[itr] = 1;
        }
    }

    for (int i = 0; i < n; i += 1) {
        dsu.Add(perm[i]);

        if (dsu.num_dsu != 1 + off) {
            continue;
        }

        cv[i] = 0;
        if (ord[0] == 0 and off) {
            if (not dsu.Inside(0)) {
                continue;
            }

            int s = dsu.Size(0);
            cv[i] = sum_here[s - 1];
            if (s - 1) {
                cv[i] -= sum_here[s - 2];
            }
        } else if (ord[0] == 0 and not off) {
            if (i) {
                cv[i] = sum_here[i - 1];      
            }
        } else if (ord[1] == 0 and off) {
            if (not dsu.Inside(0)) {
                continue;
            }

            int s = dsu.Size(0);
            cv[i] = intervals_e[{i - s + 1, i}];
        } else {
            if (i) {
                cv[i] = here[i];
            }
        }
    }

    // reset
    for (int i = 0; i < n; i += 1) {
        sum_here[i] = here[i] = 0;
    }
}

void Compute12() {
    dsu.Reset();

    int mn = perm[0];

    unordered_map<int, int> mn_count;

    for (int i = 0; i < n; i += 1) {
        cerr << "[Perm]" << perm[i] << '\n';
        dsu.Add(perm[i]);
        mn = min(mn, perm[i]);
        
        cv[i] = 0;
        if (dsu.num_dsu == 1) {
            if (ord[0] == 1) {
                // need to check for mn
                cv[i] = mn_count[mn];
            } else {
                assert(0);
            }
        }

        mn_count[mn] += dsu.num_dsu == 1;
    }
}

int prefix[kMaxN], sufix[kMaxN];

int Solve0x() {
    ComputePrefix();
    
    for (int i = 0; i < n; i += 1) {
        prefix[i] = cv[i];
    }

    Reverse();
    Inverse();

    ComputePrefix();

    for (int i = 0; i < n; i += 1) {
        sufix[i] = cv[n - i - 1];
    }

    int result = 0;
    for (int i = 0; i + 1 < n; i += 1) {
        result = (result + 1LL * prefix[i] * sufix[i + 1]) % kMod;
    }
    
    return result;
}

int Solve03() {
    ComputePrefix();
    for (int i = 0; i < n; i += 1) {
        prefix[i] = cv[i];
    }   

    Reverse();
    if (ord[0] == 2) {
        Inverse();
    }

    Compute12();

    for (int i = 0; i < n; i += 1) {
        sufix[i] = cv[n - i - 1];
    }

    int result = 0;
    for (int i = 0; i + 1 < n; i += 1) {
        result = (result + 1LL * prefix[i] * sufix[i + 1]) % kMod;
    }

    return result;
}

int Solve() {
    if (ord[0] != 0 and ord[1] != 0) {
        Reverse();
    }

    int result;
    if (ord[0] + ord[1] == 3) {
        result = Solve03();
    } else {
        result = Solve0x();   
    }   
    return result;
}

int main() {
    while (cin >> n) {
        for (int i = 0; i < n; i += 1) {
            cin >> perm[i];
            perm[i] -= 1;
        }

        for (int i = 0; i < 4; i += 1) {
            cin >> ord[i];
            ord[i] -= 1;
        }

        int result = Solve();

        cout << result << '\n';
        
    }
    return 0;
}
