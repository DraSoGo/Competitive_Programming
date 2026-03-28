#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
const int sz = 1e5 + 10;
struct GP
{
    int v;
    long long w;
    int b;
    bool operator < (const GP& a) const
    {
        return a.w < w;
    }
};

int n, e, m, f, k;
int u, v;
long long w;
vector<pair<int, long long>> G[sz];
priority_queue<GP> PQ;
bool vis[sz][15];
long long dis[sz][15];
vector<int> wiz;

void DJ(int st)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            dis[i][j] = INF;
            vis[i][j] = 0;
        }
    }

    dis[st][0] = 0;
    PQ.push({st, 0, 0});

    while (!PQ.empty())
    {
        auto [node, w, b] = PQ.top();
        PQ.pop();

        if (vis[node][b])
        {
            continue;
        }
        vis[node][b] = 1;

        for (auto [nxt, nw] : G[node])
        {
            if (dis[nxt][b] > dis[node][b] + nw)
            {
                dis[nxt][b] = dis[node][b] + nw;
                PQ.push({nxt, dis[nxt][b], b});
            }

            if (b < k && dis[nxt][b + 1] > dis[node][b])
            {
                dis[nxt][b + 1] = dis[node][b];
                PQ.push({nxt, dis[nxt][b + 1], b + 1});
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> e >> m >> f >> k;
    for (int i = 0; i < e; i++)
    {
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    wiz.resize(m);
    for (int i = 0; i < m; i++)
    {
        cin >> wiz[i];
    }

    DJ(f);

    long long mnt = INF;
    vector<int> win;

    for (int st : wiz)
    {
        long long anst = INF;
        for (int b = 0; b <= k; b++)
        {
            anst = min(anst, dis[st][b]);
        }

        if (anst < mnt)
        {
            mnt = anst;
            win.clear();
            win.push_back(st);
        }
        else if (anst == mnt)
        {
            win.push_back(st);
        }
    }

    sort(win.begin(), win.end());
    win.erase(unique(win.begin(), win.end()), win.end());

    for (int i = 0; i < win.size(); i++)
    {
        cout << win[i] << " ";
    }

    return 0;
}