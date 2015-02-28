#include <cassert>
#include <cstdio>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

	#define max_n 1010
	#define FORIT( it, v ) for ( typeof((v).begin()) it=(v).begin(); it!= (v).end(); ++it )

vector<int> Normal;
int i,j,n,m,a,b,c;
int Down[ max_n ][ max_n ];
int AIB[ max_n ];

int maxim ( int a, int b ){
	if ( a > b )
		return a;
	return b;
}

struct point {
	int ind,x,y;
	point ( int a, int b, int c ){
		x=a;
		y=b;
		ind=c;
	}
	point (){
		x=y=ind=0;
	}
} Points[ max_n ];
vector <point> Link[ max_n ];

bool mysort ( point a, point b ){
//	return atan2 ( a.y, a.x ) < atan2 ( b.y, b.x );
	if ( ( a.y > 0 ) != ( b.y > 0 ) )
		return a.y < b.y;
	return 1LL*a.y*b.x < 1LL*b.y*a.x;
}

void add ( int ind, int val ){
	for ( ; ind<max_n; ind+=( (ind)&(-ind) ))
		AIB[ ind ] += val;
}
int query ( int ind ){
	int rez=0;
	for ( ; ind; ind-= ( (ind)&(-ind) ) )
		rez += AIB[ ind ];
	return rez;
}

int main(){
    freopen ("tri2.in","r",stdin);
 	freopen ("tri2.out","w",stdout);

	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf ("%d %d", &Points[ i ].x, &Points[ i ].y );
		Points[ i ].ind = i;
	}
	
   
	for ( i=1; i<=n; ++i ){
		for ( j=i+1; j<=n; ++j ){
			if ( Points[ i ].x < Points[ j ].x ){
				Link[ i ].push_back ( point ( Points[ j ].x - Points[ i ].x , Points[ j ].y - Points[ i ].y , Points[ j ].ind ) );
			}
			else{
				Link[ j ].push_back ( point ( Points[ i ].x - Points[ j ].x , Points[ i ].y - Points[ j ].y , Points[ i ].ind ) );
			}
		}
	}
	for ( i=1; i<=n; ++i ){
		sort ( Link[i].begin(), Link[i].end(), mysort );
	}
	for ( i=1; i<=n; ++i ){
 		Normal.clear();
		FORIT ( it, Link[i] ){
			Normal.push_back ( it->x );
		}

		sort ( Normal.begin(), Normal.end() );
		Normal.resize ( unique ( Normal.begin(), Normal.end() ) - Normal.begin() ); 

		FORIT ( it, Link[i] ){
    		it->x = lower_bound( Normal.begin(), Normal.end(), it->x ) - Normal.begin() +1;
		}

		FORIT( it, Link[i] ){
        	int rez = query ( it -> x );
			add ( it -> x, 1 );     
			Down[ i ][ it-> ind ] = rez;
			Down[ it-> ind ][ i ] = rez; 
		}
		FORIT ( it, Link[i] ){
			add ( it ->x, -1 );
		}
	}
/*	printf("\n\n\n\n");
	for ( i=0; i<=n; ++i ){
		printf("%d\t",i);
		for ( j=1; j<=n; ++j ){
			if ( i == 0 )
				printf("%d\t",j);
			else
				printf("%d\t",Down[i][j]);
		}
		printf("\n\n");
	}*/
	scanf ("%d", &m );
	for ( ; m; --m ){
		scanf ("%d %d %d", &a, &b, &c );
		int q,w,e;
 		q=a;
		if ( Points[ b ].x < Points[ q ].x )
			q=b;
		if ( Points[ c ].x < Points[ q ].x )
			q=c; 
		e=a;
		if ( Points[ b ].x > Points[ e ].x )
			e=b;
		if ( Points[ c ].x > Points[ e ].x )
			e=c;
		w = a+b+c-q-e;
		if ( Down[q][e] > Down[q][w]+Down[w][e] )
			printf("%d\n",Down[q][e]-Down[q][w]-Down[w][e]-1);
		else
			printf("%d\n",Down[q][w]+Down[w][e]-Down[q][e] );
	}

    return 0;
}
