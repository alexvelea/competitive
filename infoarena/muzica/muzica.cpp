#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
    
	#define mod 131071
	#define fi first
	#define se second
	int Viz[10005];
	vector< pair<int,int> > T[mod+5];

	long long a,b,c,d,e,f,aux;
	int i,j,x,it;
	int n,m,rez;

int main(){
	freopen ("muzica.in","r",stdin);
	freopen ("muzica.out","w",stdout);
	cin>>n>>m;
	cin>>a>>b>>c>>d>>e;
	for ( i=1; i<=n; i++ ){
    	cin>>aux;
		T[aux&mod].push_back(make_pair(aux,i));
	}                  
	x=a&mod;
    for ( it=0; it<T[x].size(); it++ ){
		if ( T[x][it].fi == a ){
			Viz[ T[x][it].se ] =1;
			rez++;
			it=T[x].size();
		}
	}
	for ( i=2; i<=m; i++ ){
    	x=b&mod;
		for ( it=0; it<T[x].size(); it++ ){
			if ( ( T[x][it].fi == b ) && ( !Viz[ T[x][it].se ] ) ){
				rez++;
				Viz[ T[x][it].se ]=1;
			}
		}
		// trecem mai departe
		aux=(c*b+d*a)%e;
		a=b;
		b=aux;
	}
	cout<<rez;
	return 0;
}
