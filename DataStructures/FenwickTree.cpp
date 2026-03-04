#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


struct Fenwick {
    int n;
    vector<ll> bit;

    //  constrói a BIT em O(N log N)
    Fenwick(const vector<ll>& a) {
        n = a.size(); //0-based
        bit.assign(n + 1, 0); // IMPORTANTE: 1-based
        for (int i = 1; i <= n; i++) {
            update(i, a[i-1]); 
        }
    }

    // update(i, val): ADICIONA 'val' ao valor atual na posição 'i' (1-based)
    void update(int i, ll val) {
        for (; i <= n; i += i & -i) {
            bit[i] += val;
        }
    }

    // sum (i): Retorna a soma acumulada de [1...i]
    ll sum (int i) {
        ll s = 0;
        for (; i > 0; i -= i & -i) {
            s += bit[i];
        }
        return s;
    }

    // query(l, r): Retorna a soma no intervalo INCLUSIVO [l, r] (1-based)
    ll query(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};