#include <iostream>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f;

deque<int> deq;

bool pos[10000 * 52];
int mn[10000 * 52] = {inf};

int main() {

	int n, d;
	int el[100];
	cin >> n >> d;
	int mx = 0;
 	for (int i = 1; i <= n; ++i)
		cin >> el[i];
	pos[0] = 1;
	mn[0] = 0;
	for (int i = 1; i <= n; ++i) 
		for (int j = mx; j >= 0; --j)
			if (pos[j]) {
				pos[el[i] + j] = true;
				mx = max(el[i] + j, mx);
			}
	deq.push_front(0);
	int a = 0;
	for (int i = 1; i <= mx; ++i) {
		if (not pos[i])
			continue;
		while(deq.size() and deq.front() <= i - d - 1) 
			deq.pop_front();       
		if (deq.size() == 0)
			break;
		mn[i] = mn[deq.front()];
		mn[i] += 1;
		while (deq.size() and mn[i] <= mn[deq.back()])
			deq.pop_back();
		deq.push_back(i);
		a = i;
	}
	cout << a << ' ' << mn[a] << '\n';
	return 0;
}
