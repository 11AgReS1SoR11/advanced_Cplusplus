import os
import subprocess

def build_and_run_project():

    if not os.path.exists("build"):
        os.mkdir("build")

    os.chdir("build")

    # Run cmake
    if not os.path.exists("CMakeCache.txt"):
        subprocess.run(["cmake", "../Calculator"])

    # Build the project
    subprocess.run(["cmake", "--build", "."])

    # Run the executable file
    subprocess.run(["./calc"])

def run_tests():
    # in future tests will build separate
    subprocess.run(["./ut/tests"])

if __name__ == "__main__":
    build_and_run_project()
    run_tests()