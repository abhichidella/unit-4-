#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Structure to store an edge
struct Edge {
    int to, cost;
};

int main() {
    int n, m;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;

    vector<vector<Edge>> graph(n);

    cout << "Enter edges in format: from to weight\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // undirected (bidirectional) graph
    }

    int start, target;
    cout << "Enter source node: ";
    cin >> start;
    cout << "Enter target node: ";
    cin >> target;

    // Dijkstra’s algorithm
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dist[start] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &edge : graph[u]) {
            int v = edge.to;
            int cost = edge.cost;
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[target] == INT_MAX) {
        cout << "No path found from " << start << " to " << target << endl;
        return 0;
    }

    cout << "Minimum cost from " << start << " to " << target << " = " << dist[target] << endl;
    cout << "Path: ";

    vector<int> path;
    for (int v = target; v != -1; v = parent[v])
        path.push_back(v);

    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;

    return 0;
}
