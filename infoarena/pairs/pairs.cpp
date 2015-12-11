#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#define max_val 1000005
#define max_n 100005
#define FORIT( it,v ) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

vector<int> Div, Desc;
int Ap[max_val], El[max_n], Last[max_val], last;

int n,i,j,c,nr,ind,rez,act;

void desc( int nr ){
	if( nr == 1 )
		return ;
	if( last != Last[nr] )
	    Desc.push_back( Last[nr] );
	last=Last[nr];
	desc( nr/Last[nr] );
}

int main(){
	freopen("pairs.in","r",stdin);
	freopen("pairs.out","w",stdout);
	scanf("%d", &n );
	for( i=1; i<=n; ++i ){
		scanf("%d", &El[i] );
	}
	Last[1]=1;
	for( i=2; i<max_val; ++i ){
		if( !Last[i] ){
			Div.push_back(i);
			for( j=i; j<max_val; j+=i ){
				Last[j]=i;
			}
		}
	}
	for( i=1; i<=n; ++i ){
		Desc.erase( Desc.begin(), Desc.end() );
		last=-1;
		desc( El[i] );
		for( j=1; j<(1<<(Desc.size()) ); ++j ){
			nr=1;
			for( c=0; c<Desc.size(); ++c ){
				if( j&(1<<c) ){
					nr*=Desc[c];
				}
			}
			Ap[nr]++;
		}
	}
	long long rez=0;
	for( i=1; i<=n; ++i ){
		act=0;
		Desc.erase( Desc.begin(), Desc.end() );
		last=-1;
		desc( El[i] );
		for( j=1; j< (1<<(Desc.size() )); ++j ){
			ind=0;
			nr=1;
			for( c=0; c<Desc.size(); ++c ){
				if( (1<<c)&j ){
					ind++;
					nr*=Desc[c];
				}
			}
			if( (ind&1) )
				act+=Ap[nr];
			else
				act-=Ap[nr];
		}
		rez=0LL+rez+n-act;
	}
	cout<<rez/2;
	return 0;
}
