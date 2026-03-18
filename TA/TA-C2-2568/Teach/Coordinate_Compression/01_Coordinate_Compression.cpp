#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,id = 0;
    cin >> n;
    int A[n],tmp[n];
    map <int,int> M;
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
        tmp[i] = A[i];
    }
    sort(tmp,tmp+n);
    for (int i = 0; i < n; i++)
    {
        if(M.find(tmp[i]) == M.end())
        {
            M[tmp[i]] = id;
            id++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << M[A[i]] << " ";
    }
    
}
/*
INPUT
5
100 200 1000 200 300
OUTPUT
0 1 2 1 3
*/