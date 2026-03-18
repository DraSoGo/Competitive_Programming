#include <bits/stdc++.h>
using namespace std;

void geninput(string in, int subtask_id)
{
    ofstream fout;
    fout.open(in);

    random_device rd;
    mt19937_64 gen(rd());

    int n, m;
    bool is_disconnected = (subtask_id == 9);

    if (subtask_id < 4) {
        uniform_int_distribution<int> ranN(100, 1000);
        n = ranN(gen);
        uniform_int_distribution<int> ranM(n, 2000);
        m = ranM(gen);
    } else {
        uniform_int_distribution<int> ranN(90000, 100000);
        n = ranN(gen);
        uniform_int_distribution<int> ranM(n, 200000);
        m = ranM(gen);
    }

    int split_node = n / 2;
    // กำหนดให้ 20% ของโหนด (ช่วงท้ายๆ) เป็นโหนดทางตัน (Dummy Nodes) 
    // โหนด N ยังคงเป็นปลายทางที่อยู่ในกลุ่มโหนดหลัก (Core Nodes)
    int dummy_start = n * 4 / 5; 
    
    long long max_edges;
    if (is_disconnected) {
        long long n1 = split_node;
        long long n2 = n - split_node;
        max_edges = (n1 * (n1 - 1) / 2) + (n2 * (n2 - 1) / 2);
    } else {
        max_edges = 1LL * n * (n - 1) / 2;
    }

    if (m > max_edges) m = max_edges;

    fout << n << " " << m << "\n";

    set<pair<int, int>> existing_edges;

    uniform_int_distribution<int> ranP(1, 1000000000);
    uniform_int_distribution<int> coin(0, 1);
    
    // -----------------------------------------------------------------
    // สร้าง Core Colors 5 สี แต่ให้ ID ใหญ่มาก (เช่น หลักล้านถึงพันล้าน)
    // -----------------------------------------------------------------
    vector<int> core_colors(5);
    uniform_int_distribution<int> ranColorLarge(1, 1000000000);
    for(int i = 0; i < 5; i++) {
        core_colors[i] = ranColorLarge(gen);
    }
    uniform_int_distribution<int> ranCoreC(0, 4);

    int fixed_p = ranP(gen);
    int edges_added = 0;

    // เฟส 1: สร้าง Spanning Tree
    for (int i = 2; i <= n; i++)
    {
        if (is_disconnected && i == split_node + 1) continue;

        int u = i;
        int v;
        int c, p;

        bool is_dummy = (i >= dummy_start && i < n); // i เป็น Dummy ยกเว้น n ที่เป็นปลายทาง

        if (is_dummy) {
            // โหนดทางตัน ให้เชื่อมกับโหนดหลักแบบสุ่ม (มีแค่ 1 เส้น)
            if (is_disconnected) {
                uniform_int_distribution<int> ranNode(split_node + 1, dummy_start - 1);
                v = ranNode(gen);
            } else {
                uniform_int_distribution<int> ranNode(1, dummy_start - 1);
                v = ranNode(gen);
            }
            // ใช้สี Dummy แปลกๆ ที่ไม่ซ้ำใคร และ ID ใหญ่มาก
            c = ranColorLarge(gen); 
        } else {
            // โหนดหลัก ให้เชื่อมกันเอง
            if (is_disconnected && i > split_node) {
                int max_v = min(i - 1, dummy_start - 1);
                uniform_int_distribution<int> ranNode(split_node + 1, max_v);
                v = ranNode(gen);
            } else {
                int max_v = min(i - 1, dummy_start - 1);
                uniform_int_distribution<int> ranNode(1, max_v);
                v = ranNode(gen);
            }
            // กราฟหลักใช้ Core Colors แบบสุ่ม 1 ใน 5 สี (เพื่อให้เกิด Conflict แน่นอน)
            c = core_colors[ranCoreC(gen)];
        }

        p = (subtask_id < 4) ? fixed_p : ranP(gen);
        if (coin(gen)) swap(u, v);

        fout << u << " " << v << " " << c << " " << p << "\n";
        existing_edges.insert({min(u, v), max(u, v)});
        edges_added++;
    }

    // เฟส 2: เติม Edge ที่เหลือ (ต้องเชื่อมเฉพาะระหว่าง Core Nodes เท่านั้น)
    int remain_edges = m - edges_added;
    
    // Helper function สำหรับสุ่มโหนดหลัก (รวมถึงโหนด n ด้วย)
    auto pick_core = [&](int min_val, int max_val, bool include_n) {
        if (include_n) {
            uniform_int_distribution<int> r(min_val, max_val + 1);
            int val = r(gen);
            return (val > max_val) ? n : val;
        } else {
            uniform_int_distribution<int> r(min_val, max_val);
            return r(gen);
        }
    };

    while (remain_edges > 0)
    {
        int u, v;

        if (is_disconnected) {
            if (coin(gen)) {
                u = pick_core(1, split_node, false);
                v = pick_core(1, split_node, false);
            } else {
                u = pick_core(split_node + 1, dummy_start - 1, true);
                v = pick_core(split_node + 1, dummy_start - 1, true);
            }
        } else {
            u = pick_core(1, dummy_start - 1, true);
            v = pick_core(1, dummy_start - 1, true);
        }

        if (u == v) continue;
        int mn = min(u, v);
        int mx = max(u, v);
        if (existing_edges.count({mn, mx})) continue;

        existing_edges.insert({mn, mx});

        // ใช้เฉพาะ Core Colors เท่านั้นในเส้นทางรอง
        int c = core_colors[ranCoreC(gen)];
        int p = (subtask_id < 4) ? fixed_p : ranP(gen);

        if (coin(gen)) swap(u, v);

        fout << u << " " << v << " " << c << " " << p << "\n";
        remain_edges--;
    }

    fout.close();

    cout << "Generated " << in << " : N = " << n << ", M = " << m;
    if (subtask_id < 4) cout << " [Equal P = " << fixed_p << "]";
    if (is_disconnected) cout << " [Disconnected / Ans: -1]";
    cout << "\n";
}

int main()
{
    for (int i = 0; i <= 9; i++)
    {
        string filename = "input/input" + to_string(i) + ".in";
        geninput(filename, i);
    }
    return 0;
}
// chmod +x oshi_robot
// bash -c 'for i in {0..9}; do ./oshi_robot < "input/input$i.in" > "output/output$i.out"; done'