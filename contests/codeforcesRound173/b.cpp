#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define mp make_pair
#define fi first
#define se second
#define th third
#define INF 0x3f3f3f3f

struct trio {
    int first,second,third;
	trio(){
		fi=se=th=0;
	}
	trio( int a, int b, int c ){
		fi=a;
		se=b;
		th=c;
	}
 	int other( int nod ){
		return fi+se-nod;
	}
} ;

int a,b,n,i,sum;

int main(){
 	scanf("%d", &n );
	for( i=1; i<=n; ++i ){
		scanf("%d %d", &a, &b );
		sum+=a;
	}
	i=0;
 	while( sum>=500 ){
		sum-=1000;
		printf("G");
		i++;
	}
	for( i++; i<=n; ++i )
		printf("A");
	return 0;
}
