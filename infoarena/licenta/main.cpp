#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream fin("licenta.in");
ofstream fout("licenta.out");

int main() {
    int k, aux; fin >> k;
    vector<pair<int, int> > a, b;
    fin >> aux;
    while (aux--) {
        int x, y; fin >> x >> y;
        a.push_back({x, y});
    }
    fin >> aux;
    while (aux--) {
        int x, y; fin >> x >> y;
        b.push_back({x, y});
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    auto intersect_segments = [](pair<int, int> a, pair<int, int> b) {
        return max(0, min(a.second, b.second) - max(a.first, b.first));   
    };

    for (int itrA = 0, itrB = 0; itrA < int(a.size()) and itrB < int(b.size()); ) {
        if (intersect_segments(a[itrA], b[itrB]) >= k) {
            fout << max(a[itrA].first, b[itrB].first) << ' ' << max(a[itrA].first, b[itrB].first) + k << '\n';
            return 0;
        } else if (a[itrA].second < b[itrB].second){
            itrA += 1;
        } else {
            itrB += 1;
        }
    }
    return 0;
}
