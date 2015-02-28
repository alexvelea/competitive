#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

ifstream in("potrivire.in");
ofstream out("potrivire.out");

string a, b;
vector<string> task;

int n, m;

int solve (int beg, string t) {
	char txt[t.size() + 1];
	int P[t.size() + 1];
	
	int n = t.size();
	for (int i = 0; i < int(t.size()); ++i)
		txt[i + 1] = t [i];
	int k = 0;
	P[1] = 0;
	P[0] = 0;
	for (int i = 2; i <= n; ++i) {
		while (k && txt[k + 1] != txt[i])
			k = P[k];
		if (txt[k + 1] == txt[i])
			++k;
		P[i] = k;
	}
	k = 0;
	for (int i = beg; i < int(a.size()); ++i) {
		while (k && k != n && txt[k + 1] != a[i])
			k = P[k];
	   	if (txt[k + 1] == a[i])
			++k;
 		if (k == n)
			return i - n + 1;
	}
	return a.size();
}

int main() {
	in >> n >> m;
	in >> a;
	in >> b;
 	for (int i = 0; i < int(b.size()); ++i) {
		string c = "";
		while (i < int(b.size()) && b[i] != '*') {
			c += b[i];		
			++i;
		}
		if (c == "")
			continue;
		task.push_back(c);	
	}
	int st = 0;
	int x = int(a.size());
	for (int i = 0; i < int(task.size()); ++i) {
		int c = solve (st, task[i]);
		if (c == int(a.size())) {
			out << "-1\n";
			return 0;
		}
 		st = c + int(task[i].size());
		x = min(x, c);
	}
	out << x + 1<< ' ' << st - 1 + 1<< '\n';
	return 0;
}
