#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> pai;
    vector<int> size;

    // Construtor: Inicializa a DSU com n elementos
    DSU(int n) {
        pai.resize(n + 1);
        size.assign(n + 1, 1); // Todos começam com tamanho 1
        
        // Inicializa cada um como seu próprio pai
        for (int i = 0; i <= n; i++) {
            pai[i] = i;
        }
    }

    // Find com PATH COMPRESSION   
    int find(int x) {
        if (x == pai[x]) return x;
        //atualiza o pai direto para a raiz
        return pai[x] = find(pai[x]); 
    }

    // Unite com UNION BY SIZE
    void join(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return; // Já estão no mesmo conjunto

        // Garante que 'a' é a maior árvore para colar 'b' nela
        if (size[a] < size[b]) swap(a, b);

        pai[b] = a;        // O líder de B agora aponta para A
        size[a] += size[b]; // A absorve o tamanho de B
    }
};