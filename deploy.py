import os
import subprocess

def build_and_run_project():
    # Проверяем, собран ли проект
    if not os.path.exists("build"):
        os.mkdir("build")

    # Переходим в папку build
    os.chdir("build")

    # Запускаем cmake
    if not os.path.exists("CMakeCache.txt"):
        subprocess.run(["cmake", ".."])

    # Собираем проект
    subprocess.run(["make"])

    # Запускаем исполняемый файл
    subprocess.run(["./calc"])

if __name__ == "__main__":
    build_and_run_project()