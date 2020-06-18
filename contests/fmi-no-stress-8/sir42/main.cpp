#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 255;

int go_right[kMaxN];
int els[kMaxN];

string Solve(int n, int k) {
    bool got_sth = false;
    for (int i = 1; i <= n; i += 1) {
        if (go_right[i] != -1) {
            go_right[i] += 1;
        }
        got_sth |= go_right[i] != -1;
    }

    if (got_sth == false) {
        return string(n, '0');
    }

    go_right[0] = -1;
    go_right[n + 1] = -1;

    for (int i = 1; i <= n; i += 1) {
        els[i] = 2;
    }

    for (int i = n + 1; i >= 2; i -= 1) {
        if (go_right[i - 1] == -1) {
            continue;
        }

        if (go_right[i] == go_right[i - 1]) {
            els[i - 1] = 0;
        } else {
            els[i - 1] = 1;
        }
    }

    for (int i = 1; i <= n; i += 1) {
        if (go_right[i] != -1) {
            els[go_right[i]] = 1;
            if (go_right[i - 1] != -1) {
                for (int j = go_right[i - 1] + 1; j < go_right[i]; j += 1) {
                    els[j] = 0;
                }
            }
        }
    }

    int pos = 0;
    for (int i = 1; i <= n; i += 1) {
        if (go_right[i] != -1) {
            pos = i;
        }
    }

    int num = 0;
    for (int i = pos; i <= go_right[pos]; i += 1) {
        num += els[i] == 1;
    }

    for (int i = 1, itr = go_right[pos]; i + num <= k; i += 1) {
        while (els[itr] != 2) {
            itr -= 1;
        }

        els[itr] = 1;
    }

    for (int i = 1; i <= n; i += 1) {
        if (els[i] == 2) {
            els[i] = 0;
        }
    }

    string s;
    for (int i = 1; i <= n; i += 1) {
        s += '0' + els[i];
    }
    return s;
}

vector<int> GenerateArr(string s, int k) {
    vector<int> ans(s.size(), -1);
    for (int i = 0; i < (int)s.size(); i += 1) {
        int cnt = 0;
        for (int j = i; cnt != k and j < (int)s.size(); j += 1) {
            ans[i] = j;
            cnt += s[j] == '1';
        }

        if (cnt != k) {
            ans[i] = -1;
        }
    }

    return ans;
}

int main() {
    while (false) {
        int n = rand() % 10 + 5;
        int k = rand() % n + 1;
        string s(n, '0');

        for (int i = 0; i < n; i += 1) {
            s[i] = rand() % 2 + '0';
        }

        auto correct = GenerateArr(s, k);
        for (int i = 1; i <= n; i += 1) {
            go_right[i] = correct[i - 1];
        }
        auto S = Solve(n, k);
        auto given = GenerateArr(S, k);
        if (correct != given) {
            cerr << "~~~~~\n";
            for (auto& itr : correct) { cerr << itr << ' '; } cerr << '\n';
            for (auto& itr : given) { cerr << itr << ' '; } cerr << '\n';
            cerr << k << '\t' << s << '\t' << S << '\n';
            return 0;
        }
        cerr << "Ok!\n";
    }

    ifstream cin("sir42.in");
    ofstream cout("sir42.out");

    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; i += 1) {
        cin >> go_right[i];
    }

    cout << Solve(n, k) << '\n';

}
