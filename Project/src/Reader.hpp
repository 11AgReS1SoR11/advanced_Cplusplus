#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Reader
{
    static std::string takeData(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open()) 
        {
            std::cout << "Failed to open the XML file" << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        // add validate
        return buffer.str();
    }
};