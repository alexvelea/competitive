#include <cstdio>
#include <vector>
using namespace std;

const int max_n = 100005;

vector<int> vertex[max_n];

bool viz[max_n];
int val[max_n], val_size;
int stack[max_n], stack_size;

int n, m, a, b;
int i;

void df_inside (int nod) {
	if (val[nod])
		return;
	viz[nod] = true;
	val[nod] = ++val_size;
	for (int it=0; it<int(vertex[nod].size()); ++it)
		df_inside (vertex[nod][it]);
}

void make_comp (int nod) {
	if (viz[nod])
		return;
	viz[nod] = true;
	for (int it=0; it<int(vertex[nod].size()); ++it)
		make_comp (vertex[nod][it]);
	stack[++stack_size] = nod;
}

int main() {
	freopen ("zapada.in", "r", stdin);
	freopen ("zapada.out", "w", stdout);
	scanf ("%d %d", &n, &m);
	for (i=1; i<=m; ++i) {
		scanf("%d %d", &a, &b);
 		vertex[b].push_back(a);
	}
	for (i=1; i<=n; ++i)
		make_comp (i);
	df_inside (stack[stack_size]);
	for (i=1; i<=n; ++i) {
		printf ("%d\n", val[i]);
	}
	return 0;
}
