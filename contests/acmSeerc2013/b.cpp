#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 500005;

map<int, bool> edge[kMaxN];
int best[kMaxN];
vector<int> remaining;
queue<int> q;

void make_clear() {
	for (int i = 0; i < kMaxN; ++i) {
		edge[i].clear();
		best[i] = 0;
	}
	remaining.clear();
	while (q.size())
		q.pop();
}

long long min(long long a, int b) {
	if (a < b)
		return a;
	return 1LL * b;
}

int main() {
	int n = 0, k = 0, a = 0, b = 0;
    while (cin >> n){
        cin >> k >> a >> b;
        for (int i = 1; i <= k; ++i) {
            int a, b;
            cin >> a >> b;
            edge[a][b] = true;
            edge[b][a] = true;
        }

        q.push(1);
		long long rez;
        if (a <= b) {
			best[1] = 1;
        	// simple bfs from 1 to n
			while (q.size()) {
				int nod = q.front();
				q.pop();
				for (map<int, bool> :: iterator itr = edge[nod].begin(); itr != edge[nod].end(); ++itr) {
					int oth = itr->first;
					if (best[oth] == 0) {
						best[oth] = 1 + best[nod];
						q.push(oth);
					}
				}
			}
			
			if (best[n] == 0)
				rez = b;
			else
				rez = min(1LL * (best[n] - 1) * a, b);
		} else {
			best[1] = 1;
			for (int i = 2; i <= n; ++i)
				remaining.push_back(i);

			// another BFS
			// this time from all nodes we will iterate over all unvisited nodes
			// if edge[nod][oth] == true we don't have an edge of cost b between them
			// this could only occur m times
			// hence O(n + m)

			while (q.size()) {
				int nod = q.front();
				q.pop();
				for (int i = 0; i < int(remaining.size()); ++i) {
					int oth = remaining[i];
					if (best[oth] == 0 and edge[nod][oth] == 0) {
						best[oth] = best[nod] + 1;
						swap(remaining[i], remaining.back());
						remaining.pop_back();
						q.push(oth);
						--i;
					}
				}
			}
			if (best[n] == 0)
				rez = a;
			else
				rez = min(1LL * (best[n] - 1) * b, a);
		}
		cout << rez;
        make_clear();
    }
	return 0;
}
