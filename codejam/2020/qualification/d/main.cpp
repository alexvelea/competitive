#include <iostream>
using namespace std;

int n;
int els[105];

int num_queries = 0;
int Query(int pos) {
    num_queries += 1;
    cout << pos << endl;
    int x; cin >> x;
    return x;
}

void Fake() {
    Query(1);
}

void Answer() {
    cerr << num_queries << '\t';
    cerr << "! ";
    for (int i = 1; i <= n; i += 1) {
        cout << els[i];
        cerr << els[i];
    } cout << endl;
    char ans; cin >> ans;
    cerr << " " << ans << '\n';
    if (ans == 'N') {
        exit(0);
    }
}

int Oth(int x) { return n - x + 1; };

void FixPairs(int pair_id) {
    int x = Query(pair_id);
    if (els[pair_id] == x) { return; }
    for (int i = 1; i <= n; i += 1) {
        if (els[i] != 2) { els[i] ^= 1; }
    }
}

void FixDiff(int diff_id) {
    int x = Query(diff_id);
    if (els[diff_id] == x) { return; }
    for (int i = 1; i < Oth(i); i += 1) {
        swap(els[i], els[Oth(i)]);
    }
}

bool Ok() {
    bool ok = true;
    for (int i = 1; i <= n; i += 1) {
        ok &= (els[i] != 2);
    }
    return ok;
}

int main() {
    int t; cin >> t;
    cin >> n;
    while (t--) {
        for (int i = 1; i <= n; i += 1) { els[i] = 2; }
        num_queries = 0;
        int pair_id = 0;
        int diff_id = 0;

        int index = 1;
        while (1) {
            if (pair_id) { FixPairs(pair_id); } else { Fake(); }
            if (diff_id) { FixDiff(diff_id); } else { Fake(); }
            if (Ok()) { Answer(); break; }
            for (int i = 1; i <= 4; i += 1) {
                if (index > Oth(index)) { break; }
                els[index] = Query(index);
                els[Oth(index)] = Query(Oth(index));
                if (els[index] == els[Oth(index)]) {
                    pair_id = index;
                } else {
                    diff_id = index;
                }

                index += 1;
            }
        }
    }
}

