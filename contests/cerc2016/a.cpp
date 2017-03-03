#include<stdio.h>
#include<algorithm>
using namespace std;

#define NMAX 150
#define x first
#define y second

int n,m,r,c,answer, nr, ok;
char s[NMAX][NMAX], mat_aux[NMAX][NMAX];
pair<int, int> start_points[NMAX * NMAX];


inline void rotate90(pair<int, int> A){
	for(int i = A.x; i < A.x + r; i++)
		for(int j = A.y; j < A.y + c; j++)
			mat_aux[i - A.x + 1][j - A.y + 1] = s[i][j];
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++){
			s[A.x + r - j][A.y + i - 1] = mat_aux[i][j];
		}
}

inline void rotate180(pair<int, int> A){
	for(int i = A.x; i < A.x + r; i++)
		for(int j = A.y; j < A.y + c; j++)
			mat_aux[i - A.x + 1][j - A.y + 1] = s[i][j];
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++)
			s[A.x + r - i][A.y + c - j] = mat_aux[i][j];
}

inline bool check(pair<int,int> A, pair<int,int> B){
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++)
			if(s[i + A.x - 1][j + A.y - 1] != s[i + B.x - 1][j + B.y - 1])
				return false;
	return true;
}

inline bool equal(pair<int,int> A, pair<int,int> B){
	if(check(A,B))
		return true;
	if(r == c){
		rotate90(B);
		if(check(A, B))
			return true;
		rotate90(B);
		if(check(A, B))
			return true;
	}
	else{
		rotate180(B);
		if(check(A, B))
			return true;
	}
	
	if(r == c){
		rotate90(B);
		if(check(A, B))
			return true;
		rotate90(B);
	}
	else
		rotate180(B);
	return false;
}

inline int getLines(int px, int py){
	if(s[px][py] == '#')
		return 0;
	return 1 + getLines(px + 1, py);
}

inline int getColums(int px, int py){
	if(s[px][py] == '#')
		return 0;
	return 1 + getColums(px, py + 1);
}


int main (){

	//freopen("a.in","r",stdin);

	scanf("%d%d\n",&n,&m);
	for(int i = 1; i <= n; i++){
		scanf("%s", s[i] + 1);
	}
	
	r = getLines(2,2);
	c = getColums(2,2);
//	printf("%d %d\n", r,c);
	
	for(int i = 2; i <= n; i += r + 1)
		for(int j = 2; j <= m; j += c + 1){
			start_points[++nr] = make_pair(i,j);
		}
	for(int i = 1; i <= nr; i++){
		ok = 1;
		for(int j = 1; j < i && ok; j++){
			if(equal(start_points[i], start_points[j])){
				ok = 0;
			}
		}
		answer += ok;
	}
	
	printf("%d\n", answer);
	

	return 0;
}
