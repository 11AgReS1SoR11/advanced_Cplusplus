Calculator Project

The Calculator project is a simple calculator application written in C++ that dynamically loads libraries containing implementations of various mathematical functions. It operates without unnecessary data copying and strictly uses non-owning pointers. The project includes comprehensive test cases using Catch2.


Features

Dynamically loads shared libraries (.so) containing mathematical functions.
Evaluates mathematical expressions provided as strings.
Supports user-defined mathematical functions implemented in separate libraries (sin, cos, ^).


Requirements

Before using the Calculator project, ensure that the following software is installed on your system:
CMake
g++
Python interpreter


Usage

Clone the Calculator project repository:
    git clone https://github.com/11AgReS1SoR11/advanced_Cplusplus.git
Run the Python script to build and execute the project:
    doit run
Create an instance of the Calculator class and pass a mathematical expression to it as a string:

Calculator calculator;
double result = calculator("2+3*sin(0.5)");
The Calculator will dynamically load the required mathematical functions from shared libraries and evaluate the expression.


Testing

The project includes a comprehensive suite of test cases using the Catch2 testing framework. You can run the tests by executing the following command:
    .Calculator/ut/tests


Author

Basalaev Daniil Alexsandrovich 5030102/10201 (basalaev.da@edu.spbstu.ru)

Enjoy using the Calculator project for your mathematical computations!
