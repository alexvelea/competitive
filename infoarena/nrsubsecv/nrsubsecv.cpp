#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

ifstream in("nrsubsecv.in");
ofstream out("nrsubsecv.out");

const int max_n = 1000005, max_l = 1000005;

int left_bound[max_n], right_bound[max_n];
int el[max_n];
stack<int> st;

int n, m;

long long sum[max_l];
vector< pair<int, long long> > secv, fin;
vector< pair<int, int> > event;

int main() {
	in >> n >> m;
 	for (int i = 1; i <= n; ++i) 
		in >> el[i];
	// make the bounds
 	for (int i = 1; i <= n; ++i) {
		while ((not st.empty()) && el[i] <= el[st.top()]) {
			right_bound[st.top()] = i - st.top();
			st.pop();
		}
		st.push(i);
	}
	while (not st.empty()) {
		right_bound[st.top()] = n - st.top() + 1;
		st.pop();
	}
	for (int i = n; i; --i) {
		while ((not st.empty()) && el[i] < el[st.top()]) {
			left_bound[st.top()] = st.top() - i;
			st.pop();
		}
		st.push(i);
	}
	while (not st.empty()) {
		left_bound[st.top()] = st.top();
		st.pop();
	}
	for (int i = 1; i <= n; ++i)
		sum[el[i]] += 1LL * left_bound[i] * right_bound[i];
	for (int i = 1; i < max_l; ++i)
		sum[i] += sum[i-1];
	for (int i = 1; i <= m; ++i) {
		int x, y;
		in >> x >> y;
		x--;
		long long nr = 0;
		if (x != -1)
			nr -= sum[x];
		nr += sum[y];
		out << nr << "\n";
	}
	return 0;
}
