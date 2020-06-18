#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<int> vertex[1000];

void Check(int n, vector<int> nodes) {
    vector<bool> visited(n, false);
    for (auto node : nodes) {
        for (auto a : vertex[node]) {
            visited[a] = true;
        }
    }

    for (int i = 0; i < n; i += 1) {
        if (visited[i] == false) {
            return;
        }
    }

    for (auto& itr : nodes) {
        cout << itr << ' ';
    }
    cout << '\n';
    exit(0);
}

int main() {
    vector<pair<int, int>> coords;
    int n = 0;
    {
    string s;
    getline(cin, s);    

    stringstream in;
    in << s;

    int id, x, y;
    while (in >> id >> x >> y) {
        cerr << x << ' ' << y << ' ' << id << '\n';
        coords.push_back({x, y});
        n++;
    }
    }
    {
    stringstream in;
    string s2;
    getline(cin, s2);
    in << s2;

    int a, b;
    while (in >> a >> b) {
        vertex[a].push_back(b);
        vertex[b].push_back(a);
        cerr << coords[a].first << ' ' << coords[a].second << ' ' << coords[b].first << ' ' << coords[b].second << '\n';
    }
    }

    for (int a = 0; a < n; a += 1) {
        for (int b = a + 1; b < n; b += 1) {
        for (int c = b + 1; c < n; c += 1) {
        for (int d = c + 1; d < n; d += 1) {
            Check(n, {a, b, c, d});
        }
    }
        }
    }
    return 0;
}
