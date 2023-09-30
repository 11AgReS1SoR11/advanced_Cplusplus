#pragma once

class Calculator
{
public:
    Calculator() = default;
    ~Calculator() = default;
    double operator()(double x, double y) const;

    Calculator(const Calculator&) = delete;
    Calculator& operator=(const Calculator&) = delete;
    Calculator(Calculator&&) = delete;
    Calculator& operator=(Calculator&&) = delete;
};
