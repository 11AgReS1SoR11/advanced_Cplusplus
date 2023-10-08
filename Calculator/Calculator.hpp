#pragma once

#include "Parser.hpp"
#include "Sorter.hpp"
#include "Loader.hpp"

class Calculator
{
public:
    Calculator() = default;
    ~Calculator() = default;
    double operator()(std::string_view);

    Calculator(const Calculator&) = delete;
    Calculator& operator=(const Calculator&) = delete;
    Calculator(Calculator&&) = delete;
    Calculator& operator=(Calculator&&) = delete;

private:
    Parser parser;
    Sorter sorter;
    Loader loader;
};
