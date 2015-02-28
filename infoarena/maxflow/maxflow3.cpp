#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>
using namespace std;

#define FORIT(i,v) (vector<int> :: iterator i = v.begin(); i != v.end(); ++i)

const int max_n = 355, INF = 0x3f3f3f3f;
vector<int> vertex[max_n];

int cost[max_n][max_n], cap[max_n][max_n], f[max_n][max_n];

int best[max_n], from[max_n];
bool inq[max_n];
int deq[max_n], dr;

int max_flow, cost_flow;
int source, sink;

void clear_flow() {
	for (int i = 0; i < max_n; ++i) {
		from[i] = 0;
		best[i] = INF;
		inq[i] = false;
	}
}

bool get_flow() {
	clear_flow();
	dr = 0;
	deq[dr] = source;
	inq[source] = true;
	best[source] = 0;
	while (dr >= 0) {
		int ind = rand() % (dr+1);

		int nod = deq[ind];
        inq[nod] = false;
		deq[ind] = deq[dr--];
		for (vector<int> :: iterator it = vertex[nod].begin(); it != vertex[nod].end(); ++it)
			if (cap[nod][*it] - f[nod][*it])
				if (best[nod] + cost[nod][*it] < best[*it]) {
					best[*it] = best[nod] + cost[nod][*it];
					from[*it] = nod;
					if (inq[*it] == false) {
						deq[++dr] = *it;
						inq[*it] = true;
					}
				}
	}
	if (from[sink])
		;
	else
		return false;
	int mn = INF;
	for (int nod = sink; nod != source; nod = from[nod])
		if (mn > cap[from[nod]][nod] - f[from[nod]][nod])
			mn = cap[from[nod]][nod] - f[from[nod]][nod];
 	for (int nod = sink; nod != source; nod = from[nod]) {
 		f[from[nod]][nod] += mn;
		f[nod][from[nod]] -= mn;
	}
	max_flow += mn;
	cost_flow += mn * best[sink];
	return true;
}

int main() {
	
	srand(time(NULL));
    freopen("fmcm.in","r",stdin);
	freopen("fmcm.out","w",stdout);

	int n, m;
	cin >> n >> m >> source >> sink;
	
	for (int i = 0; i < m; ++i) {
		int a, b, c, cs;
		cin >> a >> b >> c >> cs;
		cost[a][b] = cs;
		cost[b][a] = -cs;
		cap[a][b] = c;
		f[a][b] = f[b][a] = 0;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	while (get_flow()) 
		;
	cout << cost_flow << "\n";
	return 0;
}
