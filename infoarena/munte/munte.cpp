#include <cstdio>
#include <iostream>
using namespace std;

int h,d,k,i,j,t,l;
int H[150];
struct coloana {
	unsigned long long el[55][55][2];
} cnext,clast,zero;

int main(){

    freopen ("munte.in","r",stdin);
    freopen ("munte.out","w",stdout);

    scanf ("%d %d %d", &h ,&d, &k);
    for (i=1; i<=k; i++) {
        scanf ("%d", &H[i]);
    }
    H[k+1]=h+5;

    clast.el[0][1][0]=1;
    for (i=1; i<=d; i++) {
        cnext=zero;
        for (l=k+1; l; l--) {
            for (t=0; t<2; t++) {
            	for (j=0; j<=h; j++) {
            		int milestone;
            		if (j == H[l]) 
            			milestone = l+1;
					else
						milestone = l;
            		cnext.el[j][milestone][t] += clast.el[j+1][l][t];
                    cnext.el[j][milestone][t] += clast.el[j+0][l][t];
                    if (j)
						cnext.el[j][milestone][t] += clast.el[j-1][l][t];
                }
            }
       		int milestone;
          	if (H[l] == h) 
           		milestone = l+1;
			else
				milestone = l;
            cnext.el[h][milestone][1] += clast.el[h-1][l][0];
        }
		for (l=1; l<=k+1; ++l) {
			if (i!=d)
				cnext.el[0][l][0] = cnext.el[0][l][1] = 0; // nu avem voie sa atingem 0 pe parcurs
			cnext.el[h][l][0] = 0; // nu avem cum sa fim la inaltimea h fara sa o fi atins
		}
        clast=cnext;
    }
    cout<<cnext.el[0][k+1][1] << "\n";
    return 0;
}
