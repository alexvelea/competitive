#include <climits>
#include <cstdio>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

	#define pb push_back
	#define fi first
	#define se second
	#define max_n 100005

int Color[ max_n ], Val[ max_n ], Last[ max_n ];
long long Best[ max_n ], BestColor[ max_n ];

int n,i,q;
int a,b;

pair<long long, long long> max1,max2;


struct edge {
    int a,b,c;
} ;


long long max ( long long a, long long b ){
	if ( a > b )
		return a;
	return b;
}

int main(){
	cin>>n>>q;
	for ( i=1; i<=n; ++i ){
		cin>>Val[ i ];
	}
	Color[ 0 ] = -1;
	for ( i=1; i<=n; ++i ){
		cin>>Color[ i ];
	}
	for ( i=1; i<=n; ++i ){
		if ( Best[ Color[ i ] ] ){
			Last[ i ] = 1;
		}
		Best[ Color[ i ] ] = 1;
	}
	for ( ; q; --q ){
		cin>>a>>b;

		max1.fi=max2.fi=0;
		max1.se=max2.se=-1;
 		for ( i=1; i<=n; ++i )
			Best[ i ] = BestColor[ i ] = -1LL*LONG_MAX*LONG_MAX;

        for ( i=1; i<=n; ++i ){
			long long act,other;

           	other = 1LL*b*Val[ i ];
			if ( max1.se == Color[ i ] ){
            	other = 1LL*(1LL*other + 1LL*max2.fi);
			}
			else{
				other = 1LL*(1LL*other + 1LL*max1.fi);
			}
 			if ( Last[ i ] ){
				act = 1LL*(1LL*a*Val[ i ] + 1LL*BestColor[ Color[ i ] ]);
			}
			else
				act=other;    		
			Best[ i ] = max ( act, other );
			
			BestColor[ Color[ i ] ] = max ( Best[ i ], BestColor[ Color[ i ] ] );
			
			if ( Best[ i ] >= max1.fi ){
				if ( Color[ i ] == max1.se ){
                    max1.fi = Best[ i ];
				}
				else{
					max2=max1;
					max1.fi = Best[ i ];
					max1.se = Color[ i ];
				}
			}   
			else{
                if ( Best[ i ] >= max2.fi ){
					if ( Color[ i ] == max1.se )
						;
					else{
						max2.fi = Best[ i ];
						max2.se = Color[ i ];
					}
				}
			}
 	   	}
   		cout<<max1.fi<<"\n";
   }
	return 0;
}
