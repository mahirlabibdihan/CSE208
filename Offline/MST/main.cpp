#include "Prim.hpp"
#include "Kruskal.hpp"

int getCost(vector<Edge> mst)
{
    int cost = 0;
    for (Edge e : mst)
    {
        cost += e.weight;
    }
    return cost;
}
void printMst(vector<Edge> mst)
{
    int n = mst.size();
    cout << '{';
    for (int i = 0; i < n; i++)
    {
        cout << '(' << mst[i].from << ',' << mst[i].to << ')';
        if (i < n - 1)
        {
            cout << ',';
        }
    }
    cout << '}' << endl;
}

// For undirected graph
int main()
{
    freopen("mst.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<pair<int, float>> adj[n];
    for (int i = 0; i < m; i++)
    {
        int u, v;
        float w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<Edge> mstK = kruskal(adj, n);
    vector<Edge> mstP = prim(adj, n, 0);
    if (mstK.size() < n - 1)
    {
        cerr << "ERROR: Disconnected graph" << endl;
        return EXIT_FAILURE;
    }
    cout << "Cost of the minimum spanning tree : " << getCost(mstK) << endl;
    cout << "List of edges selected by Prim's: ";
    printMst(mstP);
    cout << "List of edges selected by Kruskal's: ";
    printMst(mstK);
}