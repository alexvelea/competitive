#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

	#define max_n 3050

	int n,m,i,j,cx,cy,nr;
	char c;
	int nrx,nry;
	long long rez;

	int d,dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
	short Viz[max_n][max_n];

	struct point {
		int x,y;
	} Deq[max_n*max_n];
	int prim,ultim;

	int Ax[max_n],Bx[max_n],X[max_n];
	int Ay[max_n],By[max_n],Y[max_n];

	bool valid ( int x, int y ){
		if ( x < 0 || x > nrx+1 || y < 0 || y > nry+1 )
			return 0;
		return 1;
	}

	int bs ( int val, int cod ){
		int ind=(1<<15),rez=0;
		for ( ; ind; ind>>=1 ){
			if ( !cod ){
				if ( ( ind+rez <= nrx ) && ( Bx[ind+rez] <= val ) )
					rez+=ind;
			}
			else{
				if ( ( ind+rez <= nry ) && ( By[ind+rez] <= val ) )
					rez+=ind;
			}
		}
		return rez;
	}

int main(){
	cin>>n;
	cx=0;
	cy=0;
	for ( i=1; i<=n; i++ ){
		cin>>c>>nr;
		if ( c == 'R' ){
       		cy+=nr;
		}
		if ( c == 'L' ){
        	cy-=nr;
		}
		if ( c == 'U' ){
       		cx+=nr;
		}
		if ( c == 'D' ){
        	cx-=nr;
		}
		X[i]=cx;
		Y[i]=cy;
		Ax[++m]=cx;
		Ay[  m]=cy;
		Ax[++m]=cx+1;
		Ay[  m]=cy+1;
		Ax[++m]=cx-1;
		Ay[  m]=cy-1;
	}
	sort ( Ax, Ax+m+1 );
	sort ( Ay, Ay+m+1 );
	nrx=nry=0;
	for ( i=0; i<=m; ){
		j=i;
		while ( Ax[i]==Ax[j] )
			i++;
		Bx[++nrx]=Ax[j];
	}
	for ( i=0; i<=m; ){
		j=i;
		while ( Ay[j]==Ay[i] )
			i++;
		By[++nry]=Ay[j];
	}
 	for ( i=0; i<=n; i++ ){
		X[i]=bs(X[i],0);
		Y[i]=bs(Y[i],1);
	}
	for ( i=1; i<=n; i++ ){
		int cxn,cyn;
    	cx=X[i-1];
		cy=Y[i-1];
		cxn=X[i];
		cyn=Y[i];
		if ( cx == cxn ){
			for ( j=min(cy,cyn); j<=max(cy,cyn); j++ )
				Viz[cx][j]=1;
		}
		else{
			for ( j=min(cx,cxn); j<=max(cx,cxn); j++ )
				Viz[j][cy]=1;
		}
	}
	prim=1;
	ultim=0;
	for ( i=0; i<=nry+1; i++ ){
		Deq[++ultim].x=0;
		Deq[  ultim].y=i;
		Deq[++ultim].x=nrx+1;
		Deq[  ultim].y=i;
	}
	for ( i=1; i<nrx; i++ ){
		Deq[++ultim].x=i;
		Deq[  ultim].y=0;
		Deq[++ultim].x=i;
		Deq[++ultim].y=nry+1;
	}
	while ( prim <= ultim ){
		for ( d=0; d<4; d++ ){
			cx=Deq[prim].x+dx[d];
			cy=Deq[prim].y+dy[d];
			if ( (valid(cx,cy) ) && ( Viz[cx][cy]==0 ) ){
				Deq[++ultim].x=cx;
				Deq[  ultim].y=cy;
				Viz[cx][cy]=2;
			}
		}
		prim++;
	}
	// am terminat df-ul ..
	// yepiii
	for ( i=1; i<=nrx; i++ ){
		for ( j=1; j<=nry; j++ ){
			if ( Viz[i][j]<2 ){
                rez++;
				// daca are in dreapta 
				if ( Viz[i][j+1]<2 ){
					rez+=(long long)By[j+1]-By[j]-1;
				}
				// are in sus element valid
				if ( Viz[i+1][j] < 2 ){
					rez+=(long long)Bx[i+1]-Bx[i]-1;
				}
				// daca are si in diagonala
				if ( Viz[i+1][j+1] < 2 ){
                    rez+=(long long)(Bx[i+1]-Bx[i]-1)*(By[j+1]-By[j]-1);
				}
			}
		}
	}
/*	for ( i=0; i<=nrx+1; i++,printf("\n") ){
		for ( j=0; j<=nry+1; j++ ){
			printf("%d",Viz[i][j]);
		}
	}*/
	cout<<rez;
	return 0;
}                   
