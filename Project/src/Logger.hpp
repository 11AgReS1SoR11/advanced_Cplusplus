#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Logger
{
private:
    std::ofstream logFile;

    Logger() 
    {
        logFile.open("log.txt");
    }

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
        logFile << "[LOG] " << message << std::endl;
        return *this;
    }

    Logger& operator<<(const std::string& message) 
    {
        logFile << "[LOG] " << message << std::endl;
        return *this;
    }

    Logger& operator<<(std::string_view message) 
    {
        logFile << "[LOG] " << message << std::endl;
        return *this;
    }

    ~Logger()
    {
        logFile.close();
    }
};