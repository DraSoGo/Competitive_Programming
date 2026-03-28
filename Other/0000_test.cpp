#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18; // ใช้ค่าอนันต์ที่ใหญ่พอสำหรับผลรวมของ w

// โครงสร้างสำหรับเก็บข้อมูลใน Priority Queue
struct State {
    long long dist;
    int u;
    int blinks;
    
    // overloading operator สำหรับ Min-Heap (ค่าน้อยอยู่บน)
    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

int main() {
    // ปรับปรุงประสิทธิภาพ I/O ตามคำแนะนำ
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, e, m, dest_i, k;
    if (!(cin >> n >> e >> m >> dest_i >> k)) return 0;

    // กราฟเก็บคู่ {จุดหมาย, น้ำหนัก}
    vector<vector<pair<int, long long>>> graph(n + 1);
    for (int j = 0; j < e; ++j) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // ถนนสองทาง (Undirected Graph)
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<int> wizards(m);
    for (int j = 0; j < m; ++j) {
        cin >> wizards[j];
    }

    // dist[node][blinks] = ระยะทางสั้นที่สุดจาก dest_i ไปยัง node โดยใช้ blink ไปแล้ว blinks ครั้ง
    vector<vector<long long>> dist(n + 1, vector<long long>(k + 1, INF));
    priority_queue<State, vector<State>, greater<State>> pq;

    // เริ่มต้น Dijkstra จากเมืองเส้นชัย (dest_i)
    dist[dest_i][0] = 0;
    pq.push({0, dest_i, 0});

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        long long d = curr.dist;
        int u = curr.u;
        int b = curr.blinks;

        // ถ้าพบเส้นทางที่ดีกว่าในตารางแล้ว ให้ข้าม (Lazy Deletion)
        if (d > dist[u][b]) continue;

        // เดินทางไปยังเมืองรอบข้าง
        for (auto& edge : graph[u]) {
            int v = edge.first;
            long long w = edge.second;

            // กรณีที่ 1: เดินทางปกติ (ไม่ใช้สกิล)
            if (dist[v][b] > d + w) {
                dist[v][b] = d + w;
                pq.push({dist[v][b], v, b});
            }

            // กรณีที่ 2: ใช้สกิล Blink (ระยะทางเส้นนี้กลายเป็น 0)
            if (b < k && dist[v][b + 1] > d) {
                dist[v][b + 1] = d;
                pq.push({dist[v][b + 1], v, b + 1});
            }
        }
    }

    // หาเวลาที่น้อยที่สุดในบรรดานักเวทย์ทั้งหมด
    long long min_time = INF;
    vector<int> winners;

    for (int start_city : wizards) {
        long long best_time_for_this_wizard = INF;
        // หาเวลาที่ดีที่สุดจากการใช้สกิลตั้งแต่ 0 ถึง k ครั้ง
        for (int b = 0; b <= k; ++b) {
            best_time_for_this_wizard = min(best_time_for_this_wizard, dist[start_city][b]);
        }
        
        if (best_time_for_this_wizard < min_time) {
            // ถ้าน้อยกว่าสถิติเดิม ให้เริ่มล้างรายชื่อผู้ชนะใหม่
            min_time = best_time_for_this_wizard;
            winners.clear();
            winners.push_back(start_city);
        } else if (best_time_for_this_wizard == min_time) {
            // ถ้าเวลาเท่ากับสถิติที่ดีที่สุด ให้เพิ่มเข้าไปในรายชื่อ
            winners.push_back(start_city);
        }
    }

    // เรียงลำดับเมืองตามโจทย์สั่งและลบตัวซ้ำ (เผื่อมีคนเริ่มที่เมืองเดียวกัน)
    sort(winners.begin(), winners.end());
    winners.erase(unique(winners.begin(), winners.end()), winners.end());

    // แสดงผล
    for (int j = 0; j < winners.size(); ++j) {
        cout << winners[j] << (j == winners.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}