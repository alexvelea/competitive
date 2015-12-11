#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <deque>
#include <fstream>
#define DN 500005
#define LL long long
using namespace std;
  
typedef pair<int,int> per;
  
int n,k,bst[DN];
char cuv[DN][11];
deque<int> ind[26];
  
int lst(char s[11]) {
    return s[strlen(s)-1]-'a';
}
  
int fst(string s) {
    return s[0]-'a';
}
  
int r=1;
  
int main() {
  ifstream f("raci.in");
  ofstream g("raci.out");
  f>>n>>k;
  for(int i=0; i<n; ++i) {
    f>>cuv[i];
    //cout<<cuv[i]<<' ';
    }
	
  for(int i=0; i<n; ++i) {
    int cc=fst(cuv[i]);
    for(;ind[cc].size() && i-ind[cc].front()>k; ind[cc].pop_front());
    if(ind[cc].size()) bst[i]=bst[ind[cc].front()]+1;
    else bst[i]=1;
    r=max(r,bst[i]);
    cc=lst(cuv[i]);
      
    for(;ind[cc].size() && bst[i]>bst[ind[cc].back()];ind[cc].pop_back());
    ind[cc].push_back(i);
  }
  g<<r;
  return 0;
}
