#include <iostream>
using namespace std;

const int kMaxN = 1e5+5;

int father[kMaxN];
int target_father[kMaxN];

int is_leaf[kMaxN], should_be_leaf[kMaxN];

int main() {
    int n; cin >> n;
    int cost = 0;

    for (int i = 1; i <= n; i += 1) {
        is_leaf[i] = true;
        should_be_leaf[i] = true;
    }

    for (int i = 1; i <= n; i += 1) {
        cin >> father[i];
        is_leaf[father[i]] = false;
        cost += (father[i] != 0);
    }
    
    int target_num_fathers = 0;
    for (int i = 1; i <= n; i += 1) {
        cin >> target_father[i];
        should_be_leaf[target_father[i]] = false;
        target_num_fathers += (target_father[i] != 0);
    }

    int kept = 0;
    for (int i = 1; i <= n; i += 1) {
        if (should_be_leaf[i] and is_leaf[i]) {
            // chain is ok from leaf. check every father
            int node = i;
            while (father[node] != 0) {
                if (father[node] != target_father[node]) {
                    break;
                }
                cost -= 1;
                node = father[node];
                kept += 1;
            }
        }
    }
    
    cost += (target_num_fathers - kept);
    cout << cost << '\n';
}
