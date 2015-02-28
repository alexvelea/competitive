#include <cstdio>

#include <algorithm>
using namespace std;

	#define max_pig 100005

bool Viz[max_pig];

struct animal{
	int cost,color;
} Pig[max_pig];

bool pig_sort ( animal a, animal b ){
	return a.cost > b.cost ;
}

int n,k,i,last_color;

long long rez=0;

int ind1=1,ind2=1;

int main(){

 	freopen ("placute.in","r",stdin);
	freopen ("placute.out","w",stdout);

	scanf ("%d %d", &n, &k );
	for ( i=1; i<=n; ++i ){
		scanf ("%d %d", &(Pig[i].cost), &(Pig[i].color) );
	}
	sort ( Pig+1, Pig+n+1, pig_sort );

	last_color = Pig[1].color-1;
	int ok=1;

	for ( ; ok; ){
		// mergem cu ind1
		for ( ; ( Pig[ind1].color == last_color || Viz[ind1] == 1 ) && ind1<=n ; ind1++ )
			;
		if ( ind1 <= n ){
			rez += Pig[ind1].cost;
			Viz [ind1]=1;
			last_color = Pig[ind1].color;
			swap ( ind1, ind2 );			
		}
		else {
			ok=0;
		}
	}
	printf("%lld\n", rez );
	return 0;
}
