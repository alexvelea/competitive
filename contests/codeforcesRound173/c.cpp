#include <cstdio>
#include <cstdlib>
#include <cstring>
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
#define max_n 1000005

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
	
	int n,u1,u2,i;
	char a[max_n],b[max_n];
	scanf("%s", &a );
	scanf("%s", &b );
	if( strlen(a) != strlen(b) ){
		printf("NO\n");
		return 0;
	}
	n=strlen(a);
	u1=u2=0;
	for( i=0; i<n; ++i ){
		if( a[i]=='1' )
			u1=1;
		if( b[i]=='1' )
			u2=1;
	}
	if( u1==u2 )
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
