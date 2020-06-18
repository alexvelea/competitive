#include <iostream>
#include <map>
using namespace std;
int main() {
    int t; cin >> t;
    while (t--) {
        int xa, ya, xb, yb; cin >> xa >> ya >> xb >> yb;
        double r; cin >> r;
        int xd = xb - xa;
        int yd = yb - ya;
        int xc = 0.5 + xa + r * xd;
        int yc = 0.5 + ya + r * yd;

        cout << xc << '\t' << yc << '\n';
    }
/*    
    int n, m; cin >> n >> m;
    map<int, int> viz;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            int x; cin >> x;
            viz[x] = 1;
        }
    }

    viz.erase(0);

    for (auto& itr : viz) {
        cout << itr.first << ' ';
    }
    cout << '\n';
*/    
}

