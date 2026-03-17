#include <bits/stdc++.h>
using namespace std;

void geninput(string in, int c)
{
    ofstream fout;
    fout.open(in);

    random_device rd;
    mt19937 gen(rd());

    int n;
    vector<int> b;

    // ==========================================
    // Subtask 1 (80 Point): Testcase 0 - 15
    // Constraints: 1 <= n <= 100 และ 1 <= bi <= 7,500
    // ==========================================
    uniform_int_distribution<int> valRan1m(1, 1000000);
    if (c <= 15)
    {
        uniform_int_distribution<int> valDist1(7450, 7500);

        if (c == 0)
        {
            // N = 1 (น้อยที่สุด)
            n = 1;
            b.push_back(valDist1(gen));
        }
        else if (c == 1)
        {
            // N = 2 ตัวเลขซ้ำ
            n = 2;
            int val = valDist1(gen);
            b = {val, val};
        }
        else if (c == 2)
        {
            // N = 100 (Max ของ Subtask 1) ตัวเลขซ้ำกันทั้งหมด
            n = 100;
            int val = valDist1(gen);
            b.assign(n, val);
        }
        else if (c == 3)
        {
            // N = 100 สลับคู่เป๊ะๆ a, b, a, b...
            n = 100;
            int v1 = valDist1(gen), v2 = valDist1(gen);
            while (v1 == v2)
                v2 = valDist1(gen);
            for (int i = 0; i < n; i++)
                b.push_back((i % 2 == 0) ? v1 : v2);
        }
        else if (c == 4)
        {
            // N = 100 ไม่ซ้ำกันเลย
            n = 100;
            for (int i = 1; i <= n; i++)
                b.push_back(i);
        }
        else if (c >= 5 && c <= 10)
        {
            // N สุ่ม 50-100 แต่สุ่มตัวเลขกลุ่มเล็กๆ เพื่อให้มีเลขซ้ำเยอะ (ช่วยดักลอจิก DP)
            uniform_int_distribution<int> nDist(50, 100);
            uniform_int_distribution<int> smallVal(10, 20);
            n = nDist(gen);
            for (int i = 0; i < n; i++)
                b.push_back(smallVal(gen));
        }
        else
        {
            // N สุ่ม 90-100 สุ่มตัวเลขทั่วไปกระจายๆ กันเต็มแม็กซ์ Subtask 1
            uniform_int_distribution<int> nDist(90, 100);
            n = nDist(gen);
            for (int i = 0; i < n; i++)
                b.push_back(valDist1(gen));
        }
    }
    // ==========================================
    // Subtask 2 (20 Point): Testcase 16 - 19
    // Constraints: 1 <= n <= 4,000 และ 1 <= bi <= 1,000,000
    // ==========================================
    else
    {
        uniform_int_distribution<int> valDist2(999900, 1000000);
        
        if (c == 16)
        {
            // N = 4000 ตัวเลขเหมือนกันหมด
            n = 3000;
            int val = valDist2(gen);
            for (int i = 1; i <= 1000; i++)
            {
                b.push_back(valRan1m(gen));
            }
            for (int i = 0; i <= 3000; i++)
            {
                b .push_back(val);
            }
            n += 1000;
        }
        else if (c == 17)
        {
            // N = 4000 สลับคู่ 2 ตัวเลข
            n = 3000;
            for (int i = 1; i <= 1000; i++)
            {
                b.push_back(valRan1m(gen));
            }
            int v1 = valDist2(gen), v2 = valDist2(gen);
            while (v1 == v2)
            v2 = valDist2(gen);
            for (int i = 0; i < n; i++)
            b.push_back((i % 2 == 0) ? v1 : v2);
            n += 1000;
        }
        else if (c == 18)
        {
            // N = 4000 ตัวเลขซ้ำกันเป็นกลุ่ม (Highly Repetitive)
            n = 3000;
            for (int i = 1; i <= 1000; i++)
            {
                b.push_back(valRan1m(gen));
            }
            int pool_size = 15; // มีตัวเลขแค่ 15 แบบหมุนเวียนกัน
            vector<int> pool(pool_size);
            for (int i = 0; i < pool_size; i++)
                pool[i] = valDist2(gen);
            uniform_int_distribution<int> idxDist(0, pool_size - 1);

            for (int i = 0; i < n; i++)
                b.push_back(pool[idxDist(gen)]);
            n += 1000;
        }
        else
        {
            // N = 4000 สุ่มแบบเต็มข้อไร้ขีดจำกัด (Ultimate Stress Test)
            n = 3000;
            for (int i = 1; i <= 1000; i++)
            {
                b.push_back(valRan1m(gen));
            }
            for (int i = 0; i < n; i++)
                b.push_back(valDist2(gen));
            n += 1000;
        }
    }

    // เขียนลงไฟล์
    fout << n << "\n";
    for (int i = 0; i < n; i++)
    {
        fout << b[i] << (i == n - 1 ? "" : " ");
    }
    fout << "\n";
    fout.close();
}

int main()
{
    // สร้าง Testcases รวม 20 ไฟล์ (0 - 19)
    for (int i = 0; i <= 19; i++)
    {
        geninput("./input/input" + to_string(i) + ".in", i);
    }
    cout << "Generated 20 Testcases for Grader successfully!" << "\n";
    return 0;
}