#include <cstdio>
#include <iostream>
using namespace std;

const int max_n = 100005;

int t;
int n;
int El[max_n];
int max_substr;
int NrUnique[max_n], Father[max_n];
int sumUnique;
int LastSeen[max_n];
int Stack[max_n];
int i, dr;

int get_father (int nod) {
	if (nod == Father[nod]) 
		;
	else
		Father[nod] = get_father(Father[nod]);
	return Father[nod];
}

void join (int a, int b) {
	if (NrUnique[a] > NrUnique[b]) {
		Father[a] = b;
		NrUnique[b] += NrUnique[a];
	}else {
		Father[b] = a;
		NrUnique[a] += NrUnique[b];
	}
}

int main() {
	freopen ("unique.in", "r", stdin);
    freopen ("unique.out", "w", stdout);
	scanf ("%d", &t);
	while (t--) {
		scanf ("%d", &n);
		for (i=1; i<=n; ++i)
			scanf ("%d", &El[i]);
		El[n+1] = n+1;
		for (i=1; i<=n+1; ++i) {
			Father[i] = i;
			NrUnique[i] = 1;
			LastSeen[i] = 0;
		}
		dr = 0;
		max_substr = 0;
		for (i=1; i<=n+1; ++i) {
			sumUnique = 0;
			while (dr && El[Stack[dr]] <= El[i]) {
	 			sumUnique += NrUnique[get_father(Stack[dr])];
 				if (sumUnique == El[Stack[dr]] && i - Stack[dr-1] - 1 > max_substr) {
					max_substr = i - Stack[dr-1] - 1;
				}
	 			join (get_father(i), get_father(Stack[dr]));
				--dr;
			}
			Stack[++dr] = i;
 			if (LastSeen[El[i]]) {
				NrUnique[get_father(LastSeen[El[i]])] --;
			}
			LastSeen[El[i]] = i;
		}
		printf ("%d\n", max_substr);
	}
	return 0;
}
