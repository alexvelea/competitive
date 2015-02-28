#include <cstdio>

#include <vector>
using namespace std;

#define max_n 100105
#define pb push_back

int i,n;

long long Aib[2][ max_n ];
int L[ max_n ];
vector<long long> Rez;

long long search ( int ind, int p ){
	long long rez=0;
	for ( ; ind; ind-= ( ind & ( -ind ) ) )
		rez += Aib[p][ ind ];
	return rez;
}

void add ( int ind, long long val, int p ){
	for ( ; ind<=n; ind+=(ind&(-ind)) )
		Aib[p][ ind ] += val;
}

int main(){
	freopen ("snpid.in","r",stdin);
	freopen ("snpid.out","w",stdout);
	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf ("%d", &L[ i ]);
	}
	for ( i=n; i; --i ){
		long long nr = search ( n+1-L[i], 0 );
		Rez.pb( nr );
		add( n+1-L[i], search( n+1-L[i], 1 ) , 0 );
		add( n+1-L[i], 1, 1 );
	}
	for ( i=Rez.size()-1; i>=0; --i ){
		printf("%lld\n",Rez[i]);
	}
	return 0;
}
