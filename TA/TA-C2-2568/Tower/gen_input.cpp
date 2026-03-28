#include <bits/stdc++.h>
#include <sys/stat.h>

using namespace std;

void geninput(string in, int c)
{
    ofstream fout(in);
    random_device rd;
    mt19937 gen(rd());

    if (c <= 4) // Subtask 1: N <= 100, X <= 10,000
    {
        uniform_int_distribution<int> ran_q(8, 10);
        int q = ran_q(gen);
        fout << q << "\n";
        while (q--)
        {
            uniform_int_distribution<int> ran_n(90, 100);
            int n = ran_n(gen);
            fout << n << "\n";
            
            uniform_int_distribution<int> ran_x(1, 9000);
            uniform_int_distribution<int> ran_len(1, 500); // สุ่มความยาวช่วง
            
            for (int i = 0; i < n; i++)
            {
                int x = ran_x(gen);
                int y = x + ran_len(gen);
                fout << x << " " << y << "\n";
            }
        }
    }
    else if (c <= 8) // Subtask 2: N <= 1000, X <= 10^9
    {
        uniform_int_distribution<int> ran_q(8, 10);
        int q = ran_q(gen);
        fout << q << "\n";
        while (q--)
        {
            uniform_int_distribution<int> ran_n(900, 1000);
            int n = ran_n(gen);
            fout << n << "\n";
            
            uniform_int_distribution<int> ran_x(1, 9e8);
            uniform_int_distribution<int> ran_len(1, 5e7);
            
            for (int i = 0; i < n; i++)
            {
                int x = ran_x(gen);
                int y = x + ran_len(gen);
                fout << x << " " << y << "\n";
            }
        }
    }
    else if (c <= 14) // Subtask 3: Sum of N <= 200,000, ข้อมูลถูกเรียงมาให้แล้ว (Sorted)
    {
        uniform_int_distribution<int> ran_q(100, 200); 
        int q = ran_q(gen);
        fout << q << "\n";
        
        int sum_n = 200000; // คุมไม่ให้ Sum of N เกินลิมิต
        for (int k = 0; k < q; k++)
        {
            int n;
            if (k == q - 1) n = sum_n;
            else {
                uniform_int_distribution<int> ran_n(1, (sum_n / (q - k)) * 2);
                n = ran_n(gen);
                n = min(n, sum_n - (q - 1 - k)); 
                n = max(n, 1);
            }
            sum_n -= n;
            
            fout << n << "\n";
            uniform_int_distribution<int> ran_x(1, 9e8);
            uniform_int_distribution<int> ran_len(1, 1e7);
            
            vector<pair<int, int>> intervals;
            for (int i = 0; i < n; i++)
            {
                int x = ran_x(gen);
                int y = x + ran_len(gen);
                intervals.push_back({x, y});
            }
            
            // Subtask 3 บังคับว่าข้อมูลต้องเรียงลำดับมาให้แล้ว
            sort(intervals.begin(), intervals.end());
            for (auto p : intervals) {
                fout << p.first << " " << p.second << "\n";
            }
        }
    }
    else // Subtask 4: Sum of N <= 200,000, ข้อมูลสุ่มกระจาย (Unsorted)
    {
        uniform_int_distribution<int> ran_q(100, 500); 
        int q = ran_q(gen);
        fout << q << "\n";
        
        int sum_n = 200000; 
        for (int k = 0; k < q; k++)
        {
            int n;
            if (k == q - 1) n = sum_n;
            else {
                uniform_int_distribution<int> ran_n(1, (sum_n / (q - k)) * 2);
                n = ran_n(gen);
                n = min(n, sum_n - (q - 1 - k)); 
                n = max(n, 1);
            }
            sum_n -= n;
            
            fout << n << "\n";
            uniform_int_distribution<int> ran_x(1, 9e8);
            uniform_int_distribution<int> ran_len(1, 5e7);
            
            for (int i = 0; i < n; i++)
            {
                int x = ran_x(gen);
                int y = x + ran_len(gen);
                fout << x << " " << y << "\n";
            }
        }
    }
}

int main()
{
    // สร้างโฟลเดอร์ input (สำหรับ Linux/Mac และ Windows บางรันไทม์)
    
    for (int i = 1; i <= 20; i++)
    {
        string filename = "./testcase/";
        if (i <= 9) filename += "0";
        filename += to_string(i) + ".in";
        
        geninput(filename, i);
        cout << "Generated: " << filename << "\n";
    }
    return 0;
}