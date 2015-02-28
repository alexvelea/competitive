#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
int d=0,t=0,ans=0,tt=0;
long long n;

int main() {
	n=40000000;
	for (int i = n;i;i--){
		tt=sqrt((double)(n*n-(long long)i*i))+1e-8;
		if(tt-t>1)ans+=tt-t;
		else
			ans++;
		t=tt;
	}
	ans*=4;
	cout << ans;
	return 0;
}
