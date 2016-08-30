#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

typedef long long int64;

ifstream fin("comisia.in");
ofstream fout("comisia.out");

const int kMaxN = 2e5 + 5;
const int inf = 0x3f3f3f3f;

int persons[kMaxN];
int64 cost[kMaxN];

int main() {
    int n; fin >> n;
    for (int i = 1; i <= n; i += 1) {
        fin >> persons[i];
    }

    for (int i = 1; i <= n; i += 1) {
        int c; fin >> c;
        cost[i] = cost[i - 1] + c;
    }
    
    int64 f_cost = 1LL * inf * inf;

    for (int i = 1; i <= n; i += 1) {

        int person = pq.top().second;
        int position = i - persons[person] + 1;
        if (position >= 1) {
            f_cost = min(f_cost, cost[i] - cost[position - 1]);
        }
    }

    fout << f_cost << '\n';
    return 0;
}
