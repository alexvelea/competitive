
void solve(int nod) {
    int nodSize = max(vertex[nod].size(), 1) + 1;
    
    for (int i = 1; i <= nodSize; ++i)
        dp[nod][i] = 0;

    
    for (int itr : vertex[nod]) {
        solve(itr);
        
        int x = max(int(vertex[itr].size()), 1) + 1;
        int childSize = max(int(vertex[itr].size()), 1) + 1;
        
        
        st[1] = inf;
        dr[childSize] = inf;
        
        for (int i = 2; i <= childSize + 1; ++i) { // aici e childSize + 1 .. important
            st[i] = min(st[i - 1], dp[itr][i - 1]);
        }
        for (int i = childSize - 1; i >= 1; --i) {
            dr[i] = min(dr[i + 1], dp[itr][i + 1]);
        }
        
        for (int i = 1; i <= childSize; ++i) {
            if (i <= nodSize) {
                dp[nod][i] += min(st[i], dr[i]);
            }
            if (i + 1 <= nodSize) {
                dp[nod[i + 1] -= min(st[i], dr[i])];
            }
        }
        
        // daca cumva copilul are mai putini fii decat nodul parinte atunci nu o sa actualizez toata dinamica
        // dupa ce am terminat culorile lui las sumele partiale sa faca treaba
        if (childSize + 1 <= nodSize)
            dp[nod][ChildSize + 1] += st[childSize + 1];
    }
    for (int i = 2; i <= nodSize; ++i)
        dp[nod][i] += dp[nod][i - 1];
    
    for (int i = 1; i <= nodSize; ++i)
        dp[nod][i] += i; // adaug costul elementului // nod
}