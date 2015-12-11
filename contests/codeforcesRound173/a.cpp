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

int main(){
	int i,n,x=0;
	char S[10];
	scanf("%d", &n );
	for( i=1; i<=n; ++i ){
		scanf("%s", &S);
		if( S[0]=='+' || S[1]=='+' )
			x++;
		else
			x--;
	}
	printf("%d", x);
	return 0;
}
