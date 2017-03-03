#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f, kMaxN = 1e6+6;

vector<bool> possible(kMaxN, false);
int oth[kMaxN];

int main() {
    ios_base::sync_with_stdio(false);
    int n, k; cin >> n >> k;
    vector<int> elements;
    for (int i = 1; i <= n; i += 1) {
        cin >> oth[i];
    }

    vector<int> visited(n + 1, false);
    for (int i = 1; i <= n; i += 1) {
        if (visited[i]) {
            continue;
        }

        int dist = 0;
        int node = i;
        do {
            visited[node] = true;
            dist += 1;
            node = oth[node];
        } while (node != i);
        elements.push_back(dist);
    }

    sort(elements.begin(), elements.end());
    reverse(elements.begin(), elements.end());

    int mx = 0, odd = 0;
    for (auto itr : elements) {
        mx += itr - (itr & 1);
        odd += itr & 1;
    }

    mx = min(mx, 2 * k);
    mx += min(odd, k - mx / 2);

    const int bucket_limit = 2000;

    vector<int> inside(bucket_limit, 0);
    while (elements.size() and elements.back() < bucket_limit) {
        inside[elements.back()] += 1;
        elements.pop_back();
    }

    possible[0] = true;

    int mx_pos = 0;

    for (int i = 0; i < bucket_limit; i += 1) {
        int num = inside[i];
        if (not num) {
            continue;
        }

        int sum = 0;
        auto last = possible;
        int diff = num * i;
        for (int start = 0; start < i; start += 1) {
            for (int pos = start; pos <= min(kMaxN - 1, mx_pos + diff); pos += i) {
                if (sum) {
                    possible[pos] = true;
                    mx_pos = max(mx_pos, pos);
                }
                sum += last[pos];
                if (pos - diff >= 0) {
                    sum -= last[pos - diff];
                }
            }
        }
    }

    for (auto itr : elements) {
        for (int i = mx_pos + itr; i - itr >= 0; i -= 1) {
            if (possible[i - itr]) {
                mx_pos = max(mx_pos, i);
                possible[i] = true;
            }
        }       
    }

    int mn;
    if (possible[k]) {
        mn = k;
    } else {
        mn = k + 1;
    }
    cout << mn << ' ' << mx << '\n';


    return 0;
}
