	#include <bits/stdc++.h>
	using namespace std;

	using ll = long long;
	using vl = vector<ll>;
	using pli = pair<ll, int>; 

	const ll INF = 1e18;
	const int MAXN = 2e5 + 5;  

	vector<pli> adj[MAXN]; // (peso, v)
	vector<ll> dist(MAXN, INF);
	vector<bool> processed(MAXN, false);


	void dijkstra(int start_node) {
		priority_queue<pli> pq; //max-heap:  {-distância, nó}

		dist[start_node] = 0;
		pq.push({0LL, start_node});

		while (!pq.empty()) {
			int u = pq.top().second;
			pq.pop();

			if (processed[u]) continue;
			processed[u] = true;

			//iterar pelos vizunhos de u
			for (auto& edge : adj[u]) {
				ll weight = edge.first;  //peso (u -> v)
				int v = edge.second;

				if (dist[u] + weight < dist[v]) {
					dist[v] = dist[u] + weight;
					pq.push({-dist[v], v});
				}
			}
		}
	}