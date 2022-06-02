#include <vector>
#include <queue>
#include <climits>
#include "Edge.hpp"
using namespace std;

bool bellmanFord(vector<pair<int, int>> adj[], int n, int source, vector<int> &dist, vector<int> &parent)
{
    vector<Edge> edges;
    for (int u = 0; u < n; u++) // Put the edges on the array
    {
        for (pair<int, int> i : adj[u])
        {
            int v = i.first;
            int w = i.second;
            edges.push_back(Edge(u, v, w));
        }
    }
    dist[source] = 0;
    parent[source] = -1;
    for (int i = 0; i < n - 1; i++)
    {
        for (Edge e : edges)
        {
            int u = e.from;
            int v = e.to;
            int w = e.weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }
    for (Edge e : edges)
    {
        int u = e.from;
        int v = e.to;
        int w = e.weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v])
        {
            return false;
        }
    }
    return true;
}