#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define pb push_back
#define mp make_pair
#define max_n 100005
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

pair<int,int> Aib[max_n],x;
int P[max_n],El[max_n];
vector<int> Unic,Rez;

int n,i,mx,start;

pair<int,int> search( int ind ){
	pair<int,int> Rez;
	for( ; ind; ind-=ind&(-ind) )
		if( Rez.first < Aib[ind].first )
			Rez=Aib[ind];
	return Rez;
}

void update( int x, pair<int,int> val ){
	for( ; x<max_n; x+=x&(-x) )
		if( Aib[x].first<val.first )
			Aib[x]=val;
}

int main(){
	
	freopen("scmax.in","r",stdin);
	freopen("scmax.out","w",stdout);

	scanf("%d", &n);
	for( i=1; i<=n; ++i ){
		scanf("%d", &El[i]);
		Unic.pb(El[i]);
	}
	sort( Unic.begin(), Unic.end() );
	Unic.resize( unique( Unic.begin(), Unic.end() )-Unic.begin() );
	for( i=1; i<=n; ++i ){
		El[i]=lower_bound( Unic.begin(), Unic.end(), El[i] )-Unic.begin()+1;
	}
	for( i=1; i<=n; ++i ){
 		x = search(El[i]-1);
		P[i]=x.second;
		if( x.first+1>mx ){
			mx=x.first+1;
			start=i;
		}
		update( El[i], mp( x.first+1, i ) );
	}
	while( start != 0 ){
		Rez.pb( Unic[ El[start]-1 ] );
		start=P[start];
	}
	printf("%d\n",Rez.size());
	reverse( Rez.begin(), Rez.end() );
	FORIT( it, Rez )
		printf("%d ", *it );
	return 0;
}
