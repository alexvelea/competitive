#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
 
#define max_n 10005
#define pb push_back
 
bool Viz[max_n];
int St[max_n],Dr[max_n];
vector<int> Left[max_n];
 
int n,m,e, rez;
 
bool cuplaj( int nod ){
    if( Viz[nod] )
        return 0;
    Viz[nod]=1;
	for (int it : Left[nod]) {
        if( !Dr[it] || cuplaj( Dr[it] ) ){
            St[nod]=it;
            Dr[it]=nod;
            return 1;
        }
    }
    return 0;
}

int a[max_n], b[max_n];
 
int main(){
    cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
    }
	cin >> m;
	for (int i =1 ; i <= m; ++i) {
		cin >> b[i];
	}

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) 
			if (abs(a[i] - b[j]) <= 1) {
				Left[i].push_back(j);
			}
    bool ok = 1;
    Viz[0]=1;
    while (ok) {
        ok = 0;
        for (int i=1; i<=n; ++i)
            if (St[i] == 0 && Viz[i] == 0)
                if (cuplaj(i)) {
					rez++;
                    ok=1;
				}
        for( int i=1; i<=n; ++i )
            Viz[i]=0;
    }
    cout << rez << '\n';
	return 0;
}
