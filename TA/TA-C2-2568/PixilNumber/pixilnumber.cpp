#include <bits/stdc++.h>
using namespace std;

int ch[1000][1000];
int T[1000][1000];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
queue<pair<int,int>> Q;
int ncol[1000];
int n,q,p,np,c,nc;

void BFS(int sy,int sx)
{
    if(ch[sy][sx] == 1) return;
    Q.push({sy,sx});
    ch[sy][sx] = 1;
    while(!Q.empty())
    {
        auto[y,x] = Q.front();
        Q.pop();
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < n && !ch[ny][nx] && T[ny][nx] == T[y][x])
            {
                Q.push({ny,nx});
                ch[ny][nx] = 1;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> T[i][j];
            if(!ncol[T[i][j]])
            {
                c++;
                ncol[T[i][j]] = 1;
            }
        }
    }
    for(int i = 0; i < q; i++)
    {
        int x,y;
        cin >> y >> x;
        BFS(y,x);
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(ch[i][j] == 1) 
            {
                p++;
            } 
            else 
            {
                np++;
                if(ncol[T[i][j]] == 1) 
                {
                    ncol[T[i][j]] = 2;
                    nc++;
                }
            }
        }
    }
    cout << p << " " << np << " " << c-nc;
}