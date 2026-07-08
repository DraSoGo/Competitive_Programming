import os
import shutil

def process_problem(problem_path, testcase_subdir='testcase'):
    # Prepare base paths
    base_dir = problem_path
    testcase_dir = os.path.join(base_dir, testcase_subdir)
    input_dir = os.path.join(base_dir, 'input')
    output_dir = os.path.join(base_dir, 'output')

    # Create input/output directories if they don't exist
    os.makedirs(input_dir, exist_ok=True)
    os.makedirs(output_dir, exist_ok=True)

    # Get all files and sort them to ensure consistent ordering
    files = sorted([f for f in os.listdir(testcase_dir) if os.path.isfile(os.path.join(testcase_dir, f))])
    
    # Process files in pairs or by extension
    # We assume naming convention like 01.in, 01.out
    
    # We'll map indices to filenames
    # For a list like 01.in, 01.out, 02.in, 02.out
    # We want to re-map them to input0.in, output0.out, input1.in, output1.out
    
    # Let's group them by the original prefix
    import collections
    groups = collections.defaultdict(dict)
    for f in files:
        prefix, ext = os.path.splitext(f)
        groups[prefix][ext] = f
    
    sorted_prefixes = sorted(groups.keys())
    
    for i, prefix in enumerate(sorted_prefixes):
        if '.in' in groups[prefix]:
            src = os.path.join(testcase_dir, groups[prefix]['.in'])
            dst = os.path.join(input_dir, f'input{i}.in')
            shutil.move(src, dst)
            print(f"Moved {src} to {dst}")
        
        if '.out' in groups[prefix]:
            src = os.path.join(testcase_dir, groups[prefix]['.out'])
            dst = os.path.join(output_dir, f'output{i}.out')
            shutil.move(src, dst)
            print(f"Moved {src} to {dst}")

# Interstellar_Signal uses 'testcases' instead of 'testcase'
process_problem('Interstellar_Signal', 'testcases')
process_problem('Magic_Tournament', 'testcase')
process_problem('Tower', 'testcase')
