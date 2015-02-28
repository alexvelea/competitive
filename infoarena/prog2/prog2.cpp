#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 2005;

int el[kMaxN];

ifstream in("progr2.in");
ofstream out("progr2.out");

vector<pair<int, int> > nr;
int last_sum[kMaxN], sol[kMaxN];

bool mysort(pair<int, int> a, pair<int, int> b) {
	if (el[a.second] - el[a.first] == el[b.second] - el[b.first])
		return a.first < b.first;
	return (el[a.second] - el[a.first] < el[b.second] - el[b.first]); 
}


#define MaxChar 1000000
#define verf ( (++CharB >= MaxChar) ? (in.read(Buffer, MaxChar), CharB = 0) : (1))

long CharB = MaxChar;
char Buffer[MaxChar];

void cit (int &a) {
	if (CharB >= MaxChar)
		verf;
    bool ok=0;
    for ( ; !((Buffer[CharB] >= '0' && Buffer[CharB] <= '9') || (Buffer [CharB] == '-')); verf)
        ;
    if (Buffer[CharB] == '-') {
        verf;
        ok=1;
    }
    for (a = 0; (Buffer[CharB] >= '0' && Buffer[CharB] <= '9'); a *= 10,a += (Buffer[CharB] - '0'), verf)
        ;
    if (ok) {
        a=-a;
    }
}

int main() {
	int t;
    cit(t);
	while (t--) {
		int n;
        cit(n);
		for (int i = 1; i <= n; ++i)
            cit(el[i]);
		nr.clear();
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				nr.push_back(make_pair(i, j));
		sort(nr.begin(), nr.end(), mysort);
		int N = nr.size();
		int rez = 0;
		for (int st = 0; st < N; ){
			int dr = st;
			while (dr < N and el[nr[st].second] - el[nr[st].first] == el[nr[dr].second] - el[nr[dr].first])
				++dr;
			for (; st < dr; ++st) {
				if (last_sum[nr[st].first] == el[nr[st].second] - el[nr[st].first]) {
					sol[nr[st].second] = sol[nr[st].first] + 1;
					last_sum[nr[st].second] = el[nr[st].second] - el[nr[st].first];
					rez += sol[nr[st].second];
				} else {
					rez ++;
					sol[nr[st].second] = 1;
					last_sum[nr[st].second] = el[nr[st].second] - el[nr[st].first];
 				}
			}
		}
		out << rez << '\n';
   	} 
	return 0;
}
