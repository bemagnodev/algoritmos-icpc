        #include <bits/stdc++.h>
        using namespace std;

        typedef long long ll;

        struct SparseTable {
            int n, k;
            vector<vector<int>> st;
            vector<int> lg;// lg[i] = maximo de potencisas de 2 que cabem em i
            int neutro = 1e9; //-INF par max, 0 para mdc

            // Construtor: Martela a tabela em O(N log N)
            SparseTable(const vector<int>& arr) {
                n = arr.size();
                k = __lg(n); // Calcula o log2 necessário dinamicamente
                
                st.assign(k + 1, vector<int>(n));
                lg.assign(n + 1, 0);

                // Pré-calcula os logs para garantir O(1) na query
                for (int i = 2; i <= n; i++)
                    lg[i] = lg[i / 2] + 1;

                // Base da tabela: intervalos de tamanho 2^0 = 1 -> proprio valor do arary
                for (int i = 0; i < n; i++)
                    st[0][i] = arr[i];

                // Construção das camadas superiores
                 for (int i = 1; i <= k; i++) {
                    for (int j = 0; j + (1 << i) <= n; j++) { 
                        // O mínimo de um intervalo de 2^i é o min de dois de 2^(i-1)
                        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
                    }
                }
            }

            // Consulta em O(1)
            int query(int l, int r) {
                if (l > r) return neutro;
                int j = lg[r - l + 1];
                return min(st[j][l], st[j][r - (1 << j) + 1]);
            }
        };