#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int v, c;
    long long p;
};

struct GP
{
    int v;
    long long w;
    bool operator<(const GP &a) const
    {
        return a.w < w;
    }
};

const int sz = 2e5 + 10;

int n, m, u, v, c;
long long p;
vector<Edge> G[sz];
map<int, long long> psum[sz];
priority_queue<GP> PQ;
bool vis[sz];
long long dis[sz];

long long DJ(int st, int ed)
{
    dis[st] = 0;
    PQ.push({st, 0});
    while (!PQ.empty())
    {
        auto [node, w] = PQ.top();
        PQ.pop();
        if (vis[node])
        {
            continue;
        }
        vis[node] = 1;
        for (auto [nxt, col, cost] : G[node])
        {
            long long nw = psum[node][col] - cost;
            if (dis[nxt] > dis[node] + nw)
            {
                dis[nxt] = dis[node] + nw;
                PQ.push({nxt, dis[nxt]});
            }
        }
    }
    return dis[ed];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;

    fill(dis, dis + sz, INT_MAX);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> c >> p;
        G[u].push_back({v, c, p});
        G[v].push_back({u, c, p});

        psum[u][c] += p;
        psum[v][c] += p;
    }

    long long ans = DJ(1, n);

    if (ans == INT_MAX)
    {
        cout << -1;
    }
    else
    {
        cout << ans;
    }

    return 0;
}