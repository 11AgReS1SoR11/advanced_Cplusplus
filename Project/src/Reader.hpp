#pragma once

#include <string>
#include <vector>

struct Reader
{
    static std::vector<std::pair<std::string, std::string>> takeData(const std::string& path);

    static void deleteLastSpaces(std::string& str) noexcept;
};