#include <bits/stdc++.h>
using namespace std;

const int mxi = 55;
unsigned long long S[mxi];
unsigned long long A[mxi];

void geninput(string in, int c)
{
    ofstream fout;
    fout.open(in);

    random_device rd;
    mt19937_64 gen(rd());

    uniform_int_distribution<int> ranT(90000, 100000);
    uniform_int_distribution<int> rani1(1, 5);
    uniform_int_distribution<int> rani2(45, 50);
    
    unsigned long long T = ranT(gen);
    fout << T << "\n";
    
    if (c < 3)
    {
        for (int i = 0; i < T; i++)
        {
            unsigned long long n = rani1(gen);
            uniform_int_distribution<unsigned long long> ranx1(1, A[n]);
            unsigned long long x = ranx1(gen);
            fout << n << " " << x << "\n";
        }
    }
    else
    {
        for (int i = 0; i < T; i++)
        {
            unsigned long long n = rani2(gen);
            uniform_int_distribution<unsigned long long> ranx2(A[n-2], A[n]);
            unsigned long long x = ranx2(gen);
            fout << n << " " << x << "\n";
        }
    }
    fout.close();
}

int main()
{
    S[1] = 2;
    S[2] = 1;
    for (int i = 3; i < mxi; i++)
    {
        S[i] = S[i-1] + S[i-2];
    }
    
    A[1] = 3;
    for (int i = 2; i <= 50; i++)
    {
        A[i] = 2ULL * A[i - 1] + S[i + 1] * 3ULL;
    }
    
    for (int i = 0; i <= 9; i++)
    {
        geninput("./input/input" + to_string(i) + ".in", i);
    }
    
    return 0;
}