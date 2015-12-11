#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

	#define INF 0x3f3f3f3f

	int T[ 205 ][ 205 ];
	pair< int,int > Max1[ 205 ], Max2[ 205 ];
	int n,m;
	int i,j,k;
	int a,b,c;
	vector< pair<int,int> > Inc,Time;
	vector< pair<int,int> > V[ 205 ];
	bool Viz[ 205 ];
	int rez=0x3f3f3f3f;

bool sort_desc ( pair<int,int> a , pair<int,int> b ){
	return a.first > b.first;
}

bool sort_cresc ( pair<int,int> a, pair<int,int> b ){
	return a.first < b.first;
}

int main(){

    scanf ("%d %d", &n, &m );
	for ( i=1; i<=n; ++i ){
		for ( j=1; j<=n; ++j )
			T[ i ][ j ] =INF;
	}
	for ( i=1; i<=n; ++i ){
		T[ i ][ i ] = 0;
	}
	for ( i=1; i<=m; ++i ){
		scanf ("%d %d %d", &a, &b, &c );
		c*=2;
		V[ a ]. push_back ( make_pair ( b, c ) );
		V[ b ]. push_back ( make_pair ( a, c ) );
		T[ a ][ b ] = c;
		T[ b ][ a ] = c;
	}
	for ( k=1; k<=n; ++k ){
		for ( i=1; i<=n; ++i ){
			for ( j=1; j<=n; ++j ){
				if ( T[ i ][ j ] > T[ i ][ k ] + T[ k ][ j ] ){
					T[ i ][ j ] = T[ i ][ k ] + T[ k ][ j ];
				}
			}
		}
	}
/*	for ( i=1; i<=n; ++i,printf("\n") )
		for ( j=1; j<=n; ++j ){
			printf("%d ", T[i][j] );
		}*/
	for ( int nod=1; nod<=n; nod++ ){
		Inc.clear();
		for ( i=1; i<=n; ++i ){
			Inc.push_back ( make_pair ( T[ nod ][ i ] , i ) );
		}
		sort ( Inc.begin(), Inc.end(), sort_desc );

/*		printf("\t-%d\n",nod);
		for ( i=0; i<n; ++i ){
			printf("\t\t%d\t%d\n",Inc[ i ].first, Inc[ i ].second );
		}
		printf("\n\n");*/

		for ( int it=0; it< int(V[ nod ].size()); ++it ){
			pair<int,int> edge = V[ nod ][ it ];
			int nod2 = edge.first;
			int cost = edge.second;
        	int IncC = 0;
			
			// facem diferentele intre T[ nod ][ i ] si T[ nod2 ][ i ] 
			// -> cand o sa se intalneasca cele 2 drepte

			Time.clear();
            for ( i=1; i<=n; ++i ){
 				int moment = ( T[ nod2 ][ i ] - T[ nod ][ i ] + cost ) /2  ;
				if ( moment >= 0 )
					Time. push_back ( make_pair ( moment, i ) );
			}
			sort( Time.begin(), Time.end(), sort_cresc );
/*			printf("\t%d@%d\n",nod,nod2);
			for ( i=0; i<Time.size(); ++i ){
				printf("\t%d\t%d\n",Time[i].first,Time[i].second);
			}
			printf("\n\n");*/
			int max2 = 0, d=0;
			for ( i=1; i<=n; ++i ){
				Viz[ i ] = 0;
			}
			rez = min ( rez, Inc[ IncC ].first );
			for ( i=0; i< int ( Time.size() ); ){
 //   			printf("%d\t%d-%d\n",rez,nod,nod2);
				
				j=i;
				while ( i<Time.size() && Time[ i ].first == Time[ j ].first ){
					Viz[ Time[ i ].second ] = 1;
					max2 = max (  T[ nod2 ][ Time[ i ].second ], max2 );
					++i;
				}
				if ( i == Time.size() ){
					continue;
				}
				int dif = Time[ i ].first - Time[ j ].first;

                while ( Viz[ Inc[ IncC ].second ] )
					IncC++;
//				printf("%d@%d\n",Inc[ IncC ].first+d+dif, max2+cost-d-dif);

				if ( max2 )
					rez = min ( rez, max ( max2+(cost-d-dif) , Inc[ IncC ].first+d+dif ) );
				// acum incercam sa calculam pe "parcurs" 
				int mid = ( cost + max2 - 2*d - Inc[ IncC ].first )/2;
				if ( mid <= dif  && mid >=0 )
					rez = min ( rez, ( Inc[ IncC ].first + mid + d ) );	
				d+=dif;
			}
		}
	}       
	printf("%.7f\n",rez/2.0);

	return 0;
}         
