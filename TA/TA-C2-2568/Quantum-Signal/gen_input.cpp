#include <bits/stdc++.h>
using namespace std;

// สร้าง Random Generator (ใช้ mt19937_64 เพื่อรองรับตัวเลขขนาดใหญ่ถึง 10^9 ได้ดี)
mt19937_64 rng(1337); // กำหนด Seed คงที่เพื่อให้สุ่มกี่ครั้งก็ได้ผลเหมือนเดิม (ถ้าอยากสุ่มเปลี่ยนเรื่อยๆ ให้ใช้ random_device)

long long rand_int(long long l, long long r) {
    if (l > r) swap(l, r);
    uniform_int_distribution<long long> dist(l, r);
    return dist(rng);
}

// ฟังก์ชันสำหรับสร้างชุดข้อมูล 1 ชุดย่อย (1 Test case)
void gen_testcase(ofstream &fout, int n, int type) {
    fout << n << "\n";
    long long max_val = 1e9;

    if (type == 0) {
        // [Type 0] Completely Random
        for (int i = 0; i < n; i++) {
            long long l = rand_int(1, max_val);
            long long r = rand_int(l, max_val);
            fout << l << " " << r << "\n";
        }
    } 
    else if (type == 1) {
        // [Type 1] All identical segments (Edge Case)
        long long l = rand_int(1, max_val / 2);
        long long r = rand_int(l, max_val);
        for (int i = 0; i < n; i++) {
            fout << l << " " << r << "\n";
        }
    } 
    else if (type == 2) {
        // [Type 2] One giant segment covers all others (Edge Case)
        fout << 1 << " " << max_val << "\n"; // Giant segment
        for (int i = 1; i < n; i++) {
            long long l = rand_int(2, max_val - 1);
            long long r = rand_int(l, max_val - 1);
            fout << l << " " << r << "\n";
        }
    } 
    else if (type == 3) {
        // [Type 3] Clustered Left and Right (Edge Case)
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) { // Left cluster
                long long l = rand_int(1, 1000);
                long long r = rand_int(l, 2000);
                fout << l << " " << r << "\n";
            } else { // Right cluster
                long long l = rand_int(max_val - 2000, max_val - 1000);
                long long r = rand_int(l, max_val);
                fout << l << " " << r << "\n";
            }
        }
    }
    else {
        // [Type 4] Very short segments / Points (Edge Case l == r)
        for (int i = 0; i < n; i++) {
            long long l = rand_int(1, max_val);
            long long r = l + rand_int(0, 5); // Length 0 to 5
            fout << l << " " << r << "\n";
        }
    }
}

// ฟังก์ชันสร้างไฟล์ Input 1 ไฟล์
void geninput(string filename, int file_idx) {
    ofstream fout(filename);

    int max_sum_n, max_n_per_case, max_q;
    
    // ตั้งค่าตาม Subtask
    if (file_idx < 4) {
        // Subtask 1: n <= 1000, sum(n) <= 5000
        max_sum_n = 5000;
        max_n_per_case = 1000;
        max_q = 5000;
    } else {
        // Subtask 2: n <= 200000, sum(n) <= 200000
        max_sum_n = 200000;
        max_n_per_case = 200000;
        max_q = 10000;
    }

    // สุ่มสร้างจำนวน N ในแต่ละ Testcase จนกว่าจะใกล้เต็ม Quota sum(N)
    vector<int> n_list;
    int current_sum = 0;
    
    // เลือกลักษณะของไฟล์ (เช่น ไฟล์แรกๆ ของ subtask ให้ q เยอะๆ n น้อยๆ)
    if (file_idx == 0 || file_idx == 4) {
        // Many Q, Small N
        while (current_sum < max_sum_n && n_list.size() < max_q) {
            int n = rand_int(1, 10);
            if (current_sum + n > max_sum_n) break;
            n_list.push_back(n);
            current_sum += n;
        }
    } else if (file_idx == 1 || file_idx == 5) {
        // One big Q (Maximum N possible)
        int n = min(max_sum_n, max_n_per_case);
        n_list.push_back(n);
    } else {
        // Random mix of Q and N
        while (current_sum < max_sum_n && n_list.size() < max_q) {
            int max_possible = min((int)rand_int(1, max_n_per_case / 10 + 1), max_sum_n - current_sum);
            if (max_possible <= 0) break;
            int n = rand_int(1, max_possible);
            n_list.push_back(n);
            current_sum += n;
        }
    }

    // เขียนจำนวน Test cases (Q)
    fout << n_list.size() << "\n";

    // สลับลำดับ n_list แบบสุ่ม
    shuffle(n_list.begin(), n_list.end(), rng);

    // เขียนแต่ละ Test Case ลงไฟล์
    for (int n : n_list) {
        // สุ่มเลือกว่าจะใช้รูปแบบ Test Case แบบไหน (0-4)
        int type;
        if (n == 1) type = 0; // ถ้ามีต้นเดียว ใช้สุ่มปกติ
        else {
            int roll = rand_int(1, 100);
            if (roll <= 50) type = 0;      // 50% Random
            else if (roll <= 60) type = 1; // 10% Identical
            else if (roll <= 70) type = 2; // 10% Giant covers all
            else if (roll <= 85) type = 3; // 15% Clustered left-right
            else type = 4;                 // 15% Short/Points
        }
        gen_testcase(fout, n, type);
    }

    fout.close();
    cout << "Generated " << filename << " (Q = " << n_list.size() << ", Sum N = " << current_sum << ")\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // สร้างไฟล์ 10 ไฟล์ (0 ถึง 9)
    // 0-3 เป็นของ Subtask 1
    // 4-9 เป็นของ Subtask 2
    for (int i = 0; i <= 9; i++) {
        string filename = "./input/input" + to_string(i) + ".in";
        geninput(filename, i);
    }

    cout << "All testcases generated successfully!\n";
    return 0;
}