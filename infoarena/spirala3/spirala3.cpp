#include <cstdio>
#include <iostream>
#include <utility>
using namespace std;

    #define max_n 52

    int n,m,i,j,d,x,y,maxim;

    int dx[4]={-1,0,1,0};
    int dy[4]={0,1,0,-1};

    short Rez[max_n][max_n][max_n][max_n][4];
    char   C[max_n][max_n][4];
    bool El[max_n][max_n];

/*
    
    01
    32

*/

int max ( int a, int b ){
    if ( a>b )
        return a;
    return b;
}

void init (){
    // C[i][j][d]=cat de mult ma pot duce in directia d inclusiv cu pozitia curenta
    // d=1;
    d=0;
    for ( i=1; i<=n; i++ ){
        for ( j=1; j<=m; j++ ){
            if ( El[i][j]==0 ){
                C[i][j][d]=C[i+dx[d] ][j+dy[d] ][d]+1;
            }
            else{
                C[i][j][d]=0;
            }
 
        }
    }
    d=1;
    for ( i=1; i<=n; i++ ){
        for ( j=m; j>=1; j-- ){
            if ( El[i][j]==0 ){
                C[i][j][d]=C[i+dx[d] ][j+dy[d] ][d]+1;
            }
            else{
                C[i][j][d]=0;
            }
 
        }
    }  
    d=2;
    for ( i=n; i>=1; i-- ){
		for ( j=1; j<=m; j++ ){
		    if ( El[i][j]==0 ){
  		       C[i][j][d]=C[i+dx[d] ][j+dy[d] ][d]+1;
            }
            else{
                C[i][j][d]=0;
            }
 
        }
    }  
    d=3;
    for ( i=1; i<=n; i++ ){
        for ( j=1; j<=m; j++ ){
            if ( El[i][j]==0 ){
                C[i][j][d]=C[i+dx[d] ][j+dy[d] ][d]+1;
            }
            else{
                C[i][j][d]=0;
            }
        }
    }
}
    

void solve (){

    for ( i=1; i<=n; i++ )
        for ( j=1; j<=m; j++ )
            for ( x=1; x<=n; x++ )
                for ( y=1; y<=m; y++ )
                    for ( d=0; d<4; d++ )
                        Rez[i][j][x][y][d]=0;
    for ( i=1; i<=n; i++ ){
        for ( j=1; j<=m; j++ ){
            for ( d=0; d<4; d++ ){
                Rez[i][j][i][j][d]=El[i][j]^1;
            }
        }
    }
    init();

    for ( i=0; i<n; i++ ){
        for ( j=0; j<m; j++ ){ 
            for ( x=1; x+i<=n; x++ ){
                for ( y=1; y+j<=m; y++ ){                        
                    #define RezA Rez[x][y][x+i][y+j]
                    // coltul=0
                   if ( (!El[x][y]) && RezA[0] ){
                        if ( !El[x-1][y] ){
                            Rez[x-1][y][x+i][y+j][0]=max ( Rez[x-1][y][x+i][y+j][0], 1+RezA[0] );
                        }
                        if ( C[x-1][y][1] + RezA[0] > maxim ){
                            maxim = C[x-1][y][1] + RezA[0];
                        }

                        if ( C[x-1][y][1] >= j+1 ){
                            Rez[x-1][y][x+i][y+j][1]=max ( Rez[x-1][y][x+i][y+j][1], j+1+RezA[0] );
                        }
                    }

                    // coltul=1
                    if ( (!El[x][y+j]) && RezA[1] ){
                        if ( !El[x][y+j+1] ){
                            Rez[x][y][x+i][y+j+1][1]=max ( Rez[x][y][x+i][y+j+1][1], 1+RezA[1] );
                        }
                        if ( C[x][y+j+1][2] + RezA[1] > maxim ){
                            maxim = C[x][y+j+1][2] + RezA[1];
                        }
                        if ( C[x][y+j+1][2] >= i+1 ){
                            Rez[x][y][x+i][y+j+1][2]=max ( Rez[x][y][x+i][y+j+1][2], i+1+RezA[1] );
                        }
                    }

                    // coltul=2
                    if ( (!El[x+i][y+j]) && RezA[2]){
                        if ( !El[x+i+1][y+j] ){
                            Rez[x][y][x+i+1][y+j][2]=max (Rez[x][y][x+i+1][y+j][2], 1+RezA[2] );
                        }
                        if ( C[x+i+1][y+j][3] + RezA[2] > maxim ){
                            maxim=C[x+i+1][y+j][3] + RezA[2];
                        }
                        if ( C[x+i+1][y+j][3] >= j+1 ){
                            Rez[x][y][x+i+1][y+j][3]=max ( Rez[x][y][x+i+1][y+j][3], j+1+RezA[2] );
                        }
                    }
                    // coltul=3
                    if ( (!El[x+i][y]) && RezA[3] ){
                        if ( !El[x+i][y-1] ){
                            Rez[x][y-1][x+i][y+j][3]=max (Rez[x][y-1][x+i][y+j][3], 1+RezA[3] );
                        }
                        if ( C[x+i][y-1][0] + RezA[3] > maxim ){
                            maxim = C[x+i][y-1][0] + RezA[3] ;
                        }
                        if ( C[x+i][y-1][0] >= i+1 ){
                            Rez[x][y-1][x+i][y+j][0]=max (Rez[x][y-1][x+i][y+j][0], i+1+RezA[3]);
                        }
                    }
                }
            }
        }
    }
    for ( i=1; i<=n; i++ )
        for ( j=1; j<=m; j++ )
            for ( x=i; x<=n; x++ )
                for ( y=j; y<=m; y++ )
                    for ( d=0; d<4; d++ )
                        if ( Rez[i][j][x][y][d] > maxim )
                            maxim=Rez[i][j][x][y][d];
}

int main(){
/*   freopen ("spirala3.in","r",stdin);
    freopen ("spirala3.out","w",stdout);*/
    scanf ("%d %d", &n, &m);
    for ( i=1; i<=n; i++ ){
        for ( j=1; j<=m; j++ ){
            scanf ("%d", &El[i][j] );
        }
    }
    solve();
    /*// mirror
    for ( i=1; i<=n; i++ ){
        for ( j=1; m-j > j; j++ )
            swap ( El[i][j],El[i][m-j+1] );
    }
    solve();*/
    printf("%d", maxim);
    return 0;
}
