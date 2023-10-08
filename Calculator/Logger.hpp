#pragma once

#include <iostream>
#include <string>

class Logger
{
private:
    Logger() = default;
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    static Logger& getInstance()
    {
        static Logger log;
        return log;
    }

    Logger& operator<<(char const* message) 
    {
        std::cout << "[LOG] " << message << std::endl;
        return *this;
    }

    Logger& operator<<(const std::string& message) 
    {
        std::cout << "[LOG] " << message << std::endl;
        return *this;
    }

    Logger& operator<<(std::string_view message) 
    {
        std::cout << "[LOG] " << message << std::endl;
        return *this;
    }
};