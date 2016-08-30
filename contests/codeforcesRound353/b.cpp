#include <iostream>
using namespace std;

#define int64 long long

const int kMaxN = 1e5+5;
const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int n, a, b, c, d; cin >> n >> a >> b >> c >> d;
    int64 answer = 0;
    for (int i = 1; i <= n; i += 1) {
        int lt = i;
        int rt = b + lt - c;
        int lb = a + lt - d;
        int rb = b + lb - c;
        if (1 <= lt and lt <= n and 1 <= rt and rt <= n and 1 <= lb and lb <= n and 1 <= rb and rb <= n) {
            answer += n;
        }
    }
    cout << answer << '\n';
    return 0;
}
