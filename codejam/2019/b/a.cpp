#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main() {
    int t; cin >> t;
    for (int T = 1; T <= t; T += 1) {

        int n; cin >> n;
        vector<pair<int, int>> points;
        for (int i = 0; i < n; i += 1) {
            int a, b; cin >> a >> b;
            points.push_back({a, b});
        }

        sort(points.begin(), points.end());
        vector<pair<int, int>> gcds;
        for (int i = 0; i < n; i += 1) {
            for (int j = i + 1; j < n; j += 1) {
                auto a = points[i];
                auto b = points[j];

                if (a.second > b.second) {
                    int A = a.second - b.second;
                    int B = b.first - a.first;
                    int g = __gcd(A, B);

                    A /= g;
                    B /= g;
                    gcds.push_back({A, B});
                }
            }
        }

        sort(gcds.begin(), gcds.end());
        gcds.resize(unique(gcds.begin(), gcds.end()) - gcds.begin());

        cout << "Case #" << T << ": " << gcds.size() + 1;
        cout << "\n";
    }

    return 0;
}
