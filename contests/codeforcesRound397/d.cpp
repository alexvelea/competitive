#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<int> f(n), uniq;
    for (int i = 0; i < n; i += 1) {
        cin >> f[i];
        uniq.push_back(f[i]);
    }
    sort(uniq.begin(), uniq.end());
    uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());

    for (auto itr : uniq) {
        if (f[itr - 1] != itr) {
            cout << "-1\n";
            exit(0);
        }
    }

    vector<int> where(uniq.back() + 1);
    for (int i = 0; i < (int)uniq.size(); i += 1) {
        where[uniq[i]] = i + 1;
    }

    cout << uniq.size() << '\n';
    
    for (auto itr : f) {
        cout << where[itr] << ' ';
    }
    cout << '\n';

    for (auto itr : uniq) {
        cout << itr << ' ';
    } cout << '\n';
    return 0;
}
