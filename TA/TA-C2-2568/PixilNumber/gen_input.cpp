#include <bits/stdc++.h>
using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void geninput(string filename, int tc_num)
{
    ofstream fout(filename);
    random_device rd;
    mt19937 gen(rd());

    int n_min, n_max, q_min, q_max, color_max;

    // กำหนดขอบเขตตามความยาก
    if (tc_num < 2) {
        n_min = 5; n_max = 20;
        q_min = 5; q_max = 50;
        color_max = 5;
    } else if (tc_num < 7) {
        n_min = 50; n_max = 200;
        q_min = 100; q_max = 5000;
        color_max = 50;
    } else {
        n_min = 500; n_max = 1000;
        q_min = 50000; q_max = 100000;
        color_max = 500;
    }

    uniform_int_distribution<int> ranN(n_min, n_max);
    uniform_int_distribution<int> ranQ(q_min, q_max);

    int N = ranN(gen);
    int Q = ranQ(gen);

    if (tc_num == 9) { // บังคับเคสสุดท้ายให้ใหญ่สุด
        N = 1000;
        Q = 100000;
    }

    // 1. สร้าง Grid แบบเป็นกลุ่มก้อน (วาดสี่เหลี่ยมทับๆ กัน)
    vector<vector<int>> grid(N, vector<int>(N));
    uniform_int_distribution<int> ranColor(1, color_max);
    
    int bg_color = ranColor(gen);
    for(int i=0; i<N; ++i) 
        for(int j=0; j<N; ++j) 
            grid[i][j] = bg_color;

    int num_rects = (N * N) / 20; // จำนวนสี่เหลี่ยมที่จะวาด
    if (num_rects == 0) num_rects = 5;
    
    for(int r = 0; r < num_rects; ++r) {
        int w = uniform_int_distribution<int>(1, max(1, N/4))(gen);
        int h = uniform_int_distribution<int>(1, max(1, N/4))(gen);
        int y = uniform_int_distribution<int>(0, max(0, N-h))(gen);
        int x = uniform_int_distribution<int>(0, max(0, N-w))(gen);
        int c = ranColor(gen);
        for(int i = y; i < y+h; ++i) {
            for(int j = x; j < x+w; ++j) {
                grid[i][j] = c;
            }
        }
    }

    // 2. ใช้ BFS หา Connected Components ของแต่ละสี
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    map<int, vector<pair<int,int>>> color_components;

    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            if(!visited[i][j]) {
                int c = grid[i][j];
                // เก็บพิกัด 1 จุด ตัวแทนของกลุ่มนี้
                color_components[c].push_back({i, j}); 
                
                // กระจาย BFS เพื่อ Mark visited
                queue<pair<int,int>> q_bfs;
                q_bfs.push({i, j});
                visited[i][j] = true;
                while(!q_bfs.empty()) {
                    auto [cy, cx] = q_bfs.front(); 
                    q_bfs.pop();
                    for(int d=0; d<4; ++d) {
                        int ny = cy + dy[d], nx = cx + dx[d];
                        if(ny>=0 && ny<N && nx>=0 && nx<N && !visited[ny][nx] && grid[ny][nx] == c) {
                            visited[ny][nx] = true;
                            q_bfs.push({ny, nx});
                        }
                    }
                }
            }
        }
    }

    // 3. จัดเตรียมคำสั่ง Q (รับประกันการระบายสีครบ)
    vector<pair<int,int>> queries;
    vector<int> colors_present;
    for(auto const& [color, coords] : color_components) {
        colors_present.push_back(color);
    }
    
    // สุ่มลำดับสีที่จะถูกล็อคเป้าให้ระบายครบ
    shuffle(colors_present.begin(), colors_present.end(), gen);

    int target_full_colors = max(1, (int)colors_present.size() / 3); // อยากให้ระบายครบสัก 30% ของสีที่มี
    
    for(int i=0; i<colors_present.size(); ++i) {
        int c = colors_present[i];
        // ถ้าจำนวนครั้งที่ต้องคลิก (จำนวนกลุ่ม) รวมกับของเดิม ไม่เกิน Q ให้คลิกสีนี้ให้ครบทุกกลุ่ม
        if(queries.size() + color_components[c].size() <= Q && target_full_colors > 0) {
            for(auto const& p : color_components[c]) {
                queries.push_back(p);
            }
            target_full_colors--;
        }
    }

    // 4. ถ้าโควต้า Q ยังเหลือ ให้สุ่มพิกัดมั่วๆ ใส่เข้าไปให้ครบ
    uniform_int_distribution<int> ranCoord(0, N-1);
    while(queries.size() < Q) {
        queries.push_back({ranCoord(gen), ranCoord(gen)});
    }

    // ถ้าเกินก็ตัดออก (เผื่อไว้กรณี Q น้อยมาก)
    if(queries.size() > Q) queries.resize(Q);

    // สุ่มลำดับการคลิกเพื่อไม่ให้นักเรียนจับทางได้
    shuffle(queries.begin(), queries.end(), gen);

    // 5. พิมพ์ลงไฟล์
    fout << N << " " << Q << "\n";
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            fout << grid[i][j] << (j == N-1 ? "" : " ");
        }
        fout << "\n";
    }
    for(int i=0; i<Q; ++i) {
        fout << queries[i].first << " " << queries[i].second << "\n";
    }
    
    fout.close();
}

int main()
{

    cout << "Generating Smart Test Cases...\n";
    for (int i = 0; i <= 9; i++)
    {
        cout << " -> Generating input" << i << ".in\n";
        geninput("./input/input" + to_string(i) + ".in", i);
    }
    cout << "Done! Guaranteed non-zero for 3rd answer.\n";
    
    return 0;
}
//chmod +x pixilnumber
//bash -c 'for i in {0..9}; do ./pixilnumber < "input/input$i.in" > "output/output$i.out"; done'