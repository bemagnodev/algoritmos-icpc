#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct SegTree {
    int n;
    vector<int> tree;
    int neutro = 0;  

    SegTree(const vector<int>& a) {
        n = a.size();
        tree.assign(4 * n, neutro);
        build(a, 1, 0, n - 1);
    }

    int merge(int a, int b) {
        return a + b;
    }

    // i: índice do nó na árvore (tree index)
    // tl, tr: limites do intervalo que o nó 'i' cobre
    void build(const vector<int>& a, int i, int tl, int tr) {
        if (tl == tr) {
            tree[i] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, 2 * i, tl, tm);
            build(a, 2 * i + 1, tm + 1, tr);
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
        }
    }

    // i: nó atual da árvore
    // p: POSIÇÃO no array original (alvo do upd ate)
    // v: novo valor
    void updt(int i, int tl, int tr, int p, int v) {
        if (tl == tr) {
            tree[i] = v;
        } else {
            int tm = (tl + tr) / 2;
            
            // Se a posição 'p' está na esquerda ou direita do meio
            if (p <= tm)
                updt(2 * i, tl, tm, p, v);
            else
                updt(2 * i + 1, tm + 1, tr, p, v);
            
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
        }
    }

    // i: nó atual
    // l, r: intervalo da query (pedido do usuário)
    int qry(int i, int tl, int tr, int l, int r) {
        if (l > r) return neutro;// evitar chamadas invalidas pela RECURSÃO
        if (l == tl && r == tr) return tree[i];

        int tm = (tl + tr) / 2;
        return merge(qry(2 * i, tl, tm, l, min(r, tm)),
                     qry(2 * i + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    // Wrappers (Interface simples para a main)
    // Passamos a raiz (i=1) e o intervalo total (0 a n-1) automaticamente
    void updt(int p, int x) { updt(1, 0, n - 1, p, x); }
    int qry(int l, int r) { return qry(1, 0, n - 1, l, r); }
};