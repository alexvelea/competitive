#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

const int kMaxN = 1e5+5;
const int inf = 0x3f3f3f3f;
pair<int, int> aint[4 * kMaxN];

pair<int, int> AintQuery(int nod, int left, int right, int c0, int c1) {
    if (right < c0) {
        return {-inf, -inf};
    }
    if (c1 < left) {
        return {-inf, -inf};
    }

    if (left <= c0 and c1 <= right) {
        return aint[nod];
    }

    int mid = (c0 + c1) / 2;
    return max(AintQuery(2 * nod, left, right, c0, mid), AintQuery(2 * nod + 1, left, right, mid + 1, c1));
}

void AintUpdate(int nod, int pos, pair<int, int> value, int c0, int c1) {
    if (c0 == c1) {
        aint[nod] = value;
        return ;
    }

    int mid = (c0 + c1) / 2;
    if (pos <= mid) {
        AintUpdate(2 * nod, pos, value, c0, mid);
    } else {
        AintUpdate(2 * nod + 1, pos, value, mid + 1, c1);
    }

    aint[nod] = max(aint[2 * nod], aint[2 * nod + 1]);
    return ;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<int> a(n, 0);
    for (int i = 0; i + 1 < n; i += 1) {
        cin >> a[i]; 
        a[i] -= 1;
    }
    a[n - 1] = n;

    vector<int64> sum(n, 0);
    for (int i = n - 1; i >= 0; i -= 1) {
        if (i + 1 != n) {
            auto mx = AintQuery(1, 0, min(n - 1, a[i]), 0, n - 1); 
            int pos = mx.second;
            int right = min(n - 1, a[i]);
            
//            cerr << i << '\t' << right << '\t' << pos << '\n';
//            cerr << sum[pos] << '\t' << (n - pos) << '\t' << (right - pos + 1) << '\t' << (right - i) << '\n';
//            cerr << '\n';
            sum[i] += sum[pos] + (n - pos - 1) - 2 * (right - pos) + (right - i);
        }
        AintUpdate(1, i, {a[i], i}, 0, n - 1);
    }

    int64 answer = 0;
    for (int i = 0; i < n; i += 1) {
//        cerr << sum[i] << '\t';
        answer += sum[i];
    }
    cout << answer << '\n';
    return 0;
}
