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

def build_and_run_tests():
    if not os.path.exists("build"):
        os.mkdir("build")

    os.chdir("build")

    # Run cmake
    if not os.path.exists("CMakeCache.txt"):
        subprocess.run(["cmake", "../Calculator/ut"])

    # Build the project
    subprocess.run(["cmake", "--build", "."])

    # Run the executable file
    subprocess.run(["./ut/tests"])

if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("Usage: python deploy.py <command>")
        sys.exit(1)

    command = sys.argv[1]

    if command == "run":
        build_and_run_project()
    elif command == "run_tests":
        build_and_run_tests()
    else:
        print("Unknown command:", command)
        sys.exit(1)