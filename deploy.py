import os
import subprocess


def build_project():
    if not os.path.exists("build"):
        os.mkdir("build")

    os.chdir("build")

    # Run cmake
    if not os.path.exists("CMakeCache.txt"):
        subprocess.run(["cmake", "../Project"])

    # Build the project
    subprocess.run(["cmake", "--build", "."])


def run_tests():
    os.chdir("tests")
    subprocess.run(["./tests"])


def run_project():
    os.chdir("src")
    subprocess.run(["./project"])


if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("Usage: python deploy.py <command>")
        sys.exit(1)

    command = sys.argv[1]

    if command == "build":
        build_project()
    elif command == "run":
        build_project()
        run_project()
    elif command == "run_tests":
        build_project()
        run_tests()
    else:
        print("Unknown command:", command)
        sys.exit(1)