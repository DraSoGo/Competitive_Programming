#include<bits/stdc++.h>
using namespace std;

int n;
string grid[105];
bool visited[105][105];
int dy[] = {-1,-1,-1,0,0,1,1,1};
int dx[] = {-1,0,1,-1,1,-1,0,1};

int countMines(int y, int x){
    int cnt = 0;
    for(int d = 0; d < 8; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
        if(grid[ny][nx] == '*') cnt++;
    }
    return cnt;
}

int total = 0;

void bfs(int sy, int sx){
    queue<pair<int,int>> q;
    q.push({sy, sx});
    visited[sy][sx] = true;
    while(!q.empty()){
        auto [y, x] = q.front();
        q.pop();
        int mines = countMines(y, x);
        total += mines;
        if(mines > 0) continue;
        for(int d = 0; d < 8; d++){
            int ny = y + dy[d];
            int nx = x + dx[d];
            if(ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
            if(visited[ny][nx]) continue;
            if(grid[ny][nx] == '*') continue;
            visited[ny][nx] = true;
            q.push({ny, nx});
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    int x, y;
    cin >> x >> y;
    
    for(int i = 0; i < n; i++) cin >> grid[i];
    
    bfs(y-1, x-1);
    
    cout << total << "\n";
    
    return 0;
}