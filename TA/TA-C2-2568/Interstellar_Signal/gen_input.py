import os
import random
import string

def solve(strings):
    """ฟังก์ชันเฉลย: รับ list ของสตริง คืนค่าคำตอบที่ถูกต้อง"""
    freq = {}
    max_freq = 0
    for s in strings:
        # เรียงตัวอักษรเพื่อใช้เป็น Key ใน Dictionary
        sorted_s = "".join(sorted(s))
        freq[sorted_s] = freq.get(sorted_s, 0) + 1
        if freq[sorted_s] > max_freq:
            max_freq = freq[sorted_s]
    return max_freq

def generate_query(t, n):
    """สร้างข้อมูล 1 ชุดทดสอบ (t สัญญาณ, ความยาว n)"""
    # กำหนดจำนวนต้นแบบ (Base Patterns) เพื่อให้มั่นใจว่าจะมีข้อมูลซ้ำกันให้จับคู่
    # ยิ่ง t เยอะ จะยิ่งมีต้นแบบเยอะ เพื่อไม่ให้คำตอบกระจุกอยู่ที่เดียว
    max_bases = max(1, min(t // 2, 1000))
    num_bases = random.randint(1, max_bases)
    
    # สร้างแพทเทิร์นต้นแบบ
    base_patterns = []
    for _ in range(num_bases):
        base = random.choices(string.ascii_lowercase, k=n)
        base_patterns.append(base)
        
    strings = []
    for _ in range(t):
        # สุ่มหยิบต้นแบบมา 1 อัน
        base = random.choice(base_patterns)
        # สลับตำแหน่งตัวอักษร
        shuffled = list(base)
        random.shuffle(shuffled)
        strings.append("".join(shuffled))
        
    ans = solve(strings)
    return strings, ans

def main():
    # สร้างโฟลเดอร์สำหรับเก็บไฟล์
    os.makedirs("testcases", exist_ok=True)
    
    # กำหนดโครงสร้างของ 20 ไฟล์ [ (t1, n1), (t2, n2), ... ]
    configs = [
        # --- Subtask 1 (15 คะแนน): n = 1 ---
        [(100000, 1)] * 5,  # 01.in: Q=5, t หนาแน่น
        [(50000, 1)] * 10,  # 02.in: Q=10
        [(10, 1), (100, 1), (1000, 1)], # 03.in: Q=3
        
        # --- Subtask 2 (35 คะแนน): Sum(t*n) <= 5000 ---
        [(500, 10)] * 5,    # 04.in: Q=5
        [(100, 50)] * 5,    # 05.in: Q=5
        [(10, 500)] * 5,    # 06.in: Q=5
        [(50, 10), (20, 100), (5, 500), (2, 1000)], # 07.in: Q=4 แบบผสม
        [(1000, 5)] * 1,    # 08.in: Q=1
        [(5, 1000)] * 1,    # 09.in: Q=1
        [(2, 2500)] * 2,    # 10.in: Q=2
        
        # --- Subtask 3 (50 คะแนน): Sum(t*n) <= 500,000 ---
        [(100000, 5)] * 1,  # 11.in: ดัก TLE ดัวย t มหาศาล
        [(50000, 10)] * 1,  # 12.in
        [(10000, 50)] * 1,  # 13.in
        [(1000, 500)] * 1,  # 14.in
        [(500, 1000)] * 1,  # 15.in
        [(100, 5000)] * 1,  # 16.in
        [(10, 50000)] * 1,  # 17.in
        [(5, 100000)] * 1,  # 18.in: ดักคนทำ String manipulation ไม่ดี
        [(25000, 4)] * 5,   # 19.in: Q=5
        # 20.in: รวมมิตรไล่สเกลเพื่อเช็กความเสถียร
        [(100000, 1), (10000, 10), (1000, 100), (100, 1000), (10, 10000), (5, 20000)] 
    ]
    
    print("เริ่มสร้าง Testcase 20 ไฟล์...")
    
    for file_idx, queries in enumerate(configs, start=1):
        in_filename = f"testcases/{file_idx:02d}.in"
        out_filename = f"testcases/{file_idx:02d}.out"
        
        with open(in_filename, "w") as fin, open(out_filename, "w") as fout:
            q = len(queries)
            fin.write(f"{q}\n")
            
            for t, n in queries:
                fin.write(f"{t} {n}\n")
                strings, ans = generate_query(t, n)
                
                for s in strings:
                    fin.write(f"{s}\n")
                
                fout.write(f"{ans}\n")
                
        print(f"สร้าง {in_filename} และ {out_filename} สำเร็จ!")
        
    print("\nสร้าง Testcase ทั้งหมด 20 ไฟล์เสร็จสมบูรณ์ อยู่ในโฟลเดอร์ 'testcases' ครับ!")

if __name__ == "__main__":
    main()