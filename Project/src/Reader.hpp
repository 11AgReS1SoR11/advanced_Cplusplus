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
        while (std::getline(file, token, '<')) // TODO: remove spaces
        {
            auto sep = token.find('>');
            if (sep == std::string::npos) { continue; }
            std::string name = token.substr(0, sep);

            if (name[0] == '/') { tokens.push_back(std::pair<std::string, std::string>{}); continue; } // end name -> add empty object
    
            std::string data = token.substr(sep+1);

            std::pair<std::string, std::string> XMLdata;

            // name
            if (!name.empty())
            {
                XMLdata.first = std::move(name);
            }

            // data
            if (!data.empty())
            {
                XMLdata.second = std::move(data);
            }

            tokens.push_back(std::move(XMLdata));
        }
        
        return tokens;
    }
};