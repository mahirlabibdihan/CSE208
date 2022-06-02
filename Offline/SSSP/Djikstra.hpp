#include <vector>
#include <queue>
#include <climits>
using namespace std;

void dijkstra(vector<pair<int, int>> adj[], const int &n, const int &start, vector<int> &dist, vector<int> &parent)
{
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>> pq;
    dist[start] = 0;
    pq.push({-dist[start], start});

    // Initialize heap array
    for (int i = 0; i < n; i++)
    { // Now, get distances
        pair<int, int> temp;
        int u, w;
        do
        {
            if (pq.empty())
            {
                // Nothing to remove
                return;
            }
            temp = pq.top();
            u = temp.second;
            w = -temp.first;
            pq.pop();
        } while (visited[u]);
        visited[u] = true;
        // if (dist[u] == INFINITY)
        //     return dist;                  // Unreachable vertices
        for (pair<int, float> i : adj[u]) // Sum of length of all adjacency list is 2|E|
        {
            int v = i.first;
            float w = i.second;
            if (dist[v] > dist[u] + w) // If any vertex is already visited than this condition will always be false for that vertex. So we don't need to check that explicitly
            {
                dist[v] = dist[u] + w;  // Update distance
                parent[v] = u;          // Update who it came from
                pq.push({-dist[v], v}); // Insert new distance in heap // O(logE)
            }
        }
    }
}