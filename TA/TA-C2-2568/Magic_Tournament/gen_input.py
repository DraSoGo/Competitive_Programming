import os
import random

def generate_testcase(filename, subtask_id):
    # กำหนดโควต้าตาม Subtask
    if subtask_id <= 2: # Subtask 1: k = 0
        N, E, K = random.randint(90000, 100000), random.randint(90000, 200000), 0
    elif subtask_id <= 5: # Subtask 2: ขนาดเล็ก
        N, E, K = random.randint(800, 1000), random.randint(800, 2000), random.randint(1, 10)
    else: # Subtask 3: ขนาดใหญ่
        N, E, K = random.randint(90000, 100000), random.randint(90000, 200000), random.randint(1, 10)

    max_e = N * (N - 1) // 2
    E = min(E, max_e)
    M = random.randint(5, min(N // 2, 10000))
    
    edges, existing_edges = [], set()
    
    def add_edge(u, v, w):
        edges.append((u, v, w))
        existing_edges.add((min(u, v), max(u, v)))

    dest_node = 1
    num_winners = random.randint(2, 5) # บังคับจำนวนผู้ชนะ 2-5 คน
    branch_length = K + 3
    current_node = 2
    winners_nodes = []
    
    # ดิกชันนารีเก็บความลึก (Depth) ป้องกันการเกิดทางลัดให้สาย Blink
    nodes_by_depth = {0: [dest_node]}
    depth = {dest_node: 0}
    
    # 1. สร้างกิ่งเฉพาะกิจให้ "ผู้ชนะ" (น้ำหนักถนนน้อย)
    for i in range(num_winners):
        prev = dest_node
        for j in range(1, branch_length + 1):
            u, v, w = prev, current_node, random.randint(50, 200) # ถนนผู้ชนะใช้เวลาหลักร้อย
            add_edge(u, v, w)
            depth[v] = j
            nodes_by_depth.setdefault(j, []).append(v)
            prev = v
            current_node += 1
        winners_nodes.append(prev)
        
    # 2. สร้าง "ก้านผู้แพ้" เพื่อผลักให้คนแพ้อยู่ไกลกว่า K ก้าวเสมอ
    loser_trunk_start = current_node
    prev = dest_node
    for j in range(1, K + 2):
        u, v, w = prev, current_node, random.randint(1000000, 2000000) # ถนนหลักล้าน
        add_edge(u, v, w)
        depth[v] = j
        nodes_by_depth.setdefault(j, []).append(v)
        prev = v
        current_node += 1
    loser_trunk_end = prev
    
    # 3. สร้างกราฟที่เหลือต่อจากก้านผู้แพ้
    for i in range(current_node, N + 1):
        u = random.randint(loser_trunk_start, i - 1)
        v, w = i, random.randint(1000000, 2000000)
        add_edge(u, v, w)
        d = depth[u] + 1
        depth[v] = d
        nodes_by_depth.setdefault(d, []).append(v)
    
    # 4. เติมถนนหลอกที่เหลือ โดยห้ามข้ามเลเยอร์เกิน 1 ชั้น (ป้องกันทางลัด)
    remain_edges = E - len(edges)
    attempts = remain_edges * 3
    while remain_edges > 0 and attempts > 0:
        attempts -= 1
        d1 = random.choice(list(nodes_by_depth.keys()))
        u = random.choice(nodes_by_depth[d1])
        
        valid_d2 = [d for d in [d1 - 1, d1, d1 + 1] if d in nodes_by_depth]
        if not valid_d2: continue
        d2 = random.choice(valid_d2)
        v = random.choice(nodes_by_depth[d2])
        
        if u == v: continue
        mn, mx = min(u, v), max(u, v)
        if (mn, mx) in existing_edges: continue
        
        add_edge(u, v, random.randint(1000000, 2000000))
        remain_edges -= 1
        
    # 5. สุ่มตำแหน่งนักเวทย์ผู้แพ้ (ต้องอยู่ลึกกว่า K ก้าว)
    valid_loser_nodes = [node for node, d in depth.items() if d >= K + 1 and node not in winners_nodes]
    num_losers = min(M - num_winners, len(valid_loser_nodes))
    losers_nodes = random.sample(valid_loser_nodes, num_losers)
    
    M = num_winners + num_losers
    all_wizards = winners_nodes + losers_nodes
    
    # 6. สับเปลี่ยนหมายเลขเมืองเพื่อความเนียน
    mapping = list(range(1, N + 1))
    random.shuffle(mapping)
    real_dest = mapping[dest_node - 1]
    real_wizards = [mapping[w - 1] for w in all_wizards]
    random.shuffle(real_wizards)
    
    # 7. บันทึกไฟล์
    os.makedirs(os.path.dirname(filename), exist_ok=True)
    with open(filename, 'w') as f:
        f.write(f"{N} {E} {M} {real_dest} {K}\n")
        out_edges = [(mapping[u-1], mapping[v-1], w) for u, v, w in edges]
        random.shuffle(out_edges)
        for u, v, w in out_edges:
            if random.choice([True, False]): u, v = v, u
            f.write(f"{u} {v} {w}\n")
        f.write(" ".join(map(str, real_wizards)) + "\n")
    
    print(f"Generated {filename}: N={N}, E={E}, M={M}, K={K}, Winners={num_winners}")

if __name__ == "__main__":
    for i in range(1, 11):
        filename = f"./testcase/{i:02d}.in"
        generate_testcase(filename, i)