#include <ctime>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define FORIT(it, v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
const int max_n = 1005, x[4] = {0, 0, 1, -1}, y[4] = {1, -1, 0, 0};

int el[max_n][max_n];
bool ok[max_n][max_n];

pair<int, int> father[max_n][max_n];
bool is_active[max_n][max_n];
vector<pair<int, int> > task[max_n];

pair<int, int> get_father(pair<int, int> a) {
	if (a == father[a.first][a.second])
		return a;
	father[a.first][a.second] = get_father(father[a.first][a.second]);
	return father[a.first][a.second];
}

void p_join(pair<int, int> a, pair<int, int> b) {
	a = get_father(a);
	b = get_father(b);
	int x = rand() % 2;
	if (x)
		swap(a, b);
	father[b.first][b.second] = a;
	if (is_active[b.first][b.second])
		is_active[a.first][a.second] = true;
	return ;
}

bool task_sort(pair<int, int> a, pair<int, int> b) {
	return el[a.first][a.second] < el[b.first][b.second];
}
int main() {
	srand(time(NULL));
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			cin >> el[i][j];
			if (el[i][j] > 0)
				ok[i][j] = true;
			else
				el[i][j] *= -1;
			task[el[i][j]].push_back(make_pair(i, j));
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			father[i][j] = make_pair(i, j);
	int rez = 0;
	for (int l = 0; l < max_n; ++l) {
		FORIT(it, task[l])
			for (int d = 0; d < 4; ++d) {
				int nx = x[d] + it->first;
				int ny = y[d] + it->second;
				int x = it->first;
				int y = it->second;

				if (nx < 1 || nx > n)
					continue;
				if (ny < 1 || ny > m)
					continue;
				if (el[nx][ny] > el[x][y])
					continue;
				p_join(*it, make_pair(nx, ny));
			}
		FORIT(it, task[l])
			if (ok[it->first][it->second]){
		 	   pair<int, int> f = get_father(*it);
				if (is_active[f.first][f.second])
					;
				else {
					is_active[f.first][f.second] ++;
					rez ++;
				}
			}
	}
	cout << rez << '\n';
	return 0;
}

