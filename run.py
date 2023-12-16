#!/bin/python3

import subprocess
import sys
import shutil
import os

def clean_and_generate():
    # Check if the build directory exists
    if os.path.exists("build/"):
        # Remove the build directory
        shutil.rmtree("build/")
    # Run CMake
    subprocess.run(["cmake", "-S", ".", "-B", "build/"], check=True)

def build():
    # Run CMake to generate and build the project
    subprocess.run(["cmake", "--build", "build/", "--config", "Debug"], check=True)

def run_application(mode):
    # Run the specified application
    app_path = f"bins/{mode}"
    subprocess.run([app_path], check=True)

def main():
    try:
        # Determine modes to run based on arguments
        modes = [arg for arg in sys.argv[1:] if arg != "--clean"]
        if not modes:
            modes = ["benchmark", "test"]

        # Clean build if --clean is specified
        if "--clean" in sys.argv:
            clean_and_generate()

        build()

        # Run applications
        for mode in modes:
            if mode in ["benchmark", "test"]:
                run_application(mode)
            else:
                print(f"Invalid mode: {mode}")

    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
