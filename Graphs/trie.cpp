/**
 * @file trie.cpp
 * @brief Implementação de uma Árvore Trie.
 *
 * Estrutura de dados otimizada para busca de prefixos em um conjunto de strings.
 * Ótima para problemas de autocompletar, contagem de palavras, etc.
 *
 * Complexidades:
 * - Inserção: O(|S|), onde |S| é o tamanho da string.
 * - Remoção: O(|S|)
 * - Busca: O(|S|)
 * - Contagem de Prefixo: O(|S|)
 *
 * Memória: O(N * sigma), onde N é a soma dos comprimentos de todas as strings
 * e sigma é o tamanho do alfabeto.
 *
 * Créditos da ideia original: Enzo -> Bruno Meleitas
 */

#include <bits/stdc++.h>
using namespace std;

struct Trie {
    // Member Variables
    vector<vector<int>> children; // Matriz de adjacência para os filhos de cada nó
    vector<int> words_ending_here;      // Contador para strings que terminam neste nó
    vector<int> prefixes_passing_through; // Contador para strings que usam este nó como prefixo
    
    int sigma;      // Tamanho do alfabeto (e.g., 26 para 'a'-'z')
    char norm;      // Caractere base para normalização (e.g., 'a')
    int total_strings; // Contador total de strings na Trie

    // Construtor
    Trie    (int sigma_ = 26, char norm_ = 'a') : sigma(sigma_), norm(norm_) {
        // Inicializa a Trie com o nó raiz (nó 0)
        children.emplace_back(sigma, 0); // O nó 0 não tem filhos inicialmente (todos os ponteiros são 0)
        words_ending_here.push_back(0);
        prefixes_passing_through.push_back(0);
        total_strings = 0;
    }

    // Insere uma string na Trie
    void insert(const string& s) {
        int current_node = 0;
        prefixes_passing_through[current_node]++;

        for (char ch : s) {
            int char_index = ch - norm;
            int& next_node = children[current_node][char_index];

            if (next_node == 0) { // Se o caminho não existe, cria um novo nó
                next_node = children.size();
                children.emplace_back(sigma, 0);
                words_ending_here.push_back(0);
                prefixes_passing_through.push_back(0);
            }
            
            current_node = next_node;
            prefixes_passing_through[current_node]++;
        }
        
        words_ending_here[current_node]++;
        total_strings++;
    }

    // Busca por uma string, retorna o ID do nó final ou -1 se não encontrar
    int find_node(const string& s) {
        int current_node = 0;
        for (char ch : s) {
            int char_index = ch - norm;
            current_node = children[current_node][char_index];
            if (current_node == 0) {
                return -1; // Caminho não existe
            }
        }
        return current_node;
    }

    // Conta quantas vezes a string 's' exata foi inserida
    int count_word(const string& s) {
        int node_id = find_node(s);
        return (node_id != -1) ? words_ending_here[node_id] : 0;
    }

    // Conta quantas strings na Trie têm 's' como prefixo
    int count_prefix(const string& s) {
        int node_id = find_node(s);
        return (node_id != -1) ? prefixes_passing_through[node_id] : 0;
    }

    // Apaga uma ocorrência de uma string.
    // Nota: Esta implementação não remove os nós para simplificar, apenas decrementa contadores.
    // Em programação competitiva, isso geralmente é suficiente e mais seguro.
    void erase(const string& s) {
        if (count_word(s) == 0) return; // String não existe para ser apagada

        int current_node = 0;
        prefixes_passing_through[current_node]--;

        for (char ch : s) {
            int char_index = ch - norm;
            current_node = children[current_node][char_index];
            prefixes_passing_through[current_node]--;
        }

        words_ending_here[current_node]--;
        total_strings--;
    }
};