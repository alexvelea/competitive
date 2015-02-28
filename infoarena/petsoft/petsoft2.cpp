#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define max_n 1005
#define FORIT( it,v ) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back

int Best[max_n][max_n][2];
int Rez [max_n][2];
vector<int> Vertex[max_n];

int n,i,Father;

void get_max( int &a, int b ){
    if( a<b )
        a=b;
}

void df( int nod ){
    int n,i,j,l,o;
    FORIT( it, Vertex[nod] ){
        df( *it );
    }
    n=Vertex[nod].size();
    sort( Vertex[nod].begin(), Vertex[nod].end() );
    for( i=0; i<=n; ++i ){
        for( j=0; j<=n; ++j ){
            Best[i][j][0]=Best[i][j][1]=-1;
            if( i>j )
                Best[i][j][0]=0;
        }
        
    }
    for( i=0; i<n; ++i ){
        Best[i][i][0]=max(Rez[Vertex[nod][i]][0],Rez[Vertex[nod][i]][1]);
        Best[i][i][1]=Rez[Vertex[nod][i]][0]+abs(nod-Vertex[nod][i]);
    }
    for( l=1; l<n; ++l ){
        for( i=0; i+l<n; i++ ){
            j=i+l;
            // cele 2 capete le legam cu varful
            if(         Best[i+1][j][0] !=-1 ) get_max( Best[i][j][1], Best[i+1][j][0] + abs( nod-Vertex[nod][i] ) + Rez[Vertex[nod][i]][0] );
            if( j &&    Best[i][j-1][0] !=-1 ) get_max( Best[i][j][1], Best[i][j-1][0] + abs( nod-Vertex[nod][j] ) + Rez[Vertex[nod][j]][0] );
            
            // nu legam cele 2 capete cu varful
            for( o=0; o<2; ++o ){
                if(         Best[i+1][j][1] != -1 && Rez[Vertex[nod][i]][o] != -1 )     get_max( Best[i][j][1], Best[i+1][j][1] + Rez[Vertex[nod][i]][o] );
                if( j>0 &&   Best[i][j-1][1] != -1 && Rez[Vertex[nod][j]][o] != -1 )     get_max( Best[i][j][1], Best[i][j-1][1] + Rez[Vertex[nod][j]][o] );
                
                if( j>0 &&   Best[i][j-1][0] != -1 && Rez[Vertex[nod][j]][o] != -1 )     get_max( Best[i][j][0], Best[i][j-1][0] + Rez[Vertex[nod][j]][o] );
                if(         Best[i+1][j][0] != -1 && Rez[Vertex[nod][i]][o] != -1 )     get_max( Best[i][j][0], Best[i+1][j][0] + Rez[Vertex[nod][i]][o] );
            }
            // punem impreuna pe cele 2 elemente
            if( j && Best[i+1][j-1][1] != -1 ) get_max( Best[i][j][1], Best[i+1][j-1][1] + abs( Vertex[nod][i] - Vertex[nod][j] ) + Rez[Vertex[nod][i]][0] + Rez[Vertex[nod][j]][0] );
            if( j && Best[i+1][j-1][0] != -1 ) get_max( Best[i][j][0], Best[i+1][j-1][0] + abs( Vertex[nod][i] - Vertex[nod][j] ) + Rez[Vertex[nod][i]][0] + Rez[Vertex[nod][j]][0] );
        }
    }
    if( n ){
        Rez[nod][0]=Best[0][n-1][0];
        Rez[nod][1]=Best[0][n-1][1];
    }else{
        Rez[nod][0]= 0;
        Rez[nod][1]=-1;
    }
    return ;
}

int main(){
    freopen("petsoft.in","r",stdin);
    freopen("petsoft.out","w",stdout);
    scanf("%d", &n );
    for( i=2; i<=n; ++i ){
        scanf("%d", &Father );
        Vertex[Father].pb(i);
    }
    df(1);
    printf("%d\n", max( Rez[1][0], Rez[1][1] ) );
    return 0;
}
