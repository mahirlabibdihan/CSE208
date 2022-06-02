#include <iostream>
#include <vector>
#include "Djikstra.hpp"
using namespace std;
// For undirected graph
void printPath(int u, vector<int> &parent)
{
    if (parent[u] != -1)
    {
        printPath(parent[u], parent);
    }
    cout << u << " -> ";
}
int main()
{
    freopen("sssp.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> adj[n];
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    int s, d;
    cin >> s >> d;
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dijkstra(adj, n, s, dist, parent);
    if (parent[d] == -1)
    {
        cout << "Destination not reachable" << endl;
    }
    else
    {
        cout << "Shortest path cost: " << dist[d] << endl;
        printPath(parent[d], parent);
        cout << d << endl;
    }

    return EXIT_SUCCESS;
}
