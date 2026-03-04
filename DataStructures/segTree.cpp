#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct SegTree {
    int n;
    vector<ll> tree;
    ll neutro = 0; // Mude para INF se for MIN, -INF se for MAX

    // Função que define a operação (Soma, Max, Min, XOR...)
    ll merge(ll a, ll b) { return a + b; }
     

     SegTree(const vector<int>& a) {
        n = a.size();
        tree.assign(2 * n, neutro); // inicializa o vetor tree
        
        // 1. Copia para as folhas
        for (int i = 0; i < n; i++) tree[n + i] = a[i];
        
        // 2. Calcula os pais
        for (int i = n - 1; i > 0; --i) 
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    // Atualiza valor na posição p (0-indexed)
    void update(int p, int value) {
        p += n; // Vai para a folha
        tree[p] = value;
        
            
        // Sobe a árvore atualizando os pais
       for (; p > 1; p >>= 1) { 
            int pai = p>>1;
            tree[pai] = merge(tree[pai*2], tree[pai*2+1]); //precisava organizar a ordem dos filhos? fiquei confiuso?
        }
    }

    // Query no intervalo [l, r) -> L fechado, R aberto
    ll query(int l, int r) {
        ll res = neutro;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            
            // Se l é ímpar, ele é filho direito.
            // O pai dele inclui o filho esquerdo que NÃO queremos.
            // Então processamos l agora e avançamos para a direita.
            if (l & 1) res = merge(res, tree[l++]);
            
            // Se r é ímpar, r-1 é par (filho esquerdo).
            // Como o intervalo é aberto no fim, queremos incluir r-1.
            if (r & 1) res = merge(res, tree[--r]);
        }
        return res;
    }
};