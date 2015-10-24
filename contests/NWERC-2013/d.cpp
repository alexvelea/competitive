//Problem d @ 03-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

#define int64 long long

unordered_map<string, int64> last, now;
int n;

int el[10];
int R[10];

void bt(int f, int limit) {
    if (f - 1 == limit) {
        string txt = "";
        for (int i = 1; i <= limit; ++i) {
            txt += char(el[i] + '0');
        }
        now[txt] = 1;
        return ;
    }
    for (int v = el[f - 1] + 1; v <= n; ++v) {
        el[f] = v;
        bt(f + 1, limit);
    }
    return ;
}

int C[10];

int main() {
    ios::sync_with_stdio(false);
    int r; 
    while(cin >> r) {
    for (int i = 1; i <= r; ++i) {
        cin >> R[i];
        for (int j = 1; j <= R[i]; ++j) {
            C[j] = i;
        }
    }
    for (int i = 1; i <= 10; ++i) {
        R[i] = C[i];
        if (C[i] != 0) {
            r = i;
        }
    }
    cin >> n;
    now.clear();
    bt(1, R[1]);
    last = now;
    for (int i = 2; i <= r; ++i) {
        now.clear();    
        bt(1, R[i]);
//        cout << last.size() << '\t' << now.size() << '\n';
        for (auto &itr : now) {
            string txt = itr.first;
            int64 rez = 0;
            for (auto itr2 : last) {
                int64 exp = itr2.second;
                string txt2 = itr2.first;
                bool ok = true;
                for (int j = 0; j < int(txt.size()); ++j) {
                    if (txt[j] >= txt2[j]) {
                    } else {
                        ok = false;
                    }
                }
                if (ok) {
                    rez += exp;
                }
            }
            itr.second = rez;
        }
        last = now;
    }
    int64 rez = 0;
    for (auto itr : last) {
        rez += itr.second;
    }
    cout << rez << '\n';
    }
    return 0;
}
