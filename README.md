Чтобы запустить убедитесь, что у вас есть интерпритатор питона и введите команду 'doit run', а чтобы запустить тесты 'doit run_tests' (а чтобы просто собрать 'doit build')
Иначе перейдите в папку Project и введите:
mkdir build
cd build
cmake ../Project
cmake --build .
./Project
./tests
