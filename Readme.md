XMLResurce Project

Features

individually stores data from an xml file in the form of a tree, which can be iterated

Requirements

Before using the XMLResurce project, ensure that the following software is installed on your system: CMake g++ Python interpreter

Usage

Clone the Calculator project repository: git clone https://github.com/11AgReS1SoR11/advanced_Cplusplus.git 
Run the Python script to build and execute the project: 'doit run'
Create an instance of the Calculator class and pass a mathematical expression to it as a string:
    auto XMLres = XMLResuorce::create("path");
returns a unique_ptr to data from an xml file in the form of a tree that can be iterated over

Testing

The project includes a comprehensive suite of test cases using the Catch2 testing framework. You can run the tests by executing the following command: 'doit run_tests'

Author

Basalaev Daniil Alexsandrovich 5030102/10201 (basalaev.da@edu.spbstu.ru)

Enjoy using the XMLResurce project!