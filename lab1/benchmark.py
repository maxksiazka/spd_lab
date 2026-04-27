#!/usr/bin/env python3
#pyright: basic
import subprocess
import re
import pandas as pd
from pathlib import Path
import tempfile
import sys
import os

# Configuration
BUILD_DIR = Path("./build")
EXECUTABLE = BUILD_DIR / "lab1"
TASK_DIR = Path("./")
ALGORITHMS = ["EDD", "ERD", "Schrage", "PreemptSchrage", "Construction", "Carlier"]
ALGORITHMS += ["LookThrough"] # comment to disable LookThrough
# TASK_FILES = [f"data/100_Independent{i:04d}" for i in range(2250)]
# TASK_FILES = [f"test_data5/task_{i}.txt" for i in range(1,51)]
# TASK_FILES = [f"test_data7/task_{i}.txt" for i in range(1,51)]
# TASK_FILES = [f"test_data9/task_{i}.txt" for i in range(1,51)]
TASK_FILES = [f"test_data12/task_{i}.txt" for i in range(1,51)]
OUTPUT_CSV = Path("./benchmark_results12.csv")

def parse_output(stdout: str):
    """Extract Lmax and elapsed time from stdout."""
    lmax_match = re.search(r"Maximum lateness \(Lmax\):\s*(\-?\d+)", stdout)
    time_match = re.search(r"Elapsed time:\s*([\d.e\-+]+)s", stdout)
    
    if not lmax_match or not time_match:
        return None, None
    
    lmax = int(lmax_match.group(1))
    elapsed_time_s = float(time_match.group(1))
    elapsed_time_ms = elapsed_time_s * 1000
    
    return lmax, elapsed_time_ms

def run_benchmark():
    """Run benchmarks and collect results."""
    results = []
    
    for idx, task_file in enumerate(TASK_FILES):
        print(f"[{idx + 1}/{len(TASK_FILES)}] Processing {task_file}...")
        row = {"Index": idx, "Task": task_file}
        
        for algo in ALGORITHMS:
            print(f"  Running {algo}...", end=" ", flush=True)
            
            try:
                with tempfile.NamedTemporaryFile(mode='w+', delete=False) as tmp:
                    result = subprocess.run(
                        [str(EXECUTABLE), algo, task_file],
                        capture_output=True,
                        text=True,
                        timeout=300
                    )
                    
                    if result.returncode != 0:
                        print(f"FAILED (exit code {result.returncode})")
                        print(f"stderr: {result.stderr}")
                        sys.exit(1)
                    
                    lmax, elapsed_time_ms = parse_output(result.stdout)
                    
                    if lmax is None or elapsed_time_ms is None:
                        print("FAILED (parse error)")
                        print(f"stdout: {result.stdout}")
                        sys.exit(1)
                    
                    row[f"{algo}_Lmax"] = lmax
                    row[f"{algo}_time"] = float( elapsed_time_ms )
                    print(f"OK (Lmax={lmax}, {elapsed_time_ms:.4f}ms)")
            
            except subprocess.TimeoutExpired:
                print("TIMEOUT")
                sys.exit(1)
            except Exception as e:
                print(f"ERROR: {e}")
                sys.exit(1)
        
        results.append(row)
    
    return results

def main():
    print("CWD: ",os.getcwd())
    if not EXECUTABLE.exists():
        print(f"Error: {EXECUTABLE} not found. Build the project first.")
        sys.exit(1)
    
    print("Starting benchmark suite...")
    results = run_benchmark()
    
    df = pd.DataFrame(results)
    df.to_csv(OUTPUT_CSV, index=False)
    print(f"\nResults saved to {OUTPUT_CSV}")
    print(df)

if __name__ == "__main__":
    main()
