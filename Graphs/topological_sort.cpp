#include <bits/stdc++.h>
using namespace std;

int n; 
vector<vector<int>> adj; 
vector<int> vis; // 0: unvisited, 1: visiting, 2: visited
vector<int> ans;
bool has_cycle = false;

void dfs(int u) {
    vis[u] = 1;  
    for (int v : adj[u]) {
        if(vis[v] == 0) dfs(v);
        if(vis[v]==1){
            has_cycle = true;
        }
        if (has_cycle) return;
    }
    vis[u] = 2; // Finalizado
    ans.push_back(u);
}

bool topological_sort() {
    //reset de variaveis
    vis.assign(n + 1, 0);  
    ans.clear();
    has_cycle = false;

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) dfs(i);
    }
    reverse(ans.begin(), ans.end());
    return !has_cycle;  
}