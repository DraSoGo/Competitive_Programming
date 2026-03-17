import os
import shutil
import zipfile

# กำหนด Path ปัจจุบัน (รันสคริปต์ที่ระดับเดียวกับโฟลเดอร์โจทย์)
base_dir = '/home/drasogun/DraSoGun/OCOM/MY-CODE-CP/TA/TA-C2-2568'

# วนลูปผ่านทุกรายการในโฟลเดอร์หลัก
for problem_folder in os.listdir(base_dir):
    problem_path = os.path.join(base_dir, problem_folder)
    
    # ข้ามไฟล์ที่ไม่ใช่โฟลเดอร์ (เช่นข้ามไฟล์ .py หรือ .pdf)
    if not os.path.isdir(problem_path):
        continue
        
    # testcase_path = os.path.join(problem_path, 'testcase')
    input_dir = os.path.join(problem_path, 'input')
    output_dir = os.path.join(problem_path, 'output')
    # print(f"กำลังตรวจสอบโจทย์: {problem_folder} ...")
    print(f"ตรวจสอบโฟลเดอร์ input: {input_dir} ... {'พบ' if os.path.exists(input_dir) else 'ไม่พบ'}")
    print(f"ตรวจสอบโฟลเดอร์ output: {output_dir} ... {'พบ' if os.path.exists(output_dir) else 'ไม่พบ'}")
    # ตรวจสอบว่ามีโฟลเดอร์ input และ output อยู่จริงในโจทย์นี้หรือไม่
    if os.path.exists(input_dir) and os.path.exists(output_dir):
        print(f"กำลังจัดการ Testcase สำหรับโจทย์: {problem_folder} ...")
        
        # สร้างโฟลเดอร์ชั่วคราวเพื่อรวมไฟล์
        temp_folder = os.path.join(problem_path, 'cms_temp')
        os.makedirs(temp_folder, exist_ok=True)
        
        # ทำการคัดลอกและเปลี่ยนชื่อไฟล์จาก 0-9 เป็น 1-10
        for i in range(10):
            old_in = os.path.join(input_dir, f'input{i}.in')
            old_out = os.path.join(output_dir, f'output{i}.out')
            
            new_in = os.path.join(temp_folder, f'{i+1}.in')
            new_out = os.path.join(temp_folder, f'{i+1}.sol')
            
            # ถ้ามีไฟล์ input อยู่ ให้ copy ไปที่ใหม่
            if os.path.exists(old_in):
                shutil.copy2(old_in, new_in)
            
            # ถ้ามีไฟล์ output อยู่ ให้ copy ไปที่ใหม่ และเปลี่ยนนามสกุลเป็น .sol
            if os.path.exists(old_out):
                shutil.copy2(old_out, new_out)
                
        # สร้างไฟล์ ZIP ชื่อ cms_testcase.zip ภายในโฟลเดอร์โจทย์นั้นๆ
        zip_path = os.path.join(problem_path, 'cms_testcase.zip')
        
        with zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
            # วนลูปเอาไฟล์ที่เพิ่งสร้างในโฟลเดอร์ temp ยัดลง zip
            for file_name in os.listdir(temp_folder):
                file_path = os.path.join(temp_folder, file_name)
                # arcname=file_name เพื่อให้ไฟล์อยู่ในระดับ root ของ zip (ไม่ต้องซ้อนโฟลเดอร์)
                zipf.write(file_path, arcname=file_name)
                
        # ลบโฟลเดอร์ชั่วคราวทิ้งหลังจากการ Zip เสร็จสิ้น
        shutil.rmtree(temp_folder)
        
        print(f"✅ สร้างไฟล์สำเร็จ: {zip_path}")

print("เสร็จสิ้นการทำงานทั้งหมดแล้วครับ!")