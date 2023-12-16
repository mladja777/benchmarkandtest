#!/bin/python3

import subprocess
import os
import shutil

def is_benchmark_installed():
    # Common paths where libraries are installed
    common_paths = [
        "/usr/local/lib/",
        "/usr/lib/",
        "/opt/local/lib/",
        "/opt/lib/"
    ]

    # Check for the presence of Google Benchmark library files in common paths
    for path in common_paths:
        if os.path.exists(os.path.join(path, "libbenchmark.a")) or \
           os.path.exists(os.path.join(path, "libbenchmark.so")):
            return True
    return False

def install_google_benchmark():
    try:
        # Temporary directory for cloning and building Google Benchmark
        tmp_dir = "/tmp/google_benchmark_install"
        os.makedirs(tmp_dir, exist_ok=True)
        os.chdir(tmp_dir)

        # Clone the Google Benchmark repository
        subprocess.run(["git", "clone", "https://github.com/google/benchmark.git"], check=True)

        # Create a build directory
        build_dir = os.path.join(tmp_dir, "benchmark/build")
        os.makedirs(build_dir, exist_ok=True)
        os.chdir(build_dir)

        # Run CMake and build
        subprocess.run(["cmake", "..", "-DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON"], check=True)
        subprocess.run(["make"], check=True)

        # Install (might require admin/sudo rights)
        subprocess.run(["sudo", "make", "install"], check=True)

        # Clean up: Return to the original directory and remove temp directory
        os.chdir("../../..")
        shutil.rmtree(tmp_dir)

    except subprocess.CalledProcessError as e:
        print(f"An error occurred during the installation process: {e}")
        return False
    return True

def main():
    if is_benchmark_installed():
        print("Google Benchmark is already installed.")
    else:
        print("Google Benchmark is not installed. Starting installation...")
        if install_google_benchmark():
            print("Google Benchmark installed successfully.")
        else:
            print("Failed to install Google Benchmark.")

if __name__ == "__main__":
    main()
