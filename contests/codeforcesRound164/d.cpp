#include <cstdio>
#include <vector>
using namespace std;

#define FORIT( it, v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define max_m 100005
#define MOD 1000000009
#define pb push_back

struct stare {
	int V[3], number;
	stare (){
		V[0]=V[1]=V[2]=0;
	}
	stare ( int a, int b, int c ){
		V[0]=a;
		V[1]=b;
		V[2]=c;
		number = -1;
	}
	int id(){
		if ( number != -1 )
			return number;
		int i;
		number=0;
		for ( i=0; i<3; ++i ){
			number<<=5;
			number++;
			number+=V[0];
		}
		return number;
	}
	void sort (){
		if ( V[0] > V[1] )
			swap ( V[0], V[1] );
		if ( V[0] > V[2] )
			swap ( V[0], V[2] );
		if ( V[1] > V[2] )
			swap ( V[1], V[2] );
	}
} ;

int n,h,i,j;
vector<stare> Act,Next;
bool Viz[ max_m ];
int RezAct[ max_m ], RezNext[ max_m ];
 
stare next ( int ind, stare a ){
	if ( ind != -1 ){
		a.V[ind]=0;
	}
	for ( int i=0; i<3; ++i ){
		a.V[i]++;
		if ( a.V[i] == 0 )
			a.V[i]=-1;
		if ( a.V[i] > h )
			a.V[i] = h+1;
	}
	a.sort();
	return a;
}

bool valid ( int i, int ind, stare a ){
	bool ok=0;
	if ( ind == -1 ){
	}
	for ( int i=0; i<3; ++i ){
		if ( a.V[i] != -1 && a.V[i]
	}
}

int main(){
	scanf ("%d %d", &n, &h );
	it->id()[5];
	Act.pb( stare( -1, -1, -1 ) );
	for ( i=1; i<=n; ++i ){
		FORIT ( it, Act ){
			Viz[ it->id() ] = false;
			RezAct[ it->id() ] = RezNext[ it->id() ];
			RezNext[ it->id() ] = 0;
		}
		FORIT ( it, Act ){
        	for ( j=-1; j<3; ++j ){
				if ( valid ( i, j, *it ) ){
					stare a = next ( j, *it );
					if ( !Viz[ a.id() ] ){
						Viz[ a.id() ] = true;
						Next.pb( a );
					}                
					RezNext[ a.id() ]+=RezAct[ it->id() ];
				}
			}
		}
		swap ( Act, Next );
		Next.clear();
	}

	return 0;
}    
