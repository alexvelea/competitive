#include <iostream>
#include <set>
#include <vector>
#include <tuple>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

set<tuple<int, int, int>> Intervals;

int AddNode(int index, int value) {
//    cerr << "!" << (make_tuple(-inf, +inf, 0) < make_tuple(value, -inf, +inf)) << '\n';
    auto itr = Intervals.lower_bound(make_tuple(value, +inf, +inf));
    int parent, left, right;
    itr--;

    tie(left, right, parent) = *itr;
//    cerr << value << '\t' << parent << '\t' << left << '\t' << right << '\n';
    Intervals.erase(itr);

    Intervals.insert(make_tuple(left, value - 1, index));
    Intervals.insert(make_tuple(value + 1, right, index));

    return parent;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    int root; cin >> root;
    Intervals.insert(make_tuple(-inf, +inf, 0));

    AddNode(root, root);
    vector<int> answers;
    for (int i = 2; i <= n; i += 1) {
        int answer = 0;
        int x; cin >> x;
        answer = AddNode(x, x);
        answers.push_back(answer);
    }
    for (auto itr : answers) {
        cout << itr << ' ';
    }
    return 0;
}
