#include <bits/stdc++.h>
#include <sys/stat.h> // สำหรับสร้างโฟลเดอร์
using namespace std;

void geninput(string filename, int tc_num)
{
    ofstream fout(filename);
    random_device rd;
    mt19937 gen(rd());

    int N, K;
    vector<int> A;

    // แบ่งเงื่อนไขตาม Subtask
    if (tc_num == 0) {
        // Example 1: N=5, K=1
        N = 5; K = 1;
        A = {2, 7, 9, 3, 1};
    } 
    else if (tc_num == 1) {
        // Example 2: N=5, K=2 (Greedy Trap)
        N = 5; K = 2;
        A = {40, 10, 50, 10, 40};
    } 
    else if (tc_num <= 3) {
        // Subtask 1: N <= 20
        uniform_int_distribution<int> ranN(5, 20);
        N = ranN(gen);
        
        if (tc_num == 2) K = uniform_int_distribution<int>(0, N/2)(gen);
        if (tc_num == 3) K = N; // Edge case: K = N
    } 
    else if (tc_num <= 6) {
        // Subtask 2: N <= 1000
        uniform_int_distribution<int> ranN(500, 1000);
        N = ranN(gen);
        
        if (tc_num == 4) K = 0; // Free for all (K=0)
        if (tc_num == 5) K = uniform_int_distribution<int>(10, 100)(gen);
        if (tc_num == 6) K = uniform_int_distribution<int>(5, 50)(gen); // เดี๋ยวบังคับให้ติดลบหมด
    } 
    else {
        // Subtask 3: N <= 100000
        N = 100000;
        if (tc_num == 7) K = 1; // Small K
        if (tc_num == 8) K = uniform_int_distribution<int>(10000, 50000)(gen); // Large K
        if (tc_num == 9) K = 100000; // Max edge case
    }

    // สร้าง Array A ถ้ายังไม่ได้กำหนดค่า (จาก Example)
    if (A.empty()) {
        A.resize(N);
        uniform_int_distribution<int> ranA(-10000, 10000);
        uniform_int_distribution<int> ranNeg(-10000, -1);
        
        for (int i = 0; i < N; ++i) {
            if (tc_num == 6) {
                // บังคับให้เป็นค่าติดลบทั้งหมดเพื่อเช็คว่าโค้ดตอบ 0 ไหม
                A[i] = ranNeg(gen);
            } else {
                A[i] = ranA(gen);
            }
        }
    }

    // เขียนลงไฟล์
    fout << N << " " << K << "\n";
    for (int i = 0; i < N; ++i) {
        fout << A[i] << (i == N - 1 ? "" : " ");
    }
    fout << "\n";
    
    fout.close();
}

int main()
{
    // สร้างโฟลเดอร์ input อัตโนมัติ (เผื่อลืมสร้าง)
    system("mkdir -p input");
    system("mkdir -p output");

    cout << "Generating Smart Test Cases for Volatile Crystal Mines...\n";
    for (int i = 0; i <= 9; i++)
    {
        cout << " -> Generating input" << i << ".in\n";
        geninput("input/input" + to_string(i) + ".in", i);
    }
    cout << "Done! Covered all Subtasks constraints.\n";
    
    return 0;
}

/*
วิธีรันเพื่อสร้างไฟล์ Output (สมมติว่าไฟล์เฉลยชื่อ sol.cpp):

1. คอมไพล์ไฟล์เฉลย:
   g++ -O3 sol.cpp -o sol

2. รันสคริปต์ Bash เพื่อสร้างไฟล์ output:
   mkdir -p output
   bash -c 'for i in {0..9}; do ./sol < "input/input$i.in" > "output/output$i.out"; done'
*/