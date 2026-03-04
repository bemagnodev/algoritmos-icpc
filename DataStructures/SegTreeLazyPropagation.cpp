#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

struct SegTree {
    int n;
    vl tree;
    vl lazy;
    ll neutro = 0;

    // Funções inline para legibilidade
    int left(int i) { return i << 1; }       // i * 2
    int right(int i) { return (i << 1) | 1; } // i * 2 + 1
    
    // Função de combinação
    ll merge(ll a, ll b) { return a + b; }

    SegTree(const vl& a) {
        n = a.size();
        tree.assign(4 * n, neutro);
        lazy.assign(4 * n, 0);
        build(a, 1, 0, n - 1);
    }

    void build(const vl& a, int i, int tl, int tr) {
        if (tl == tr) {
            tree[i] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, left(i), tl, tm);        
            build(a, right(i), tm + 1, tr);
            tree[i] = merge(tree[left(i)], tree[right(i)]);
        }
    }

    void push(int i, int tl, int tr) {
        if (lazy[i] != 0) {
            int tm = (tl + tr) / 2;
            
            // Aplica no filho esquerdo------------//
            tree[left(i)] =merge(tree [left(i)], lazy[i] * (tm - tl + 1)); // RSQ
            // tree[left(i)] =merge(tree [left(i)], lazy[i]); //RMQ
           
            lazy[left(i)] =merge(lazy[left(i)] ,lazy[i]);
            
            // Aplica no filho direito ------------//
            tree[right(i)] =merge(tree [right(i)], lazy[i] * (tr - tm)); // RSQ
            // tree[right(i)] =merge(tree [right(i)], lazy[i]); //RMQ
           
            lazy[right(i)] =merge(lazy[right(i)] ,lazy[i]);
            

            //Limpa o pai
            lazy[i] = neutro;
        }
    }

    void upd(int i, int tl, int tr, int l, int r, ll v) {
        if (l > r) return;

        if (l == tl && r == tr) {
            //RSQ ------------//
            tree[i] += v * (tr - tl + 1); 
            lazy[i] += v;
            //RMQ ------------//
            // tree[i] = merge(tree[i], v);
            // lazy[i] = merge(lazy[i], v);
        } else {
            push(i, tl, tr);
            int tm = (tl + tr) / 2;
            
            upd(left(i), tl, tm, l, min(r, tm), v);
            upd(right(i), tm + 1, tr, max(l, tm + 1), r, v);
            
            tree[i] = merge(tree[left(i)], tree[right(i)]);
        }
    }

    ll qry(int i, int tl, int tr, int l, int r) {
        if (l > r) return neutro;
        if (l == tl && r == tr) return tree[i];

        push(i, tl, tr);
        int tm = (tl + tr) / 2;
        
        return merge(
            qry(left(i), tl, tm, l, min(r, tm)),
            qry(right(i), tm + 1, tr, max(l, tm + 1), r)
        );
    }

    // Wrappers
    void upd(int l, int r, ll v) { upd(1, 0, n - 1, l, r, v); }
    ll qry(int l, int r) { return qry(1, 0, n - 1, l, r); }
};