#pragma once

#include <string>
#include <fstream>
#include <stdexcept>

struct Reader
{
    static std::vector<std::pair<std::string, std::string>> takeData(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open()) 
        {
            //std::cout << "Failed to open the XML file" << std::endl; // TODO: replace in logger
            throw std::runtime_error("Failed to open the XML file"); 
        }

        // TODO: validate
        
        std::vector<std::pair<std::string, std::string>> tokens;
        std::string token;
        std::getline(file, token, '<'); // get line before text
        while (std::getline(file, token, '<'))
        {
            auto sep = token.find('>');

            if (sep == std::string::npos)
            {
                throw std::runtime_error("Incorrect XML data");
            }

            std::string name = token.substr(0, sep);

            if (name[0] == '/') { tokens.push_back(std::pair<std::string, std::string>{"", ""}); continue; } // end name -> add empty object
    
            std::string data = token.substr(sep+1);

            if (name.empty() || data.empty())
            {
                throw std::runtime_error("Incorrect XML data"); 
            }

            deleteLastSpaces(name);
            deleteLastSpaces(data);

            std::pair<std::string, std::string> XMLdata{std::move(name), std::move(data)};

            tokens.push_back(std::move(XMLdata));
        }
        
        return tokens;
    }

    static void deleteLastSpaces(std::string& str) noexcept
    {
        while (!str.empty() && (str.back() == ' ' || str.back() == '\n')) 
        {
            str.pop_back();
        }
    }
};