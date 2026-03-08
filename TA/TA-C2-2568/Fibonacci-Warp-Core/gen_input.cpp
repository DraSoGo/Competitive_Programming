#include <bits/stdc++.h>
using namespace std;

vector<long long> fibs;

// ฟังก์ชันสร้างเลขฟีโบนัชชีล่วงหน้าเก็บไว้ใน Array (ถึงประมาณ 10^18)
void precompute() {
    fibs.push_back(1);
    fibs.push_back(2);
    while (true) {
        long long next_f = fibs[fibs.size() - 1] + fibs[fibs.size() - 2];
        if (next_f > 1000000000000000000LL) { // ถ้าเกิน 10^18 ให้หยุด
            fibs.push_back(next_f); 
            break;
        }
        fibs.push_back(next_f);
    }
}

void geninput(string filename, int tc_num) {
    ofstream fout(filename);
    random_device rd;
    // สำคัญมาก! ต้องใช้ mt19937_64 สำหรับสุ่มเลขระดับ 10^18
    mt19937_64 gen(rd()); 

    long long t_min, t_max, k_min, k_max;

    // แบ่งตาม Subtask
    if (tc_num < 2) {
        // Subtask 1: (20%) T <= 10, K <= 10^4
        t_min = 1; t_max = 10;
        k_min = 1; k_max = 10000LL;
    } else if (tc_num < 5) {
        // Subtask 2: (30%) T <= 10^4, K <= 10^9
        t_min = 1000; t_max = 10000;
        k_min = 1; k_max = 1000000000LL;
    } else {
        // Subtask 3: (50%) T <= 10^5, K <= 10^18
        t_min = 50000; t_max = 100000;
        k_min = 1; k_max = 1000000000000000000LL; 
    }

    uniform_int_distribution<long long> ranT(t_min, t_max);
    long long T = ranT(gen);

    // บังคับให้ Test case ตัวสุดท้ายของแต่ละ Subtask เป็น Worst Case เสมอ (เพื่อเทส Time Limit)
    if (tc_num == 1 || tc_num == 4 || tc_num == 9) {
        T = t_max;
    }

    fout << T << "\n";

    uniform_int_distribution<long long> ranK(1, k_max);
    uniform_int_distribution<int> ranType(1, 10);
    uniform_int_distribution<int> ranFib(0, fibs.size() - 1);

    for (int i = 0; i < T; i++) {
        long long K;
        int type = ranType(gen);
        
        // ดักเคสพิเศษ: ข้อแรกของไฟล์ Worst case ให้เป็นค่า K สูงสุดไปเลย
        if (i == 0 && (tc_num == 1 || tc_num == 4 || tc_num == 9)) {
            K = k_max; 
        } 
        else if (type <= 6) {
            // โอกาส 60% สุ่มเลขมั่วๆ ทั่วไป
            K = ranK(gen);
        } 
        else if (type <= 8) {
            // โอกาส 20% สุ่มให้ตรงกับเลขฟีโบนัชชีเป๊ะๆ (คำตอบต้องเป็น 1)
            K = fibs[ranFib(gen)];
            while (K > k_max) K = fibs[ranFib(gen)]; 
        } 
        else {
            // โอกาส 20% สุ่มให้เป็นผลรวมของฟีโบนัชชี 2-4 ตัว
            K = 0;
            int terms = uniform_int_distribution<int>(2, 4)(gen);
            for(int j = 0; j < terms; j++) {
                K += fibs[ranFib(gen)];
            }
            if (K > k_max || K <= 0) K = ranK(gen); // ถ้าบวกแล้วล้นขอบเขต ก็สุ่มใหม่แบบธรรมดา
        }
        
        fout << K << "\n";
    }
    fout.close();
}

int main() {
    precompute();
    system("mkdir -p input");
    system("mkdir -p output");

    cout << "Generating Test Cases for The Fibonacci Warp Core...\n";
    for (int i = 0; i <= 9; i++) {
        cout << " -> Generating input" << i << ".in\n";
        geninput("./input/input" + to_string(i) + ".in", i);
    }
    cout << "Done!\n";
    return 0;
}